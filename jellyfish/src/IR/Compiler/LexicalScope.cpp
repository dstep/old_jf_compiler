#include <IR/Compiler/LexicalScope.h>
#include <Support/IntrusiveList.h>

namespace jf{
	namespace ir{
		namespace compiler{
			LexicalScope::LexicalScope(LexicalScope* parent, MemoryPoolSlice* pool)
				: parent(parent)
				, pool(pool)
				, references(pool)
				, currentState(nullptr){
			}

			LexicalScopeReference LexicalScope::find(const StringRef& name){
				LexicalScopeReferenceSlot*& slot = references.getOrInsert(name);
				if ( slot ){
					return slot->reference;
				}else{
					slot = new(pool->allocate(sizeof(LexicalScopeReferenceSlot)))LexicalScopeReferenceSlot();
					if ( parent ){
						slot->reference = parent->find(name);
					}
					return slot->reference;
				}
			}

			void LexicalScope::add(const StringRef& name, LexicalScopeReference reference){
				//Ensure slot from parent
				find(name);

				LexicalScopeReferenceSlot* slot = references.get(name);

				LexicalScopeAddedName* addedName = new(pool->allocate(sizeof(LexicalScopeAddedName)))LexicalScopeAddedName(slot, slot->reference);
				addedName->next = currentState->addedName;
				currentState->addedName = addedName;

				slot->reference = reference;
			}
			
			void LexicalScope::mergeStates(LexicalScopeState* leftState, LexicalScopeState* rightState) const{
				leftState->controlFlow = ControlFlow::merge(leftState->controlFlow, rightState->controlFlow);
				leftState->unreachableReported &= rightState->unreachableReported;
			}

			void LexicalScope::concatState(LexicalScopeState* state){
				currentState->controlFlow = ControlFlow::concat(state->controlFlow, currentState->controlFlow);
				currentState->unreachableReported |= state->unreachableReported;
			}

			void LexicalScope::pushState(LexicalScopeState* state, bool inheritControlFlow){
				state->next = currentState;
				if ( inheritControlFlow && currentState ){
					state->controlFlow = currentState->controlFlow;
					state->unreachableReported = currentState->unreachableReported;
				}
				currentState = state;
			}

			void LexicalScope::popState(){
				iterate_list(addedName, currentState->addedName){
					addedName->slot->reference = addedName->prevReference;
				}
				currentState = currentState->next;
			}

			void LexicalScope::terminateControlFlow(){
				currentState->controlFlow = ControlFlow::concat(currentState->controlFlow, ControlFlow::AlwaysTerminate);
			}

			bool LexicalScope::shouldReportUnreachableCode(){
				bool result = currentState->controlFlow == ControlFlow::AlwaysTerminate && !currentState->unreachableReported;
				if ( result ){
					currentState->unreachableReported = true;
				}
				return result;
			}

			bool LexicalScope::isAlwaysTerminated(){
				return currentState->controlFlow == ControlFlow::AlwaysTerminate;
			}
		}
	}
}