#pragma once
#include <Support/StringRef.h>
#include <Support/Container/HashMap.h>
#include <Support/SourceLoc.h>
#include "ControlFlow.h"

namespace jf{
	namespace ir{
		namespace instr{
			struct Type;
			struct Instr;
			class FunctionFrame;
		}

		namespace compiler{
			namespace ScopeReferenceKind{
				enum Value{
					None,
					FunctionParam,
					LocalVariable,
					Temporary
				};
			}

			struct LexicalTemporary{
				SrcSpan where;
				StringRef name;
				instr::Type* type;
				instr::Instr* producer;
				instr::FunctionFrame* frame;

				LexicalTemporary(const SrcSpan& where, const StringRef& name, instr::Type* type, instr::Instr* producer, instr::FunctionFrame* frame)
					: where(where)
					, name(name)
					, type(type)
					, producer(producer)
					, frame(frame){
				}
			};
			
			struct LexicalScopeReference{
				ScopeReferenceKind::Value kind;
				void* reference;

				LexicalScopeReference()
					: kind(ScopeReferenceKind::None)
					, reference(nullptr){
				}

				LexicalScopeReference(ScopeReferenceKind::Value kind, void* reference)
					: kind(kind)
					, reference(reference){
				}
			};

			struct LexicalScopeReferenceSlot{				
				LexicalScopeReference reference;

				LexicalScopeReferenceSlot(){
				}
			};

			struct LexicalScopeAddedName{
				LexicalScopeAddedName* next;
				LexicalScopeReferenceSlot* slot;
				LexicalScopeReference prevReference;

				LexicalScopeAddedName(LexicalScopeReferenceSlot* slot, const LexicalScopeReference& prevReference)
					: next(nullptr)
					, slot(slot)
					, prevReference(prevReference){
				}
			};

			struct LexicalScopeState{
				LexicalScopeState* next;
				LexicalScopeAddedName* addedName;
				ControlFlow::Value controlFlow;
				bool unreachableReported;

				LexicalScopeState()
					: next(nullptr)
					, addedName(nullptr)
					, controlFlow(ControlFlow::AlwaysPass)
					, unreachableReported(false){
				}
			};
			
			class LexicalScope{
			public:
				LexicalScope(LexicalScope* parent, MemoryPoolSlice* pool);

				LexicalScopeReference find(const StringRef& name);

				void pushState(LexicalScopeState* state, bool inheritControlFlow = true);
				void popState();

				void terminateControlFlow();

				bool shouldReportUnreachableCode();

				bool isAlwaysTerminated();

				void mergeStates(LexicalScopeState* leftState, LexicalScopeState* rightState) const;
				void concatState(LexicalScopeState* state);

				void add(const StringRef& name, LexicalScopeReference reference);
			private:
				LexicalScope* parent;
				MemoryPoolSlice* pool;
				StringMap<LexicalScopeReferenceSlot*> references;

				LexicalScopeState* currentState;
			};
		}
	}
}