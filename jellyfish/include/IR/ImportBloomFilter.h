#pragma once
#include <Support/Container/BloomFilter.h>
#include <Support/Container/CascadeBloomFilter.h>
#include <Support/StringRef.h>

namespace jf{
	namespace ir{
		class ImportModule;
		class Module;
		
		typedef BloomFilter<1024, 7> ExportTableFilter;

		typedef CascadeBloomFilter<ExportTableFilter, Module*> ImportFilter;

		void ImportModuleFilterConstructor(ExportTableFilter* filter, ImportModule* module);

		Module* ImportModuleElementExtractor(ImportModule* module);

		ExportTableFilter::Hash ExportTableHashName(const StringRef& name);
	}
}