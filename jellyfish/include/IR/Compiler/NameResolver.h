#pragma once
#include <Support/Diagnostic.h>
#include <IR/Module.h>

namespace jf{
	namespace ir{
		namespace compiler{
			class NameResolver{
			public:
				NameResolver(IDiagnosticStream* stream, MemoryPoolSlice* tempPool, MemoryPoolSlice* hostPool);

				void run(Module* module);
			private:
				void buildFilters();
				void resolveNames();

				IDiagnosticStream* stream;
				MemoryPoolSlice* hostPool;
				MemoryPoolSlice* tempPool;
				Module* module;
			};
		}
	}
}