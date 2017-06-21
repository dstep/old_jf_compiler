#include <Support/Macros.h>
#include <Support/Threading/Mutex.h>
#include <Support/Memory.h>

#if defined(JF_PLATFORM_WIN)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
namespace jf{
	namespace threading{
		namespace system{
			class MutexImpl{
			public:
				MutexImpl(){
					InitializeCriticalSection(&cs);
				}
				
				~MutexImpl(){
					DeleteCriticalSection(&cs);
				}

				CRITICAL_SECTION cs;
			};
		}

		Mutex::Mutex()
			: impl(new(MemoryAllocate(sizeof(system::MutexImpl)))system::MutexImpl()){
		}

		Mutex::~Mutex(){
			impl->~MutexImpl();
			MemoryFree(impl);
		}

		void Mutex::lock(){
			EnterCriticalSection(&impl->cs);
		}

		void Mutex::unlock(){
			LeaveCriticalSection(&impl->cs);
		}
	}
}
#endif