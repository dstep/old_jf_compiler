#pragma once
#include "Memory.h"
#include "MemoryPool.h"

namespace jf{
	MemoryPool* GetMemoryPool();

	class ThreadEnableMemoryAPI{
		static const size_t MemoryPoolInitialSize = 1024 * 1024;
	public:
		ThreadEnableMemoryAPI();
		~ThreadEnableMemoryAPI();
	private:
		MemoryPool pool;
		u8 buffer[MemoryPoolInitialSize];
	};

	extern ThreadEnableMemoryAPI MainThreadEnableMemoryAPI;
}