#include <Pipeline/ModuleContext.h>
#include <Pipeline/Pipeline.h>
#include <Pipeline/ModuleContextJob.h>
#include <Pipeline/ModuleSource.h>
#include <Parser/RunLexer.h>
#include <Parser/RunParser.h>
#include <Support/Match.h>
#include <IR/Compiler/IRBuilder.h>
#include <IR/Compiler/NameResolver.h>
#include <IR/Compiler/PrepareDataflow.h>
#include <IR/Compiler/LayoutBuilder.h>
#include <IR/Compiler/ModuleInstrCompiler.h>
#include <IR/Import.h>

namespace jf{
	namespace pipeline{
		#define JOB(name, fn) class Job##name: public ModuleContextJob{ \
			public: \
				Job##name(ModuleContext* context) \
					: ModuleContextJob(context){ \
				}\
				\
				void run(){ \
				module->fn(); \
			} } 

		#define NEW_JOB(name) new(processPool.allocate(sizeof(Job##name)))Job##name(this)

		JOB(Resume, resumeCompilation);
		JOB(ResolveNames, resolveNames);
		JOB(InstrCompile, instrCompile);

		ModuleContext::ModuleContext(Pipeline* pipeline, IDiagnosticStream* diagnosticStream, QualID* qid)
			: qid(qid->slice(this))
			, status(NotCompiled)
			, pipeline(pipeline)
			, diagnosticStream(diagnosticStream)
			, runningStatus(NotRunning)
			, jobs(nullptr)
			, object(nullptr)
			, exportTableCallback(nullptr)
			, backendsInfo(&backendsPool){
		}

		ModuleContext::~ModuleContext(){
			dropModuleObject();

			iterate_enumerable(backendInfo, backendsInfo){
				backendInfo.getValue()->~BackendInfo();
			}
		}

		void ModuleContext::newCompilationStarted(){
			lastStatus = status.read();
			if ( lastStatus < ExportReady ){
				diagnosticStream->report(Subsystem("Pipeline").file(qid->asString()).type(DiagnosticType::Info).code("DebugLog").parameter("message", "Module doesn't reach even ExportTable state, so it is dropped"));
				dropModuleObject();
			}
			processPool.reset();
			exportTableCallback.write(nullptr);
			status.write(NotCompiled);
			currentStream = diagnosticStream;
		}

		void ModuleContext::requestCompilation(){
			do{
				u32 oldStatus = status.read();
				if ( oldStatus == NotCompiled ){
					if ( status.compareAndSwap(oldStatus, CompilationStarted) == oldStatus ){
						startCompilation();
						return;
					}
				}else{
					break;
				}
			}while(true);
		}

		void ModuleContext::requestInstrCompiler(){
			do{
				u32 oldStatus = status.read();
				if ( oldStatus == ExportReady ){
					if ( status.compareAndSwap(oldStatus, InstrCompileStarted) == oldStatus ){
						addJob(NEW_JOB(InstrCompile));;
						return;
					}
				}else{
					break;
				}
			}while(true);
		}

		void ModuleContext::startCompilation(){
			addJob(NEW_JOB(Resume));
		}

		StringRef ModuleContext::getRelativeFileName(){
			if ( fileName.isEmpty() ){
				size_t length = qid->asString().getLength();
				u8* buffer = (u8*)allocate(length + 3);
				::memcpy(buffer, qid->asString().getData(), length);
				for ( size_t i = 0; i < length; i++ ){
					if ( buffer[i] == '.' ){
						buffer[i] = '/';
					}
				}
				::memcpy(buffer + length, ".jf", 3);
				fileName = StringRef(buffer, length + 3);
			}
			return fileName;
		}

		void ModuleContext::resumeCompilation(){
			diagnosticStream->report(Subsystem("Pipeline").file(qid->asString()).type(DiagnosticType::Info).code("DebugLog").parameter("message", "Resuming compilation"));
			//TODO:: check for archive
			//TODO:: check for cached result

			//Run lexer and parser
			auto sources = pipeline->getModuleSources();
			{
				MemoryPoolSlice stack(GetMemoryPool());
				
				for ( size_t i = 0; i < sources.getSize(); i++ ){
					match ( sources.get(i) )
						rule(ModuleSourceSrcPath, source)
							StringRef fullFilePath = file::ResolvePath(&stack, stack, source->path, getRelativeFileName());
							StringRef relativeFilePath = file::MakePathRelativeToDirectory(&stack, stack, pipeline->getFullPathToWorkingDirectory(), fullFilePath);

							StringRef fileContents;
							bool fileRead = false;
							file::FileStatus::Value status;
							file::FileCacheRecord cacheRecord;

							if ( object && object->tag == SourceModuleObjectTag ){
								SourceModuleObject* sourceModuleObject = (SourceModuleObject*)object;
								if ( file::IsPathsEqual(sourceModuleObject->filePath, relativeFilePath) ){
									status = file::ReadFile(&stack, fullFilePath, sourceModuleObject->cacheRecord, fileContents, MaxSourceFileSize, sizeof(size_t));
									cacheRecord = sourceModuleObject->cacheRecord;
									fileRead = true;
									if ( status == file::FileStatus::NotModified ){
										reuseModuleObject();
										goto leaveIteration;
									}
								}
							}

							if ( !fileRead ){
								status = file::ReadFile(&stack, fullFilePath, cacheRecord, fileContents, MaxSourceFileSize, sizeof(size_t));
							}

							switch ( status ){
							case file::FileStatus::OK:{
								dropModuleObject();
								parseSourceFile(fullFilePath, relativeFilePath, cacheRecord, fileContents);
								goto leaveIteration;
							}break;
							case file::FileStatus::FileTooLarge:{
								diagnosticStream->report(Subsystem("Pipeline").file(fullFilePath).type(DiagnosticType::Error).code("Module.FileTooLarge"));
								reportNoModuleObjectGenerated();
								goto leaveIteration;
							}break;
							case file::FileStatus::NotAccessible:{
								diagnosticStream->report(Subsystem("Pipeline").file(fullFilePath).type(DiagnosticType::Error).code("Module.FileNotAccessible"));
								reportNoModuleObjectGenerated();
								goto leaveIteration;
							}break;
							case file::FileStatus::NotFound:{
							}break;
							default:{
								assert(false);
							}break;
							}
						erule
						nodefrule
					ematch
				}
				diagnosticStream->report(Subsystem("Pipeline").file(qid->asString()).type(DiagnosticType::Error).code("Module.NotFound"));
				reportNoModuleObjectGenerated();
			leaveIteration:
				;
			}
		}

		class ParserErrorParameres: public ILocalizationParamProvider{
		public:
			ParserErrorParameres(parser::ParserError& error)
				: error(error){
			}

			void acceptExpected(ILocalizationParamVisitor& visitor, parser::ParserErrorExpected* expected){
				if ( expected ){
					acceptExpected(visitor, expected->next);
					visitor.visitLocalizableString("expected", expected->expected);
				}
			}

			void accept(ILocalizationParamVisitor& visitor){
				visitor.visitLocalizableString("token", error.getRelatedToken().getName());
				if ( error.getSecondToken().type != parser::Token::Undefined ){
					visitor.visitLocalizableString("second_token", error.getSecondToken().getName());
				}
				parser::ParserErrorExpected* expected = error.getExpected();
				acceptExpected(visitor, expected);
			}
		private:
			parser::ParserError& error;
		};

		class DiagnosticStreamWrapper: public IDiagnosticStream{
		public:
			DiagnosticStreamWrapper(const StringRef& file, IDiagnosticStream* stream)
				: file(file)
				, stream(stream){
			}

			void report(IDiagnosticContext& context){
				stream->report(DiagnosticFile(context, file));
			}
		private:
			IDiagnosticStream* stream;
			StringRef file;
		};

		void ModuleContext::parseSourceFile(const StringRef& fullFilePath, const StringRef& relativeFilePath, const file::FileCacheRecord& cacheRecord, const StringRef& content){
			SourceModuleObject* sourceModuleObject = new(MemoryAllocate(sizeof(SourceModuleObject)))SourceModuleObject;
			object = sourceModuleObject;
			sourceModuleObject->cacheRecord = cacheRecord;
			sourceModuleObject->filePath = fullFilePath.slice(&object->irPool);

			{
				MemoryPoolSlice stack(GetMemoryPool());
				container::ArrayList<parser::Token>* tokens = container::CreateArray<parser::Token>(&stack);
				container::ArrayList<parser::LexerError>* lexerErrors = container::CreateArray<parser::LexerError>(&stack);
				parser::RunLexer(content, &stack, &sourceModuleObject->definitionPool, stack, tokens, lexerErrors);

				for ( auto e = lexerErrors->enumerate(); e.hasNext(); e.advance() ){
					auto& error = e.get();
					diagnosticStream->report(Subsystem("Lexer").file(fullFilePath).at(error.getSrcLoc()).type(DiagnosticType::Error).code(error.getQualCode()).parameter<StringLiteral>("related_text", error.getRelatedText()));
				}

				container::ArrayList<parser::ParserError>* parserErrors = container::CreateArray<parser::ParserError>(&stack);
				parser::ast::Module* astModule = parser::ParseModule(&stack, &sourceModuleObject->symbolPool, &sourceModuleObject->definitionPool, stack, tokens, parserErrors);
				for ( auto e = parserErrors->enumerate(); e.hasNext(); e.advance() ){
					auto& error = e.get();
					diagnosticStream->report(Subsystem("Parser").file(fullFilePath).at(error.getSrcLoc()).type(DiagnosticType::Error).code(error.getQualCode()).parameters(ParserErrorParameres(error)));
				}

				currentStream = new(processPool.allocate(sizeof(DiagnosticStreamWrapper)))DiagnosticStreamWrapper(object->filePath, diagnosticStream);
				ir::compiler::IRBuilder builder(currentStream, &stack, &sourceModuleObject->irPool, &sourceModuleObject->definitionPool);
				sourceModuleObject->module = builder.build(astModule);
				sourceModuleObject->module->qid = qid;
				sourceModuleObject->module->fileName = sourceModuleObject->filePath;
			}

			

			object = sourceModuleObject;
			prepareDataflowOnModule();
			proceeedToExportReadyStatus();
			satisfyImports();
		}
		
		void ModuleContext::reuseModuleObject(){
			currentStream = new(processPool.allocate(sizeof(DiagnosticStreamWrapper)))DiagnosticStreamWrapper(object->filePath, diagnosticStream);
			currentStream->report(Subsystem("Pipeline").type(DiagnosticType::Info).code("DebugLog").parameter<PlainString>("message", "Reusing previous module object"));
			
			prepareDataflowOnModule();
			proceeedToExportReadyStatus();
			satisfyImports();
		}

		void ModuleContext::prepareDataflowOnModule(){
			ir::compiler::PrepareDataflow prepareDataflow;
			prepareDataflow.run(object->module);
		}

		class ExportTableCallback: public IModuleExportTableCallback{
		public:
			ExportTableCallback(ModuleContext* ownerContext, ir::ImportModule* targetModule, threading::AtomicInt* counter)
				: ownerContext(ownerContext)
				, targetModule(targetModule)
				, counter(counter){
			}

			void onReady(ir::Module* module){
				targetModule->setResolvedModule(module);
				countdown();
			}

			void onNeverReady(){
				targetModule->setResolvedModule(nullptr);
				countdown();
			}

			void countdown(){
				if ( !counter->decrement() ){
					ownerContext->onImportsSatisfied();
				}
			}

			ModuleContext* ownerContext;
			ir::ImportModule* targetModule;
			threading::AtomicInt* counter;
		};

		void ModuleContext::satisfyImports(){
			auto imports = object->module->imports;
			size_t n = imports.getSize();
			threading::AtomicInt* counter = new(processPool.allocate(sizeof(threading::AtomicInt)))threading::AtomicInt((u32)n + 1);
			for ( size_t i = 0; i < n; i++ ){
				ModuleContext* targetModuleContext = pipeline->getModule(imports[i]->getQID());
				targetModuleContext->requestCompilation();
				ExportTableCallback* callback = new(processPool.allocate(sizeof(ExportTableCallback)))ExportTableCallback(this, imports[i], counter);
				targetModuleContext->requestExportTable(callback);
			}
			if ( !counter->decrement() ){
				onImportsSatisfied();
			}
		}

		void ModuleContext::onImportsSatisfied(){
			addJob(NEW_JOB(ResolveNames));
		}

		class JobProxy: public threading::IJob, private ModuleContextJob{
		public:
			JobProxy(ModuleContext* context, threading::IJob* job)
				: ModuleContextJob(context)
				, job(job){
			}

			void run(bool deadlocked, threading::JobCompletionCallback callback){
				this->deadlocked = deadlocked;
				new(this->callback)threading::JobCompletionCallback(callback);
				module->addJob(this);
			}

			void run(){
				job->run(deadlocked, *callback.get());
			}
		private:
			bool deadlocked;
			Space<threading::JobCompletionCallback> callback;
			threading::IJob* job;
		};

		class JobWrapper: public ir::compiler::JobWrapper{
		public:
			JobWrapper(ModuleContext* context, MemoryPoolSlice* processPool)
				: context(context)
				, processPool(processPool){
			}

			threading::IJob* wrap(threading::IJob* job){
				return new(processPool->allocate(sizeof(JobProxy)))JobProxy(context, job);
			}
		private:
			ModuleContext* context;
			MemoryPoolSlice* processPool;
		};

		void ModuleContext::resolveNames(){
			diagnosticStream->report(Subsystem("Pipeline").file(qid->asString()).type(DiagnosticType::Info).code("DebugLog").parameter<PlainString>("message", "Resolving names"));
			//TODO:: We can check hash here and reuse resolved state (if we are resolved already)
			object->resolutionPool.reset();

			MemoryPoolSlice stack(GetMemoryPool());

			ir::compiler::NameResolver resolver(currentStream, &stack, &object->resolutionPool);
			resolver.run(object->module);

			stack.reset();

			JobWrapper jobWrapper(this, &processPool);
			ir::compiler::LayoutBuilder layoutBuilder(currentStream, pipeline->getDataflow(), &jobWrapper, &stack, &object->resolutionPool, &processPool);
			layoutBuilder.run(object->module);
		}

		void ModuleContext::instrCompile(){
			currentStream->report(Subsystem("Pipeline").type(DiagnosticType::Info).code("DebugLog").parameter<PlainString>("message", "InstrCompile"));
			
			object->instrPool.reset();

			MemoryPoolSlice stack(GetMemoryPool());
			ir::compiler::ModuleInstrCompiler compiler(currentStream, &stack, &object->instrPool);
			compiler.run(object->module);

			status.write(Compiled);
		}

		void ModuleContext::dropModuleObject(){
			if ( object ){
				MemoryFree(object);
				object = nullptr;
			}
		}

		void ModuleContext::reportNoModuleObjectGenerated(){
			fallToFatalError();
		}
		
		void ModuleContext::run(){
			while ( true ){
				ModuleContextJob* job;
				{
					acquire_lock(jobsLock);
					job = jobs.read();
					jobs.write(nullptr);
					if ( !job ){
						runningStatus.write(NotRunning);
						return;
					}
				}
				while ( job ){
					ModuleContextJob* nextJob = job->nextJob;
					job->run();
					job = nextJob;
				}
			}
		}

		void ModuleContext::addJob(ModuleContextJob* job){
			acquire_lock(jobsLock);
			job->nextJob = jobs.read();
			jobs.write(job);
			if ( runningStatus.read() == NotRunning ){
				runningStatus.write(Running);
				pipeline->getThreadPool()->addJob(this);
			}
		}

		static u8 PoisonCallbackAddr = 0;
		static IModuleExportTableCallback* PoisonCallback = (IModuleExportTableCallback*)&PoisonCallbackAddr;
		
		void ModuleContext::proceeedToExportReadyStatus(){
			status.write(ExportReady);
			IModuleExportTableCallback* callback;
			do{
				callback = exportTableCallback.read();
			}while ( callback != exportTableCallback.compareAndSwap(callback, PoisonCallback) );

			while ( callback ){
				IModuleExportTableCallback* next = callback->next;
				callback->onReady(object->module);
				callback = next;
			}
		}

		void ModuleContext::fallToFatalError(){
			status.write(FatalError);
			IModuleExportTableCallback* callback;
			do{
				callback = exportTableCallback.read();
			}while ( callback != exportTableCallback.compareAndSwap(callback, PoisonCallback) );

			if ( callback != PoisonCallback ){
				while ( callback ){
					IModuleExportTableCallback* next = callback->next;
					callback->onNeverReady();
					callback = next;
				}
			}
		}
		
		void ModuleContext::requestExportTable(IModuleExportTableCallback* callback){
			IModuleExportTableCallback* next;
			do{
				next = exportTableCallback.read();
				if ( next == PoisonCallback ){
					u32 status = this->status.read();
					if ( status >= ExportReady ){
						callback->onReady(object->module);	
					}else{
						callback->onNeverReady();
					}
				}
				callback->next = next;
			}while( next != exportTableCallback.compareAndSwap(next, callback) );
		}

		bool ModuleContext::isCompiled(){
			return status.read() == Compiled;
		}

		void ModuleContext::runBackendCompiler(backend::IBackendModuleCompiler* compiler){
			auto module = object->module;
			auto backendID = compiler->getBackendID();
			auto& backendInfo = backendsInfo.getOrInsert(backendID);
			if ( !backendInfo ){
				backendInfo = new(backendsPool.allocate(sizeof(BackendInfo)))BackendInfo;
			}
			ir::GlobalFunction* mainFunction = nullptr;
			if ( pipeline->getMainFunction()->getOwner() == module ){
				mainFunction = pipeline->getMainFunction();
			}
			compiler->visitModule(module, mainFunction, &backendInfo->pool, backendInfo->object);
		}
	}
}