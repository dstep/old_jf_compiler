#include <IR/Compiler/LayoutBuilder.h>
#include <Support/Container/SearchTree.h>
#include <Support/Container/ArrayList.h>

namespace jf{
	namespace ir{
		namespace compiler{
			struct BuildLayoutContext{
				IDiagnosticStream* stream;
				MemoryPoolSlice* hostPool;
			};

			class BuildLayoutBase{
			public:
				BuildLayoutBase(BuildLayoutContext* context)
					: context(context){
				}

				ImplementsInterface::Map buildImplementsMap(const ArrayRef<ImplementsInterface>& implements, const ImplementsInterface::Map& parentMap = ImplementsInterface::Map()){
					ImplementsInterface::Map implementsMap = parentMap;

					Interface* largestExtendedInterface = nullptr;
					size_t largestInterfaceSize = 0;

					if ( parentMap.isEmpty() ){
						iterate_array(extend, implements){
							Interface* targetInterface = extend.get().getTargetInterface();
							if ( targetInterface && extend.get().getDependency()->satisfied ){
								size_t size = targetInterface->getImplementsMap().calculateSize() + 1;
								if ( size > largestInterfaceSize ){
									largestInterfaceSize = size;
									largestExtendedInterface = targetInterface;
								}
							}
						}

						if ( largestExtendedInterface ){
							implementsMap = largestExtendedInterface->getImplementsMap();
						}
					}

					iterate_array(extend, implements){
						Interface* targetInterface = extend.get().getTargetInterface();
						if ( targetInterface && extend.get().getDependency()->satisfied ){
							if ( targetInterface != largestExtendedInterface ){
								targetInterface->getImplementsMap().traverseInorder([this, &implementsMap](Interface* interface, const bool& ){
										implementsMap.getOrInsert(this->context->hostPool, interface) = true;
									});
							}
							implementsMap.getOrInsert(context->hostPool, targetInterface) = true;
						}
					}

					implementsMap.freeze();

					return implementsMap;
				}
			protected:
				BuildLayoutContext* context;
			};

			Ordering::Value CompareInterfacesBasedOnMethodMapSize(Interface* const& left, Interface* const& right){
				size_t sizeLeft = left->getMethodMap().calculateSize();
				size_t sizeRight = right->getMethodMap().calculateSize();
				Ordering::Value compareSize = Ordering::Compare(sizeRight, sizeLeft);
				if ( compareSize == Ordering::Eq ){
					return Ordering::Compare(right, left);
				}
				return compareSize;
			}

			class BuildInterfaceLayout: public threading::IJob, public BuildLayoutBase{
			public:
				BuildInterfaceLayout(BuildLayoutContext* context, Interface* interface)
					: BuildLayoutBase(context)
					, interface(interface){
				}

				void run(bool deadlocked, threading::JobCompletionCallback callback){
					MemoryPoolSlice stack(GetMemoryPool());
					
					if ( deadlocked ){
						context->stream->report(Subsystem("Compiler").at(interface->getSrcLoc()).type(DiagnosticType::Error).code("CompilerError.CyclicDependence").parameter<StringLiteral>("name", interface->getName()));
					}

					interface->setImplementsMap(buildImplementsMap(interface->getExtends()));

					Interface::MethodMap methodMap;
					SearchTree<Interface*, ImplementsInterface*, CompareInterfacesBasedOnMethodMapSize > interfacesToMergeSorted;
					
					iterate_array(extend, interface->getExtends()){
						Interface* targetInterface = extend.get().getTargetInterface();
						if ( targetInterface && extend.get().getDependency()->satisfied ){
							interfacesToMergeSorted.getOrInsert(&stack, targetInterface) = &extend.get();
						}
					}

					interfacesToMergeSorted.traverseInorder([this, &methodMap](Interface* interface, ImplementsInterface* implements){
							if ( methodMap.isEmpty() ){
								methodMap = interface->getMethodMap();
							}else{
								const Interface::MethodMap& theirMethodMap = interface->getMethodMap();
								auto visitor = [this, &methodMap, implements](const StringRef& name, InterfaceMethod* method){
										this->mergeMethod(methodMap, implements->getSrcLoc(), name, method);
									};
								theirMethodMap.traverseInorder(visitor);
							}
						});

					iterate_array(method, interface->getMethods()){
						mergeMethod(methodMap, method.get().getSrcLoc(), method.get().getName(), &method.get());
					}

					methodMap.freeze();
					interface->setMethodMap(methodMap);

					callback.run();
				}

				void mergeMethod(Interface::MethodMap& methodMap, const SrcSpan& responsibleLocation, const StringRef& name, InterfaceMethod* method){
					InterfaceMethod*& methodSlot = methodMap.getOrInsert(context->hostPool, name);
					if ( methodSlot ){
						if ( methodSlot != method ){
							context->stream->report
								(
									Subsystem("Compiler")
										.at(responsibleLocation)
										.type(DiagnosticType::Error)
										.code("CompilerError.InterfaceMethodDuplicateName")
										.parameter<StringLiteral>("name", name)
										.parameter<ReferencedSymbol>("previous", methodSlot->makeReference())
										.parameter<ReferencedSymbol>("duplicate", method->makeReference())
								);
						}
					}else{
						methodSlot = method;
					}
				}
			private:
				Interface* interface;
			};

			class BuildClassLayout: public threading::IJob, public BuildLayoutBase{
			public:
				BuildClassLayout(BuildLayoutContext* context, Class* class_)
					: BuildLayoutBase(context)
					, class_(class_){
				}

				void run(bool deadlocked, threading::JobCompletionCallback callback){
					if ( deadlocked ){
						context->stream->report(Subsystem("Compiler").at(class_->getSrcLoc()).type(DiagnosticType::Error).code("CompilerError.CyclicDependence").parameter<StringLiteral>("name", class_->getName()));
					}

					Class::MembersMap membersMap;
					Class::AbstractsMap abstractsMap;
					Class::BasesMap basesMap;
					Class::ConstructorsMap constructorsMap;
					ImplementsInterface::Map implementsMap;

					if ( class_->getExtends() && class_->getExtends()->getTargetClass() && class_->getExtends()->getDependency()->satisfied ){
						Class* targetClass = class_->getExtends()->getTargetClass();
						membersMap = targetClass->getMembersMap();
						abstractsMap = targetClass->getAbstractMap();
						basesMap = targetClass->getBasesMap();
						implementsMap = targetClass->getImplementsMap();
						constructorsMap = targetClass->getAllConstructorsMap();
						class_->setLevel(targetClass->getLevel() + 1);
					}else{
						class_->setLevel(0);
					}

					basesMap.add(context->hostPool, class_, 1);

					class_->setImplementsMap(buildImplementsMap(class_->getImplements(), implementsMap));

					iterate_array(constructor_, class_->getConstructors()){
						ClassConstructor& constructor = constructor_.get();
						ir::Class* baseClass = nullptr;
						if ( constructor.getBaseName() ){
							ExportName baseResolution = constructor.getBaseName()->getResolution();							
							if ( baseResolution ){
								if ( baseResolution.kind == ExportKind::Class ){
									baseClass = (ir::Class*)baseResolution.reference;
									if ( !basesMap.find(baseClass) ){									
										context->stream->report
											(
												Subsystem("Compiler")
													.at(constructor.getBaseName()->getSrcLoc())
													.type(DiagnosticType::Error)
													.code("CompilerError.ConstructorBaseIsNotBaseClass")
													.parameter("class", baseResolution.makeSymbol(constructor.getBaseName()->getResolutionModule()))
											);
										baseClass = nullptr;
									}
								}else{
									context->stream->report
											(
												Subsystem("Compiler")
													.at(constructor.getBaseName()->getSrcLoc())
													.type(DiagnosticType::Error)
													.code("CompilerError.ConstructorBaseIsNotClass")
													.parameter("reference", baseResolution.makeSymbol(constructor.getBaseName()->getResolutionModule()))
											);
								}
							}
						}
						constructor.setBaseClass(baseClass);
						if ( constructorsMap.find(constructor.getName()) ){
							constructorsMap.replace(context->hostPool, constructor.getName(), &constructor);
						}else{
							constructorsMap.add(context->hostPool, constructor.getName(), &constructor);
						}
					}

					iterate_array(field, class_->getFields()){
						ClassMember*& memberSlot = membersMap.getOrInsert(context->hostPool, field.get().getName());
						if ( memberSlot ){
						//incompatible override
							context->stream->report
								(
									Subsystem("Compiler")
										.at(field.get().getSrcLoc())
										.type(DiagnosticType::Error)
										.code("CompilerError.FieldOverride")
										.parameter<StringLiteral>("name", field.get().getName())
										.parameter("previous", memberSlot->makeReference())
								);
						}
						if ( !memberSlot || memberSlot->getOwner() != class_ ){
							memberSlot = &field.get();
						}
					}
					iterate_array(method, class_->getMethods()){
						ClassMember*& memberSlot = membersMap.getOrInsert(context->hostPool, method.get().getName());
						if ( memberSlot ){
							if ( memberSlot->tag == ClassMethodTag ){
								if ( method.get().getKind() != ClassMethod::Override ){
									context->stream->report
										(
											Subsystem("Compiler")
												.at(method.get().getSrcLoc())
												.type(DiagnosticType::Error)
												.code("CompilerError.NoOverrideMark")
												.parameter<StringLiteral>("name", method.get().getName())
												.parameter("previous", memberSlot->makeReference())
										);
								}
								ClassMethod* baseMethod = (ClassMethod*)memberSlot;
								if ( baseMethod->getKind() == ClassMethod::Abstract ){
									abstractsMap.remove(context->hostPool, baseMethod);
								}
								method.get().setBaseMethod(baseMethod);
								membersMap.replace(context->hostPool, method.get().getName(), &method.get());
							}else{
								context->stream->report
									(
										Subsystem("Compiler")
											.at(method.get().getSrcLoc())
											.type(DiagnosticType::Error)
											.code("CompilerError.MethodOverride")
											.parameter<StringLiteral>("name", method.get().getName())
											.parameter("previous", memberSlot->makeReference())
									);
							}
						}else{
							memberSlot = &method.get();
							method.get().setBaseMethod(nullptr);
							if ( method.get().getKind() == ClassMethod::Override ){
								context->stream->report
									(
										Subsystem("Compiler")
											.at(method.get().getSrcLoc())
											.type(DiagnosticType::Error)
											.code("CompilerError.ExtraOverrideMark")
											.parameter<StringLiteral>("name", method.get().getName())
									);
							}
						}
						if ( method.get().getKind() == ClassMethod::Abstract ){
							abstractsMap.add(context->hostPool, &method.get(), &method.get());
						}
					}
					membersMap.freeze();
					abstractsMap.freeze();
					basesMap.freeze();
					constructorsMap.freeze();

					class_->setMembersMap(membersMap);
					class_->setAbstractsMap(abstractsMap);
					class_->setBasesMap(basesMap);
					class_->setAllConstructorsMap(constructorsMap);
					
					callback.run();
				}
			private:
				Class* class_;
			};

			LayoutBuilder::LayoutBuilder(IDiagnosticStream* stream, threading::DataflowManager* dataflow, JobWrapper* jobWrapper, MemoryPoolSlice* tempPool, MemoryPoolSlice* hostPool, MemoryPoolSlice* processPool)
				: stream(stream)
				, dataflow(dataflow)
				, jobWrapper(jobWrapper)
				, tempPool(tempPool)
				, processPool(processPool)
				, hostPool(hostPool){
			}

			void LayoutBuilder::run(Module* module){
				this->module = module;

				BuildLayoutContext* context = new(processPool->allocate(sizeof(BuildLayoutContext)))BuildLayoutContext;
				context->hostPool = hostPool;
				context->stream = stream;

				{
					auto interfaces = module->interfaces;
					size_t n = interfaces.getSize();
					for ( size_t i = 0; i < n; i++ ){
						threading::DataflowJob* job = interfaces.get(i)->getDataflowJob();
						auto extends = interfaces.get(i)->getExtends();
						iterate_array(extend, extends){
							auto dependency = extend.get().getDependency();
							dependency->satisfied = false;
							Interface* interface = extend.get().getTargetInterface();
							if ( interface ){
								job->addDependency(interface->getDataflowJob(), dependency);
							}
						}
						dataflow->addJob(job, jobWrapper->wrap(new(processPool->allocate(sizeof(BuildInterfaceLayout)))BuildInterfaceLayout(context, interfaces.get(i))));
					}
				}
				{
					auto classes = module->classes;
					size_t n = classes.getSize();
					for ( size_t i = 0; i < n; i++ ){
						threading::DataflowJob* job = classes.get(i)->getDataflowJob();

						auto extends = classes.get(i)->getExtends();
						if ( extends ){
							auto dependency = extends->getDependency();
							dependency->satisfied = false;
							Class* class_ = extends->getTargetClass();
							if ( class_ ){
								job->addDependency(class_->getDataflowJob(), dependency);
							}
						}

						auto implements = classes.get(i)->getImplements();
						iterate_array(implement, implements){
							auto dependency = implement.get().getDependency();
							dependency->satisfied = false;
							Interface* interface = implement.get().getTargetInterface();
							if ( interface ){
								job->addDependency(interface->getDataflowJob(), dependency);
							}
						}

						dataflow->addJob(job, jobWrapper->wrap(new(processPool->allocate(sizeof(BuildClassLayout)))BuildClassLayout(context, classes.get(i))));
					}
				}
			}
		}
	}
}