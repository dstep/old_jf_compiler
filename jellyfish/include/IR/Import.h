#pragma once
#include <Support/QualID.h>
#include <Support/SourceLoc.h>
#include "ImportBloomFilter.h"
#include "Export.h"

namespace jf{
	namespace ir{
		class Module;

		class ImportModule{
		public:
			ImportModule(const SrcSpan& where, QualID* qid)
				: where(where)
				, qid(qid)
				, resolvedModule(nullptr){
			}

			const SrcSpan& getSrcLoc() const{
				return where;
			}

			QualID* getQID() const{
				return qid;
			}

			void setResolvedModule(Module* module){
				this->resolvedModule = module;
			}

			Module* getResolvedModule(){
				return resolvedModule;
			}
		private:
			SrcSpan where;
			QualID* qid;
			Module* resolvedModule;
		};

		class Namespace{
		public:
			Namespace(const StringRef& name, const ArrayRef<ImportModule*>& modules)
				: name(name)
				, modules(modules){
			}

			const StringRef& getName() const{
				return name;
			}

			const ArrayRef<ImportModule*>& getModules() const{
				return modules;
			}

			ImportFilter* getFilter(){
				return filter;
			}

			bool isDefaultNamespace(){
				return name.getLength() == 0;
			}
		private:
			StringRef name;
			ArrayRef<ImportModule*> modules;
			Space<ImportFilter> filter;
		};

		class ImportName{
		public:
			enum Usage{
				TypeReference,
				ExtendedInterface,
				ImplementedInterface,
				ExtendedClass,
				ConstructorBase
			};

			ImportName(Usage usage, Namespace* ns, const SrcSpan& where, const StringRef& name)
				: usage(usage)
				, ns(ns)
				, name(name)
				, where(where){
			}

			const SrcSpan& getSrcLoc(){
				return where;
			}

			const StringRef& getName(){
				return name;
			}

			const ExportName& getResolution(){
				return resolution;
			}

			Module* getResolutionModule(){
				return resolutionModule;
			}

			void setResolution(Module* resolutionModule, const ExportName& resolution){
				this->resolution = resolution;
				this->resolutionModule = resolutionModule;
			}

			Namespace* getNamespace(){
				return ns;
			}

			Usage getUsage(){
				return usage;
			}
		private:
			Usage usage;			
			Namespace* ns;
			SrcSpan where;
			StringRef name;
			Module* resolutionModule;
			ExportName resolution;
		};
	}
}