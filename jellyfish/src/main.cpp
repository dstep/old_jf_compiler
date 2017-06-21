#include <cstdio>
#include <Pipeline/Pipeline.h>
#include <Pipeline/ModuleContext.h>
#include <Support/String/ParseQualID.h>
#include <Support/Localization.h>
#include <Support/Diagnostic.h>
#include <Support/Platform/Windows.h>
#include <Support/Twine.h>
#include <Support/SafeMath.h>
#include <Support/Container/CascadeBloomFilter.h>
#include <Support/Container/BloomFilter.h>
#include <Backend/LLVM/LLVMBackend.h>
#include <Backend/LLVM/LLVMContext.h>
#include <Backend/LLVM/LLVMModule.h>
#include <Backend/LLVM/LLVMCompileTarget.h>
#include <Backend/LLVM/JIT/JITEngine.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/TargetSelect.h>

#include <WinJITInjectTargetSelf.h>
#include <Support/Obligation.h>

#include "runtime.h"

using namespace jf;

#include "localization.inc"

LocalizationDictionary dictionary;

namespace{
class Params: public ILocalizationParamProvider{
public:
	Params(StringRef message, IDiagnosticContext& context)
		: message(message)
		, context(context){
	}

	~Params(){
	}

	void accept(ILocalizationParamVisitor& visitor){
		switch ( context.getType() ){
		case DiagnosticType::Trace:{
			visitor.visitLocalizableString("type", "TRACE");
		}break;
		case DiagnosticType::Info:{
			visitor.visitLocalizableString("type", "INFO");
		}break;
		case DiagnosticType::Warning:{
			visitor.visitLocalizableString("type", "WARNING");
		}break;
		case DiagnosticType::Error:{
			visitor.visitLocalizableString("type", "ERROR");
		}break;
		}
		visitor.visitValue("subsystem", PlainString(context.getSubsystem()));
		if ( !context.getFile().isEmpty() ){
			visitor.visitValue("file", PlainString(context.getFile()));
		}
		visitor.visitValue("message", PlainString(message));
		if ( !context.getSourceLocation().isUndefined() ){
			visitor.visitValue("where", context.getSourceLocation()); 
		}
	}

	StringRef message;
	IDiagnosticContext& context;
};
}

class DiagnosticStream: public IDiagnosticStream{
public:
	DiagnosticStream(LocalizationDictionary* dictionary)
		: dictionary(dictionary){

		consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void report(IDiagnosticContext& context){
		MemoryPoolSlice stack(GetMemoryPool());
		StringRef message = dictionary->makeLocalizedString(&stack, stack, context.getDiagnosticCode(), context.getParameters());
		const char* da = "DiagnosticOutput";

		Params params(message, context);

		StringRef fullString = dictionary->makeLocalizedString(&stack, stack, da, params);
		
		wchar_t* wideString = platform::Widen(&stack, fullString);
		switch ( context.getType() ){
		case DiagnosticType::Trace:{
			SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}break;
		case DiagnosticType::Info:{
			SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		}break;
		case DiagnosticType::Warning:{
			SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}break;
		case DiagnosticType::Error:{
			SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
		}break;
		}

		WriteConsoleW(consoleHandle, wideString, lstrlenW(wideString), NULL, NULL);
		
		SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		fullString = dictionary->makeLocalizedString(&stack, stack, "MSVCOutput", params);
		OutputDebugStringW(platform::Widen(&stack, fullString));
	}
private:
	HANDLE consoleHandle;
	LocalizationDictionary* dictionary;
} diagnostic(&dictionary);

class ThreadContext: public threading::ThreadContext{
public:
	void* initializeCurrentThread(){
		ThreadEnableMemoryAPI* threadContext = new(MemoryAllocate(sizeof(ThreadEnableMemoryAPI)))ThreadEnableMemoryAPI();
		return threadContext;
	}

	void destroyCurrentThread(void* userdata){
		ThreadEnableMemoryAPI* threadContext = (ThreadEnableMemoryAPI*)userdata;
		threadContext->~ThreadEnableMemoryAPI();
		MemoryFree(threadContext);
	}
} threadContext;

//#define COMPILE_AGAIN
#define WORKERS_THREAD_COUNT 0

class LLVMCompilerJob: public threading::ThreadPoolJob{
public:
	LLVMCompilerJob(pipeline::Pipeline* pipeline, pipeline::ModuleContext* module, backend::llvm::jit::JITEngine* jitEngine){
		this->module = module;
		this->pipeline = pipeline;
		this->jitEngine = jitEngine;
	}

	void run(){
		MemoryPoolSlice stack(GetMemoryPool());
		backend::llvm::LLVMContext context;
		backend::llvm::LLVMModule llvmModule(&stack, module->getQID()->asString(), &context);
		backend::llvm::LLVMBackend compiler(&stack, &context, &llvmModule);
		module->runBackendCompiler(&compiler);

		{
			auto moduleContent = llvmModule.getModule();
			std::error_code errorMessage;
			StringRef file = file::ResolvePath(&stack, stack, pipeline->getIntermediateDirectoryPath(), (module->getQID()->asString() + ".ll").toString(&stack));
			llvm::raw_fd_ostream stream(::llvm::StringRef((const char*)file.getData(), file.getLength()), errorMessage, llvm::sys::fs::F_None);
			moduleContent->print(stream, nullptr);
		}

		backend::llvm::LLVMCompileTarget compileTarget;
		//TODO:: clone module
		/*{
			auto objectFileContent = compileTarget.run(module->getDiagnostic(), stack, &stack, llvmModule.getModule(), backend::llvm::CompilationTarget::Win64, backend::llvm::FileType::Assembly);
			StringRef file = file::ResolvePath(&stack, stack, pipeline->getIntermediateDirectoryPath(), (module->getQID()->asString() + ".s").toString(&stack));
			file::WriteFile(stack, file, StringRef(objectFileContent.getRaw(), objectFileContent.getSize()));
		}
		{
			auto objectFileContent = compileTarget.run(module->getDiagnostic(), stack, &stack, llvmModule.getModule(), backend::llvm::CompilationTarget::Win64, backend::llvm::FileType::Object);
			StringRef file = file::ResolvePath(&stack, stack, pipeline->getIntermediateDirectoryPath(), (module->getQID()->asString() + ".obj").toString(&stack));
			file::WriteFile(stack, file, StringRef(objectFileContent.getRaw(), objectFileContent.getSize()));
		}
		*/
		jitEngine->addModule(llvmModule.getModule());
	}

private:
	backend::llvm::jit::JITEngine* jitEngine;
	pipeline::Pipeline* pipeline;
	pipeline::ModuleContext* module;
};

int main(int argc, char** argv){
	::llvm::InitializeAllTargets();
	::llvm::InitializeAllTargetMCs();
	::llvm::InitializeAllAsmPrinters();
	::llvm::InitializeAllAsmParsers();

	OwnedPool<> pool;

	for ( size_t i = 0; i < sizeof(localization) / sizeof(const char*[2]); i++ ){
		if ( LocalizationParseError* error = dictionary.addLocalization(localization[i][0], localization[i][1]) ){
			diagnostic.report(Subsystem("Localization").type(DiagnosticType::Error).code("LocalizationError.ParseError").parameters(LocalizationParseErrorParams(localization[i][0], error)));
		}
	}

	diagnostic.report(Subsystem("jellyfish").code("DebugLog").parameter("message", "Engine started"));

	threading::ThreadPool threadPool(&threadContext, WORKERS_THREAD_COUNT);

	pipeline::Pipeline pipeline(&diagnostic, &threadPool);

	if ( argc > 1 ){
		pipeline.runWithProjectPath(argv[1]);
	}else{
		pipeline.setWorkingDirectory("./language");
		pipeline.runWithProjectPath("e000.jfproject");
	}

	pipeline.runInstrCompiler();

	diagnostic.report(Subsystem("jellyfish").code("DebugLog").parameter("message", "Generating LLVM"));

	backend::llvm::jit::JITEngine engine(&diagnostic, backend::llvm::CompilationTarget::Win64);

	pipeline.iterateModules([&threadPool, &pool, &pipeline, &engine](const StringRef& name, jf::pipeline::ModuleContext* module){
			if ( module->isCompiled() ){
				LLVMCompilerJob* job = new(pool.allocate(sizeof(LLVMCompilerJob)))LLVMCompilerJob(&pipeline, module, &engine);
				threadPool.addJob(job);
			}
		});

	threadPool.join();

	

#if defined(COMPILE_AGAIN)
	diagnostic.report(Subsystem("jellyfish").code("DebugLog").parameter("message", "Recompilation..."));
	pipeline.runWithProjectPath("e000.jfproject");
	pipeline.runInstrCompiler();
#endif
	diagnostic.report(Subsystem("jellyfish").code("DebugLog").parameter("message", "Done"));
	
	connect::IJITInjectTarget::MainFunc func = nullptr;

	initializeJFRuntime();

	connect::IJITInjectTarget* injectTarget = connect::CreateWinJITTargetSelf(&func);
	obligation([&](){connect::DestroyWinJITTargetSelf(injectTarget);});
	engine.run(injectTarget);

	if ( func ){
		diagnostic.report(Subsystem("jellyfish").code("DebugLog").parameter("message", "---- Running JF ----"));	
		func();
		diagnostic.report(Subsystem("jellyfish").code("DebugLog").parameter("message", "---- Program has ended ----"));
	}else{
		diagnostic.report(Subsystem("jellyfish").code("DebugLog").parameter("message", "No main function injected with JIT engine"));
	}

	system("pause");

	return 0;
}