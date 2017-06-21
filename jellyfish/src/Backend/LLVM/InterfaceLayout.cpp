#include <Backend/LLVM/InterfaceLayout.h>
#include <Backend/LLVM/LLVMContext.h>
#include <Backend/LLVM/LLVMModule.h>
#include <Backend/LLVM/FunctionCompiler.h>
#include <Backend/LLVM/Common.h>
#include <IR/Interface.h>
#include <IR/Module.h>
#include <Support/Twine.h>
#include <llvm/IR/Constants.h>
#include <Support/Match.h>

namespace jf{
	namespace backend{
		namespace llvm{
			InterfaceLayout::InterfaceLayout(LLVMContext* context, MemoryPoolSlice* pool, ir::Interface* interface)
				: context(context)
				, pool(pool)
				, interface(interface)
				, layoutBuilt(false)
				, interfaceType(nullptr)
				, implementsMap(pool)
				, methodsMap(pool)
				, methodsList(pool)
				, implementsList(pool){
			}

			::llvm::Type* InterfaceLayout::getInterfaceType(){
				if ( !interfaceType ){
					MemoryPoolSlice stack(GetMemoryPool());
					interfaceType = ::llvm::StructType::create(context->getContext(), toLLVM(("interface:" + interface->getOwner()->qid->asString() + "." + interface->getName()).toString(&stack)));
				}
				return interfaceType;
			}

			u32 InterfaceLayout::getMethodIndex(ir::InterfaceMethod* method){
				requestLayout();
				return methodsMap.get(method);
			}

			void InterfaceLayout::requestLayout(){
				if ( !layoutBuilt ){
					::llvm::SmallVector<::llvm::Type*, 64> types;
					implementsMap.set(interface, MakePair(this, 0u));
					iterate_array(method, interface->getMethods()){
						::llvm::FunctionType* type = context->getMethodType(&method.get());	
						
						methodsList.push(&method.get());
						methodsMap.set(&method.get(), types.size());

						types.push_back(type->getPointerTo());
					}
					iterate_array(extends, interface->getExtends()){
						ir::Interface* baseInterface = extends.get().getBaseInterface();						
						if ( baseInterface ){
							auto implementsSlot = implementsMap.getOrInsert(baseInterface);
							if ( !implementsSlot.first ){
								InterfaceLayout* baseLayout = context->getInterfaceLayout(baseInterface);
								implementsSlot.first = baseLayout;
								implementsSlot.second = types.size();
								embedInterface(baseLayout, types);
							}
						}
					}
					getInterfaceType();
					interfaceType->setBody(types);
					layoutBuilt = true;
				}
			}

			void InterfaceLayout::embedInterface(InterfaceLayout* layout, ::llvm::SmallVectorImpl<::llvm::Type*>& types){
				layout->requestLayout();
				iterate_enumerable(method, layout->methodsList){
					methodsList.push(method.get());
					methodsMap.set(method.get(), types.size());
					types.push_back(context->getMethodType(method.get()));
				}
				iterate_enumerable(base, layout->implementsList){
					auto implementsSlot = implementsMap.getOrInsert(base.get()->interface);
					if ( !implementsSlot.first ){
						implementsSlot.first = base.get();
						implementsSlot.second = types.size();
					}
					embedInterface(base.get(), types);
				}
			}
		}
	}
}