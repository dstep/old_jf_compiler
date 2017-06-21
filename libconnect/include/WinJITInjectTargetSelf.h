#pragma once
#include "IJITInjectTarget.h"

namespace jf{
	namespace connect{
		IJITInjectTarget* CreateWinJITTargetSelf(IJITInjectTarget::MainFunc* funcPtr);
		void DestroyWinJITTargetSelf(IJITInjectTarget* target);
	}
}