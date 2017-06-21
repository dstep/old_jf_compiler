#include <Backend/LLVM/ClassLayout.h>
#include <Backend/LLVM/LLVMContext.h>
#include <Backend/LLVM/LLVMModule.h>
#include <Backend/LLVM/FunctionCompiler.h>
#include <Backend/LLVM/Common.h>
#include <IR/Class.h>
#include <IR/Module.h>
#include <Support/Twine.h>
#include <llvm/IR/Constants.h>
#include <Support/Match.h>

namespace jf{
	namespace backend{
		namespace llvm{
			ClassLayout::ClassLayout(LLVMContext* context, MemoryPoolSlice* pool, ir::Class* class_)
				: context(context)
				, pool(pool)
				, class_(class_)
				, objectType(nullptr)
				, classType(nullptr)
				, size(nullptr)
				, layoutBuilt(false)
				, classLayoutBuilt(false)
				, vtableLayout(pool)
				, implementsTableBuilt(false){
			}

			::llvm::Type* ClassLayout::getObjectType(){				
				if ( !objectType ){
					MemoryPoolSlice stack(GetMemoryPool());
					objectType = ::llvm::StructType::create(context->getContext(), toLLVM(("class:" + class_->getOwner()->qid->asString() + "." + class_->getName()).toString(&stack)));
				}
				return objectType->getPointerTo();
			}

			::llvm::Type* ClassLayout::getClassType(){
				if ( !classType ){
					MemoryPoolSlice stack(GetMemoryPool());
					classType = ::llvm::StructType::create(context->getContext(), toLLVM(("classvtable:" + class_->getOwner()->qid->asString() + "." + class_->getName()).toString(&stack)));
				}
				return classType->getPointerTo();
			}

			void ClassLayout::createVTablePart(LLVMModule* module, ::llvm::SmallVector<::llvm::Constant*, 128>& values, ClassLayout* layout){
				ir::Class* baseClass = layout->class_->getBaseClass();
				if ( baseClass ){
					ClassLayout* baseLayout = context->getClassLayout(baseClass);
					baseLayout->requestLayout();
					createVTablePart(module, values, baseLayout);
					::llvm::Constant* constant = ::llvm::ConstantStruct::get(baseLayout->classType, values); //-V510
					values.clear();
					values.push_back(constant);
				}else{
					values.push_back(::llvm::ConstantPointerNull::get(::llvm::Type::getInt8PtrTy(context->getContext())));
					values.push_back(::llvm::ConstantPointerNull::get(::llvm::Type::getInt8PtrTy(context->getContext())));
				}

				iterate_enumerable(method, layout->vtableLayout){
					auto overrider = overrideMap.find(method.get());
					if ( overrider ){
						if ( isSeparateSlotNeeded(overrider->getOverride()) ){
							MemoryPoolSlice stack(GetMemoryPool());
							FunctionCompiler compiler(&stack, context, module);
							::llvm::FunctionType* funType = context->getMethodType(method.get());
							::llvm::Function* function = ::llvm::Function::Create(funType, ::llvm::GlobalValue::InternalLinkage, "", module->getModule());
							compiler.captureFunctionDeclaration(function);
							compiler.captureReturnValue(method.get()->getSignature()->getReturnType());
							compiler.captureThisObject(method.get()->getOwner());
							iterate_array(param, method.get()->getSignature()->getParams()){
								compiler.captureParam(&param.get());
							}
							compiler.makeDecoratedVirtualCall(method.get()->getSignature(), overrider);
						}else{
							values.push_back(::llvm::ConstantExpr::getBitCast(module->getDeclaration(overrider), context->getMethodType(method.get())->getPointerTo()));
						}
					}else{
						values.push_back(module->getDeclaration(method.get()));
					}
				}
			}

			::llvm::Constant* ClassLayout::createVTableInitializer(LLVMModule* module){
				requestClassLayout();
				::llvm::SmallVector<::llvm::Constant*, 128> values;
				createVTablePart(module, values, this);
				::llvm::Constant* constant = ::llvm::ConstantStruct::get(classType, values);
				values.clear();
				return constant;
			}

			::llvm::StructType* ClassLayout::getClassVTableType(){
				getClassType();
				return classType;
			}

			void ClassLayout::requestLayout(){
				if ( !layoutBuilt ){
					::llvm::SmallVector<::llvm::Type*, 128> types;

					if ( class_->getBaseClass() ){
						ir::Class* baseClass = class_->getBaseClass();
						ClassLayout* baseLayout = context->getClassLayout(baseClass);
						baseLayout->requestLayout();
						types.push_back(baseLayout->objectType);
						fieldsMap = baseLayout->fieldsMap;						
					}else{
						types.push_back(getClassType());
					}

					iterate_array(field, class_->getFields()){
						size_t typesCount = context->convertType(pool, field.get().getType(), context->getTypeStack());
						u32 oldSize = (u32)types.size();
						while ( typesCount > 0 ){
							types.push_back(context->getTypeStack().takeLast());
							typesCount--;
						}
						u32 newSize = (u32)types.size();
						fieldsMap.add(pool, &field.get(), MakePair(this, MakePair(oldSize, newSize - oldSize)));	
					}
					fieldsMap.freeze();

					getObjectType();
					objectType->setBody(types);

					layoutBuilt = true;
				}
			}

			::llvm::Constant* ClassLayout::getSize(){
				if ( !size ){
					requestLayout();
					::llvm::Constant* idx[] = {
							::llvm::ConstantInt::get(::llvm::Type::getInt32Ty(context->getContext()), 1)
						};
					::llvm::Constant* gep = 
						::llvm::ConstantExpr::getGetElementPtr
							(
								::llvm::ConstantPointerNull::get(objectType->getPointerTo()), 
								idx
							);
					size = 
						::llvm::ConstantExpr::getPtrToInt
							(
								gep,
								::llvm::Type::getInt32Ty(context->getContext())
							);
				}
				return size;
			}

			void ClassLayout::requestImplementsTable(){
				if ( !implementsTableBuilt ){
					if ( class_->getBaseClass() ){
						ir::Class* baseClass = class_->getBaseClass();
						ClassLayout* baseLayout = context->getClassLayout(baseClass);
						baseLayout->requestImplementsTable();
						interfaceMap = baseLayout->interfaceMap;
						implementsTableLayout = baseLayout->implementsTableLayout;
					}

					iterate_array(interface, class_->getImplements()){
						ir::Interface* baseInterface = interface.get().getBaseInterface();
						if ( baseInterface ){
							if ( !interfaceMap.has(baseInterface) ){
								InterfaceLayout* interfaceLayout = context->getInterfaceLayout(baseInterface);
								interfaceLayout->requestLayout();								
								iterate_enumerable(interface, interfaceLayout->implementsMap){
									if ( !interfaceMap.has(interface.getKey()) ){
										interfaceMap.add(pool, interface.getKey(), MakePair((u32)implementsTableLayout.size(), interface.getValue().second));
									}
								}
								implementsTableLayout.push_back(interfaceLayout->getInterfaceType());
							}
						}
					}

					implementsTableType = ::llvm::StructType::get(context->getContext(), implementsTableLayout);

					implementsTableBuilt = true;
				}
			}

			::llvm::GlobalVariable* ClassLayout::createImplementsTable(LLVMModule* module){
				requestImplementsTable();
				MemoryPoolSlice stack(GetMemoryPool());
				return new ::llvm::GlobalVariable(*module->getModule(), implementsTableType, true, ::llvm::GlobalValue::ExternalLinkage, nullptr, toLLVM(("classimplements:" + class_->getOwner()->qid->asString() + "." + class_->getName()).toString(&stack)));
			}

			::llvm::Constant* ClassLayout::getInterfaceFromImplementsTable(::llvm::GlobalVariable* implementsTable, ir::Interface* interface){
				auto location = interfaceMap.find(interface);
				::llvm::Type* int32Ty = ::llvm::Type::getInt32Ty(context->getContext());
				::llvm::Constant* indexes[] = {
						::llvm::ConstantInt::get(int32Ty, 0), 
						::llvm::ConstantInt::get(int32Ty, location.first), 
						::llvm::ConstantInt::get(int32Ty, location.second)
					};
				InterfaceLayout* interfaceLayout = context->getInterfaceLayout(interface);
				return ::llvm::ConstantExpr::getBitCast(::llvm::ConstantExpr::getGetElementPtr(implementsTable, indexes), interfaceLayout->getInterfaceType()->getPointerTo());
			}

			::llvm::Constant* ClassLayout::createImplementsTableInitializer(LLVMModule* module){
				::llvm::SmallVector<::llvm::Constant*, 64> values;	
				::llvm::SmallVector<::llvm::Constant*, 64> localValues;			
				requestImplementsTable();
				values.resize(implementsTableLayout.size());
				auto& implementsMap = class_->getImplementMethodsMap();
				interfaceMap.traverseInorder([&](ir::Interface* interface, const Pair<u32, u32>& location){
						if ( location.second == 0 ){
							InterfaceLayout* interfaceLayout = context->getInterfaceLayout(interface);
							
							interfaceLayout->requestLayout();
							iterate_enumerable(imethod, interfaceLayout->methodsList){
								auto implement = implementsMap.find(imethod.get());
								if ( implement ){
									if ( isWrapperNeeded(implement) ){
										MemoryPoolSlice stack(GetMemoryPool());
										FunctionCompiler compiler(&stack, context, module);
										::llvm::FunctionType* funType = context->getMethodType(implement->getBaseMethod());
										::llvm::Function* function = ::llvm::Function::Create(funType, ::llvm::GlobalValue::InternalLinkage, "", module->getModule());
										compiler.captureFunctionDeclaration(function);
										compiler.captureReturnValue(implement->getBaseMethod()->getSignature()->getReturnType());
										compiler.captureThisObject(implement->getOverrideMethod()->getOwner());
										iterate_array(param, implement->getBaseMethod()->getSignature()->getParams()){
											compiler.captureParam(&param.get());
										}
										compiler.makeDecoratedVirtualCall(implement->getBaseMethod()->getSignature(), implement->getOverrideMethod());
										localValues.push_back(::llvm::ConstantExpr::getBitCast(function, interfaceLayout->interfaceType->getContainedType(imethod.getIndex())));
									}else{
										localValues.push_back(::llvm::ConstantExpr::getBitCast(module->getDeclaration(implement->getOverrideMethod()), interfaceLayout->interfaceType->getContainedType(imethod.getIndex())));
									}
								}else{
									localValues.push_back(::llvm::ConstantPointerNull::get(::llvm::cast<::llvm::PointerType>(interfaceLayout->interfaceType->getContainedType(imethod.getIndex()))));
								}
							}
							values[location.first] = ::llvm::ConstantStruct::get(interfaceLayout->interfaceType, localValues);
							localValues.clear();
						}
					});
				return ::llvm::ConstantStruct::get(implementsTableType, values);
			}

			Pair<ClassLayout*, u32> ClassLayout::getMethodIndex(ir::ClassMethod* method){
				requestClassLayout();
				return methodsMap.find(method);
			}

			Pair<ClassLayout*, Pair<u32, u32> > ClassLayout::getFieldIndex(ir::ClassField* field){
				requestLayout();
				return fieldsMap.find(field);
			}

			bool ClassLayout::isSeparateSlotNeeded(ir::ClassMethodOverride* overrider){
				iterate_array(param, overrider->getParamCoercions()){
					if ( !context->isBitCastCoercion(param.get()) ){
						return false;
					}
				}
				if ( !context->isBitCastCoercion(overrider->getRetValCoercion()) ){
					return false;
				}
				return true;
			}

			bool ClassLayout::isWrapperNeeded(ir::ClassMethodImplements* overrider){
				iterate_array(param, overrider->getParamCoercions()){
					if ( !context->isBitCastCoercion(param.get()) ){
						return false;
					}
				}
				if ( !context->isBitCastCoercion(overrider->getRetValCoercion()) ){
					return false;
				}
				return true;
			}

			void ClassLayout::requestClassLayout(){
				if ( !classLayoutBuilt ){
					::llvm::SmallVector<::llvm::Type*, 128> types;

					ClassLayout* baseLayout = nullptr;

					if ( class_->getExtends() && class_->getExtends()->getTargetClass() && class_->getExtends()->getDependency()->satisfied ){
						ir::Class* baseClass = class_->getExtends()->getTargetClass();
						baseLayout = context->getClassLayout(baseClass);
						baseLayout->requestClassLayout();
						types.push_back(baseLayout->classType);
						methodsMap = baseLayout->methodsMap;
						overrideMap = baseLayout->overrideMap;
					}else{
						types.push_back(::llvm::Type::getInt8PtrTy(context->getContext()));
						types.push_back(::llvm::Type::getInt8PtrTy(context->getContext()));
					}

					iterate_array(method, class_->getMethods()){
						auto overrider = method.get().getOverride();
						bool makeNewSlot = true;
						if ( baseLayout && overrider ){
							auto baseMethodRef = baseLayout->methodsMap.find(overrider->getBaseMethod());
							if ( !isSeparateSlotNeeded(overrider) ){
								methodsMap.add(pool, &method.get(), baseMethodRef);								
								makeNewSlot = false;
							}
							overrideMap.addOrReplace(pool, overrider->getBaseMethod(), &method.get());							
						}
						if ( makeNewSlot ){
							methodsMap.add(pool, &method.get(), MakePair(this, (u32)types.size()));
							types.push_back(context->getMethodType(&method.get())->getPointerTo());
							vtableLayout.push(&method.get());
						}
					}
					methodsMap.freeze();

					getClassType();
					classType->setBody(types);

					classLayoutBuilt = true;
				}
			}
		}
	}
}