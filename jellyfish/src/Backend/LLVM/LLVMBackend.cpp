#include <Backend/LLVM/LLVMBackend.h>
#include <Backend/LLVM/LLVMModuleInfo.h>
#include <Support/Match.h>

namespace jf{
	namespace backend{
		namespace llvm{
			LLVMBackend::LLVMBackend(MemoryPoolSlice* tempPool, LLVMContext* context, LLVMModule* module)
				: tempPool(tempPool)
				, context(context)
				, module(module)
				, functionCompiler(tempPool, context, module){
			}

			BackendModuleInfo::ID LLVMBackend::getBackendID(){
				return LLVMModuleInfo::ID;
			}

			void LLVMBackend::visitModule(ir::Module* module, ir::GlobalFunction* mainFunction, MemoryPoolSlice* pool, BackendModuleInfo*& moduleInfo){
				iterate_array(function, module->functions){
					auto globalFunction = function.get();
					functionCompiler.captureFunctionDeclaration(this->module->getDeclaration(globalFunction));
					match(globalFunction->getBody())
						rule(ir::FunctionBodyCode, body)
							functionCompiler.captureReturnValue(globalFunction->getSignature()->getReturnType());
							iterate_array(param, globalFunction->getSignature()->getParams()){							
								functionCompiler.captureParam(&param.get());
							}
							functionCompiler.enterFunctionFrame(body->getFrame());
							functionCompiler.leaveFunctionFrame();
						erule
						rule(ir::FunctionBodyFFI, body)
							functionCompiler.makeFFICall(body->getString());
						erule
					ematch					
				}

				iterate_array(class__, module->classes){
					auto class_ = class__.get();
					ClassLayout* layout = this->context->getClassLayout(class_);
					::llvm::Constant* initializer = layout->createVTableInitializer(this->module);
					this->module->getClassTable(class_)->setInitializer(initializer);
					this->module->getClassImplementsTable(class_)->setInitializer(layout->createImplementsTableInitializer(this->module));
					iterate_array(method_, class_->getMethods()){
						auto method = &method_.get();
						functionCompiler.captureFunctionDeclaration(this->module->getDeclaration(method));
						match(method->getBody())
							rule(ir::FunctionBodyCode, body)
								functionCompiler.captureReturnValue(method->getSignature()->getReturnType());
								functionCompiler.captureThisObject(class_);
								iterate_array(param, method->getSignature()->getParams()){							
									functionCompiler.captureParam(&param.get());
								}
								functionCompiler.enterFunctionFrame(body->getFrame());
								functionCompiler.leaveFunctionFrame();
							erule
							rule(ir::FunctionBodyFFI, body)
								functionCompiler.makeFFICall(body->getString());
							erule
						ematch		
					}
					iterate_array(constructor_, class_->getConstructors()){
						auto constructor = &constructor_.get();
						functionCompiler.captureFunctionDeclaration(this->module->getDeclaration(constructor));
						match(constructor->getBody())
							rule(ir::FunctionBodyCode, body)
								functionCompiler.captureReturnValue(constructor->getSignature()->getReturnType());
								functionCompiler.captureConstructorStack();
								functionCompiler.captureThisObject(class_);
								iterate_array(param, constructor->getSignature()->getParams()){							
									functionCompiler.captureParam(&param.get());
								}
								functionCompiler.enterFunctionFrame(body->getFrame());
								functionCompiler.leaveFunctionFrame();
							erule
							rule(ir::FunctionBodyFFI, body)
								functionCompiler.makeFFICall(body->getString());
							erule
						ematch		

						if ( class_->getBaseClass() ){
							functionCompiler.captureFunctionDeclaration(this->module->getClosureDeclaration(constructor));
							functionCompiler.makeConstructorCallFromClosure(constructor);
						}
					}
				}

				if ( mainFunction ){
					functionCompiler.generateMainFunction(mainFunction);
				}

				LLVMModuleInfo* llvmModuleInfo;
				if ( !moduleInfo ){
					llvmModuleInfo = new(pool->allocate(sizeof(LLVMModuleInfo)))LLVMModuleInfo(pool);
					moduleInfo = llvmModuleInfo;
				}else{
					llvmModuleInfo = (LLVMModuleInfo*)moduleInfo;
					llvmModuleInfo->reset();
				}

				llvmModuleInfo->archive = this->module->archiveModule(*tempPool, pool);
			}

		}
	}
}