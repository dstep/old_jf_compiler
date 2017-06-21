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

			class ClassLayout{
			public:
				ClassLayout(LLVMContext* context, MemoryPoolSlice* pool, ir::Class* class_);

				::llvm::Type* getObjectType();
				::llvm::Type* getClassType();
				::llvm::StructType* getClassVTableType();
				::llvm::Constant* getSize();
								
				Pair<ClassLayout*, u32> getMethodIndex(ir::ClassMethod* method);
				Pair<ClassLayout*, Pair<u32, u32> > getFieldIndex(ir::ClassField* field);

				void requestLayout();
				void requestClassLayout();
				void requestImplementsTable();

				::llvm::GlobalVariable* createImplementsTable(LLVMModule* module);
				::llvm::Constant* getInterfaceFromImplementsTable(::llvm::GlobalVariable* implementsTable, ir::Interface* interface);
				
				::llvm::Constant* createVTableInitializer(LLVMModule* module);
				::llvm::Constant* createImplementsTableInitializer(LLVMModule* module);
			private:
				void createVTablePart(LLVMModule* module, ::llvm::SmallVector<::llvm::Constant*, 128>& values, ClassLayout* layout);

				bool isSeparateSlotNeeded(ir::ClassMethodOverride* overrider);
				bool isWrapperNeeded(ir::ClassMethodImplements* overrider);

				LLVMContext* context;
				MemoryPoolSlice* pool;
				ir::Class* class_;
				bool layoutBuilt;
				bool classLayoutBuilt;
				bool implementsTableBuilt;

				::llvm::StructType* objectType;
				::llvm::StructType* classType;
				::llvm::StructType* implementsTableType;
				::llvm::Constant* size;

				::llvm::SmallVector<::llvm::Type*, 64> implementsTableLayout;

				SearchTree< ir::ClassField*, Pair<ClassLayout*, Pair<u32, u32> >, Ordering::Compare<ir::ClassField*> > fieldsMap;
				SearchTree< ir::ClassMethod*, Pair<ClassLayout*, u32>, Ordering::Compare<ir::ClassMethod*> > methodsMap;
				SearchTree< ir::ClassMethod*, ir::ClassMethod*, Ordering::Compare<ir::ClassMethod*> > overrideMap;

				SearchTree< ir::Interface*, Pair<u32, u32>, Ordering::Compare<ir::Interface*> > interfaceMap;

				ArrayList< ir::ClassMethod* > vtableLayout;
			};
		}
	}
}