#pragma once
#include "IDebugTarget.h"
#define nominmax
#include <Windows.h>

namespace jf{
	namespace connect{
		IDebugTarget* CreateWinDebugTargetRemote(HANDLE process, bool is32Bits);
		void DestroyWinDebugTargetRemote(IDebugTarget* target);
	}
}