#pragma once
#include "Thread.h"
#include "Monitor.h"
#include "Atomic.h"
#include "SpinLock.h"

namespace jf{
	namespace threading{
		class ThreadContext{
		public:
			virtual void* initializeCurrentThread() = 0;
			virtual void destroyCurrentThread(void*) = 0;
		};

		class ThreadPool;

		class ThreadPoolJob{
		public:
			virtual void run() = 0;

		private:
			friend class ThreadPool;
			ThreadPoolJob* nextJob;
		};

		class ThreadPoolWorker: public Runnable{
		public:
			ThreadPoolWorker(ThreadPool* owner, ThreadContext* threadContext);
			~ThreadPoolWorker();

			void run();
		private:
			ThreadPool* owner;
			ThreadContext* threadContext;
			void* contextUserdata;
			Thread thread;
			Monitor monitor;
			volatile bool terminate;

			friend class ThreadPool;
			ThreadPoolWorker* nextWorker;
			void runJob(ThreadPoolJob* job);
			threading::AtomicPointer<ThreadPoolJob> job;
		};

		class ThreadPool{
		public:
			ThreadPool(ThreadContext* threadContext, size_t threadsCount);
			~ThreadPool();

			void addJob(ThreadPoolJob* job);

			void join();
		private:
			void createWorker();

			ThreadContext* threadContext;

			friend class ThreadPoolWorker;
			ThreadPoolJob* pullJob(ThreadPoolWorker* worker);

			threading::SpinLock workerLock;
			threading::AtomicPointer<ThreadPoolWorker> workers;
			threading::AtomicPointer<ThreadPoolJob> jobs;
			threading::AtomicInt runningThreads;
			threading::Monitor jobDoneMonitor;
		};
	}
}