#include <Support/MemoryPool.h>
#include <Support/SafeMath.h>
#include <cassert>

namespace jf{
	MemoryPool::MemoryPool(size_t pageSize, size_t toleratedLossPerPage)
		: memoryLimit(nullptr)
		, memoryPointer(nullptr)
		, lastPage(nullptr)
		, pageSize(pageSize ? (pageSize < sizeof(MemoryPool::Page) ? sizeof(MemoryPool::Page) : pageSize) : DefaultPageSize)
		, toleratedLossPerPage(toleratedLossPerPage ? toleratedLossPerPage : pageSize / 16){
	}

	MemoryPool::MemoryPool(u8* buffer, size_t size, size_t pageSize, size_t toleratedLossPerPage)
		: memoryLimit(buffer + size)
		, memoryPointer(buffer)
		, lastPage(nullptr)
		, pageSize(pageSize ? (pageSize < sizeof(MemoryPool::Page) ? sizeof(MemoryPool::Page) : pageSize) : (size > DefaultPageSize ? size : DefaultPageSize)){
		this->toleratedLossPerPage = toleratedLossPerPage ? toleratedLossPerPage : this->pageSize / 16;
	}
	
	MemoryPool::~MemoryPool(){
		assert(!lastPage);
	}

	MemoryPoolSlice::MemoryPoolSlice(MemoryPool* pool)
		: pool(pool)
		, lastPage(pool->lastPage)
		, memoryPointer(pool->memoryPointer)
		, memoryLimit(pool->memoryLimit){
	}
	
	MemoryPoolSlice::MemoryPoolSlice(const MemoryPoolSlice& slice)
		: pool(slice.pool)
		, lastPage(pool->lastPage)
		, memoryPointer(pool->memoryPointer)
		, memoryLimit(pool->memoryLimit){
	}

	MemoryPoolSlice::~MemoryPoolSlice(){
		reset();
	}

	void MemoryPoolSlice::reset(){
		if ( pool->lastPage != lastPage ){
			do{
				MemoryPool::Page* nextPage = pool->lastPage->next;
				MemoryFree(pool->lastPage);
				pool->lastPage = nextPage;
			}while ( pool->lastPage != lastPage );
			pool->memoryLimit = memoryLimit;
		}
		pool->memoryPointer = memoryPointer;
	}

	void* MemoryPoolSlice::allocate(size_t size) const{
		if ( size > MemoryPool::MaxAllocationSize ){
			throw OutOfMemoryException("Memory request is too large");
		}else{
			size_t availableSize = pool->memoryLimit - pool->memoryPointer;
			if ( availableSize < size ){
				if ( availableSize > pool->toleratedLossPerPage || size > pool->pageSize ){
					MemoryPool::Page* page = (MemoryPool::Page*)MemoryAllocate(size + sizeof(void*));
					page->next = pool->lastPage;
					pool->lastPage = page;
					return page->payload;
				}else{
					MemoryPool::Page* page = (MemoryPool::Page*)MemoryAllocate(pool->pageSize);
					page->next = pool->lastPage;
					pool->lastPage = page;
					pool->memoryLimit = page->payload + pool->pageSize - sizeof(MemoryPool::Page);
					pool->memoryPointer = page->payload;
				}
			}
			size_t consumedSize = size;
			u8* ret = pool->memoryPointer;
			//Fun fact: MSVC can't optimize it:
			//while ( consumedSize % sizeof(size_t) ){
			//	consumedSize++;
			//}
			consumedSize = (consumedSize + sizeof(size_t) - 1) & ~(sizeof(size_t) - 1);
			pool->memoryPointer += consumedSize;
			return ret;
		}
	}

	void* MemoryPoolSlice::allocateArray(size_t size, size_t count) const{
		if ( count == 0 ){
			return allocate(0);
		}
		size_t carry = 0;
		size_t totalSize = multiplyWithCarry(size, count, &carry);
		if ( carry ){
			throw OutOfMemoryException("Array is too large");
		}
		return allocate(totalSize);
	}

	void* MemoryPoolSlice::allocateDynamic(size_t primarySize, size_t objectSize, size_t objectCount) const{
		size_t carry = 0;
		size_t dynamicSize = multiplyWithCarry(objectSize, objectCount, &carry);
		if ( carry ){
			throw OutOfMemoryException("Dynamic is too large");
		}
		size_t totalSize = addWithCarry(dynamicSize, primarySize, &carry);
		if ( carry ){
			throw OutOfMemoryException("Dynamic is too large");
		}
		return allocate(totalSize);
	}
}