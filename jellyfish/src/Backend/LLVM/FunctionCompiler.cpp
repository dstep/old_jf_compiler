#include <Backend/LLVM/FunctionCompiler.h>
#include <Backend/LLVM/Common.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/ADT/SmallVector.h>
#include <IR/Instr/FunctionFrame.h>
#include <Support/Match.h>
#include <llvm/IR/Intrinsics.h>

namespace jf{
	namespace backend{
		namespace llvm{
			class CodegenError: public std::runtime_error{
			public:
				CodegenError(const char* what) : std::runtime_error(what){
				}
			};

			FunctionCompiler::FunctionCompiler(MemoryPoolSlice* tempPool, LLVMContext* context, LLVMModule* module)
				: tempPool(tempPool)
				, context(context)
				, module(module)
				, valueStack(tempPool)
				, returnByRef(tempPool)
				, params(tempPool)
				, paramIndex(tempPool)
				, localVars(tempPool)
				, localVarIndex(tempPool)
				, values(tempPool)
				, valueIndex(tempPool)
				, bblocks(tempPool)
				, builder(context->getContext())
				, entryBuilder(context->getContext())
				, closures(tempPool){
			}

			void FunctionCompiler::generateMainFunction(ir::GlobalFunction* globalFunction){
				::llvm::Function* function = ::llvm::Function::Create(::llvm::FunctionType::get(::llvm::Type::getVoidTy(context->getContext()), false), ::llvm::GlobalValue::ExternalLinkage, "__jf_main", module->getModule());
				::llvm::BasicBlock* bb = ::llvm::BasicBlock::Create(context->getContext(), "entry", function);
				::llvm::IRBuilder<> builder(bb);
				builder.CreateCall(module->getDeclaration(globalFunction))->setCallingConv(::llvm::CallingConv::Fast);
				builder.CreateRetVoid();
			}

			void FunctionCompiler::captureFunctionDeclaration(::llvm::Function* function){
				this->function = function;
				argIterator = function->getArgumentList().begin();

				params.clear();
				returnByRef.clear();
				paramIndex.clear();
				localVarIndex.clear();
				localVars.clear();
				values.clear();
				valueIndex.clear();

				closureObject = nullptr;

				bblocks.clear();

				thisObject = nullptr;
			}

			void FunctionCompiler::captureThisObject(ir::Class* class_){
				thisObject = argIterator;
				argIterator++;
			}

			void FunctionCompiler::captureClosureObject(){
				closureObject = argIterator;
				argIterator++;
			}

			void FunctionCompiler::enterFunctionFrame(ir::instr::FunctionFrame* frame){
				this->frame = frame;

				entryBlock = ::llvm::BasicBlock::Create(context->getContext(), "entry", function);
				entryBuilder.SetInsertPoint(entryBlock);

				if ( closureObject ){
					::llvm::SmallVector<::llvm::Type*, 32> types;
					types.push_back(::llvm::Type::getInt8PtrTy(context->getContext()));
					frame->iterateUpValues([&](ir::instr::Instr* value, ir::instr::InstrUpValue* upValue){
							size_t count = context->convertType(upValue->type, valueStack.types);
							while ( count-- ){
								types.push_back(valueStack.types.takeLast());
							}
						});
					frame->iterateCapturedLocalVars([&](ir::instr::LocalVar* localVar, u32){
							size_t count = context->convertType(localVar->type, valueStack.types);
							while ( count-- ){
								types.push_back(valueStack.types.takeLast()->getPointerTo());
							}
						});
					::llvm::StructType* closureEnvType = ::llvm::StructType::get(context->getContext(), types);
					::llvm::Value* env = entryBuilder.CreateBitCast(closureObject, closureEnvType->getPointerTo());
					u32 envIndex = 1;
					frame->iterateUpValues([&](ir::instr::Instr* value, ir::instr::InstrUpValue* upValue){
							size_t count = context->convertType(upValue->type, valueStack.types);
							setValue(upValue->frameIndex, MakePair((u32)values.getSize(), (u32)count));
							while ( count-- ){
								::llvm::Type* type = valueStack.types.takeLast();
								if ( type->isAggregateType() ){
									values.push(entryBuilder.CreateStructGEP(env, envIndex++));
								}else{
									values.push(entryBuilder.CreateLoad(entryBuilder.CreateStructGEP(env, envIndex++)));
								}
							}
							
						});
					frame->iterateCapturedLocalVars([&](ir::instr::LocalVar* localVar, u32){
							size_t count = context->convertType(localVar->type, valueStack.types);
							localVarIndex.set(localVar, MakePair((u32)localVars.getSize(), (u32)count));
							while ( count-- ){
								::llvm::Type* type = valueStack.types.takeLast();
								localVars.push(entryBuilder.CreateLoad(entryBuilder.CreateStructGEP(env, envIndex++)));
							}							
						});
				}

				iterate_list(localVar, frame->getFirstLocalVariable()){
					size_t count = context->convertType(localVar->type, valueStack.types);

					localVarIndex.set(localVar, MakePair((u32)localVars.getSize(), (u32)count));
					
					for ( ; count; count-- ){
						localVars.push(entryBuilder.CreateAlloca(valueStack.types.takeLast()));
					}
				}

				size_t numInstr = frame->getInstrCount();
				while ( valueIndex.getSize() < numInstr ){
					valueIndex.push(MakePair((u32)0, (u32)0));
				}

				try{
					iterate_list(bb, frame->getFirstBasicBlock()){
						builder.SetInsertPoint(getBasicBlock(bb));
						iterate_list(instr, bb->getFirstInstr()){
							compileInstr(instr);
						}
						compileInstr(bb->getTerminator());
					}
				}catch(CodegenError&){
				}
			}

			::llvm::Value* FunctionCompiler::getValue(ir::instr::Instr* instr, s32 index){
				if ( index < 0 ){
					auto src = valueIndex.get(instr->frameIndex);
					return values.get(src.first + src.second + index);
				}else{
					return values.get(valueIndex.get(instr->frameIndex).first + index);
				}
			}

			void FunctionCompiler::compileCoercion(u32 frameIndex, ir::instr::Coercion* coercion, Pair<u32, u32> src){
				using namespace ir::instr;
				size_t beginIndex = values.getSize();

				if ( coercion ){
					match(coercion)
						rule(CoercionConstInt, coercion)
							values.push(builder.getInt32(coercion->value));
						erule
						rule(CoercionConstFloat, coercion)
							values.push(::llvm::ConstantFP::get(::llvm::Type::getFloatTy(context->getContext()), coercion->value));
						erule
						rule(CoercionConstDouble, coercion)
							values.push(::llvm::ConstantFP::get(::llvm::Type::getDoubleTy(context->getContext()), coercion->value));
						erule
						rule(CoercionIntToDouble, coercion)
							values.push(builder.CreateSIToFP(values.get(src.first), builder.getDoubleTy()));
						erule
						rule(CoercionFloatToDouble, coercion)
							values.push(builder.CreateFPExt(values.get(src.first), builder.getDoubleTy()));
						erule
						rule(CoercionConstString, coercion)
							size_t length = coercion->value->value.getLength();
							if ( length <= 15 ){
								uint8_t string[16];
								::memset(string, 0, 16);
								string[0] = (uint8_t)length;								
								::memcpy(string + 1, coercion->value->value.getData(), length);
								::llvm::Constant* value = ::llvm::ConstantDataArray::getString(context->getContext(), ::llvm::StringRef((char*)string, 16), false);
								::llvm::Constant* stringConstant = 
									new ::llvm::GlobalVariable
										(
											*module->getModule(), 
											context->getSmallStringType(), 
											true, 
											::llvm::GlobalValue::InternalLinkage,
											value
										);
								values.push(stringConstant);
							}else{
								::llvm::Constant* value = ::llvm::ConstantDataArray::getString(context->getContext(), toLLVM(coercion->value->value), false);
								::llvm::Constant* constant = new ::llvm::GlobalVariable(*module->getModule(), value->getType(), true, ::llvm::GlobalValue::InternalLinkage, value);
								::llvm::Constant* stringConstant = 
									new ::llvm::GlobalVariable
										(
											*module->getModule(), 
											context->getLargeStringType(), 
											true, 
											::llvm::GlobalValue::InternalLinkage,
											::llvm::ConstantStruct::get
												(
													context->getLargeStringType(), 
													::llvm::ConstantInt::get(context->getI8Type(), 0xff),
													::llvm::UndefValue::get(context->getLargeStringType()->getContainedType(1)),
													::llvm::ConstantInt::get(context->getI32Type(), length),
													::llvm::ConstantExpr::getPtrToInt(constant, context->getI64Type()),
													nullptr
												)
										);
								values.push(builder.CreateBitCast(stringConstant, context->getSmallStringType()->getPointerTo()));
							}							
						erule
						rule(CoercionToBaseClass, coercion)
							ClassLayout* layout = context->getClassLayout(coercion->to);
							values.push(builder.CreateBitCast(values.get(src.first), layout->getObjectType()));
						erule
						rule(CoercionToClassImplemented, coercion)
							ClassLayout* layout = context->getClassLayout(coercion->from);
							values.push(module->getInterfaceImplement(layout, coercion->to));
							values.push(builder.CreateBitCast(values.get(src.first), ::llvm::Type::getInt8PtrTy(context->getContext())));
						erule
						rule(CoercionNullToMaybe, coercion)
							switch ( context->getOptionalBehavior(coercion->valueType) ){
							case OptionalBehavior::ExtraBit:{
								values.push(builder.getFalse());
								size_t count = context->convertType(coercion->valueType, valueStack.types);
								while ( count-- ){
									values.push(::llvm::UndefValue::get(valueStack.types.takeLast()));
								}
							}break;
							case OptionalBehavior::NullPointer0:{
								size_t count = context->convertType(coercion->valueType, valueStack.types);
								count--;
								values.push(::llvm::ConstantPointerNull::get(::llvm::cast<::llvm::PointerType>(valueStack.types.takeLast())));
								while ( count-- ){
									values.push(::llvm::UndefValue::get(valueStack.types.takeLast()));
								}
							}break;
							default:{
								unreachable;
							}break;
							}
						erule
						rule(CoercionWrapMaybe, coercion)							
							switch ( context->getOptionalBehavior(coercion->valueType) ){
							case OptionalBehavior::ExtraBit:{
								values.push(builder.getTrue());
								compileCoercion(frameIndex, coercion->valueCoercion, src);
								return;
							}break;
							case OptionalBehavior::NullPointer0:{
								compileCoercion(frameIndex, coercion->valueCoercion, src);
								return;
							}break;
							default:{
								unreachable;
							}break;
							}
						erule
						rule(CoercionId, coercion)
							valueIndex.set(frameIndex, src);
							return;
						erule
						defrule(_)
							assert(false);
						erule
					ematch
				}else{
					cancelCompilation("no coercion");
				}

				setValue(frameIndex, MakePair((u32)beginIndex, (u32)(values.getSize() - beginIndex)));
			}

			void FunctionCompiler::compileReturn(u32 frameIndex, Pair<u32, u32> src){
				size_t beginIndex = values.getSize();

				::llvm::Value* returnWithInstr = nullptr;
				iterate_enumerable(dest, returnByRef){
					size_t i = dest.getIndex();
					if ( dest.get() == nullptr ){
						returnWithInstr = values.get(src.first + i);
					}else{
						move(dest.get(), values.get(src.first + i));
					}
				}
				if ( returnWithInstr ){
					builder.CreateRet(returnWithInstr);
				}else{
					builder.CreateRetVoid();
				}

				setValue(frameIndex, MakePair((u32)beginIndex, (u32)(values.getSize() - beginIndex)));
			}

			void FunctionCompiler::setValue(u32 frameIndex, Pair<u32, u32> src){
				while ( valueIndex.getSize() <= frameIndex ){
					valueIndex.push(src);
				}
				valueIndex.set(frameIndex, src);
			}

			void FunctionCompiler::compileInstr(ir::instr::Instr* instr){
				using namespace ir::instr;

				size_t beginIndex = values.getSize();

				match(instr)
					rule(InstrConstTrue, instr)
						values.push(::llvm::ConstantInt::getTrue(::llvm::Type::getInt1Ty(context->getContext())));
					erule
					rule(InstrReturn, instr)
						compileReturn(instr->frameIndex, valueIndex.get(instr->value->frameIndex));
						return;
					erule
					rule(InstrThisParam, instr)
						values.push(thisObject);
					erule
					rule(InstrConstUnit, instr)
					erule
					rule(InstrConstFalse, instr)
						values.push(::llvm::ConstantInt::getFalse(::llvm::Type::getInt1Ty(context->getContext())));
					erule
					rule(InstrWriteLocal, instr)
						auto dest = localVarIndex.get(instr->localVar);
						auto src = valueIndex.get(instr->value->frameIndex);
						for ( size_t i = 0; i < dest.second; i++ ){
							move(localVars.get(dest.first + i), values.get(src.first + i));
						}
					erule
					rule(InstrReadLocal, instr)
						auto src = localVarIndex.get(instr->localVar);
						for ( size_t i = 0; i < src.second; i++ ){
							::llvm::Value* value = localVars.get(src.first + i);
							if ( value->getType()->getContainedType(0)->isAggregateType() ){
								values.push(value);
							}else{
								values.push(builder.CreateLoad(value));
							}
						}
					erule
					rule(InstrUncondBranch, instr)
						builder.CreateBr(getBasicBlock(instr->bb));
					erule
					rule(InstrParam, instr)
						auto src = paramIndex.get(instr->param);
						for ( size_t i = 0; i < src.second; i++ ){
							::llvm::Value* value = params.get(src.first + i);
							values.push(value);
						}
					erule
					rule(InstrCoercion, instr)
						compileCoercion(instr->frameIndex, instr->coercion, valueIndex.get(instr->value->frameIndex));
						return;
					erule
					rule(InstrIndexClassField, instr)
						ClassLayout* layout = context->getClassLayout(instr->field->getOwner());
						::llvm::Value* object = getValue(instr->object);
						auto field = layout->getFieldIndex(instr->field);
						if ( object->getType() != field.first->getObjectType() ){
							object = builder.CreateBitCast(object, field.first->getObjectType());
						}
						for ( u32 i = 0; i < field.second.second; i++ ){
							::llvm::Value* fieldValue = builder.CreateStructGEP(object, field.second.first + i);
							if ( !fieldValue->getType()->getContainedType(0)->isAggregateType() ){
								fieldValue = builder.CreateLoad(fieldValue);
							}
							values.push(fieldValue);
						}
					erule
					rule(InstrWriteClassField, instr)
						ClassLayout* layout = context->getClassLayout(instr->field->getOwner());
						::llvm::Value* object = getValue(instr->object);
						auto field = layout->getFieldIndex(instr->field);
						if ( object->getType() != field.first->getObjectType() ){
							object = builder.CreateBitCast(object, field.first->getObjectType());
						}
						auto src = valueIndex.get(instr->value->frameIndex);
						for ( u32 i = 0; i < field.second.second; i++ ){
							::llvm::Value* fieldValue = builder.CreateStructGEP(object, field.second.first + i);
							move(fieldValue, values.get(src.first + i));
						}
					erule
					rule(InstrFinalizeConstructor, instr)
						ClassLayout* layout = context->getClassLayout(instr->class_);
						::llvm::Value* classTable = module->getClassTable(instr->class_);
						builder.CreateStore(classTable, builder.CreateBitCast(getValue(instr->object), classTable->getType()->getPointerTo()));
					erule
					rule(InstrCallInterfaceMethod, instr)
						args.clear();
						InterfaceLayout* layout = context->getInterfaceLayout(instr->method->getOwner());
						::llvm::Value* object = getValue(instr->object, 1);
						auto method = layout->getMethodIndex(instr->method);
						::llvm::Value* interfaceTable = getValue(instr->object, 0);
						::llvm::Value* callee = builder.CreateLoad(builder.CreateStructGEP(interfaceTable, method));
						
						size_t count = context->convertType(tempPool, instr->method->getSignature()->getReturnType(), valueStack.types);
						captureReturnValues(args, count, valueStack.types);
						args.push_back(object);

						for ( size_t i = 0; i < instr->argsCount; i++ ){
							auto src = valueIndex.get(instr->args[i]->frameIndex);
							for ( size_t j = 0; j < src.second; j++ ){
								args.push_back(values.get(src.first + j));
							}
						}

						::llvm::CallInst* callResult = builder.CreateCall(callee, args);
						callResult->setCallingConv(::llvm::CallingConv::Fast);
						readReturnValues(callResult, args, beginIndex);
					erule
					rule(InstrCallClassMethod, instr)
						args.clear();
						ClassLayout* layout = context->getClassLayout(instr->method->getOwner());
						::llvm::Value* object = getValue(instr->object);
						auto method = layout->getMethodIndex(instr->method);
						::llvm::Type* calleeTableType = method.first->getClassType();
						::llvm::Value* classTable = builder.CreateLoad(builder.CreateBitCast(object, calleeTableType->getPointerTo()));
						::llvm::Value* callee = builder.CreateLoad(builder.CreateStructGEP(classTable, method.second));
						if ( object->getType() != method.first->getObjectType() ){
							object = builder.CreateBitCast(object, method.first->getObjectType());
						}

						size_t count = context->convertType(tempPool, instr->method->getSignature()->getReturnType(), valueStack.types);
						captureReturnValues(args, count, valueStack.types);
						args.push_back(object);

						for ( size_t i = 0; i < instr->argsCount; i++ ){
							auto src = valueIndex.get(instr->args[i]->frameIndex);
							for ( size_t j = 0; j < src.second; j++ ){
								args.push_back(values.get(src.first + j));
							}
						}

						::llvm::CallInst* callResult = builder.CreateCall(callee, args);
						callResult->setCallingConv(::llvm::CallingConv::Fast);
						readReturnValues(callResult, args, beginIndex);
					erule
					rule(InstrCallGlobal, instr)
						args.clear();
						::llvm::Function* callee = module->getDeclaration(instr->function);

						size_t count = context->convertType(tempPool, instr->function->getSignature()->getReturnType(), valueStack.types);
						captureReturnValues(args, count, valueStack.types);

						for ( size_t i = 0; i < instr->argsCount; i++ ){
							auto src = valueIndex.get(instr->args[i]->frameIndex);
							for ( size_t j = 0; j < src.second; j++ ){
								args.push_back(values.get(src.first + j));
							}
						}
						::llvm::CallInst* callResult = builder.CreateCall(callee, args);
						callResult->setCallingConv(::llvm::CallingConv::Fast);
						readReturnValues(callResult, args, beginIndex);					
					erule
					rule(InstrCallBuiltinFunction, instr)
						switch ( instr->function->id ){
						case BuiltinFunction::ID::Negate:{
							switch ( instr->typeArgs.get(0)->getRepr()->tag ){
							case TypeIntTag: values.push(builder.CreateNeg(getValue(instr->args[0]))); break;
							case TypeFloatTag:
							case TypeDoubleTag: values.push(builder.CreateFNeg(getValue(instr->args[0]))); break;
							default: unreachable;
							}
						}break;
						case BuiltinFunction::ID::Plus:{
							switch ( instr->typeArgs.get(0)->getRepr()->tag ){
							case TypeIntTag: values.push(builder.CreateAdd(getValue(instr->args[0]), getValue(instr->args[1]))); break;
							case TypeFloatTag:
							case TypeDoubleTag: values.push(builder.CreateFAdd(getValue(instr->args[0]), getValue(instr->args[1]))); break;
							default: unreachable;
							}
						}break;
						case BuiltinFunction::ID::Remainder:{
							switch ( instr->typeArgs.get(0)->getRepr()->tag ){
							case TypeIntTag: values.push(builder.CreateSRem(getValue(instr->args[0]), getValue(instr->args[1]))); break;
							case TypeFloatTag:
							case TypeDoubleTag: values.push(builder.CreateFRem(getValue(instr->args[0]), getValue(instr->args[1]))); break;
							default: unreachable;
							}
						}break;
						case BuiltinFunction::ID::Minus:{
							switch ( instr->typeArgs.get(0)->getRepr()->tag ){
							case TypeIntTag: values.push(builder.CreateSub(getValue(instr->args[0]), getValue(instr->args[1]))); break;
							case TypeFloatTag:
							case TypeDoubleTag: values.push(builder.CreateFSub(getValue(instr->args[0]), getValue(instr->args[1]))); break;
							default: unreachable;
							}
						}break;
						case BuiltinFunction::ID::Divide:{
							switch ( instr->typeArgs.get(0)->getRepr()->tag ){
							case TypeIntTag: values.push(builder.CreateSDiv(getValue(instr->args[0]), getValue(instr->args[1]))); break;
							case TypeFloatTag:
							case TypeDoubleTag: values.push(builder.CreateFDiv(getValue(instr->args[0]), getValue(instr->args[1]))); break;
							default: unreachable;
							}
						}break;
						case BuiltinFunction::ID::Multiply:{
							switch ( instr->typeArgs.get(0)->getRepr()->tag ){
							case TypeIntTag: values.push(builder.CreateMul(getValue(instr->args[0]), getValue(instr->args[1]))); break;
							case TypeFloatTag:
							case TypeDoubleTag: values.push(builder.CreateFMul(getValue(instr->args[0]), getValue(instr->args[1]))); break;
							default: unreachable;
							}
						}break;
						case BuiltinFunction::ID::Sqrt:{
							switch ( instr->typeArgs.get(0)->getRepr()->tag ){
							case TypeFloatTag: values.push(builder.CreateCall(module->getIntrinsic(Intrinsic::FloatSqrt), getValue(instr->args[0]))); break;
							case TypeDoubleTag: values.push(builder.CreateCall(module->getIntrinsic(Intrinsic::DoubleSqrt), getValue(instr->args[0]))); break;
							default: unreachable;
							}
						}break;

						case BuiltinFunction::ID::Concat:{
							::llvm::Value* result = makeTemporary(context->getSmallStringType());
							builder.CreateCall3(module->getIntrinsic(Intrinsic::StringConcat), result, getValue(instr->args[0]), getValue(instr->args[1]));
							values.push(result);
						}break;

						case BuiltinFunction::ID::EmptyArray:{
							::llvm::StructType* structType = context->getTypeAsStruct(instr->typeArgs.get(0)->getRepr());
							::llvm::Constant* valueSize = context->getSizeOf(structType);
							//TODO::
							values.push(builder.CreateCall2(module->getIntrinsic(Intrinsic::EmptyArray), valueSize, ::llvm::ConstantPointerNull::get(builder.getInt8PtrTy())));
						}break;

						case BuiltinFunction::ID::ArrayPush:{
							::llvm::StructType* structType = context->getTypeAsStruct(instr->typeArgs.get(0)->getRepr());
							::llvm::Value* space = builder.CreateCall(module->getIntrinsic(Intrinsic::ArrayPush), getValue(instr->object));
							::llvm::Value* dest = builder.CreateBitCast(space, structType->getPointerTo());
							auto src = valueIndex.get(instr->args[0]->frameIndex);
							for ( size_t i = 0; i < src.second; i++ ){
								move(builder.CreateStructGEP(dest, i), values.get(src.first + i));
							}
						}break;
						case BuiltinFunction::ID::ArrayPop:{
							builder.CreateCall(module->getIntrinsic(Intrinsic::ArrayPop), getValue(instr->object));
						}break;
						case BuiltinFunction::ID::ArrayClear:{
							builder.CreateCall(module->getIntrinsic(Intrinsic::ArrayClear), getValue(instr->object));
						}break;
						case BuiltinFunction::ID::ArraySize:{
							values.push(builder.CreateCall(module->getIntrinsic(Intrinsic::ArraySize), getValue(instr->object)));
						}break;
						
						case BuiltinFunction::ID::ArrayGet:{
							::llvm::StructType* structType = context->getTypeAsStruct(instr->typeArgs.get(0)->getRepr());
							::llvm::Value* space = builder.CreateCall2(module->getIntrinsic(Intrinsic::ArrayRef), getValue(instr->object), getValue(instr->args[0]));
							::llvm::Value* src = builder.CreateBitCast(space, structType->getPointerTo());
							for ( size_t i = 0; i < structType->getStructNumElements(); i++ ){
								if ( structType->getElementType(i)->isAggregateType() ){
									::llvm::Value* copy = makeTemporary(structType->getElementType(i));
									move(copy, builder.CreateStructGEP(src, i));
									values.push(copy);
								}else{
									values.push(builder.CreateLoad(builder.CreateStructGEP(src, i)));
								}
							}
						}break;
						case BuiltinFunction::ID::ArraySet:{
							::llvm::StructType* structType = context->getTypeAsStruct(instr->typeArgs.get(0)->getRepr());
							::llvm::Value* space = builder.CreateCall2(module->getIntrinsic(Intrinsic::ArrayRef), getValue(instr->object), getValue(instr->args[0]));
							::llvm::Value* dest = builder.CreateBitCast(space, structType->getPointerTo());
							auto src = valueIndex.get(instr->args[1]->frameIndex);
							for ( size_t i = 0; i < structType->getStructNumElements(); i++ ){
								move(builder.CreateStructGEP(dest, i), values.get(src.first + i));
							}
						}break;

						case BuiltinFunction::ID::AllocateBytes:{
							values.push(getValue(instr->args[0]));
							values.push(builder.CreateCall(module->getIntrinsic(Intrinsic::AllocateBytes), getValue(instr->args[0])));
						}break;

						case BuiltinFunction::ID::BytesWriteFloat:{
							builder.CreateCall4(module->getIntrinsic(Intrinsic::BytesWriteFloat), getValue(instr->object, 0), getValue(instr->object, 1), getValue(instr->args[0]), getValue(instr->args[1]));
						}break;
						case BuiltinFunction::ID::BytesWriteU16:{
							builder.CreateCall4(module->getIntrinsic(Intrinsic::BytesWriteU16), getValue(instr->object, 0), getValue(instr->object, 1), getValue(instr->args[0]), getValue(instr->args[1]));
						}break;

						default:{
							unreachable;
						}break;
						}
						/*switch ( instr->id ){
						case BuiltinFunction::Later:{
							cancelCompilation("builtin not resolved");
						}break;

						case BuiltinFunction::ConcatString: values.push(builder.CreateCall2(module->getIntrinsic(Intrinsic::StringConcat), getValue(instr->args[0]), getValue(instr->args[1]))); break;
						
						case BuiltinFunction::PlusInt: values.push(builder.CreateAdd(getValue(instr->args[0]), getValue(instr->args[1]))); break;
						case BuiltinFunction::PlusFloat: 
						case BuiltinFunction::PlusDouble: values.push(builder.CreateFAdd(getValue(instr->args[0]), getValue(instr->args[1]))); break;
						
						case BuiltinFunction::RoundFloat: values.push(builder.CreateCall(module->getIntrinsic(Intrinsic::FloatRound), getValue(instr->args[1]))); break;
						case BuiltinFunction::RoundDouble: values.push(builder.CreateCall(module->getIntrinsic(Intrinsic::DoubleRound), getValue(instr->args[0]))); break;

						case BuiltinFunction::FloorFloat: values.push(builder.CreateCall(module->getIntrinsic(Intrinsic::FloatRound), getValue(instr->args[0]))); break;
						case BuiltinFunction::FloorDouble: values.push(builder.CreateCall(module->getIntrinsic(Intrinsic::DoubleRound), getValue(instr->args[0]))); break;

						case BuiltinFunction::CeilFloat: values.push(builder.CreateCall(module->getIntrinsic(Intrinsic::FloatRound), getValue(instr->args[0]))); break;
						case BuiltinFunction::CeilDouble: values.push(builder.CreateCall(module->getIntrinsic(Intrinsic::DoubleRound), getValue(instr->args[0]))); break;

						case BuiltinFunction::NearbyIntFromDouble: values.push(builder.CreateCall(module->getIntrinsic(Intrinsic::DoubleNearbyInt), getValue(instr->args[0]))); break;
						case BuiltinFunction::NearbyFloatFromDouble: values.push(builder.CreateCall(module->getIntrinsic(Intrinsic::DoubleNearbyFloat), getValue(instr->args[0]))); break;
						case BuiltinFunction::NearbyIntFromFloat: values.push(builder.CreateCall(module->getIntrinsic(Intrinsic::FloatNearbyInt), getValue(instr->args[0]))); break;
						case BuiltinFunction::NearbyFloatFromInt: values.push(builder.CreateCall(module->getIntrinsic(Intrinsic::IntNearbyFloat), getValue(instr->args[0]))); break;

						default: assert(false);
						}*/
					erule
					rule(InstrCompare, instr)
						if ( instr->compareClass ){
							match(instr->compareClass)
								rule(CompareUndef, compareClass)
									values.push(builder.getFalse());
								erule
								rule(CompareNumeric, compareClass)
									switch ( compareClass->type->getRepr()->tag ){
									case TypeIntTag:
										switch ( instr->op ){
										case InstrCompare::EQ: values.push(builder.CreateICmpEQ(getValue(instr->lhs), getValue(instr->rhs))); break;
										case InstrCompare::NE: values.push(builder.CreateICmpNE(getValue(instr->lhs), getValue(instr->rhs))); break;
										case InstrCompare::LE: values.push(builder.CreateICmpSLE(getValue(instr->lhs), getValue(instr->rhs))); break;
										case InstrCompare::GE: values.push(builder.CreateICmpSGE(getValue(instr->lhs), getValue(instr->rhs))); break;
										case InstrCompare::LT: values.push(builder.CreateICmpSLT(getValue(instr->lhs), getValue(instr->rhs))); break;
										case InstrCompare::GT: values.push(builder.CreateICmpSGT(getValue(instr->lhs), getValue(instr->rhs))); break;
										default: unreachable;
										}
									break;
									case TypeFloatTag:
									case TypeDoubleTag:
										switch ( instr->op ){
										case InstrCompare::EQ: values.push(builder.CreateFCmpOEQ(getValue(instr->lhs), getValue(instr->rhs))); break;
										case InstrCompare::NE: values.push(builder.CreateFCmpONE(getValue(instr->lhs), getValue(instr->rhs))); break;
										case InstrCompare::LE: values.push(builder.CreateFCmpOLE(getValue(instr->lhs), getValue(instr->rhs))); break;
										case InstrCompare::GE: values.push(builder.CreateFCmpOGE(getValue(instr->lhs), getValue(instr->rhs))); break;
										case InstrCompare::LT: values.push(builder.CreateFCmpOLT(getValue(instr->lhs), getValue(instr->rhs))); break;
										case InstrCompare::GT: values.push(builder.CreateFCmpOGT(getValue(instr->lhs), getValue(instr->rhs))); break;
										default: unreachable;
										}
									break;
									}
								erule
								rule(CompareString, compareClass)
									switch ( instr->op ){
									case InstrCompare::EQ:
									case InstrCompare::NE:{
										::llvm::Value* value = builder.CreateCall2(module->getIntrinsic(Intrinsic::StringEqual), getValue(instr->lhs), getValue(instr->rhs));
										if ( instr->op == InstrCompare::NE ){
											value = builder.CreateNot(value);
										}
										values.push(value);
									}break;
									default:{
										::llvm::Value* value = builder.CreateCall2(module->getIntrinsic(Intrinsic::StringCompare), getValue(instr->lhs), getValue(instr->rhs));
										switch ( instr->op ){
										case InstrCompare::LE: values.push(builder.CreateICmpSLE(value, builder.getInt32(0))); break;
										case InstrCompare::GE: values.push(builder.CreateICmpSGE(value, builder.getInt32(0))); break;
										case InstrCompare::LT: values.push(builder.CreateICmpSLT(value, builder.getInt32(0))); break;
										case InstrCompare::GT: values.push(builder.CreateICmpSGT(value, builder.getInt32(0))); break;
										default: unreachable;
										}
									}break;
									}
								erule
								defrule(_)
									assert(false);
								erule
							ematch
						}else{
							assert(false);
						}
					erule
					rule(InstrCondBranch, instr)
						builder.CreateCondBr(getValue(instr->condition), getBasicBlock(instr->bbTrue), getBasicBlock(instr->bbFalse));
					erule
					rule(InstrUnwrapMaybe, instr)
						auto src = valueIndex.get(instr->value->frameIndex);
						switch ( context->getOptionalBehavior(instr->valueType) ){
						case OptionalBehavior::ExtraBit:{
							valueIndex.set(instr->frameIndex, MakePair(src.first + 1, src.second - 1));
							return;
						}break;
						case OptionalBehavior::NullPointer0:{
							valueIndex.set(instr->frameIndex, src);
							return;
						}break;
						default:{
							unreachable;
						}break;
						}
					erule
					rule(InstrBadCode, instr)
						builder.CreateUnreachable();
						builder.ClearInsertionPoint();
					erule
					rule(InstrBrMaybe, instr)
						::llvm::BasicBlock* bbNull = getBasicBlock(instr->bbNull);
						::llvm::BasicBlock* bbValue = getBasicBlock(instr->bbValue);
						switch ( context->getOptionalBehavior(instr->valueType) ){
						case OptionalBehavior::ExtraBit:{
							builder.CreateCondBr(getValue(instr->value, 0), bbValue, bbNull);
						}break;
						case OptionalBehavior::NullPointer0:{
							::llvm::Value* value = getValue(instr->value);
							builder.CreateCondBr(builder.CreateICmpNE(value, ::llvm::ConstantPointerNull::get(::llvm::cast<::llvm::PointerType>(value->getType()))), bbValue, bbNull);
						}break;
						default:{
							unreachable;
						}break;
						}
					erule
					rule(InstrContinueConstructor, instr)
						::llvm::Value* object = thisObject;
						::llvm::Value* recordValue = constructorStack;
						::llvm::Value* callbackValue = constructorCallback;

						if ( instr->closureFrame ){
							Closure closure;
							closure.frame = instr->closureFrame;
							::llvm::FunctionType* fTy = ::llvm::FunctionType::get(::llvm::Type::getVoidTy(context->getContext()), ::llvm::Type::getInt8PtrTy(context->getContext()), false);
							closure.function = ::llvm::Function::Create(fTy, ::llvm::GlobalValue::InternalLinkage, "", module->getModule());
							closure.function->setCallingConv(::llvm::CallingConv::Fast);
							closure.signature = nullptr;
							closures.push(closure);

							::llvm::Value* env = makeClosureRecord(closure.frame);
							::llvm::StructType* callbackType = ::llvm::StructType::get
								(
									::llvm::Type::getInt8PtrTy(context->getContext()),
									fTy->getPointerTo(),
									env->getType(),
									nullptr
								);
							::llvm::Value* newCallbackValue = makeTemporary(callbackType);
							builder.CreateStore(callbackValue, builder.CreateStructGEP(newCallbackValue, 0));
							builder.CreateStore(closure.function, builder.CreateStructGEP(newCallbackValue, 1));
							builder.CreateStore(env, builder.CreateStructGEP(newCallbackValue, 2));
							callbackValue = builder.CreateBitCast(newCallbackValue, ::llvm::Type::getInt8PtrTy(context->getContext()));
						}

						if ( instr->constructorRecord ){
							iterate_list(record, instr->constructorRecord){
								if ( record->next ){
									recordValue = pushConstructorRecord(recordValue, record);
								}else{
									::llvm::Function* constructorFunction = module->getDeclaration(record->constructor);

									args.clear();
									args.push_back(recordValue);
									args.push_back(callbackValue);
									args.push_back(builder.CreateBitCast(object, constructorFunction->getFunctionType()->getContainedType(3)));
							
									pushRecordArgs(record);

									builder.CreateCall(constructorFunction, args);	
									args.clear();						
								}
							}
						}else if ( !instr->leaf ){
							::llvm::Type* params[] = {
									::llvm::Type::getInt8PtrTy(context->getContext()), //closure record
									::llvm::Type::getInt8PtrTy(context->getContext()), //up-calls stack
									object->getType() //object
								};
							::llvm::FunctionType* funType = ::llvm::FunctionType::get
								(
									::llvm::Type::getVoidTy(context->getContext()), 
									params,
									false
								);
							::llvm::StructType* consClosureType = ::llvm::StructType::get
								(
									::llvm::Type::getInt8PtrTy(context->getContext()), //next record
									funType->getPointerTo(), //function
									nullptr
								);
							::llvm::Value* castedRecordClosure = builder.CreateBitCast(recordValue, consClosureType->getPointerTo());
							::llvm::Value* closureCallee = builder.CreateLoad(builder.CreateStructGEP(castedRecordClosure, 1));
							::llvm::Value* args[] = {recordValue, callbackValue, object};
							builder.CreateCall(closureCallee, args)->setCallingConv(::llvm::CallingConv::Fast);
						}else{
							builder.CreateCall2(module->getIntrinsic(Intrinsic::UnwindConstructorCallback), callbackValue, builder.CreateBitCast(object, builder.getInt8PtrTy()));
						}
					erule
					rule(InstrNewObject, instr)
						ClassLayout* layout = context->getClassLayout(instr->class_);
						::llvm::Value* object = builder.CreateBitCast(builder.CreateCall(module->getIntrinsic(Intrinsic::AllocateObject), layout->getSize()), layout->getObjectType());
						::llvm::Value* recordValue = ::llvm::ConstantPointerNull::get(builder.getInt8PtrTy());
						iterate_list(record, instr->constructorRecord){
							if ( record->next ){
								recordValue = pushConstructorRecord(recordValue, record);
							}else{								
								args.clear();
								args.push_back(recordValue);
								args.push_back(::llvm::ConstantPointerNull::get(builder.getInt8PtrTy()));
								args.push_back(object);
							
								pushRecordArgs(record);

								builder.CreateCall(module->getDeclaration(record->constructor), args);	
								args.clear();						
							}
						}						
						values.push(object);
					erule
					defrule(_)
						unreachable;
					erule
				ematch

				setValue(instr->frameIndex, MakePair((u32)beginIndex, (u32)(values.getSize() - beginIndex)));
			}

			void FunctionCompiler::pushRecordArgs(ir::instr::ConstructorRecord* record){
				for ( size_t i = 0; i < record->argsCount; i++ ){
					auto src = valueIndex.get(record->args[i]->frameIndex);
					for ( size_t j = 0; j < src.second; j++ ){
						args.push_back(values.get(src.first + j));
					}
				}
			}

			::llvm::Value* FunctionCompiler::makeClosureRecord(ir::instr::FunctionFrame* frame){
				::llvm::SmallVector<::llvm::Type*, 32> types;
				types.push_back(::llvm::Type::getInt8PtrTy(context->getContext()));
				frame->iterateUpValues([&](ir::instr::Instr* value, ir::instr::InstrUpValue* upValue){
						size_t count = context->convertType(upValue->type, valueStack.types);
						while ( count-- ){
							types.push_back(valueStack.types.takeLast());
						}
					});
				frame->iterateCapturedLocalVars([&](ir::instr::LocalVar* localVar, u32){
						size_t count = context->convertType(localVar->type, valueStack.types);
						while ( count-- ){
							types.push_back(valueStack.types.takeLast()->getPointerTo());
						}
					});
				::llvm::StructType* closureEnvType = ::llvm::StructType::get(context->getContext(), types);
				::llvm::Value* env = makeTemporary(closureEnvType);
				u32 envIndex = 1;
				frame->iterateUpValues([&](ir::instr::Instr* value, ir::instr::InstrUpValue* upValue){
						auto src = valueIndex.get(value->frameIndex);
						for ( u32 i = 0; i < src.second; i++ ){
							move(builder.CreateStructGEP(env, envIndex++), values.get(src.first + i));
						}
					});
				frame->iterateCapturedLocalVars([&](ir::instr::LocalVar* localVar, u32){
						auto src = localVarIndex.get(localVar);
						for ( u32 i = 0; i < src.second; i++ ){
							builder.CreateStore(builder.CreateStructGEP(env, envIndex++), localVars.get(src.first + i));
						}
					});
				return env;
			}

			::llvm::Value* FunctionCompiler::pushConstructorRecord(::llvm::Value* prev, ir::instr::ConstructorRecord* record){
				args.clear();
				args.push_back(prev);				
				args.push_back(module->getClosureDeclaration(record->constructor));	
				pushRecordArgs(record);			
				
				argsTypes.clear();
				for ( auto& arg : args ){
					argsTypes.push_back(arg->getType());
				}
				::llvm::StructType* recordType = ::llvm::StructType::get(context->getContext(), argsTypes);
				::llvm::Value* nextRecordValue = makeTemporary(recordType);
				for ( size_t i = 0; i < args.size(); i++ ){
					builder.CreateStore(args[i], builder.CreateStructGEP(nextRecordValue, i));
				}
				return builder.CreateBitCast(nextRecordValue, builder.getInt8PtrTy());				
			}

			void FunctionCompiler::captureConstructorStack(){
				constructorStack = argIterator++;
				constructorCallback = argIterator++;
			}

			void FunctionCompiler::captureReturnValues(::llvm::SmallVector<::llvm::Value*, 64>& args, size_t count, ArrayList<::llvm::Type*>& types){
				bool returnByVal = false;
				for ( ; count; count-- ){
					::llvm::Type* type = types.takeLast();
					if ( type->isAggregateType() || returnByVal ){
						::llvm::Value* tmp = makeTemporary(type);
						values.push(tmp);
						args.push_back(tmp);
					}else{
						values.push(nullptr);
						returnByVal = true;
					}
				}
			}

			::llvm::Value* FunctionCompiler::makeTemporary(::llvm::Type* type){
				return entryBuilder.CreateAlloca(type);
			}

			void FunctionCompiler::readReturnValues(::llvm::Value* returnValue, ::llvm::SmallVector<::llvm::Value*, 64>& args, size_t beginIndex){
				size_t n = values.getSize();
				size_t j = 0;
				for ( size_t i = beginIndex; i < n; i++ ){
					if ( !values.get(i) ){
						values.set(i, returnValue);
					}else{
						values.set(i, read(args[j++]));
					}
				}
			}

			::llvm::Value* FunctionCompiler::read(::llvm::Value* value){
				if ( value->getType()->isAggregateType() ){
					return value;
				}else{
					return builder.CreateLoad(value);
				}
			}

			::llvm::BasicBlock* FunctionCompiler::getBasicBlock(ir::instr::BasicBlock* bb){
				::llvm::BasicBlock*& block = bblocks.getOrInsert(bb);
				if ( !block ){
					block = ::llvm::BasicBlock::Create(context->getContext(), "", function);
				}
				return block;
			}

			void FunctionCompiler::move(::llvm::Value* dest, ::llvm::Value* src){
				if ( src->getType()->getPointerTo() == dest->getType() ){
					builder.CreateStore(src, dest);
				}else if ( src->getType() == dest->getType() ){
					builder.CreateStore(builder.CreateLoad(src), dest);
				}else{
					assert(false);
				}
			}

			void FunctionCompiler::leaveFunctionFrame(){
				entryBuilder.CreateBr(getBasicBlock(frame->getEntry()));

				if ( closures.getSize() > 0 ){
					Closure closure = closures.takeLast();
					ir::FunctionSignature* signature = closure.signature;
					captureFunctionDeclaration(closure.function);
					if ( signature ){
						captureReturnValue(signature->getReturnType());
						captureClosureObject();
						iterate_array(param, signature->getParams()){
							captureParam(&param.get());
						}
					}else{
						captureClosureObject();
					}
					enterFunctionFrame(closure.frame);
					leaveFunctionFrame();
				}
			}

			void FunctionCompiler::captureReturnValue(const ir::Type& type){
				size_t count = context->convertType(tempPool, type, valueStack.types);
				if ( !function->getReturnType()->isVoidTy() ){
					count--;
					returnByRef.push(nullptr);
					valueStack.types.pop();
				}
				for ( ; count; count-- ){
					returnByRef.push(argIterator);
					argIterator++;
					valueStack.types.pop();
				}
			}

			void FunctionCompiler::captureParam(ir::Param* param){
				size_t count = context->convertType(tempPool, param->getType(), valueStack.types);
				paramIndex.set(param, MakePair((u32)params.getSize(), (u32)count));
				for ( ; count; count-- ){
					params.push(argIterator);
					argIterator++;
					valueStack.types.pop();
				}
			}

			void FunctionCompiler::makeConstructorCallFromClosure(ir::ClassConstructor* constructor){
				::llvm::SmallVector<::llvm::Type*, 32> types;
				::llvm::SmallVector<::llvm::Value*, 32> args;
				auto callee = module->getDeclaration(constructor);
				types.push_back(::llvm::Type::getInt8PtrTy(context->getContext())); //prev record
				types.push_back(::llvm::Type::getInt8PtrTy(context->getContext())); //function (== this->function)
				size_t skipArgs = 3;

				for ( auto& param : function->args() ){
					args.push_back(&param);
				}

				for ( auto& param : callee->args() ){
					if ( skipArgs ){
						skipArgs--;						
					}else{
						types.push_back(param.getType());
					}
				}

				::llvm::BasicBlock* bb = ::llvm::BasicBlock::Create(context->getContext(), "", function);
				::llvm::IRBuilder<> builder(bb);

				::llvm::StructType* closureRecordType = ::llvm::StructType::get(context->getContext(), types);
				::llvm::Value* closureValue = builder.CreateBitCast(args[0], closureRecordType->getPointerTo());
				::llvm::SmallVector<::llvm::Value*, 32> values;
				values.push_back(builder.CreateLoad(builder.CreateStructGEP(closureValue, 0)));
				values.push_back(args[1]);
				values.push_back(args[2]);
				for ( size_t i = 2; i < types.size(); i++ ){
					values.push_back(builder.CreateLoad(builder.CreateStructGEP(closureValue, i)));
				}
				builder.CreateCall(callee, values)->setCallingConv(::llvm::CallingConv::Fast);
				builder.CreateRetVoid();
			}

			void FunctionCompiler::makeFFICall(const StringRef& string){
				auto ffi = module->getModule()->getOrInsertFunction(toLLVM(string), function->getFunctionType());
				::llvm::BasicBlock* bb = ::llvm::BasicBlock::Create(context->getContext(), "", function);
				::llvm::IRBuilder<> builder(bb);
				::llvm::SmallVector<::llvm::Value*, 16> args;
				for ( auto& argument : function->getArgumentList() ){
					args.push_back(&argument);
				}
				::llvm::Value* value = builder.CreateCall(ffi, args);
				if ( function->getReturnType()->isVoidTy() ){
					builder.CreateRetVoid();
				}else{
					builder.CreateRet(value);
				}
			}

			void FunctionCompiler::makeDecoratedVirtualCall(ir::FunctionSignature* base, ir::ClassMethod* method){
				entryBlock = ::llvm::BasicBlock::Create(context->getContext(), "entry", function);
				entryBuilder.SetInsertPoint(entryBlock);

				::llvm::BasicBlock* firstBB = ::llvm::BasicBlock::Create(context->getContext(), "", function);

				builder.SetInsertPoint(firstBB);
				args.clear();
				ClassLayout* layout = context->getClassLayout(method->getOwner());
				::llvm::Value* object = builder.CreateBitCast(thisObject, layout->getObjectType());
				auto methodIndex = layout->getMethodIndex(method);
				::llvm::Type* calleeTableType = methodIndex.first->getClassType();
				::llvm::Value* classTable = builder.CreateLoad(builder.CreateBitCast(object, calleeTableType->getPointerTo()));
				::llvm::Value* callee = builder.CreateLoad(builder.CreateStructGEP(classTable, methodIndex.second));
				if ( object->getType() != methodIndex.first->getObjectType() ){
					object = builder.CreateBitCast(object, methodIndex.first->getObjectType());
				}

				size_t argsCount = base->getParamsCount();
				for ( size_t i = 0; i < argsCount; i++ ){
					auto src = paramIndex.get(base->getParam(i));
					u32 startIndex = values.getSize();
					for ( size_t j = 0; j < src.second; j++ ){
						values.push(params.get(j + src.first));
					}
					compileCoercion(i, method->getOverride()->getParamCoercions()[i], MakePair(startIndex, src.second));
					
				}

			
				size_t beginIndex = values.getSize();

				size_t count = context->convertType(tempPool, method->getSignature()->getReturnType(), valueStack.types);
				captureReturnValues(args, count, valueStack.types);
				args.push_back(object);

				for ( size_t i = 0; i < argsCount; i++ ){
					auto dst = valueIndex.get(i);
					for ( size_t j = 0; j < dst.second; j++ ){
						args.push_back(values.get(dst.first + j));
					}
				}

				::llvm::CallInst* callResult = builder.CreateCall(callee, args);
				callResult->setCallingConv(::llvm::CallingConv::Fast);
				readReturnValues(callResult, args, beginIndex);

				Pair<u32, u32> result(beginIndex, values.getSize() - beginIndex);

				compileCoercion(argsCount, method->getOverride()->getRetValCoercion(), result);
				compileReturn(argsCount + 1, valueIndex.get(argsCount));

				entryBuilder.CreateBr(firstBB);
			}

			void FunctionCompiler::cancelCompilation(const char* reason){
				throw CodegenError(reason);
			}
		}
	}
}