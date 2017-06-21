#pragma once
#include <Support/Diagnostic.h>
#include <IR/Module.h>
#include <Support/Threading/Dataflow.h>

namespace jf{
	namespace ir{
		namespace compiler{
			class PrepareDataflow{
			public:
				PrepareDataflow();

				void run(Module* module);
			private:
				Module* module;
			};
		}
	}
}