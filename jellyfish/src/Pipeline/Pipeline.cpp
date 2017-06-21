#include <Pipeline/Pipeline.h>
#include <Pipeline/ModuleContext.h>
#include <Pipeline/ProjectSettingsParser.h>
#include <Support/Container/ArrayList.h>
#include <Pipeline/ModuleSource.h>

namespace jf{
	namespace pipeline{
		Pipeline::Pipeline(IDiagnosticStream* diagnosticStream, threading::ThreadPool* threadPool)
			: settingsPool(4 * 1024)
			, settings(nullptr)
			, workingDirectoryPool(1, 1)
			, threadPool(threadPool)
			, diagnosticStream(diagnosticStream)
			, mainModuleReadyCallback(this)
			, mainFunction(nullptr){
		}

		void Pipeline::setWorkingDirectory(const StringRef& path){
			MemoryPoolSlice stack(GetMemoryPool());
			workingDirectoryPool.reset();
			workingDirectory = file::ResolveCurrentPath(&workingDirectoryPool, stack, path);
			settingsCacheRecord.reset();
		}

		bool Pipeline::runWithProjectPath(const StringRef& projectPath){
			MemoryPool* pool = GetMemoryPool();
			MemoryPoolSlice stack(pool);
			
			StringRef output;
			StringRef path = file::ResolvePath(&stack, stack, workingDirectory, projectPath);
			if ( !file::IsPathsEqual(path, settingsPath) ){
				settingsCacheRecord.reset();
			}
			switch ( file::ReadFile(&stack, path, settingsCacheRecord, output, 1 * 1024 * 1024, 0) ){
			case file::FileStatus::NotModified:{
				diagnosticStream->report(Subsystem("Project").file(path).type(DiagnosticType::Info).code("Project.NotModified").parameter<StringLiteral>("project", projectPath));
			}break;
			case file::FileStatus::OK:{
				ProjectSettingsParser parser;
				settingsPool.reset();

				settingsPath = path.slice(&settingsPool);
				settings = parser.parse(&settingsPool, output);

				auto errors = parser.getErrors();
				for ( size_t i = 0; i < errors.getSize(); i++ ){
					auto& error = errors.get(i);
					diagnosticStream->report(Subsystem("Project").file(path).at(SrcSpan::Line(error.getLine())).type(DiagnosticType::Error).code(error.getQualCode()).parameter<StringLiteral>("related_text", error.getSource()));
				}
				
				container::ArrayList<ModuleSource*> sources(&stack);
				for ( size_t i = 0; i < settings->sources.getSize(); i++ ){
					StringRef path = file::ResolvePath(&settingsPool, stack, workingDirectory, settings->sources.get(i));
					if ( file::IsDirectory(path) ){
						sources.push(new(settingsPool.allocate(sizeof(ModuleSourceSrcPath))) ModuleSourceSrcPath(path));
					}else{
						diagnosticStream->report
							(
								Subsystem("Project")
								.file(path)
								.type(DiagnosticType::Error)
								.code("Project.InvalidSourcePath")
								.parameter<StringLiteral>("short_path", settings->sources.get(i))
								.parameter<StringLiteral>("full_path", path)
							);
					}
				}
				moduleSources = sources.slice(&settingsPool);
				intermediateDirectory = file::ResolvePath(&settingsPool, stack, workingDirectory, settings->itermediate);
			}break;
			default:{
				diagnosticStream->report
					(
						Subsystem("Project")
						.file(path)
						.type(DiagnosticType::Error)
						.code("Project.Unavailable")
						.parameter<StringLiteral>("project", projectPath)
					);
				return false;
			}break;
			}

			stack.reset();

			modules.traverseInorder([](const StringRef& moduleName, ModuleContext* context){
					context->newCompilationStarted();
				});

			//TODO:: process archives, close non-related, open related
			mainFunction = nullptr;

			if ( settings->main ){
				QualID* mainModule = settings->main->slice(&stack, 0, settings->main->getPartsCount() - 1);
				if ( mainModule ){
					auto module = getModule(mainModule);
					module->requestCompilation();
					this->mainModule = module;
					module->requestExportTable(&mainModuleReadyCallback);					
				}
			}

			run();
			
			return true;
		}

		void Pipeline::onMainModuleExportReady(ir::Module* module){
			ir::ExportName name = module->exportMap->get(settings->main->getPart(settings->main->getPartsCount() - 1));
			if ( name.kind == ir::ExportKind::Function ){
				ir::GlobalFunction* function = (ir::GlobalFunction*)name.reference;
				if ( function->getSignature()->getReturnType().getTag() == ir::TypeTagUnit && function->getSignature()->getParamsCount() == 0 ){
					mainFunction = function;
				}else{
					mainModule->getDiagnostic()->report(Subsystem("Pipeline").at(function->getSrcLoc()).code("CompilerError.InvalidMainSignature"));
				}
			}else{
				mainModule->getDiagnostic()->report(Subsystem("Pipeline").code("CompilerError.NoMainFunction"));
			}
		}

		void Pipeline::runInstrCompiler(){
			{
				acquire_mutex(modulesMutex);
				modules.traverseInorder([](const StringRef&, ModuleContext* context){
						context->requestInstrCompiler();
					});
			}
			run();
		}

		ModuleContext* Pipeline::getModule(QualID* qid){
			assert(qid);
			ModuleContext* module = nullptr;
			bool moduleJustCreated = false;
			{
				acquire_mutex(modulesMutex);
				module = modules.find(qid->asString());
				if ( !module ){
					module = new(MemoryAllocate(sizeof(ModuleContext)))ModuleContext(this, diagnosticStream, qid);
					modules.add(module->getPool(), module->getQID()->asString(), module);
					moduleJustCreated = true;
				}
			}
			if ( moduleJustCreated ){
				diagnosticStream->report(Subsystem("Pipeline").file(qid->asString()).type(DiagnosticType::Info).code("DebugLog").parameter<PlainString>("message", "Module added"));
			}
			return module;
		}

		void Pipeline::run(){
			do{
				threadPool->join();
			}while ( dataflow.join() );
		}
	}
}