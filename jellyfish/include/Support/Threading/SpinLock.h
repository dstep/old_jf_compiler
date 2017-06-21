#pragma once
#include "../Types.h"
#include "Atomic.h"

/**
* Non-recursive userspace mutex
*/
namespace jf{
	namespace threading{
		class SpinLock{
		public:
			SpinLock();
			~SpinLock();
			void lock();
			void unlock();
		private:
			AtomicInt value;
		};

		class ScopedSpinLock{
		public:
			ScopedSpinLock(SpinLock& t)
				: t(t){
				t.lock();
			}

			~ScopedSpinLock(){
				t.unlock();
			}
		private:
			SpinLock& t;
		};

		#define acquire_lock(m) jf::threading::ScopedSpinLock _lock_##__LINE__(m);
	}
}