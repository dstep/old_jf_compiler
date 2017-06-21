#pragma once
#include "Remote.h"

namespace jf{
	namespace connect{
		class IJITInjectTarget{
		public:		
			typedef void(*MainFunc)();
				
			virtual Addr allocateCodePage(Size size, Size align) = 0;
			virtual Addr allocateDataPage(Size size, Size align, bool readOnly) = 0;
			virtual void freePage(Addr addr) = 0;
			virtual Addr querySymbol(const char* name) = 0;
			virtual Size writeMemory(Addr addr, Size size, const void* data) = 0;
			virtual Size readMemory(Addr addr, Size size, void* buffer) = 0;
			virtual void commitPage(Addr addr, bool code, bool readOnly) = 0;
			virtual void submitMain(Addr addr) = 0;
		};
	}
}