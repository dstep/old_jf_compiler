#include <Support/Threading/ThreadLocal.h>
#include <Support/BuildSettings.h>

#if defined(JF_PLATFORM_WIN)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
namespace jf{
	namespace threading{
		ThreadLocalBase::ThreadLocalBase()
			: impl((void*)TlsAlloc()){
		}

		ThreadLocalBase::~ThreadLocalBase(){
			TlsFree((DWORD)impl);
		}

		void* ThreadLocalBase::get(){
			return TlsGetValue((DWORD)impl);
		}

		void ThreadLocalBase::set(void* ptr){
			TlsSetValue((DWORD)impl, ptr);
		}
	}
}
#endif