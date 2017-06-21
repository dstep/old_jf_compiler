#include <Support/Macros.h>
#include <Support/Threading/Monitor.h>
#include <Support/Memory.h>

#if defined(JF_PLATFORM_WIN)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
namespace jf{
	namespace threading{
		namespace system{
			class MonitorImpl{
			public:
				MonitorImpl(){
					InitializeCriticalSection(&cs);
					InitializeConditionVariable(&cv);
				}

				~MonitorImpl(){
					DeleteCriticalSection(&cs);
				}

				CONDITION_VARIABLE cv;
				CRITICAL_SECTION cs;
			};
		}

		Monitor::Monitor()
			: impl(new(MemoryAllocate(sizeof(system::MonitorImpl)))system::MonitorImpl()){
		}

		Monitor::~Monitor(){
			impl->~MonitorImpl();
			MemoryFree(impl);
		}

		void Monitor::acquire(){
			EnterCriticalSection(&impl->cs);
		}

		void Monitor::release(){
			LeaveCriticalSection(&impl->cs);
		}

		void Monitor::wait(){
			SleepConditionVariableCS(&impl->cv, &impl->cs, INFINITE);
		}

		void Monitor::notify(){
			WakeConditionVariable(&impl->cv);
		}

		void Monitor::notifyAll(){
			WakeAllConditionVariable(&impl->cv);
		}
	}
}
#endif