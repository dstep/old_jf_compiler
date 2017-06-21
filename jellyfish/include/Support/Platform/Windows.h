#pragma once
#include "../StringRef.h"
#include "../MemoryPool.h"
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

namespace jf{
	namespace platform{
		wchar_t* Widen(MemoryPoolSlice* pool, const StringRef& string);
		StringRef Narrow(MemoryPoolSlice* pool, wchar_t* wideString);
	}
}