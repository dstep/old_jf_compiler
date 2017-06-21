#include <Backend/LLVM/LLVMModuleInfo.h>

namespace jf{
	namespace backend{
		namespace llvm{
			BackendModuleInfo::ID LLVMModuleInfo::ID = "llvm";

			void LLVMModuleInfo::reset(){
				slice.reset();
				archive = nullptr;
			}
		}
	}
}