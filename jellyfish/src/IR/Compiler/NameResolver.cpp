#include <IR/Compiler/NameResolver.h>
#include <Support/Container/ArrayList.h>

namespace jf{
	namespace ir{
		namespace compiler{
			NameResolver::NameResolver(IDiagnosticStream* stream, MemoryPoolSlice* tempPool, MemoryPoolSlice* hostPool)
				: stream(stream)
				, tempPool(tempPool)
				, hostPool(hostPool){
			}

			void NameResolver::run(Module* module){
				this->module = module;

				buildFilters();

				resolveNames();
			}

			void NameResolver::buildFilters(){
				auto namespaces = module->namespaces;
				size_t n = namespaces.getSize();
				for ( size_t i = 0; i < n; i++ ){
					new(namespaces[i]->getFilter())ImportFilter(namespaces[i]->getModules(), ImportModuleFilterConstructor, ImportModuleElementExtractor, hostPool);
				}
			}

			class ElementVisitor{
			public:
				ElementVisitor(ArrayList<ir::Module*>& candidateModules)
					: candidateModules(candidateModules){
				}

				void operator()(ir::Module* module){
					candidateModules.push(module);
				}
			private:
				ArrayList<ir::Module*>& candidateModules;
			};

			class CandidatesProvider: public ILocalizationParamProvider{
			public:
				CandidatesProvider(ArrayList< Pair<ir::Module*, ir::ExportName> >& candidateNames)
					: candidateNames(candidateNames){
				}

				void accept(ILocalizationParamVisitor& visitor){
					for ( auto enumerator = candidateNames.enumerate(); enumerator.hasNext(); enumerator.advance() ){
						visitor.visitValue("candidate", enumerator.get().second.makeSymbol(enumerator.get().first));
					}
				}
			private:
				ArrayList< Pair<ir::Module*, ir::ExportName> >& candidateNames;
			};

			void NameResolver::resolveNames(){
				auto names = module->importNames;
				size_t n = names.getSize();
				ArrayList<ir::Module*> candidateModules(tempPool);
				ArrayList< Pair<ir::Module*, ir::ExportName> > variantsNames(tempPool);
				ArrayList< Pair<ir::Module*, ir::ExportName> > candidateNames(tempPool);
				ElementVisitor visitor(candidateModules);

				for ( size_t i = 0; i < n; i++ ){
					auto name = names.get(i);
					ExportName choosenResolution;
					Module* choosenModule = nullptr;
					u32 resolutionsCount = 0;

					if ( name->getNamespace()->isDefaultNamespace() ){
						auto exportName = module->exportMap->get(name->getName());
						if ( exportName ){
							variantsNames.push(Pair<ir::Module*, ir::ExportName>(module, exportName));
							switch ( name->getUsage() ){
							case ImportName::ExtendedClass:
							case ImportName::ConstructorBase:{
								if ( exportName.kind == ExportKind::Class ){
									if ( !choosenResolution ){
										choosenResolution = exportName;
										choosenModule = module;
									}
									candidateNames.push(Pair<ir::Module*, ir::ExportName>(module, exportName));								
								}
							}break;
							case ImportName::ExtendedInterface:
							case ImportName::ImplementedInterface:{
								if ( exportName.kind == ExportKind::Interface ){
									if ( !choosenResolution ){
										choosenResolution = exportName;
										choosenModule = module;
									}
									candidateNames.push(Pair<ir::Module*, ir::ExportName>(module, exportName));									
								}
							}break;
							case ImportName::TypeReference:{
								if ( exportName.isTypeReference() ){
									if ( !choosenResolution ){
										choosenResolution = exportName;
										choosenModule = module;
									}	
									candidateNames.push(Pair<ir::Module*, ir::ExportName>(module, exportName));								
								}
							}break;
							default: unreachable;
							}
						}
					}

					if ( !choosenResolution ){
						auto filter = name->getNamespace()->getFilter();				
						filter->visitElements(ExportTableHashName(name->getName()), visitor);
						for ( auto enumerator = candidateModules.enumerate(); enumerator.hasNext(); enumerator.advance() ){
							auto exportName = enumerator.get()->exportMap->get(name->getName());						
							if ( exportName ){
								variantsNames.push(Pair<ir::Module*, ir::ExportName>(enumerator.get(), exportName));
								switch ( name->getUsage() ){
								case ImportName::ExtendedClass:
								case ImportName::ConstructorBase:{
									if ( exportName.kind == ExportKind::Class ){
										if ( !choosenResolution ){
											choosenResolution = exportName;
											choosenModule = enumerator.get();
										}
										candidateNames.push(Pair<ir::Module*, ir::ExportName>(enumerator.get(), exportName));								
									}
								}break;
								case ImportName::ExtendedInterface:
								case ImportName::ImplementedInterface:{
									if ( exportName.kind == ExportKind::Interface ){
										if ( !choosenResolution ){
											choosenResolution = exportName;
											choosenModule = enumerator.get();
										}
										candidateNames.push(Pair<ir::Module*, ir::ExportName>(enumerator.get(), exportName));									
									}
								}break;
								case ImportName::TypeReference:{
									if ( exportName.isTypeReference() ){
										if ( !choosenResolution ){
											choosenResolution = exportName;
											choosenModule = enumerator.get();
										}	
										candidateNames.push(Pair<ir::Module*, ir::ExportName>(enumerator.get(), exportName));								
									}
								}break;
								default: unreachable;
								}
							}
						}

					
						if ( !choosenResolution ){
							CandidatesProvider provider(variantsNames);
							stream->report(Subsystem("Compiler").at(name->getSrcLoc()).type(DiagnosticType::Error).code("CompilerError.UnresolvedName").parameter<StringLiteral>("name", name->getName()).parameters(provider));
						}else if ( candidateNames.getSize() > 1 ){
							CandidatesProvider provider(candidateNames);
							stream->report(Subsystem("Compiler").at(name->getSrcLoc()).type(DiagnosticType::Error).code("CompilerError.AmbigiousName").parameter<StringLiteral>("name", name->getName()).parameters(provider));
							choosenResolution = ExportName();
						}						
					}
					name->setResolution(choosenModule, choosenResolution);

					candidateModules.clear();
					candidateNames.clear();
					variantsNames.clear();
				}
			}
		}
	}
}