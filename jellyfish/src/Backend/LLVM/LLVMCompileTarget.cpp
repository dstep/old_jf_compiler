#include <Backend/LLVM/LLVMCompileTarget.h>
#include <llvm/ADT/Triple.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/MC/SubtargetFeature.h>
#include <llvm/PassManager.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetSubtargetInfo.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/PassRegistry.h>

namespace jf{
	namespace backend{
		namespace llvm{
			LLVMCompileTarget::LLVMCompileTarget(){
			}

			ArrayRef<u8> LLVMCompileTarget::run(IDiagnosticStream* diagnostic, MemoryPoolSlice& tempPool, MemoryPoolSlice* hostPool, ::llvm::Module* module, CompilationTarget::Value target, FileType::Value fileType){
				auto targetMachine = CreateTargetMachine(diagnostic, target);

				if ( !targetMachine ){
					diagnostic->report(Subsystem("LLVMBackend").code("LLVMError.TargetMachineCreationFailed"));
					return ArrayRef<u8>();
				}

				::llvm::TargetMachine::CodeGenFileType llvmFileType;
				switch ( fileType ){
				case FileType::Assembly: llvmFileType = ::llvm::TargetMachine::CGFT_AssemblyFile; break;
				case FileType::Object: llvmFileType = ::llvm::TargetMachine::CGFT_ObjectFile; break;
				default: unreachable;
				}

				module->setTargetTriple(targetMachine->getTargetTriple());

				if (const ::llvm::DataLayout* dataLayout = targetMachine->getSubtargetImpl()->getDataLayout() ){
					module->setDataLayout(dataLayout);
				}

				::llvm::SmallVector<char, 1 * 1024 * 1024>* out = new(tempPool.allocate(sizeof(::llvm::SmallVector<char, 1 * 1024 * 1024>)))::llvm::SmallVector<char, 1 * 1024 * 1024>();
				::llvm::raw_svector_ostream stream(*out);
				::llvm::formatted_raw_ostream formattedStream(stream);

				::llvm::PassManager passManager;
				passManager.add(new ::llvm::DataLayoutPass());

				if ( targetMachine->addPassesToEmitFile
						(
							passManager,
							formattedStream,
							llvmFileType,
							true,
							nullptr,
							nullptr
						) ){
					diagnostic->report(Subsystem("LLVMBackend").code("LLVMError.TargetDoesntSupportFileType"));
					return ArrayRef<u8>();
				}

				passManager.run(*module);

				formattedStream.flush();

				return ArrayRef<u8>((u8*)out->data(), out->size()).copy(hostPool);
			}
		}
	}
}