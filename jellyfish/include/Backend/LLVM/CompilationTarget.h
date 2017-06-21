#pragma once
#include <llvm/Target/TargetMachine.h>
#include <Support/Diagnostic.h>

namespace jf{
	namespace backend{
		namespace llvm{
			namespace CompilationTarget{
				enum Value{
					Win32,
					Win64
				};
			}

			::llvm::TargetMachine* CreateTargetMachine(IDiagnosticStream* diagnostic, CompilationTarget::Value target);
		}
	}
}