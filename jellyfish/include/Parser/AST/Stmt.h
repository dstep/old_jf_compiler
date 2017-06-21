#pragma once
#include "Common.h"
#include "Expr.h"

namespace jf{
	namespace parser{
		namespace ast{
			enum StmtTag{
				StmtEvalTag,
				StmtAssignTag,
				StmtIfTag,
				StmtForTag,
				StmtWhileTag,
				StmtRepeatTag,
				StmtVarTag,
				StmtLetTag,
				StmtMatchTag,
				StmtConstructTag,
				StmtConstructPassTag,
				StmtBlockTag,
				StmtFFITag
			};

			struct Stmt{
				Stmt* next;
				StmtTag tag;
				SrcSpan where;

				Stmt(StmtTag tag, const SrcSpan& where)
					: tag(tag)
					, where(where)
					, next(nullptr){
				}
			};

			struct StmtEval: public Stmt{
				enum Kind{
					Naked,
					Eval,
					Return,
					Raise
				} kind;
				Expr* expr;

				StmtEval(const SrcSpan& where, Kind kind, Expr* expr)
					: Stmt(StmtEvalTag, where)
					, kind(kind)
					, expr(expr){
				}
			};

			struct StmtAssign: public Stmt{
				ExprList* lhs;
				ExprList* rhs;

				StmtAssign(const SrcSpan& where, ExprList* lhs, ExprList* rhs)
					: Stmt(StmtAssignTag, where)
					, lhs(lhs)
					, rhs(rhs){
				}
			};

			struct StmtIf: public Stmt{
				Expr* cond;
				Stmt* then;
				Stmt* else_;

				StmtIf(const SrcSpan& where, Expr* cond, Stmt* then, Stmt* else_)
					: Stmt(StmtIfTag, where)
					, cond(cond)
					, then(then)
					, else_(else_){
				}
			};

			struct StmtFor: public Stmt{
				Name* names;
				Expr* expr;
				Stmt* stmts;

				StmtFor(const SrcSpan& where, Name* names, Expr* expr, Stmt* stmts)
					: Stmt(StmtForTag, where)
					, names(names)
					, expr(expr)
					, stmts(stmts){
				}
			};

			struct StmtWhile: public Stmt{
				Expr* cond;
				Stmt* stmts;

				StmtWhile(const SrcSpan& where, Expr* cond, Stmt* stmts)
					: Stmt(StmtWhileTag, where)
					, cond(cond)
					, stmts(stmts){
				}
			};

			struct StmtRepeat: public Stmt{
				Stmt* stmts;
				Expr* cond;				

				StmtRepeat(const SrcSpan& where, Stmt* stmts, Expr* cond)
					: Stmt(StmtRepeatTag, where)
					, cond(cond)
					, stmts(stmts){
				}
			};

			struct StmtBlock: public Stmt{
				Stmt* stmts;

				StmtBlock(const SrcSpan& where, Stmt* stmts)
					: Stmt(StmtBlockTag, where)
					, stmts(stmts){
				}
			};

			struct StmtVar: public Stmt{
				Name* names;
				Type* type;
				Expr* expr;

				StmtVar(const SrcSpan& where, Name* names, Type* type, Expr* expr)
					: Stmt(StmtVarTag, where)
					, names(names)
					, type(type)
					, expr(expr){
				}
			};

			struct StmtLet: public Stmt{
				Pattern* patterns;
				ExprList* expr;

				StmtLet(const SrcSpan& where, Pattern* patterns, ExprList* expr)
					: Stmt(StmtLetTag, where)
					, patterns(patterns)
					, expr(expr){
				}
			};

			struct StmtMatch: public Stmt{
				ExprList* values;
				MatchCase<Stmt>* cases;

				StmtMatch(const SrcSpan& where, ExprList* values, MatchCase<Stmt>* cases)
					: Stmt(StmtMatchTag, where)
					, values(values)
					, cases(cases){
				}
			};

			struct StmtConstruct: public Stmt{
				ConstructorStringPart* consString;
				AssignPair* pairs;

				StmtConstruct(const SrcSpan& where, ConstructorStringPart* consString, AssignPair* pairs)
					: Stmt(StmtConstructTag, where)
					, consString(consString)
					, pairs(pairs){
				}
			};

			struct StmtConstructPass: public Stmt{
				ConstructorStringPart* consString;

				StmtConstructPass(const SrcSpan& where, ConstructorStringPart* consString)
					: Stmt(StmtConstructTag, where)
					, consString(consString){
				}
			};

			struct StmtFFI: public Stmt{
				StringRef string;

				StmtFFI(const SrcSpan& where, const StringRef& string)
					: Stmt(StmtFFITag, where)
					, string(string){
				}
			};
		}
	}
}