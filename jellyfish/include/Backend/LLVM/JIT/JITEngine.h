#pragma once
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/RTDyldMemoryManager.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <map>
#include "../CompilationTarget.h"
#include <IJITInjectTarget.h>
#include <IDebugTarget.h>

namespace jf{
	namespace backend{
		namespace llvm{
			namespace jit{
				class JITEngine: private ::llvm::RTDyldMemoryManager, private OwnedPool<>{
				public:
					JITEngine(IDiagnosticStream* diagnostic, CompilationTarget::Value target);

					void addModule(::llvm::Module* module);

					void run(connect::IJITInjectTarget* target);

				private:

					uint64_t getSymbolAddress(const std::string &Name);
					uint8_t* allocateCodeSection(
						uintptr_t Size, unsigned Alignment, unsigned SectionID,
						::llvm::StringRef SectionName);

					uint8_t* allocateDataSection(
						uintptr_t Size, unsigned Alignment, unsigned SectionID,
						::llvm::StringRef SectionName, bool IsReadOnly);

					bool finalizeMemory(std::string *ErrMsg);
					void notifyObjectLoaded(::llvm::ExecutionEngine *EE, const ::llvm::ObjectImage *Obj);

					IDiagnosticStream* diagnostic;
					::llvm::LLVMContext context;
					std::unique_ptr<::llvm::TargetMachine> targetMachine;
					::llvm::ExecutionEngine* engine;

					connect::IJITInjectTarget* injectTarget;

					bool processExit;

					struct Section{
						connect::Addr remoteAddr;
						void* localAddr;

						uintptr_t Size;
						unsigned Alignment;
						unsigned SectionID;
						std::string sectionName;
						bool code;
						bool readOnly;
					};
					std::vector<Section> sections;
					std::vector<size_t> unmappedSections;
				};
			}
		}
	}
}