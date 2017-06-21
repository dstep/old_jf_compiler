#include <IR/ImportBloomFilter.h>
#include <IR/Module.h>

namespace jf{
	namespace ir{
		void ImportModuleFilterConstructor(ExportTableFilter* filter, ImportModule* module){
			Module* resolvedModule = module->getResolvedModule();
			if ( resolvedModule ){
				*filter = resolvedModule->exportFilter;
			}else{
				new(filter)ExportTableFilter();
			}
		}
		
		Module* ImportModuleElementExtractor(ImportModule* module){
			return module->getResolvedModule();
		}

		ExportTableFilter::Hash ExportTableHashName(const StringRef& name){
			return ExportTableFilter::hash(name.getData(), name.getLength());
		}
	}
}