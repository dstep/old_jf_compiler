#include <Support/Macros.h>
#include <Support/Threading/SpinLock.h>
#include <Support/Threading/Atomic.h>

#if defined(JF_PLATFORM_WIN)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
namespace jf{
	namespace threading{
		namespace system{
			class SpinLockImpl{
			public:
				SpinLockImpl()
					: lock(0){
				}
				
				~SpinLockImpl(){
				}

				AtomicInt lock;
			};
		}

		SpinLock::SpinLock()
			: value(0){
		}

		SpinLock::~SpinLock(){
		}

		void SpinLock::lock(){
			do{
			}while(value.compareAndSwap(0, 1) != 0);
		}

		void SpinLock::unlock(){
			value.write(0);
		}
	}
}
#endif