#pragma once
#include <Backend/LLVM/CompilationTarget.h>
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
			::llvm::TargetMachine* CreateTargetMachine(IDiagnosticStream* diagnostic, CompilationTarget::Value target){
				::llvm::Triple::ArchType arch;
				::llvm::Triple::OSType os;
				::llvm::Triple::VendorType vendor;
				std::string cpuStr;
				std::string archString;

				switch ( target ){
				case CompilationTarget::Win32:{
					arch = ::llvm::Triple::x86;
					os = ::llvm::Triple::Win32;
					vendor = ::llvm::Triple::PC;
					archString = "x86";
					cpuStr = "";
				}break;
				case CompilationTarget::Win64:{
					arch = ::llvm::Triple::x86_64;
					os = ::llvm::Triple::Win32;
					vendor = ::llvm::Triple::PC;
					archString = "x86-64";
					cpuStr = "";
				}break;
				default: unreachable;
				}
				
				::llvm::Triple triple;
				triple.setArch(arch);
				triple.setOS(os);
				triple.setVendor(vendor);
				triple.setObjectFormat(::llvm::Triple::ELF);

				std::string error;
				const ::llvm::Target* llvmTarget = ::llvm::TargetRegistry::lookupTarget(archString, triple, error);
				if ( !llvmTarget ){
					diagnostic->report(Subsystem("LLVMBackend").code("InternalError").parameter<PlainString>("message", StringRef(error.c_str())));
					return nullptr;
				}

				::llvm::TargetOptions options;

				options.NoFramePointerElim = 1;

				::llvm::SubtargetFeatures features;

				::llvm::CodeGenOpt::Level optLevel = ::llvm::CodeGenOpt::None;

				::llvm::TargetMachine* targetMachine
					(
					  llvmTarget->createTargetMachine
						(
							triple.getTriple(), 
							cpuStr, 
							features.getString(),
							options, 
							::llvm::Reloc::Default, 
							::llvm::CodeModel::Default, 
							optLevel
						)
					);
				return targetMachine;
			}
		}
	}
}