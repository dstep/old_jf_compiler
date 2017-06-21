#pragma once
#include <llvm/IR/Module.h>
#include <Support/StringRef.h>
#include <Support/Container/HashMap.h>
#include "LLVMContext.h"
#include <IR/Module.h>
#include "ModuleArchive.h"

namespace jf{
	namespace backend{
		namespace llvm{
			struct ValueStack{
				ValueStack(MemoryPoolSlice* pool)
					: types(pool)
					, values(pool){
				}

				ArrayList<::llvm::Type*> types;
				ArrayList<::llvm::Value*> values;
			};

			namespace Intrinsic{
				enum ID{
					AllocateObject,

					UnwindConstructorCallback,

					MakeString,
					StringEqual,
					StringCompare,
					StringConcat,
					FloatRound,
					DoubleRound,
					FloatCeil,
					DoubleCeil,
					FloatFloor,
					DoubleFloor,

					DoubleNearbyInt,
					DoubleNearbyFloat,

					FloatNearbyInt,					
					IntNearbyFloat,

					EmptyArray,

					ArrayPush,
					ArrayPop,
					ArrayRef,
					ArrayClear,
					ArraySize,

					FloatSqrt,
					DoubleSqrt,

					AllocateBytes,
					BytesWriteFloat,
					BytesWriteU16,
					
					Count
				};
			};

			class LLVMModule{
			public:
				LLVMModule(MemoryPoolSlice* tempPool, const StringRef& moduleId, LLVMContext* context);
				~LLVMModule();

				::llvm::Module* getModule(){
					return module;
				}

				::llvm::Module* extractModule(){
					::llvm::Module* module = this->module;
					this->module = nullptr;
					return module;
				}

				::llvm::Function* getDeclaration(ir::GlobalFunction* globalFunction);
				::llvm::Function* getDeclaration(ir::ClassConstructor* constructor);
				::llvm::Function* getDeclaration(ir::ClassMethod* method);
				::llvm::Function* getClosureDeclaration(ir::ClassConstructor* constructor);

				::llvm::Constant* getIntrinsic(Intrinsic::ID intrinsic);

				::llvm::GlobalVariable* getClassTable(ir::Class* class_);
				::llvm::GlobalVariable* getClassImplementsTable(ir::Class* class_);
				::llvm::Constant* getInterfaceImplement(ClassLayout* class_, ir::Interface* interface);

				ModuleArchive* archiveModule(MemoryPoolSlice& tempPool, MemoryPoolSlice* hostPool);
			private:
				::llvm::Function* createDeclaration(ir::GlobalFunction* globalFunction);
				::llvm::Function* createDeclaration(ir::ClassConstructor* constructor);
				::llvm::Function* createClosureDeclaration(ir::ClassConstructor* constructor);
				::llvm::Function* createDeclaration(ir::ClassMethod* method);
				::llvm::GlobalVariable* createClassTable(ir::Class* class_);

				::llvm::Constant* createIntrinsic(Intrinsic::ID intrinsic);

				::llvm::Constant* intrinsics[Intrinsic::Count];
				
				MemoryPoolSlice* tempPool;
				LLVMContext* context;
				::llvm::Module* module;
				PtrHash<ir::GlobalFunction, ::llvm::Function*> globalFunctions;
				PtrHash<ir::ClassConstructor, Pair<::llvm::Function*, ::llvm::Function*> > classConstructors;
				PtrHash<ir::ClassMethod, ::llvm::Function*> classMethods;
				PtrHash<ir::Class, ::llvm::GlobalVariable*> classTables;
				HashMap< ClassLayout*, ::llvm::GlobalVariable* > classImplements;
			};
		}
	}
}