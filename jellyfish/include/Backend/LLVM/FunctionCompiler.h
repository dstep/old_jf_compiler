#pragma once
#include "LLVMContext.h"
#include "LLVMModule.h"
#include <IR/Instr/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

namespace jf{
	namespace backend{
		namespace llvm{
			class FunctionCompiler{
			public:
				FunctionCompiler(MemoryPoolSlice* tempPool, LLVMContext* context, LLVMModule* module);

				void generateMainFunction(ir::GlobalFunction* function);

				void captureFunctionDeclaration(::llvm::Function* function);

				void makeFFICall(const StringRef& string);
				void makeDecoratedVirtualCall(ir::FunctionSignature* base, ir::ClassMethod* method);
				void makeConstructorCallFromClosure(ir::ClassConstructor* constructor);

				void captureConstructorStack();
				void captureReturnValue(const ir::Type& type);
				void captureThisObject(ir::Class* class_);
				void captureParam(ir::Param* param);
				void captureClosureObject();

				void enterFunctionFrame(ir::instr::FunctionFrame* frame);
				void leaveFunctionFrame();
			private:
				void compileInstr(ir::instr::Instr* instr);
				void cancelCompilation(const char* reason);

				void move(::llvm::Value* dest, ::llvm::Value* src);
				::llvm::Value* read(::llvm::Value* value);

				void captureReturnValues(::llvm::SmallVector<::llvm::Value*, 64>& args, size_t count, ArrayList<::llvm::Type*>& types);
				void readReturnValues(::llvm::Value* returnValue, ::llvm::SmallVector<::llvm::Value*, 64>& args, size_t beginIndex);

				::llvm::Value* pushConstructorRecord(::llvm::Value* prev, ir::instr::ConstructorRecord* record);
				void pushRecordArgs(ir::instr::ConstructorRecord* record);

				void compileCoercion(u32 frameIndex, ir::instr::Coercion* coercion, Pair<u32, u32> src);
				void compileReturn(u32 frameIndex, Pair<u32, u32> src);

				::llvm::Value* makeClosureRecord(ir::instr::FunctionFrame* frame);

				void setValue(u32 frameIndex, Pair<u32, u32> src);

				::llvm::Value* makeTemporary(::llvm::Type* type);

				::llvm::Value* getValue(ir::instr::Instr* instr, s32 index = 0);
				::llvm::BasicBlock* getBasicBlock(ir::instr::BasicBlock* bb);

				MemoryPoolSlice* tempPool;
				LLVMContext* context;
				LLVMModule* module;
				ValueStack valueStack;

				ir::instr::FunctionFrame* frame;
				::llvm::Function* function;
				::llvm::Function::ArgumentListType::iterator argIterator;

				::llvm::BasicBlock* entryBlock;

				::llvm::IRBuilder<> builder;
				::llvm::IRBuilder<> entryBuilder;

				ArrayList<::llvm::Argument*> returnByRef;
				ArrayList<::llvm::Argument*> params;
				ArrayList<::llvm::Value*> localVars;
				PtrHash<ir::Param, Pair<u32, u32> > paramIndex;
				::llvm::Argument* thisObject;
				::llvm::Argument* constructorStack;
				::llvm::Argument* constructorCallback;
				::llvm::Argument* closureObject;
				PtrHash< ir::instr::LocalVar, Pair<u32, u32> > localVarIndex;

				ArrayList<::llvm::Value*> values;
				ArrayList< Pair<u32, u32> > valueIndex;

				struct Closure{
					::llvm::Function* function;
					ir::FunctionSignature* signature;
					ir::instr::FunctionFrame* frame;
				};
				ArrayList<Closure> closures;

				::llvm::SmallVector<::llvm::Value*, 64> args;
				::llvm::SmallVector<::llvm::Type*, 64> argsTypes;

				PtrHash<ir::instr::BasicBlock, ::llvm::BasicBlock*> bblocks;
			};
		}
	}
}