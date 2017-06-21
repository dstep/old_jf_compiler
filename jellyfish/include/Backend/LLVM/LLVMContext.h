#pragma once

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/TypeBuilder.h>
#include <IR/Type.h>
#include <IR/Instr/Type.h>
#include <Support/Container/ArrayList.h>
#include <Support/Container/HashMap.h>
#include "ClassLayout.h"
#include "InterfaceLayout.h"

namespace jf{
	namespace backend{
		namespace llvm{
			namespace OptionalBehavior{
				enum Value{
					ExtraBit,
					NullPointer0
				};
			}

			class LLVMContext: private OwnedPool<>{
			public:
				LLVMContext();
				~LLVMContext();

				::llvm::LLVMContext& getContext(){
					return context;
				}

				ClassLayout* getClassLayout(ir::Class* class_);
				InterfaceLayout* getInterfaceLayout(ir::Interface* interface);

				::llvm::FunctionType* getMethodType(ir::ClassMethod* method);
				::llvm::FunctionType* getMethodType(ir::InterfaceMethod* method);

				size_t convertType(MemoryPoolSlice* pool, const ir::Type& type, ArrayList<::llvm::Type*>& types);
				size_t convertType(ir::instr::Type* type, ArrayList<::llvm::Type*>& types);

				OptionalBehavior::Value getOptionalBehavior(ir::instr::Type* type);

				void fillReturnValue(const ir::Type& type, ::llvm::Type*& returnType, ArrayList<::llvm::Type*>& params); 
				void fillParams(const ir::Type& type, ArrayList<::llvm::Type*>& params); 

				ArrayList<::llvm::Type*>& getTypeStack(){
					return typeStack;
				}

				::llvm::StructType* getTypeAsStruct(ir::instr::Type* type);
				::llvm::Constant* getSizeOf(::llvm::Type* type);

				bool isBitCastCoercion(ir::instr::Coercion* coercion);

				::llvm::StructType* getLargeStringType();
				::llvm::ArrayType* getSmallStringType();

				::llvm::Type* getI1Type();
				::llvm::Type* getI8Type();
				::llvm::Type* getI32Type();
				::llvm::Type* getI64Type();

				::llvm::Type* getVoidType();
			private:
				::llvm::FunctionType* createMethodType(ir::ClassMethod* method);
				::llvm::FunctionType* createMethodType(ir::InterfaceMethod* method);

				::llvm::ArrayType* smallStringType;
				::llvm::StructType* largeStringType;

				::llvm::Type* i64Ty;
				::llvm::Type* i32Ty;
				::llvm::Type* voidTy;
				::llvm::Type* i8Ty;
				::llvm::PointerType* i8PtrTy;
				::llvm::Type* i1Ty;

				::llvm::LLVMContext context;
				PtrHash<ir::Class, ClassLayout*> classLayouts;
				PtrHash<ir::Interface, InterfaceLayout*> interfaceLayouts;
				PtrHash<ir::ClassMethod, ::llvm::FunctionType*> methodTypes;
				PtrHash<ir::InterfaceMethod, ::llvm::FunctionType*> imethodTypes;

				ArrayList<::llvm::Type*> typeStack;
			};
		}
	}
}