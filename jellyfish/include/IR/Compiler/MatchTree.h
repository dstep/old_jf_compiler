#pragma once
#include <Support/Types.h>
#include <Support/IntrusiveList.h>
#include <Parser/AST/AST.h>
#include <IR/Instr/Type.h>

namespace jf{
	namespace ir{
		namespace compiler{
			struct MatchNode;

			struct MatchTree{
				MatchNode* root;
			};

			struct MatchValue{
				instr::Type* type;
				Value value;

				MatchValue(instr::Type* type)
					: type(type){
				}
			};

			enum MatchAssumptionTag{
				MatchAssumptionConditionTag,
				MatchAssumptionNullTag,
				MatchAssumptionValueTag
			};
			
			struct MatchAssumption{
				MatchAssumption* next;
				MatchAssumption* prev;

				MatchAssumptionTag tag;

				MatchAssumption(MatchAssumptionTag tag)
					: tag(tag){
				}
			};

			struct MatchTreeRemember{
				MatchTreeRemember* prev;
				MatchValue* value;
				SrcSpan where;
				StringRef name;

				MatchTreeRemember(MatchTreeRemember* prev, MatchValue* value, const SrcSpan& where, const StringRef& name)
					: value(value)
					, name(name)
					, prev(prev)
					, where(where){
				}
			};

			struct MatchAssumptionCondition: public MatchAssumption{
				parser::ast::Expr* expr;

				MatchAssumptionCondition(parser::ast::Expr* expr)
					: MatchAssumption(MatchAssumptionConditionTag)
					, expr(expr){
				}
			};

			struct MatchAssumptionNull: public MatchAssumption{
				MatchValue* value;

				MatchAssumptionNull(MatchValue* value)
					: MatchAssumption(MatchAssumptionNullTag)
					, value(value){
				}
			};

			struct MatchAssumptionValue: public MatchAssumption{
				MatchValue* value;
				MatchValue* valueValue;

				MatchAssumptionValue(MatchValue* value, MatchValue* valueValue)
					: MatchAssumption(MatchAssumptionValueTag)
					, value(value)
					, valueValue(valueValue){
				}
			};

			enum MatchNodeTag{
				MatchNodeSuccessTag,
				MatchNodeFailTag,
				MatchNodeEqualTag,
				MatchNodeConditionTag,
				MatchNodeMaybeTag,
			};

			struct MatchNode{
				MatchNodeTag tag;
				
				MatchNode(MatchNodeTag tag)
					: tag(tag){
				}
			};

			struct MatchSuccessIncomingValue{
				MatchSuccessIncomingValue* next;
				Value value;

				MatchSuccessIncomingValue(const Value& value)
					: next(nullptr)
					, value(value){
				}
			};

			struct MatchSuccessIncoming{
				MatchSuccessIncoming* next;
				instr::BasicBlock* bb;
				MatchSuccessIncomingValue* values;

				MatchSuccessIncoming(instr::BasicBlock* bb, MatchSuccessIncomingValue* values)
					: next(nullptr)
					, bb(bb)
					, values(values){
				}
			};

			struct MatchNodeSuccess: public MatchNode{
				u32 actionIndex;
				SrcSpan where;
				MatchTreeRemember* remember;
				List<MatchSuccessIncoming> incomings;

				MatchNodeSuccess(u32 actionIndex, const SrcSpan& where, MatchTreeRemember* remember)
					: MatchNode(MatchNodeSuccessTag)
					, actionIndex(actionIndex)
					, where(where)
					, remember(remember){
				}
			};

			struct MatchFailNodeIncoming{
				MatchFailNodeIncoming* next;
				instr::BasicBlock* bb;

				MatchFailNodeIncoming(instr::BasicBlock* bb)
					: next(nullptr)
					, bb(bb){
				}
			};

			struct MatchNodeFail: public MatchNode{
				List<MatchFailNodeIncoming> incomings;
				
				MatchNodeFail()
					: MatchNode(MatchNodeFailTag){
				}
			};

			struct MatchNodeMaybe: public MatchNode{
				MatchValue* value;
				MatchNode* nodeNull;
				MatchNode* nodeValue;
				MatchValue* valueValue;

				MatchNodeMaybe(MatchValue* value, MatchNode* nodeNull, MatchNode* nodeValue, MatchValue* valueValue)
					: MatchNode(MatchNodeMaybeTag)
					, value(value)
					, nodeNull(nodeNull)
					, nodeValue(nodeValue)
					, valueValue(valueValue){
				}
			};
						
			struct MatchNodeEqual: public MatchNode{
				MatchValue* value;
				parser::ast::Expr* expr;
				MatchNode* nodeEqual;
				MatchNode* nodeNotEqual;

				MatchNodeEqual(MatchValue* value, parser::ast::Expr* expr, MatchNode* nodeEqual, MatchNode* nodeNotEqual)
					: MatchNode(MatchNodeEqualTag)
					, value(value)
					, expr(expr)
					, nodeEqual(nodeEqual)
					, nodeNotEqual(nodeNotEqual){
				}
			};

			struct MatchNodeCondition: public MatchNode{
				parser::ast::Expr* expr;
				MatchNode* nodeTrue;
				MatchNode* nodeFalse;
				MatchTreeRemember* remember;

				MatchNodeCondition(parser::ast::Expr* expr, MatchNode* nodeTrue, MatchNode* nodeFalse, MatchTreeRemember* remember)
					: MatchNode(MatchNodeConditionTag)
					, expr(expr)
					, nodeTrue(nodeTrue)
					, nodeFalse(nodeFalse)
					, remember(remember){
				}
			};
		}
	}
}