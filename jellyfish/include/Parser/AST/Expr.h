#pragma once
#include "Common.h"

namespace jf{
	namespace parser{
		namespace ast{
			enum ExprTag{
				ExprUnitTag,
				ExprTrueTag,
				ExprFalseTag,
				ExprNullTag,
				ExprStringTag,
				ExprNumberTag,
				ExprBinOpTag,
				ExprUnOpTag,
				ExprCoerceTag,
				ExprIfTag,
				ExprIDTag,
				ExprMissingTag,
				ExprCallTag,
				ExprSubscriptTag,
				ExprInstanceTag,
				ExprTupleTag,
				ExprMatchTag,
				ExprNewTag,
				ExprWithTag,
				ExprLambdaTag
			};

			struct Expr{
				ExprTag tag;
				SrcSpan where;

				Expr(ExprTag tag, const SrcSpan& where)
					: tag(tag)
					, where(where){
				}
			};

			struct ExprMissing: public Expr{
				ExprMissing(const SrcLoc& where)
					: Expr(ExprMissingTag, SrcSpan(where, where)){
				}
			};

			struct ExprUnit: public Expr{
				ExprUnit(const SrcSpan& where)
					: Expr(ExprUnitTag, where){
				}
			};

			struct ExprTrue: public Expr{
				ExprTrue(const SrcSpan& where)
					: Expr(ExprTrueTag, where){
				}
			};

			struct ExprFalse: public Expr{
				ExprFalse(const SrcSpan& where)
					: Expr(ExprFalseTag, where){
				}
			};

			struct ExprNull: public Expr{
				ExprNull(const SrcSpan& where)
					: Expr(ExprNullTag, where){
				}
			};
			
			struct ExprString: public Expr{
				StringRef content;

				ExprString(const SrcSpan& where, const StringRef& content)
					: Expr(ExprStringTag, where)
					, content(content){
				}
			};

			struct ExprNumber: public Expr{
				StringRef content;

				ExprNumber(const SrcSpan& where, const StringRef& content)
					: Expr(ExprNumberTag, where)
					, content(content){
				}
			};

			struct ExprID: public Expr{
				StringRef content;

				ExprID(const SrcSpan& where, const StringRef& content)
					: Expr(ExprIDTag, where)
					, content(content){
				}
			};

			struct ExprBinOp: public Expr{
				enum ID{
					Concat,
					Plus,
					Minus,
					Mult,
					Div,
					Rem,
					EQ,
					NE,
					LT,
					GT,
					LE,
					GE,
					And,
					Or
				} id;
				Expr* lhs;
				Expr* rhs;

				ExprBinOp(const SrcSpan& where, ID id, Expr* lhs, Expr* rhs)
					: Expr(ExprBinOpTag, where)
					, id(id)
					, lhs(lhs)
					, rhs(rhs){
				}
			};

			struct ExprUnOp: public Expr{
				enum ID{
					Negate,
					Not
				} id;
				Expr* operand;

				ExprUnOp(const SrcSpan& where, ID id, Expr* operand)
					: Expr(ExprUnOpTag, where)
					, id(id)
					, operand(operand){
				}
			};

			struct ExprCoerce: public Expr{
				Expr* expr;
				Type* type;

				ExprCoerce(const SrcSpan& where, Expr* expr, Type* type)
					: Expr(ExprCoerceTag, where)
					, expr(expr)
					, type(type){
				}
			};

			struct ExprIf: public Expr{
				Expr* cond;
				Expr* then;
				Expr* else_;

				ExprIf(const SrcSpan& where, Expr* cond, Expr* then, Expr* else_)
					: Expr(ExprIfTag, where)
					, cond(cond)
					, then(then)
					, else_(else_){
				}
			};

			struct ExprCall: public Expr{
				Expr* callee;
				ExprList* params;

				ExprCall(const SrcSpan& where, Expr* callee, ExprList* params)
					: Expr(ExprCallTag, where)
					, callee(callee)
					, params(params){
				}
			};

			struct ExprTuple: public Expr{
				ExprList* params;

				ExprTuple(const SrcSpan& where, ExprList* params)
					: Expr(ExprTupleTag, where)
					, params(params){
				}
			};

			struct ExprSubscript: public Expr{
				StringRef id;
				Expr* lhs;

				ExprSubscript(const SrcSpan& where, Expr* lhs, const StringRef& id)
					: Expr(ExprSubscriptTag, where)
					, id(id)
					, lhs(lhs){
				}
			};

			struct ExprInstance: public Expr{
				Expr* lhs;
				TypeList* params;

				ExprInstance(const SrcSpan& where, Expr* lhs, TypeList* params)
					: Expr(ExprInstanceTag, where)
					, params(params)
					, lhs(lhs){
				}
			};

			struct ExprMatch: public Expr{
				ExprList* params;
				MatchCase<Expr>* cases;

				ExprMatch(const SrcSpan& where, ExprList* params, MatchCase<Expr>* cases)
					: Expr(ExprMatchTag, where)
					, params(params)
					, cases(cases){
				}
			};

			struct ExprWith: public Expr{
				Expr* lhs;
				AssignPair* values;

				ExprWith(const SrcSpan& where, Expr* lhs, AssignPair* values)
					: Expr(ExprWithTag, where)
					, lhs(lhs)
					, values(values){
				}
			};

			struct ExprNew: public Expr{
				QualID* id;
				ConstructorStringPart* consString;

				ExprNew(const SrcSpan& where, QualID* id, ConstructorStringPart* consString)
					: Expr(ExprNewTag, where)
					, id(id)
					, consString(consString){
				}
			};

			struct ExprLambda: public Expr{
				FunctionSignature* signature;
				FunctionBody* body;

				ExprLambda(const SrcSpan& where, FunctionSignature* signature, FunctionBody* body)
					: Expr(ExprLambdaTag, where)
					, signature(signature)
					, body(body){
				}
			};
		}
	}
}