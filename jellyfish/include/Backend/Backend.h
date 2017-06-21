#pragma once
#include <IR/Module.h>
#include <IR/Instr/Instr.h>

#include "BackendModuleInfo.h"

namespace jf{
	namespace backend{
		class IBackendModuleCompiler{
		public:
			virtual BackendModuleInfo::ID getBackendID() = 0;
			virtual void visitModule(ir::Module* module, ir::GlobalFunction* mainFunction, MemoryPoolSlice* backendPool, BackendModuleInfo*& backendInfo) = 0;
		};
	}
}