#pragma once
#include <cstdint>
#include <vector>
#include "Remote.h"

namespace jf{
	namespace connect{
		class IThreadVisitor;

		class IDebugTargetCallback{
		public:
			virtual void onBreakpoint() = 0;
			virtual void onException() = 0;
			virtual void onExit() = 0;
		};
		
		class IDebugTarget{
		public:
			
	
			enum MemoryPermission{
				MemoryRead = 1,
				MemoryWrite = 2,
				MemoryExecute = 4,
				MemoryRW = MemoryRead | MemoryWrite,
				MemoryRWX = MemoryRW | MemoryExecute
			};

			virtual void setCallback(IDebugTargetCallback* callback) = 0;
	
			virtual Addr allocateMemory(Size size, Size align, MemoryPermission permission) = 0;
			virtual bool freeMemory(Addr addr) = 0;
			virtual bool setMemoryPermissions(Addr addr, MemoryPermission permission) = 0;
			virtual Size writeMemory(Addr addr, Size size, const void* buffer) = 0;
			virtual Size readMemory(Addr addr, Size size, void* buffer) = 0;

			virtual Addr querySymbol(const char* name, Size nameLength) = 0;

			typedef uint64_t ThreadID;

			enum ThreadStatus{
				ThreadRunning,
				ThreadSuspended,
				ThreadTerminated
			};

			virtual bool debugSuspend(uint64_t timeout) = 0;
			virtual bool debugResume(uint64_t timeout) = 0;

			virtual void debugWait(uint64_t timeout) = 0;

			virtual void enumerateThreads(IThreadVisitor& visitor) = 0;

			virtual void suspendProcess() = 0;
			
			virtual ThreadID execute(Addr addr) = 0;
			virtual ThreadID execute1(Addr addr, Word param) = 0;	

			virtual void detach() = 0;
	
			virtual ThreadStatus getThreadStatus(ThreadID thread) = 0;	
			virtual void suspendThread(ThreadID thread) = 0;
			virtual void resumeThread(ThreadID thread) = 0;
			virtual void terminateThread(ThreadID thread) = 0;
		
			virtual Word readRegister(ThreadID thread, const char* reg) = 0;
			virtual void writeRegister(ThreadID thread, const char* reg, Word word) = 0;
		};

		class IThreadVisitor{
		public:
			virtual void notifyThreadCount(uint64_t count) = 0;
			virtual void visitThread(uint64_t index, IDebugTarget::ThreadID thread) = 0;
		};
	}
}