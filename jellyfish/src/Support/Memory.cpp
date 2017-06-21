#include <Support/Memory.h>
#include <Support/MemoryPool.h>

//#define JF_TRACK_ALLOCATIONS

#if defined(JF_PLATFORM_WIN)
#include <Windows.h>
namespace jf{
	static HANDLE heap = GetProcessHeap();
	
	void* MemoryAllocate(size_t size){	
		void* memory = HeapAlloc(heap, 0, size);
	#if defined(JF_TRACK_ALLOCATIONS)
		printf("Allocating block of size %lld (%p)\n", (u64)size, memory);
	#endif
		if ( !memory ){
			throw OutOfMemoryException("Out of memory");
		}
		return memory;
	}

	void MemoryFree(void* ptr){
	#if defined(JF_TRACK_ALLOCATIONS)
		printf("Freeing block at (%p)\n", ptr);
	#endif
		HeapFree(heap, 0, ptr);
	}
}
#else
namespace jf{
	void* MemoryAllocate(size_t size){
		void* memory = ::malloc(size);			
		if ( !memory ){
			throw OutOfMemoryException("Out of memory");
		}
		return memory;
	}

	void MemoryFree(void* ptr){
		::free(ptr);
	}
}
#endif
