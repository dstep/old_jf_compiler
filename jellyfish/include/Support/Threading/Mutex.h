#pragma once
#include "../Types.h"

namespace jf{
	namespace threading{
		namespace system{
			class MutexImpl;
		}

		class Mutex{
		public:
			Mutex();
			~Mutex();
			void lock();
			void unlock();
		private:
			system::MutexImpl* impl;
		};

		class ScopedMutexLock{
		public:
			ScopedMutexLock(Mutex& t)
				: t(t){
				t.lock();
			}

			~ScopedMutexLock(){
				t.unlock();
			}
		private:
			Mutex& t;
		};

		#define acquire_mutex(m) jf::threading::ScopedMutexLock _lock_##__LINE__(m);
	}
}