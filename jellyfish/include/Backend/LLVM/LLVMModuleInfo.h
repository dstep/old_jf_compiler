#pragma once
#include <Support/Types.h>
#include "../BackendModuleInfo.h"
#include "ModuleArchive.h"

namespace jf{
	namespace backend{
		namespace llvm{
			class LLVMModuleInfo: public BackendModuleInfo{
			public:
				static BackendModuleInfo::ID ID;

				LLVMModuleInfo(MemoryPoolSlice* pool)
					: BackendModuleInfo(ID)
					, slice(*pool)
					, archive(nullptr){
				}

				void reset();

				ModuleArchive* archive;
			private:
				MemoryPoolSlice slice;
			};
		}
	}
}