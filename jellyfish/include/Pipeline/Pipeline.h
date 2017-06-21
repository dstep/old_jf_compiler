#pragma once
#include "ProjectSettings.h"
#include <Support/File/FileSystem.h>
#include <Support/Diagnostic.h>
#include <Support/Threading/Mutex.h>
#include <Support/Threading/ThreadPool.h>
#include <Support/Threading/Dataflow.h>
#include "ModuleExportTableCallback.h"

namespace jf{
	namespace ir{
		class Module;
		class GlobalFunction;
	}

	namespace pipeline{
		class ModuleContext;
		struct ModuleSource;

		class Pipeline{
		public:
			Pipeline(IDiagnosticStream* diagnosticStream, threading::ThreadPool* pool);

			void setWorkingDirectory(const StringRef& path);
			bool runWithProjectPath(const StringRef& projectPath);
			void runInstrCompiler();
			ModuleContext* getModule(QualID* qid);

			ProjectSettings* getProjectSettings(){
				return settings;
			}

			threading::DataflowManager* getDataflow(){
				return &dataflow;
			}

			threading::ThreadPool* getThreadPool(){
				return threadPool;
			}

			ArrayRef<ModuleSource*> getModuleSources(){
				return moduleSources;
			}

			StringRef getFullPathToWorkingDirectory(){
				return workingDirectory;
			}

			StringRef getIntermediateDirectoryPath(){
				return intermediateDirectory;
			}

			template<class Func>
			void iterateModules(Func&& func){
				modules.traverseInorder(func);
			}

			ir::GlobalFunction* getMainFunction(){
				return mainFunction;
			}
		private:
			void onMainModuleExportReady(ir::Module* module);

			void run();

			class MainModuleExportTableReady: public IModuleExportTableCallback{
			public:
				MainModuleExportTableReady(Pipeline* pipeline)
					: pipeline(pipeline){
				}

				void onReady(ir::Module* module){
					pipeline->onMainModuleExportReady(module);
				}

				void onNeverReady(){
				}
			private:
				Pipeline* pipeline;
			} mainModuleReadyCallback;

			IDiagnosticStream* diagnosticStream;

			OwnedPool<> settingsPool;
			ProjectSettings* settings;	
			StringRef settingsPath;		
			file::FileCacheRecord settingsCacheRecord;
			ArrayRef<ModuleSource*> moduleSources;

			OwnedPool<> workingDirectoryPool;
			StringRef workingDirectory;
			StringRef intermediateDirectory;

			threading::ThreadPool* threadPool;

			threading::DataflowManager dataflow;

			threading::Mutex modulesMutex;
			ModuleContext* mainModule;
			ir::GlobalFunction* mainFunction;
			container::SearchTree<StringRef, ModuleContext*, StringRef::Compare> modules; 
		};
	}
}