#pragma once
#include <Support/MemoryAPI.h>
#include <Support/QualID.h>
#include <Support/Diagnostic.h>
#include <Support/Threading/Atomic.h>
#include <Support/Threading/ThreadPool.h>
#include <Backend/Backend.h>
#include <Backend/BackendModuleInfo.h>
#include "ModuleObject.h"
#include "ModuleExportTableCallback.h"

namespace jf{
	namespace pipeline{
		class Pipeline;
		class ModuleContext;
		class ModuleContextJob;

		#define MaxSourceFileSize 4*(1<<20)

		class ModuleContext: private OwnedPool<>, private threading::ThreadPoolJob{
		public:
			ModuleContext(Pipeline* pipeline, IDiagnosticStream* diagnosticStream, QualID* qid);
			~ModuleContext();

			void newCompilationStarted();
			void requestCompilation();
			void requestInstrCompiler();
			void requestExportTable(IModuleExportTableCallback* callback);

			void runBackendCompiler(backend::IBackendModuleCompiler* compiler);

			bool isCompiled();

			StringRef getRelativeFileName();

			QualID* getQID(){
				return qid;
			}

			MemoryPoolSlice* getPool(){
				return this;
			}

			IDiagnosticStream* getDiagnostic(){
				return currentStream;
			}
		public:
			void resumeCompilation();
			void onImportsSatisfied();
			void resolveNames();
			void instrCompile();
			void addJob(ModuleContextJob* job);

		private:
			void startCompilation();
			void reuseModuleObject();
			void dropModuleObject();
			void reportNoModuleObjectGenerated();
			void parseSourceFile(const StringRef& fullFilePath, const StringRef& relativeFilePath, const file::FileCacheRecord& cacheRecord, const StringRef& content);
			void prepareDataflowOnModule();
			void proceeedToExportReadyStatus();
			void satisfyImports();
			void fallToFatalError();

			void run();
			
			Pipeline* pipeline;
			QualID* qid;
			StringRef fileName;
			IDiagnosticStream* diagnosticStream;
			IDiagnosticStream* currentStream;

			ModuleObject* object;

			OwnedPool<1024> processPool;

			enum Status{
				FatalError = -1,
				NotCompiled = 0,				
				CompilationStarted,
				ExportReady,
				InstrCompileStarted,
				Compiled
			};

			u32 lastStatus;
			threading::AtomicInt status;

			enum RunningStatus{
				NotRunning,
				Running
			};

			threading::AtomicInt runningStatus;
			threading::SpinLock jobsLock;
			threading::AtomicPointer<ModuleContextJob> jobs;
			threading::AtomicPointer<IModuleExportTableCallback> exportTableCallback;

			OwnedPool<> backendsPool;
			struct BackendInfo{
				OwnedPool<> pool;
				backend::BackendModuleInfo* object;

				BackendInfo()
					: object(nullptr){
				}
			};
			HashMap<backend::BackendModuleInfo::ID, BackendInfo*> backendsInfo;
		};
	}
}