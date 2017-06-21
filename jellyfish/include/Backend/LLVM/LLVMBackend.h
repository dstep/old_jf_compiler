#pragma once

#include "../Backend.h"
#include <IR/Instr/FunctionFrame.h>
#include "FunctionCompiler.h"

namespace jf{
	namespace backend{
		namespace llvm{
			class LLVMContext;
			class LLVMModule;

			class LLVMBackend: public IBackendModuleCompiler{
			public:
				LLVMBackend(MemoryPoolSlice* tempPool, LLVMContext* context, LLVMModule* module);

				BackendModuleInfo::ID getBackendID();
				void visitModule(ir::Module* module, ir::GlobalFunction* mainFunction, MemoryPoolSlice* pool, BackendModuleInfo*& moduleInfo);
			private:
				LLVMContext* context;
				LLVMModule* module;
				MemoryPoolSlice* tempPool;

				FunctionCompiler functionCompiler;
			};
		}
	}
}