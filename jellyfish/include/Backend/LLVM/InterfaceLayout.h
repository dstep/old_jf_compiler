#pragma once

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/TypeBuilder.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Constant.h>
#include <IR/Type.h>
#include <IR/Instr/Type.h>
#include <Support/Container/ArrayList.h>
#include <Support/Pair.h>

namespace jf{
	namespace backend{
		namespace llvm{
			class LLVMContext;
			class LLVMModule;

			class ClassLayout;

			class InterfaceLayout{
			public:
				InterfaceLayout(LLVMContext* context, MemoryPoolSlice* pool, ir::Interface* interface);

				::llvm::Type* getInterfaceType();

				u32 getMethodIndex(ir::InterfaceMethod* method);

				void requestLayout();
			private:
				LLVMContext* context;
				MemoryPoolSlice* pool;
				ir::Interface* interface;

				void embedInterface(InterfaceLayout* layout, ::llvm::SmallVectorImpl<::llvm::Type*>& types); 

				::llvm::StructType* interfaceType;
				bool layoutBuilt;
				PtrHash<ir::Interface, Pair<InterfaceLayout*, u32> > implementsMap;
				ArrayList<InterfaceLayout*> implementsList;
				PtrHash<ir::InterfaceMethod, u32> methodsMap;
				ArrayList<ir::InterfaceMethod*> methodsList;

				friend class ClassLayout;
			};
		}
	}
}