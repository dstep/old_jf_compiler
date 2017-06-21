#pragma once
#include "Type.h"
#include "BasicBlock.h"
#include "Instr.h"

namespace jf{
	namespace ir{
		namespace instr{
			class FunctionFrame;
						
			class FunctionFrame{
			public:
				FunctionFrame(FunctionFrame* parent)
					: parent(parent)
					, expectedReturnType(nullptr)
					, entryBlock(nullptr)
					, nextInstrIndex(0)
					, localVarsCount(0)
					, upValuesCount(0)
					, constructorTarget(nullptr)
					, constructorBase(nullptr){
				}
				
				void setExpectedReturn(Type* expectedReturnType){
					this->expectedReturnType = expectedReturnType;
				}

				void setConstructorSemantic(ir::Class* base, ir::Class* target){
					constructorTarget = target;
					constructorBase = base;
				}

				bool isConstructor(){
					return constructorTarget != nullptr;
				}

				ir::Class* getConstructorBase(){
					return constructorBase;
				}

				ir::Class* getConstructorTarget(){
					return constructorTarget;
				}

				Type* getExpectedReturn(){
					return expectedReturnType;
				}

				void setEntry(BasicBlock* entryBlock){
					this->entryBlock = entryBlock;
				}

				void addBasicBlock(BasicBlock* bb){
					blocks = blocks.append(bb);
				}

				BasicBlock* getEntry(){
					return entryBlock;
				}

				BasicBlock* getFirstBasicBlock(){
					return blocks.first;
				}

				u32 takeNextInstrIndex(){
					return nextInstrIndex++;
				}

				u32 getInstrCount(){
					return nextInstrIndex;
				}

				u32 getLocalVarsCount(){
					return localVarsCount;
				}

				instr::LocalVar* getFirstLocalVariable(){
					return localVariables.first;
				}

				instr::InstrUpValue* addUpValue(MemoryPoolSlice* pool, FunctionFrame* owner, instr::Instr* producer, instr::Type* type);
				
				instr::LocalVar* addLocalVariable(MemoryPoolSlice* pool, const SrcSpan& where, const StringRef& name, instr::Type* type);

				void addCapturedVariable(MemoryPoolSlice* pool, instr::LocalVar* localVar);
								
				template<class Func>
				void iterateCapturedLocalVars(Func&& func){
					capturedVars.traverseInorder(func);
				}

				template<class Func>
				void iterateUpValues(Func&& func){
					upValueIndex.traverseInorder(func);
				}
			private:
				ir::Class* constructorBase;
				ir::Class* constructorTarget;

				FunctionFrame* parent;

				u32 nextInstrIndex, localVarsCount;
				u32 upValuesCount;

				Type* expectedReturnType;
				BasicBlock* entryBlock;
				List<BasicBlock> blocks;
				List<instr::LocalVar> localVariables;

				SearchTree< instr::Instr*, instr::InstrUpValue*, Ordering::Compare<instr::Instr*> > upValueIndex;
				SearchTree< instr::LocalVar*, u32, Ordering::Compare<instr::LocalVar*> > capturedVars;
			};
		}
	}
}