#pragma once
#include <Support/Types.h>

namespace jf{
	namespace backend{
		class BackendModuleInfo{
		public:
			typedef const char* ID;
			BackendModuleInfo(ID tag)
				: tag(tag){
			}
		private:
			ID tag;
		};
	}
}