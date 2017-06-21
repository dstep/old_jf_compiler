#pragma once
#include <llvm/ADT/StringRef.h>
#include <Support/StringRef.h>
#include <llvm/ADT/ArrayRef.h>
#include <Support/ArrayRef.h>

namespace jf{
	namespace backend{
		namespace llvm{
			inline ::llvm::StringRef toLLVM(const StringRef& string){
				return ::llvm::StringRef((const char*)string.getData(), string.getLength());
			}

			template<class T>
			::llvm::ArrayRef<T> toLLVM(const ArrayRef<T>& array){
				return ::llvm::ArrayRef<T>(array.getRaw(), array.getSize());
			}
		}
	}
}