#pragma once
#include <Support/Diagnostic.h>
#include <IR/Module.h>
#include <Support/Threading/Dataflow.h>

namespace jf{
	namespace ir{
		namespace compiler{
			class JobWrapper{
			public:
				virtual threading::IJob* wrap(threading::IJob* job) = 0;
			};

			class LayoutBuilder{
			public:
				LayoutBuilder(IDiagnosticStream* stream, threading::DataflowManager* dataflow, JobWrapper* jobWrapper, MemoryPoolSlice* tempPool, MemoryPoolSlice* hostPool, MemoryPoolSlice* processPool);

				void run(Module* module);
			private:
				
				threading::DataflowManager* dataflow;
				IDiagnosticStream* stream;
				JobWrapper* jobWrapper;
				MemoryPoolSlice* hostPool;
				MemoryPoolSlice* processPool;
				MemoryPoolSlice* tempPool;
				Module* module;
			};
		}
	}
}