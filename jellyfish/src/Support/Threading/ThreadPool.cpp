#include <Support/Threading/ThreadPool.h>

namespace jf{
	namespace threading{
		ThreadPoolWorker::ThreadPoolWorker(ThreadPool* owner, ThreadContext* threadContext)
			: owner(owner)
			, threadContext(threadContext)
			, terminate(false)
			, nextWorker(nullptr)
			, job(nullptr){

			thread.run(this);
		}

		ThreadPoolWorker::~ThreadPoolWorker(){
			terminate = true;
			synchronized(monitor){
				monitor.notifyAll();
			}
			thread.join();
		}

		void ThreadPoolWorker::run(){
			contextUserdata = threadContext->initializeCurrentThread();

			while ( !terminate ){
				ThreadPoolJob* job = this->job.read();
				if ( job ){
					this->job.write(nullptr);
					while ( job ){
						job->run();
						job = owner->pullJob(this);
					}
				}
				synchronized(monitor){
					if ( !terminate ){
						monitor.wait();
					}					
				}
			}

			threadContext->destroyCurrentThread(contextUserdata);
		}

		void ThreadPoolWorker::runJob(ThreadPoolJob* job){
			this->job.write(job);
			synchronized(monitor){
				monitor.notifyAll();
			}
		}

		ThreadPool::ThreadPool(ThreadContext* threadContext, size_t threadsCount)
			: threadContext(threadContext)
			, workers(nullptr)
			, jobs(nullptr)
			, runningThreads(0){

			for ( size_t i = 0; i < threadsCount; i++ ){
				createWorker();
			}
		}

		ThreadPool::~ThreadPool(){
			join();
			ThreadPoolWorker* firstWorker;
			do{
				firstWorker = workers.read();
			}while ( workers.compareAndSwap(firstWorker, nullptr) != firstWorker );
			while ( firstWorker ){
				ThreadPoolWorker* nextWorker = firstWorker->nextWorker;
				delete firstWorker;
				firstWorker = nextWorker;
			}
		}

		void ThreadPool::addJob(ThreadPoolJob* job){
			ThreadPoolWorker* freeWorker;
			{
				acquire_lock(workerLock);
			
				freeWorker = workers.read();
				if ( !freeWorker ){
					job->nextJob = jobs.read();
					jobs.write(job);
					synchronized(jobDoneMonitor){
						jobDoneMonitor.notifyAll();
					}
					return;
				}
				workers.write(freeWorker->nextWorker);
				runningThreads.increment();
			}
			freeWorker->runJob(job);
		}
		
		ThreadPoolJob* ThreadPool::pullJob(ThreadPoolWorker* worker){
			ThreadPoolJob* job;
			{
				acquire_lock(workerLock);

				job = jobs.read();
				if ( !job ){
					worker->nextWorker = workers.read();
					workers.write(worker);
					if ( !runningThreads.decrement() ){
						synchronized(jobDoneMonitor){
							jobDoneMonitor.notifyAll();
						}
					}
					return nullptr;
				}
				jobs.write(job->nextJob);
			}
			return job;
		}

		void ThreadPool::join(){
			while ( true ){
				ThreadPoolJob* job = nullptr;
				synchronized(jobDoneMonitor){
					{
						acquire_lock(workerLock);
						job = jobs.read();
						if ( job ){
							jobs.write(job->nextJob);
						}
					}

					if ( job ){
						goto performJob;
					}
				
					if ( runningThreads.read() == 0 ){
						return;
					}

					jobDoneMonitor.wait();
				}
			performJob:
				if ( job ){
					job->run();
					job = nullptr;
				}
			}
		}

		void ThreadPool::createWorker(){
			ThreadPoolWorker* newWorker = new ThreadPoolWorker(this, threadContext);
			do{
				newWorker->nextWorker = workers.read();
			}while ( workers.compareAndSwap(newWorker->nextWorker, newWorker) != newWorker->nextWorker );
		}		
	}
}