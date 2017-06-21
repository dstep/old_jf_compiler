#pragma once
#define TheHostPool hostPool
#define TheTempPool tempPool
#define TheInstrCompiler parent
#define TheDiagnostic parent->parent->stream
#include <IR/Compiler/InstrCompilerCommon.h>

#include <IR/Compiler/MatchTreeCompiler.h>

namespace jf{
	namespace ir{
		namespace compiler{	
			MatchTreeCompiler::MatchTreeCompiler(InstrCompiler* parent, MemoryPoolSlice* tempPool, MemoryPoolSlice* hostPool)
				: tempPool(tempPool)
				, hostPool(hostPool)
				, values(tempPool)
				, parent(parent)
				, assumptions(nullptr)
				, lastAssumption(nullptr)
				, root(nullptr)
				, maybeValues(tempPool)
				, successNodes(tempPool)
				, remember(nullptr)
				, failNode(nullptr){
				failNode = alloc(MatchNodeFail)();
				root = failNode;				
			}
			
			MatchValue* MatchTreeCompiler::addValue(instr::Type* type){
				MatchValue* value = alloc(MatchValue)(type);
				values.push(value);
				return value;
			}

			void MatchTreeCompiler::addCase(const SrcSpan& where, parser::ast::Pattern* patterns){
				assumptions = lastAssumption = nullptr;
				remember = nullptr;

				size_t index = 0;
				iterate_list(pattern, patterns){
					if ( values.getSize() > index ){
						MatchValue* value = values.get(index);
						compilePattern(pattern, value);
					}
					index++;					
				}
			}

			MatchNode* MatchTreeCompiler::getRootNode(){
				return root;
			}

			MatchNodeFail* MatchTreeCompiler::getFailNode(){
				return failNode;
			}

			MatchValue* MatchTreeCompiler::getMatchValueOptionalValue(MatchValue* value){
				auto& valueSlot = maybeValues.getOrInsert(value);
				if ( !valueSlot ){
					valueSlot = alloc(MatchValue)(((instr::TypeOptional*)value->type)->valueType);
				}
				return valueSlot;
			}

			void MatchTreeCompiler::compilePattern(parser::ast::Pattern* pattern, MatchValue* value){
				match(pattern)
					rule(ast::PatternRemember, pattern)
						remember = alloc(MatchTreeRemember)(remember, value, pattern->where, pattern->name);
						compilePattern(pattern->pattern, value);
					erule
					rule(ast::PatternVar, pattern)
						remember = alloc(MatchTreeRemember)(remember, value, pattern->where, pattern->name);
					erule
					rule(ast::PatternPrim, pattern)
						switch ( pattern->id ){
						case ast::PatternPrim::Null:{
							match(value->type)
								rule(instr::TypeOptional, type)
									addAssumption(temp(MatchAssumptionNull)(value));
								erule
								defrule(_)
									//report error
								erule
							ematch
						}break;
						}
					erule
					rule(ast::PatternCons, pattern)
						//TODO::
						if ( pattern->name->prev == nullptr ){
							if ( pattern->name->id == "value" ){
								match(value->type)
									rule(instr::TypeOptional, type)
										MatchValue* valueValue = getMatchValueOptionalValue(value);
										addAssumption(temp(MatchAssumptionValue)(value, valueValue));
										if ( pattern->params ){
											compilePattern(pattern->params, valueValue);
										}
										if ( pattern->params->next ){
											//TODO:: report error
										}
									erule
									defrule(_)
										//report error
									erule
								ematch
							}
						}
					erule
				ematch
			}

			MatchNodeSuccess* MatchTreeCompiler::addGuardedAction(const SrcSpan& where, parser::ast::Expr* guard){
				MatchAssumption* assumption = temp(MatchAssumptionCondition)(guard);
				addAssumption(assumption);
				MatchNodeSuccess* successNode = createNewSuccessNode(where, remember);
				extractAssumption(assumption);
				return successNode;
			}

			MatchNodeSuccess* MatchTreeCompiler::addDefaultAction(const SrcSpan& where){
				MatchNodeSuccess* successNode = createNewSuccessNode(where, remember);
				updateMatchTree(successNode);
				return successNode;
			}

			MatchNodeSuccess* MatchTreeCompiler::createNewSuccessNode(const SrcSpan& where, MatchTreeRemember* remember){
				MatchNodeSuccess* successNode = alloc(MatchNodeSuccess)((u32)successNodes.getSize(), where, remember);
				successNodes.push(successNode);
				return successNode;
			}

			void MatchTreeCompiler::updateMatchTree(MatchNode* successNode){
				root = updateMatchTree(root, successNode);
			}

			void MatchTreeCompiler::addAssumption(MatchAssumption* assumption){
				assumption->prev = lastAssumption;
				assumption->next = nullptr;
				if ( lastAssumption ){
					lastAssumption->next = assumption;
				}else{
					assumptions = lastAssumption = assumption;
				}				
			}

			MatchAssumption* MatchTreeCompiler::extractAssumption(MatchAssumption* assumption){
				if ( assumption->prev ){
					assumption->prev->next = assumption->next;
				}else{
					this->assumptions = assumption->next;
				}
				if ( assumption->next ){
					assumption->next->prev = assumption->prev;
				}else{
					this->lastAssumption = assumption->prev;
				}
				return assumption;
			}
			
			#define extract_assumption(name, index) \
				MatchAssumption* name = assumptions.get(index); \
				assumptions.set(index, assumptions.takeLast());

			#define restore_assumption(name)

			#define begin_iterate_assumptions() \
				{MatchAssumption* nextAssumption = nullptr; \
				for ( MatchAssumption* assumption = assumptions; assumption; assumption = nextAssumption ){ \
					nextAssumption = assumption->next; 
			#define end_iterate_assumptions() }}

			void MatchTreeCompiler::restoreAssumption(MatchAssumption* assumption){
				if ( assumption->prev ){
					assumption->prev->next = assumption;
				}else{
					this->assumptions = assumption;
				}
				if ( assumption->next ){
					assumption->next->prev = assumption;
				}else{
					this->lastAssumption = assumption;
				}
			}

			MatchNode* MatchTreeCompiler::updateMatchTree(MatchNode* node, MatchNode* successNode){
			#define update(t) updateMatchTree(t, successNode)

				match(node)
					rule(MatchNodeSuccess, node)
						return node;
					erule
					rule(MatchNodeFail, node)
						MatchNode* newNode = successNode;
						MatchNode** nodeTarget = &newNode;
						begin_iterate_assumptions()

							match(assumption)
								rule(MatchAssumptionNull, assumption)
									MatchNodeMaybe* maybeNode = alloc(MatchNodeMaybe)(assumption->value, successNode, node, nullptr);
									*nodeTarget = maybeNode;
									nodeTarget = &maybeNode->nodeNull;
								erule
								rule(MatchAssumptionValue, assumption)
									MatchNodeMaybe* maybeNode = alloc(MatchNodeMaybe)(assumption->value, node, successNode, assumption->valueValue);
									*nodeTarget = maybeNode;
									nodeTarget = &maybeNode->nodeValue;
								erule
								rule(MatchAssumptionCondition, assumption)
									MatchNodeCondition* conditionNode = alloc(MatchNodeCondition)(assumption->expr, successNode, node, remember);
									*nodeTarget = conditionNode;
									nodeTarget = &conditionNode->nodeTrue;
								erule
							ematch

						end_iterate_assumptions()

						return newNode;
					erule
					rule(MatchNodeMaybe, node)
						begin_iterate_assumptions()
							match(assumption)
								rule(MatchAssumptionNull, assumption)
									if ( assumption->value == node->value ){
										extractAssumption(assumption);
										node->nodeNull = update(node->nodeNull);
										restoreAssumption(assumption);
										return node;
									}
								erule
								rule(MatchAssumptionValue, assumption)
									if ( assumption->value == node->value ){
										extractAssumption(assumption);
										node->nodeValue = update(node->nodeValue);
										restoreAssumption(assumption);
										return node;
									}
								erule
							ematch
						end_iterate_assumptions()

						node->nodeNull = update(node->nodeNull);
						node->nodeValue = update(node->nodeValue);
						return node;
					erule
					rule(MatchNodeCondition, node)
						node->nodeFalse = update(node->nodeFalse);
						node->nodeTrue = update(node->nodeTrue);
						return node;
					erule
					rule(MatchNodeEqual, node)
						node->nodeEqual = update(node->nodeEqual);
						node->nodeNotEqual = update(node->nodeNotEqual);
						return node;
					erule
					nodefrule;
				ematch
			}
		}
	}
}