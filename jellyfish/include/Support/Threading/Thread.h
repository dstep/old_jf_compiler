#pragma once
#include "../Types.h"

namespace jf{
	namespace threading{
		namespace system{
			class ThreadImpl;
		}

		u64 GetThreadID();

		class Runnable{
		public:
			virtual void run() = 0;
		};

		class Thread{
		public:
			Thread(Runnable* runnable);
			Thread();
			~Thread();

			void run(Runnable* runnanble);

			bool isTerminated();

			void suspend();
			void resume();
			void join();
		private:
			system::ThreadImpl* impl;
			Runnable* runnable;
		};
	}
}