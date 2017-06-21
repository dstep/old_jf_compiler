#include "IDebugTarget.h"
#include <Windows.h>
#include <Psapi.h>
#include <map>

#include "WinDebugTargetRemote.h"

namespace jf{
	namespace connect{
		class WinDebugTargetRemoteProcess: public IDebugTarget{
		
			struct Allocation{
				Addr addr;
				Size size;
				MemoryPermission permissions;
			};

			struct ThreadInfo{
				HANDLE handle;
				DWORD threadID;
			};

		public:
			WinDebugTargetRemoteProcess(HANDLE processHandle)
				: processHandle(processHandle)
				, externalBreakpoint(false){

				SYSTEM_INFO systemInfo;
				GetSystemInfo(&systemInfo);
				
				workBuffer = allocateMemory(4 * 1024, 0, MemoryRW);

				debugSuspend(INFINITE);

				DWORD bytesNeeded = 0;
				modules.resize(1024);
				if ( EnumProcessModulesEx(processHandle, &modules.at(0), (DWORD)(sizeof(HMODULE) * modules.size()), &bytesNeeded, LIST_MODULES_ALL) != FALSE ){
					modules.resize(bytesNeeded / sizeof(HMODULE));
					EnumProcessModulesEx(processHandle, &modules.at(0), bytesNeeded, &bytesNeeded, LIST_MODULES_ALL);
				}else{
					modules.resize(0);
				}
			}

			~WinDebugTargetRemoteProcess(){
				freeMemory(workBuffer);
			}

			Addr allocateMemory(Size size, Size align, MemoryPermission permission){
				void* addr = VirtualAllocEx(processHandle, nullptr, size, MEM_COMMIT | MEM_RESERVE, getMemoryProtection(permission));
				if ( !addr ){
					return (Addr)0;
				}
				Allocation allocation;
				allocation.addr = (Addr)addr;
				allocation.size = size;
				allocation.permissions = permission;
				allocations.insert(std::make_pair((Addr)addr, allocation));
				return (Addr)addr;
			}

			bool freeMemory(Addr addr){
				auto it = allocations.find(addr);
				if ( it != allocations.end() ){
					return VirtualFreeEx(processHandle, (void*)addr, it->second.size, MEM_RELEASE) == TRUE;
				}else{
					return false;
				}
			}

			bool setMemoryPermissions(Addr addr, MemoryPermission permission){
				auto it = allocations.find(addr);
				if ( it != allocations.end() ){
					DWORD oldProt;
					return VirtualProtectEx(processHandle, (void*)addr, it->second.size, getMemoryProtection(permission), &oldProt) == TRUE;
				}else{
					return false;
				}
			}

			Size writeMemory(Addr addr, Size size, const void* buffer){
				Size bytesWritten = 0;
				if ( WriteProcessMemory(processHandle, (void*)addr, buffer, size, &bytesWritten) ){
					return bytesWritten;
				}else{
					return 0;
				}
			}

			Size readMemory(Addr addr, Size size, void* buffer){
				Size bytesRed = 0;
				if ( ReadProcessMemory(processHandle, (void*)addr, buffer, size, &bytesRed) ){
					return bytesRed;
				}else{
					return 0;
				}
			}

			ThreadID execute(Addr addr){
				DWORD threadId;
				HANDLE threadHandle = CreateRemoteThread(processHandle, NULL, 0, (LPTHREAD_START_ROUTINE)addr, NULL, 0, &threadId);
				if ( threadHandle != INVALID_HANDLE_VALUE ){
					return (ThreadID)threadHandle;
				}else{
					return 0;
				}
			}

			ThreadID execute1(Addr addr, Word param){
				DWORD threadId;
				HANDLE threadHandle = CreateRemoteThread(processHandle, NULL, 0, (LPTHREAD_START_ROUTINE)addr, (void*)param, 0, &threadId);
				if ( threadHandle != INVALID_HANDLE_VALUE ){
					return (ThreadID)threadHandle;
				}else{
					return 0;
				}
			}

			Addr querySymbol(const char* name, Size nameLength){
				for ( auto module : modules ){
					FARPROC proc = getRemoteProcAddr(processHandle, module, name);
					if ( proc ){
						return (Addr)proc;
					}
				}
				return (Addr)0;
			}

			void enumerateThreads(IThreadVisitor& visitor){
				uint64_t i = 0;
				visitor.notifyThreadCount(threads.size());
				for ( auto thread : threads ){
					visitor.visitThread(i++, thread.first);
				}
			}

			void suspendProcess(){
				class ThreadVisitor: public IThreadVisitor{
				public:
					ThreadVisitor(WinDebugTargetRemoteProcess* debugTarget)
						: debugTarget(debugTarget){
					}

					void notifyThreadCount(uint64_t count){
					}

					void visitThread(uint64_t index, IDebugTarget::ThreadID thread){
						debugTarget->suspendThread(thread);
					}
				private:
					WinDebugTargetRemoteProcess* debugTarget;
				} visitor(this);
				enumerateThreads(visitor);
			}

			bool debugSuspend(uint64_t timeout){
				if ( DebugBreakProcess(processHandle) ){
					externalBreakpoint = true;
					breakPointEvent = false;
					while ( !breakPointEvent ){
						debugWaitForEvent(timeout);
					}
					return true;
				}else{
					return false;
				}
			}

			void debugWait(uint64_t timeout){
				debugWaitForEvent(timeout);
			}

			bool debugResume(uint64_t timeout){				
				return ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE) != FALSE;
			}

			void detach(){
				DebugActiveProcessStop(GetProcessId(processHandle));
			}
	
			bool debugWaitForEvent(uint64_t timeout){
				DEBUG_EVENT event;
				DWORD continueStatus = DBG_CONTINUE;

				if ( WaitForDebugEvent(&event, (DWORD)timeout) ){
					debugEvent = event;

					switch ( event.dwDebugEventCode ){
					case EXCEPTION_DEBUG_EVENT:{
						switch ( event.u.Exception.ExceptionRecord.ExceptionCode ){
						case EXCEPTION_BREAKPOINT:{
							if ( externalBreakpoint ){
								externalBreakpoint = false;
							}else{
								callback->onBreakpoint();
							}
							continueStatus = 0;
							breakPointEvent = true;
						}break;
						default:{
							callback->onException();
							continueStatus = 0;
						}break;
						}
					}break;					
					case CREATE_PROCESS_DEBUG_EVENT:{
						HANDLE handle = event.u.CreateProcessInfo.hThread;
						ThreadInfo threadInfo;
						threadInfo.handle = handle;
						threadInfo.threadID = event.dwThreadId;
						threads.insert(std::make_pair(event.dwThreadId, threadInfo));
					}break;
					case CREATE_THREAD_DEBUG_EVENT:{
						HANDLE handle = event.u.CreateThread.hThread;
						ThreadInfo threadInfo;
						threadInfo.handle = handle;
						threadInfo.threadID = event.dwThreadId;
						threads.insert(std::make_pair(event.dwThreadId, threadInfo));
					}break;
					case EXIT_PROCESS_DEBUG_EVENT:{
						callback->onExit();
					}break;
					case EXIT_THREAD_DEBUG_EVENT:{
						threads.erase(event.dwThreadId);
					}break;
					}
					if ( continueStatus ){
						ContinueDebugEvent(event.dwProcessId, event.dwThreadId, continueStatus);
					}
					return true;
				}
				return false;
			}

			ThreadInfo* findThreadInfo(ThreadID thread){
				auto it = threads.find((DWORD)thread);
				if ( it == threads.end() ){
					return nullptr;
				}else{
					return &it->second;
				}
			}

			ThreadStatus getThreadStatus(ThreadID thread){
				ThreadInfo* threadInfo = findThreadInfo(thread);
				if ( threadInfo ){
					DWORD result = WaitForSingleObject(threadInfo->handle, 0);
					if ( result == WAIT_TIMEOUT ){
						DWORD suspendCounter = SuspendThread(threadInfo->handle);
						ResumeThread(threadInfo->handle);
						if ( suspendCounter > 0 ){
							return ThreadSuspended;
						}else{
							return ThreadRunning;
						}
					}else{
						return ThreadTerminated;
					}
				}else{
					return ThreadTerminated;
				}
			}
			
			void suspendThread(ThreadID thread){
				ThreadInfo* threadInfo = findThreadInfo(thread);
				if ( threadInfo ){
					SuspendThread(threadInfo->handle);
				}
			}

			void resumeThread(ThreadID thread){
				ThreadInfo* threadInfo = findThreadInfo(thread);
				if ( threadInfo ){
					ResumeThread(threadInfo->handle);
				}
			}

			void terminateThread(ThreadID thread){
				ThreadInfo* threadInfo = findThreadInfo(thread);
				if ( threadInfo ){
					TerminateThread(threadInfo->handle, 1);
				}
			}
		
			Word readRegister(ThreadID thread, const char* reg){
				#define reg(name, id) if ( !::strcmp(reg, name) ) return context.id;
				ThreadInfo* threadInfo = findThreadInfo(thread);
				if ( threadInfo ){
					CONTEXT context;
					if ( GetThreadContext(threadInfo->handle, &context) ){
						#include "WinContextRegMapping.inc"
					}
				}
				return 0;
			}

			void writeRegister(ThreadID thread, const char* reg, Word word){
				ThreadInfo* threadInfo = findThreadInfo(thread);
				if ( threadInfo ){
					CONTEXT context;
					if ( GetThreadContext(threadInfo->handle, &context) ){
						#define reg(name, id) if ( !::strcmp(reg, name) ) context.id = word;
						#include "WinContextRegMapping.inc"
						SetThreadContext(threadInfo->handle, &context);
					}
				}
			}

			void setCallback(IDebugTargetCallback* callback){
				this->callback = callback;
			}
		private:
			IDebugTargetCallback* callback;

			bool externalBreakpoint;

			template<class T>
			T Deref(T& addr){
				uint8_t buffer[sizeof(T)];
				if ( readMemory((Addr)&addr, sizeof(T), buffer) != sizeof(T) ){
					DebugBreak();
				}
				return *(T*)buffer;
			}

			uint16_t Deref16(Addr addr){
				uint8_t buffer[2];
				if ( readMemory((Addr)addr, sizeof(buffer), buffer) != 2 ){
					DebugBreak();
				}
				return *(uint16_t*)buffer;
			}

			uint8_t Deref8(Addr addr){
				uint8_t buffer[1];
				if ( readMemory((Addr)addr, sizeof(buffer), buffer) != 1 ){
					DebugBreak();
				}
				return *(uint8_t*)buffer;
			}

			uint32_t Deref32(Addr addr){
				uint8_t buffer[4];
				if ( readMemory((Addr)addr, sizeof(buffer), buffer) != 4 ){
					DebugBreak();
				}
				return *(uint32_t*)buffer;
			}

			int StrCmpRemote(Addr remote, const char* local){
				while ( true ){
					char c1 = Deref8(remote);
					char c2 = *local;
					if ( c1 < c2 )
						return -1;
					if ( c2 < c1 )
						return 1;
					if ( c1 == 0 )
						return 0;
					remote++;
					local++;
				}
			}

			
			FARPROC WINAPI getRemoteProcAddr(HANDLE process, HMODULE hModule, LPCSTR lpProcName ){
				UINT_PTR uiLibraryAddress = 0;
				FARPROC fpResult          = NULL;

				if( hModule == NULL )
					return NULL;

				// a module handle is really its base address
				uiLibraryAddress = (UINT_PTR)hModule;

				__try
				{
					UINT_PTR uiAddressArray = 0;
					UINT_PTR uiNameArray    = 0;
					UINT_PTR uiNameOrdinals = 0;
					PIMAGE_NT_HEADERS pNtHeaders             = NULL;
					PIMAGE_DATA_DIRECTORY pDataDirectory     = NULL;
					PIMAGE_EXPORT_DIRECTORY pExportDirectory = NULL;
			
					// get the VA of the modules NT Header
					pNtHeaders = (PIMAGE_NT_HEADERS)(uiLibraryAddress + Deref(((PIMAGE_DOS_HEADER)uiLibraryAddress)->e_lfanew));

					pDataDirectory = (PIMAGE_DATA_DIRECTORY)&pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ];


					// get the VA of the export directory
					pExportDirectory = (PIMAGE_EXPORT_DIRECTORY)( uiLibraryAddress + Deref(pDataDirectory->VirtualAddress) );
			
					// get the VA for the array of addresses
					uiAddressArray = ( uiLibraryAddress + Deref(pExportDirectory->AddressOfFunctions) );

					// get the VA for the array of name pointers
					uiNameArray = ( uiLibraryAddress + Deref(pExportDirectory->AddressOfNames) );
				
					// get the VA for the array of name ordinals
					uiNameOrdinals = ( uiLibraryAddress + Deref(pExportDirectory->AddressOfNameOrdinals) );

					// test if we are importing by name or by ordinal...
					if( ((DWORD)lpProcName & 0xFFFF0000 ) == 0x00000000 )
					{
						// import by ordinal...

						// use the import ordinal (- export ordinal base) as an index into the array of addresses
						uiAddressArray += ( ( IMAGE_ORDINAL( (DWORD)lpProcName ) - Deref(pExportDirectory->Base) ) * sizeof(DWORD) );

						// resolve the address for this imported function
						fpResult = (FARPROC)( uiLibraryAddress + Deref(uiAddressArray) );
					}
					else
					{
						// import by name...
						DWORD dwCounter = Deref(pExportDirectory->NumberOfNames);
						IMAGE_EXPORT_DIRECTORY ed = Deref(*pExportDirectory);

						while( dwCounter-- )
						{
							char * cpExportedFunctionName = (char *)(uiLibraryAddress + Deref32(uiNameArray));
				
							// test if we have a match...
							if( StrCmpRemote( (Addr)cpExportedFunctionName, lpProcName ) == 0 )
							{
								// use the functions name ordinal as an index into the array of name pointers
								uiAddressArray += ( Deref16( uiNameOrdinals ) * sizeof(DWORD) );
					
								// calculate the virtual address for the function
								fpResult = (FARPROC)(uiLibraryAddress + Deref32( uiAddressArray ));
					
								// finish...
								break;
							}
						
							// get the next exported function name
							uiNameArray += sizeof(DWORD);

							// get the next exported function name ordinal
							uiNameOrdinals += sizeof(WORD);
						}
					}
				}
				__except( EXCEPTION_EXECUTE_HANDLER )
				{
					fpResult = NULL;
				}

				return fpResult;
			}

			DWORD getMemoryProtection(MemoryPermission permission){
				switch ( permission ){
				case MemoryRead:{
					return PAGE_READONLY;
				}break;
				case MemoryRW:
				case MemoryWrite:{
					return PAGE_READWRITE;
				}break;
				case MemoryExecute:{
					return PAGE_EXECUTE;
				}break;
				case MemoryRWX:{
					return PAGE_EXECUTE_READWRITE;
				}break;
				default:{
					return PAGE_NOACCESS;
				}break;
				}
			}

			HANDLE processHandle;

			std::map<Addr, Allocation> allocations;
			std::map<DWORD, ThreadInfo> threads;
			std::vector<HMODULE> modules;
			Size pageSize;
			Addr workBuffer;
			DEBUG_EVENT debugEvent;

			bool breakPointEvent;
		};

		IDebugTarget* CreateWinDebugTargetRemote(HANDLE process, bool is32Bits){
			return new WinDebugTargetRemoteProcess(process);
		}

		void DestroyWinDebugTargetRemote(IDebugTarget* target){
			delete (WinDebugTargetRemoteProcess*)target;
		}
	}
}