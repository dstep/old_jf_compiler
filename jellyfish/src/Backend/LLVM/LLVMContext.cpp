#include <Backend/LLVM/LLVMContext.h>
#include <Backend/LLVM/Common.h>
#include <llvm/IR/Constants.h>
#include <Support/Macros.h>
#include <Support/Match.h>
#include <IR/Instr/Coercion.h>

namespace jf{
	namespace backend{
		namespace llvm{
			LLVMContext::LLVMContext()
				: classLayouts(this)
				, methodTypes(this)
				, typeStack(this)
				, interfaceLayouts(this)
				, imethodTypes(this)
				
				, i1Ty(nullptr)
				, i8PtrTy(nullptr)
				, i8Ty(nullptr)
				, voidTy(nullptr)
				, i32Ty(nullptr)
				, i64Ty(nullptr)
				, smallStringType(nullptr)
				, largeStringType(nullptr){
			}

			LLVMContext::~LLVMContext(){
			}

			::llvm::ArrayType* LLVMContext::getSmallStringType(){
				if ( !smallStringType ){
					smallStringType = ::llvm::ArrayType::get(getI8Type(), 16);  
				}
				return smallStringType;
			}

			::llvm::StructType* LLVMContext::getLargeStringType(){
				if ( !largeStringType ){
					largeStringType = ::llvm::StructType::get(getI8Type(), ::llvm::ArrayType::get(getI8Type(), 3), getI32Type(), getI64Type(), nullptr);
				}
				return largeStringType;
			}

			::llvm::Type* LLVMContext::getI1Type(){
				if ( !i1Ty ){
					i1Ty = ::llvm::Type::getInt1Ty(context);
				}
				return i1Ty;
			}

			::llvm::Type* LLVMContext::getI8Type(){
				if ( !i8Ty ){
					i8Ty = ::llvm::Type::getInt8Ty(context);
				}
				return i8Ty;
			}

			::llvm::Type* LLVMContext::getI32Type(){
				if ( !i32Ty ){
					i32Ty = ::llvm::Type::getInt32Ty(context);
				}
				return i32Ty;
			}

			::llvm::Type* LLVMContext::getI64Type(){
				if ( !i64Ty ){
					i64Ty = ::llvm::Type::getInt64Ty(context);
				}
				return i64Ty;
			}

			::llvm::Type* LLVMContext::getVoidType(){
				if ( !voidTy ){
					voidTy = ::llvm::Type::getVoidTy(context);
				}
				return voidTy;
			}

			size_t LLVMContext::convertType(MemoryPoolSlice* pool, const ir::Type& type, ArrayList<::llvm::Type*>& types){
				return convertType(ir::instr::BuildType(pool, type), types);
			}

			::llvm::StructType* LLVMContext::getTypeAsStruct(ir::instr::Type* type){
				size_t count = convertType(type, typeStack);
				::llvm::SmallVector<::llvm::Type*, 64> types;
				while ( count-- ){
					types.push_back(typeStack.takeLast());
				}
				return ::llvm::StructType::get(context, types);
			}

			::llvm::Constant* LLVMContext::getSizeOf(::llvm::Type* type){
				return ::llvm::ConstantExpr::getPtrToInt
					(
						::llvm::ConstantExpr::getGetElementPtr
							(
								::llvm::ConstantPointerNull::get(type->getPointerTo()),
								::llvm::ConstantInt::get(::llvm::Type::getInt32Ty(context), 1)
							),
						::llvm::Type::getInt32Ty(context)
					);
			}

			OptionalBehavior::Value LLVMContext::getOptionalBehavior(ir::instr::Type* type){
				type = type->getRepr();
				match(type)
					rule(ir::instr::TypeUnit, type)
						return OptionalBehavior::ExtraBit;
					erule
					rule(ir::instr::TypeUndef, type)
						return OptionalBehavior::ExtraBit;
					erule
					rule(ir::instr::TypeError, type)
						return OptionalBehavior::ExtraBit;
					erule
					rule(ir::instr::TypeBool, type)
						return OptionalBehavior::ExtraBit;
					erule
					rule(ir::instr::TypeString, type)
						return OptionalBehavior::ExtraBit;
					erule
					rule(ir::instr::TypeInt, type)
						return OptionalBehavior::ExtraBit;
					erule
					rule(ir::instr::TypeFloat, type)
						return OptionalBehavior::ExtraBit;
					erule
					rule(ir::instr::TypeDouble, type)
						return OptionalBehavior::ExtraBit;
					erule
					rule(ir::instr::TypeBytes, type)
						return OptionalBehavior::ExtraBit;
					erule
					rule(ir::instr::TypeClass, type)
						return OptionalBehavior::NullPointer0;
					erule
					rule(ir::instr::TypeInterface, type)
						return OptionalBehavior::NullPointer0;
					erule
					rule(ir::instr::TypeOptional, type)
						return getOptionalBehavior(type->valueType);
					erule
					defrule(_)
						unreachable;
					erule
				ematch
			}

			size_t LLVMContext::convertType(ir::instr::Type* type, ArrayList<::llvm::Type*>& types){
				type = type->getRepr();
				match(type)
					rule(ir::instr::TypeUnit, type)
						return 0;
					erule
					rule(ir::instr::TypeUndef, type)
						return 0;
					erule
					rule(ir::instr::TypeError, type)
						return 0;
					erule
					rule(ir::instr::TypeBool, type)
						types.push(::llvm::Type::getInt1Ty(context));
						return 1;
					erule
					rule(ir::instr::TypeString, type)
						types.push(getSmallStringType());
						return 1;
					erule
					rule(ir::instr::TypeInt, type)
						types.push(::llvm::Type::getInt32Ty(context));
						return 1;
					erule
					rule(ir::instr::TypeFloat, type)
						types.push(::llvm::Type::getFloatTy(context));
						return 1;
					erule
					rule(ir::instr::TypeDouble, type)
						types.push(::llvm::Type::getDoubleTy(context));
						return 1;
					erule
					rule(ir::instr::TypeBytes, type)
						types.push(::llvm::Type::getInt8PtrTy(context));
						types.push(::llvm::Type::getInt32Ty(context));
						return 2;
					erule
					rule(ir::instr::TypeClass, type)
						types.push(getClassLayout(type->class_)->getObjectType());
						return 1;
					erule
					rule(ir::instr::TypeInterface, type)
						types.push(::llvm::Type::getInt8PtrTy(context));
						types.push(getInterfaceLayout(type->interface)->getInterfaceType()->getPointerTo());
						return 2;
					erule
					rule(ir::instr::TypeArray, type)
						types.push(::llvm::Type::getInt8PtrTy(context));
						return 1;
					erule
					rule(ir::instr::TypeEnum, type)
						//TODO::
						types.push(::llvm::Type::getInt8PtrTy(context));
						return 1;
					erule
					rule(ir::instr::TypeOptional, type)
						OptionalBehavior::Value optionalBehavior = getOptionalBehavior(type);
						size_t size = convertType(type->valueType, types);
						switch ( optionalBehavior ){
						case OptionalBehavior::ExtraBit:{
							types.push(::llvm::Type::getInt1Ty(context));
							return size + 1;
						}break;
						case OptionalBehavior::NullPointer0:{
							return size;
						}break;
						default:{
							unreachable;
						}break;
						}
					erule
					defrule(_)
						unreachable;
					erule
				ematch
			}

			ClassLayout* LLVMContext::getClassLayout(ir::Class* class_){
				ClassLayout*& layout = classLayouts.getOrInsert(class_);
				if ( !layout ){
					layout = new(allocate(sizeof(ClassLayout)))ClassLayout(this, this, class_);
				}
				return layout;
			}

			InterfaceLayout* LLVMContext::getInterfaceLayout(ir::Interface* interface){
				InterfaceLayout*& layout = interfaceLayouts.getOrInsert(interface);
				if ( !layout ){
					layout = new(allocate(sizeof(InterfaceLayout)))InterfaceLayout(this, this, interface);
				}
				return layout;
			}

			::llvm::FunctionType* LLVMContext::getMethodType(ir::ClassMethod* method){
				::llvm::FunctionType*& functionType = methodTypes.getOrInsert(method);
				if ( !functionType ){
					functionType = createMethodType(method);
				}
				return functionType;
			}

			::llvm::FunctionType* LLVMContext::getMethodType(ir::InterfaceMethod* method){
				::llvm::FunctionType*& functionType = imethodTypes.getOrInsert(method);
				if ( !functionType ){
					functionType = createMethodType(method);
				}
				return functionType;
			}

			::llvm::FunctionType* LLVMContext::createMethodType(ir::InterfaceMethod* method){
				ArrayList<::llvm::Type*> params(this);
				::llvm::Type* result = nullptr;
				fillReturnValue(method->getSignature()->getReturnType(), result, params);
				params.push(::llvm::Type::getInt8PtrTy(context));
				iterate_array(param, method->getSignature()->getParams()){
					fillParams(param.get().getType(), params);
				}				
				if ( !result ){
					result = ::llvm::Type::getVoidTy(getContext());
				}
				return ::llvm::FunctionType::get(result, toLLVM(params.asFlatArray(this)), false);
			}

			::llvm::FunctionType* LLVMContext::createMethodType(ir::ClassMethod* method){
				ArrayList<::llvm::Type*> params(this);
				::llvm::Type* result = nullptr;
				ClassLayout* layout = getClassLayout(method->getOwner());
				fillReturnValue(method->getSignature()->getReturnType(), result, params);
				params.push(layout->getObjectType());
				iterate_array(param, method->getSignature()->getParams()){
					fillParams(param.get().getType(), params);
				}
				
				if ( !result ){
					result = ::llvm::Type::getVoidTy(getContext());
				}
				return ::llvm::FunctionType::get(result, toLLVM(params.asFlatArray(this)), false);
			}

			void LLVMContext::fillReturnValue(const ir::Type& type, ::llvm::Type*& returnType, ArrayList<::llvm::Type*>& params){
				size_t count = convertType(this, type, typeStack);
				for ( ; count; count-- ){
					::llvm::Type* type = typeStack.takeLast();
					if ( !type->isAggregateType() && !returnType ){
						returnType = type;
					}else{
						params.push(type->getPointerTo());
					}
				}
			}

			void LLVMContext::fillParams(const ir::Type& type, ArrayList<::llvm::Type*>& params){
				size_t count = convertType(this, type, typeStack);
				for ( ; count; count-- ){
					::llvm::Type* type = typeStack.takeLast();
					if ( type->isAggregateType() ){
						params.push(type->getPointerTo());
					}else{
						params.push(type);
					}
				}
			}

			bool LLVMContext::isBitCastCoercion(ir::instr::Coercion* coercion){
				if ( !coercion ){
					return false;
				}
				match(coercion)
					rule(ir::instr::CoercionToBaseClass, _)
						return true;
					erule
					defrule(_)
						return false;
					erule
				ematch
			}
		}
	}
}