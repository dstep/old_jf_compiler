#include <Backend/LLVM/ModuleArchive.h>

namespace jf{
	namespace backend{
		namespace llvm{
			ModuleArchive::ModuleArchive(const ArrayRef<u8>& data)
				: data(data){
			}
		}
	}
}