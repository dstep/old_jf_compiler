#include <Support/Macros.h>
#include <Support/Threading/Atomic.h>

#if defined(JF_PLATFORM_WIN)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
namespace jf{
	namespace threading{
		namespace system{		
			s32 CompareAndSwap(s32 volatile * pointer, s32 compare, s32 swap){
				return (s32)InterlockedCompareExchange((u32 volatile *)pointer, swap, compare);
			}

			s64 CompareAndSwap(s64 volatile * pointer, s64 compare, s64 swap){
				return InterlockedCompareExchange64(pointer, swap, compare);
			}

			void* CompareAndSwap(void* volatile * pointer, void* compare, void* swap){
				return InterlockedCompareExchangePointer(pointer, swap, compare);
			}
			
			s32 AtomicIncrement(s32 volatile* pointer){
				return InterlockedIncrement((u32 volatile *)pointer);
			}

			s32 AtomicDecrement(s32 volatile* pointer){
				return InterlockedDecrement((u32 volatile *)pointer);
			}	
		}
	}
}
#else
#	error Primitives for your system are not defined
#endif