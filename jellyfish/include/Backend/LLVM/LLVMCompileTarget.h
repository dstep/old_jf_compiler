#pragma once

#include "../Backend.h"
#include "LLVMModule.h"
#include <Support/Diagnostic.h>
#include "CompilationTarget.h"

namespace jf{
	namespace backend{
		namespace llvm{
			namespace FileType{
				enum Value{
					Assembly,
					Object
				};
			};

			class LLVMCompileTarget{
			public:
				LLVMCompileTarget();

				ArrayRef<u8> run(IDiagnosticStream* diagnostic, MemoryPoolSlice& tempPool, MemoryPoolSlice* hostPool, ::llvm::Module* module, CompilationTarget::Value target, FileType::Value fileType);
			private:
			};
		}
	}
}