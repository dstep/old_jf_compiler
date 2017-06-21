#pragma once
#include <Support/MemoryAPI.h>
#include <Support/ArrayRef.h>

namespace jf{
	namespace backend{
		namespace llvm{
			class ModuleArchive{
			public:
				ModuleArchive(const ArrayRef<u8>& data);

			private:
				ArrayRef<u8> data;
			};
		}
	}
}