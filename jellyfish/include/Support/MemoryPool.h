#pragma once
#include "Types.h"
#include "Memory.h"
#include <stdexcept>

namespace jf{
	class MemoryPoolSlice;

	class MemoryPool{
	public:
		const static size_t DefaultPageSize = 16 * 1024;		
		const static size_t MaxAllocationSize = 256 * 1024 * 1024;
	public:
		MemoryPool(size_t pageSize = 0, size_t toleratedLossPerPage = 0);
		MemoryPool(u8* buffer, size_t size, size_t pageSize = 0, size_t toleratedLossPerPage = 0);
		~MemoryPool();
	private:
		struct Page{
			Page* next;
		#pragma warning(push)
		#pragma warning(disable:4200)
			u8 payload[0];
		#pragma warning(pop)
		};

		size_t pageSize;
		size_t toleratedLossPerPage;
		Page* lastPage;
		u8* memoryPointer;
		u8* memoryLimit;

		friend class MemoryPoolSlice;
	};

	/**
	* If passed by reference to function - no allocations from the pool slice outlives the function call
	* If passed by pointer - allocations from the pool may outlive function call
	*/
	class MemoryPoolSlice{
	public:
		explicit MemoryPoolSlice(MemoryPool* pool);
		MemoryPoolSlice(const MemoryPoolSlice& slice);
		~MemoryPoolSlice();

		void* allocate(size_t size) const;
		void* allocateArray(size_t size, size_t count) const;
		void* allocateDynamic(size_t primarySize, size_t objectSize, size_t objectCount) const;

		void reset();
	private:
		MemoryPoolSlice(MemoryPoolSlice&& slice);
		const MemoryPoolSlice& operator=(const MemoryPoolSlice& slice);
		const MemoryPoolSlice& operator=(MemoryPoolSlice&& slice);

		MemoryPool* pool;
		MemoryPool::Page* lastPage;
		u8* memoryPointer;
		u8* memoryLimit;
	};

	template<size_t N = 4 * 1024>
	class OwnedPool: public MemoryPool, public MemoryPoolSlice{
	public:
		OwnedPool(size_t pageSize = 0, size_t toleratedLossPerPage = 0)
			: MemoryPool(buffer, N, pageSize, toleratedLossPerPage)
			, MemoryPoolSlice(this){
		}
	private:
		u8 buffer[N];
	};
}