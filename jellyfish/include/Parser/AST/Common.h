#pragma once
#include <Support/SourceLoc.h>
#include <Support/StringRef.h>
#include <Support/IntrusiveList.h>

namespace jf{
	namespace parser{
		namespace ast{
			struct QualID{
				SrcSpan where;
				StringRef id;
				QualID* prev;

				QualID(SrcSpan where, StringRef id)
					: where(where)
					, id(id)
					, prev(nullptr){
				}

				QualID(SrcSpan where, QualID* prev, StringRef id)
					: where(where)
					, id(id)
					, prev(prev){
				}
			};


			struct Expr;
			struct Type;
			struct Stmt;
			struct Pattern;
			
			struct ExprList{
				ExprList* next;
				Expr* expr;

				ExprList(Expr* expr)
					: expr(expr)
					, next(nullptr){					
				}
			};

			struct Name{
				Name* next;
				SrcSpan where;
				StringRef id;

				Name(const SrcSpan& where, const StringRef& id)
					: where(where)
					, id(id)
					, next(nullptr){
				}
			};

			template<class T>
			struct WithSrcLoc{
				SrcLoc srcLoc;
				T value;

				WithSrcLoc(const SrcLoc& srcLoc, const T& value)
					: srcLoc(srcLoc)
					, value(value){
				}

				operator T&(){
					return value;
				}

				operator const SrcLoc&(){
					return srcLoc;
				}
			};

			template<class Action>
			struct MatchBranch{
				MatchBranch<Action>* next;
				SrcSpan where;
				Expr* guard;
				Action* action;

				MatchBranch(const SrcSpan& where, Expr* guard, Action* action)
					: next(nullptr)
					, guard(guard)
					, action(action)
					, where(where){
				}

				MatchBranch(const SrcSpan& where, Expr* guard, Action* action, MatchBranch<Action>* next)
					: next(next)
					, guard(guard)
					, action(action)
					, where(where){
				}
			};

			template<class Action>
			struct MatchCase{
				MatchCase<Action>* next;
				SrcSpan where;
				Pattern* patterns;
				MatchBranch<Action>* branches;

				MatchCase(const SrcSpan& where, Pattern* patterns, MatchBranch<Action>* branches)
					: where(where)
					, next(nullptr)
					, patterns(patterns)
					, branches(branches){
				}
			};

			struct ConstructorStringPart{
				ConstructorStringPart* next;
				ConstructorStringPart* prev;
				SrcSpan where;
				StringRef name;
				ExprList* params;

				ConstructorStringPart(ConstructorStringPart* prev, const SrcSpan& where, const StringRef& name, ExprList* params)
					: prev(prev)
					, next(nullptr)
					, where(where)
					, name(name)
					, params(params){
					if ( prev ){
						prev->next = this;
					}
				}
			};
						
			struct AssignPair{
				AssignPair* next;
				Name* names;
				Expr* value;

				AssignPair(Name* names, Expr* value)
					: next(nullptr)
					, names(names)
					, value(value){
				}
			};
		}
	}
}	