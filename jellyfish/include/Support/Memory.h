#pragma once
#include <stdexcept>
#include "Types.h"

namespace jf{
	void* MemoryAllocate(size_t size);
	void MemoryFree(void* ptr);
	
	class OutOfMemoryException: public std::runtime_error{
	public:
		OutOfMemoryException(const char* what) : runtime_error(what) {}
	};

	template<class T>
	class Space{
	public:
		Space(){
		}

		Space(const T& t){
			new(buffer)T(t);
		}

		T* get(){
			return (T*)buffer;
		}

		operator T*(){
			return (T*)buffer;
		}

		T* operator->(){
			return (T*)buffer;
		}
	private:
		u8 buffer[sizeof(T)];
	};
}

