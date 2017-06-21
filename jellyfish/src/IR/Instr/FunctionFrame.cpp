#include <IR/Instr/FunctionFrame.h>

namespace jf{
	namespace ir{
		namespace instr{
			instr::LocalVar* FunctionFrame::addLocalVariable(MemoryPoolSlice* pool, const SrcSpan& where, const StringRef& name, instr::Type* type){
				instr::LocalVar* localVariable = new(pool->allocate(sizeof(instr::LocalVar)))instr::LocalVar(this, localVarsCount++, where, name, type);
				localVariables = localVariables.append(localVariable);
				return localVariable;
			}

			instr::InstrUpValue* FunctionFrame::addUpValue(MemoryPoolSlice* pool, FunctionFrame* owner, instr::Instr* producer, instr::Type* type){
				instr::InstrUpValue*& upValueSlot = upValueIndex.getOrInsert(pool, producer);
				if ( !upValueSlot ){
					if ( parent != owner ){
						producer = parent->addUpValue(pool, owner, producer, type);
					}
					instr::InstrUpValue* upValue = new(pool->allocate(sizeof(instr::InstrUpValue)))instr::InstrUpValue(this, upValuesCount++, producer, type);
					upValue->frameIndex = takeNextInstrIndex();
					upValueSlot = upValue;
				}
				return upValueSlot;
			}

			void FunctionFrame::addCapturedVariable(MemoryPoolSlice* pool, instr::LocalVar* localVar){
				if ( localVar->owner == this ){
					return;
				}

				u32& slot = capturedVars.getOrInsert(pool, localVar);
				if ( !slot ){
					slot = 1;
					parent->addCapturedVariable(pool, localVar);
				}
			}
		}
	}
}