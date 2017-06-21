#pragma once
#include <Backend/LLVM/JIT/JITEngine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/raw_ostream.h>

namespace jf{
	namespace backend{
		namespace llvm{
			namespace jit{
				JITEngine::JITEngine(IDiagnosticStream* diagnostic, CompilationTarget::Value target)
					: diagnostic(diagnostic){

					targetMachine.reset(CreateTargetMachine(diagnostic, target));
					
					std::unique_ptr<::llvm::Module> jitMainModule(new ::llvm::Module("jit", context));
					
					::llvm::EngineBuilder builder(std::move(jitMainModule));
					builder.setEngineKind(::llvm::EngineKind::JIT);
					builder.setCodeModel(::llvm::CodeModel::JITDefault);

					std::string error;
					builder.setMCJITMemoryManager(this);
					builder.setErrorStr(&error);

					engine = builder.create(targetMachine.get());
					if ( !engine ){
						diagnostic->report(Subsystem("LLVMJIT").code("InternalError").parameter<PlainString>("message", error.c_str()));
					}
				}

				uint64_t JITEngine::getSymbolAddress(const std::string &name){
					return injectTarget->querySymbol(name.c_str());
				}

				void JITEngine::addModule(::llvm::Module* module){
					if ( engine ){		
						std::string content;
						::llvm::raw_string_ostream stream(content);
						::llvm::WriteBitcodeToFile(module, stream);
						stream.flush();
						auto result = ::llvm::parseBitcodeFile(::llvm::MemoryBufferRef(content, ""), context);
						if ( !result ){
							diagnostic->report(Subsystem("LLVMJIT").code("InternalError").parameter<PlainString>("message", result.getError().message().c_str()));
						}else{
							auto clonedModule = result.get();
							engine->addModule(std::move(std::unique_ptr<::llvm::Module>(clonedModule)));
						}
					}
				}

				void JITEngine::run(connect::IJITInjectTarget* target){
					this->injectTarget = target;

					if ( engine ){
						void* mainPtr = engine->getPointerToNamedFunction("__jf_main", false);
						
						engine->finalizeObject();

						void* mainPtr2 = engine->getPointerToNamedFunction("__jf_main", false);
						if ( mainPtr2 ){
							injectTarget->submitMain((connect::Addr)mainPtr2);
						}
					}
				}

				void JITEngine::notifyObjectLoaded(::llvm::ExecutionEngine *EE, const ::llvm::ObjectImage *Obj){
					for ( auto& sectionIndex : unmappedSections ){
						auto& section = sections[sectionIndex];
						engine->mapSectionAddress(section.localAddr, section.remoteAddr);											
					}
					unmappedSections.clear();
				}

				uint8_t* JITEngine::allocateCodeSection(
					uintptr_t Size, unsigned Alignment, unsigned SectionID,
					::llvm::StringRef SectionName){
					Section section;
					section.readOnly = true;
					section.code = true;
					section.Alignment = Alignment;
					section.SectionID = SectionID;
					section.Size = Size;
					section.localAddr = allocate(Size);
					section.remoteAddr = injectTarget->allocateCodePage(Size, Alignment);
					unmappedSections.push_back(sections.size());
					sections.push_back(section);					
					return (uint8_t*)section.localAddr;
				}

				uint8_t* JITEngine::allocateDataSection(
					uintptr_t Size, unsigned Alignment, unsigned SectionID,
					::llvm::StringRef SectionName, bool IsReadOnly){
					Section section;
					section.readOnly = IsReadOnly;
					section.code = false;
					section.Alignment = Alignment;
					section.SectionID = SectionID;
					section.Size = Size;
					section.localAddr = allocate(Size);
					section.remoteAddr = injectTarget->allocateDataPage(Size, Alignment, IsReadOnly);
					unmappedSections.push_back(sections.size());
					sections.push_back(section);
					return (uint8_t*)section.localAddr;
				}

				bool JITEngine::finalizeMemory(std::string *ErrMsg){
					for ( auto& section : sections ){
						if ( injectTarget->writeMemory(section.remoteAddr, section.Size, section.localAddr) != section.Size ){
							diagnostic->report(Subsystem("LLVMJIT").code("InternalError").parameter<PlainString>("message", "Can't write remote memory"));
						}
						injectTarget->commitPage(section.remoteAddr, section.code, section.readOnly);											
					}
					sections.clear();
					return true;
				}
			}
		}
	}
}