#pragma once
#include <Support/SourceLoc.h>
#include "Common.h"

namespace jf{
	namespace parser{
		namespace ast{
			enum FunctionBodyTag{
				FunctionBodyImportTag,
				FunctionBodyDefinedTag,
				FunctionBodyExprTag
			};

			struct FunctionBody{
				SrcSpan where;
				FunctionBodyTag tag;

				FunctionBody(FunctionBodyTag tag, SrcSpan where)
					: tag(tag)
					, where(where){
				}
			};

			struct FunctionBodyImport: public FunctionBody{
				StringRef string;

				FunctionBodyImport(const SrcSpan& where, const StringRef& string)
					: FunctionBody(FunctionBodyImportTag, where)
					, string(string){
				}
			};

			struct FunctionBodyDefined: public FunctionBody{
				Stmt* stmt;

				FunctionBodyDefined(const SrcSpan& where, Stmt* stmt)
					: FunctionBody(FunctionBodyDefinedTag, where)
					, stmt(stmt){
				}
			};

			struct FunctionBodyExpr: public FunctionBody{
				Expr* expr;

				FunctionBodyExpr(const SrcSpan& where, Expr* expr)
					: FunctionBody(FunctionBodyExprTag, where)
					, expr(expr){
				}
			};

			struct ParamGroup{
				ParamGroup* next;
				Name* names;
				Type* type;
				
				ParamGroup(Name* names, Type* type)
					: names(names)
					, type(type)
					, next(nullptr){
				}
			};

			struct FunctionSignature{
				SrcSpan where;
				ParamGroup* params;
				Type* returnType;

				FunctionSignature(const SrcSpan& where, ParamGroup* params, Type* returnType)
					: params(params)
					, returnType(returnType)
					, where(where){
				}
			};
		}
	}
}