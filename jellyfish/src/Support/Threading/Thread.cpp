#include <Support/Threading/Thread.h>
#include <Support/Macros.h>

#if defined(JF_PLATFORM_WIN)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
namespace jf{
	namespace threading{
		namespace system{
			static DWORD WINAPI ThreadProc(LPVOID lpdwThreadParam);

			class ThreadImpl{
			public:
				ThreadImpl(Thread* thread, Runnable* runnable)
					: runnable(runnable){
					threadHandle = CreateThread(nullptr, 0, ThreadProc, this, CREATE_SUSPENDED, nullptr);
				}

				HANDLE threadHandle;
				Runnable* runnable;

				friend static DWORD WINAPI ThreadProc(LPVOID lpdwThreadParam);
			};

			static DWORD WINAPI ThreadProc(LPVOID lpdwThreadParam){
				ThreadImpl* thread = (ThreadImpl*)lpdwThreadParam;
				thread->runnable->run();
				return 0;
			}
		}

		u64 GetThreadID(){
			return ::GetCurrentThreadId();
		}

		Thread::Thread(Runnable* runnable)
			: impl(new system::ThreadImpl(this, runnable))
			, runnable(nullptr){
			run(runnable);			
		}

		Thread::Thread()
			: impl(new system::ThreadImpl(this, runnable))
			, runnable(nullptr){
		}

		Thread::~Thread(){
			join();
			delete impl;
		}

		void Thread::run(Runnable* runnable){
			this->runnable = runnable;
			this->impl->runnable = runnable;
			resume();
		}

		bool Thread::isTerminated(){
			DWORD result = WaitForSingleObject(impl->threadHandle, 0);
			if (result == WAIT_OBJECT_0) {
				return true;
			}else{
				return false;
			}
		}

		void Thread::suspend(){
			SuspendThread(impl->threadHandle);
		}

		void Thread::resume(){
			ResumeThread(impl->threadHandle);
		}

		void Thread::join(){
			WaitForSingleObject(impl->threadHandle, INFINITE);		
		}
	}
}
#endif