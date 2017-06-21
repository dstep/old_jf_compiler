#include <Support/MemoryAPI.h>
#include <Support/Threading/ThreadLocal.h>

namespace jf{
	static threading::ThreadLocal<MemoryPool> memoryPool;
	ThreadEnableMemoryAPI MainThreadEnableMemoryAPI;
	
	MemoryPool* GetMemoryPool(){
		return memoryPool.get();
	}

	ThreadEnableMemoryAPI::ThreadEnableMemoryAPI()
		: pool(buffer, MemoryPoolInitialSize){ //-V670
		memoryPool.set(&pool);
	}

	ThreadEnableMemoryAPI::~ThreadEnableMemoryAPI(){
	}
}