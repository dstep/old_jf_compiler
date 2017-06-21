#pragma once

namespace jf{
	namespace threading{
		namespace system{
			class MonitorImpl;
		}

		class Monitor{
		public:
			Monitor();
			~Monitor();

			void acquire();
			void wait();
			void notify();
			void notifyAll();
			void release();
		private:
			system::MonitorImpl* impl;
		};

		class ScopedMonitorLock{
		public:
			ScopedMonitorLock(Monitor& t)
				: t(t){
				t.acquire();
			}

			~ScopedMonitorLock(){
				t.release();
			}
		private:
			Monitor& t;
		};

		#define synchronized(m) for ( bool done = false; !done; ) for ( jf::threading::ScopedMonitorLock _lock_##__LINE__(m); !done; done = true )
	}
}