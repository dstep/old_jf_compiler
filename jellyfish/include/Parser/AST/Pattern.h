#pragma once
#include "Common.h"

namespace jf{
	namespace parser{
		namespace ast{
			enum PatternTag{
				PatternPrimTag,
				PatternQuoteTag,
				PatternNumberTag,
				PatternStringTag,
				PatternRememberTag,
				PatternConsTag,
				PatternEnumTag,
				PatternVarTag,
				PatternTupleTag
			};

			struct Pattern{
				Pattern* next;
				PatternTag tag;
				SrcSpan where;

				Pattern(PatternTag tag, const SrcSpan& where)
					: tag(tag)
					, next(nullptr)
					, where(where){
				}
			};

			struct PatternPrim: public Pattern{
				enum ID{
					Unit,
					True,
					False,
					Null,
					Wildcard
				} id;

				PatternPrim(const SrcSpan& where, ID id)
					: Pattern(PatternPrimTag, where)
					, id(id){
				}
			};

			struct PatternRemember: public Pattern{
				Pattern* pattern;
				StringRef name;

				PatternRemember(const SrcSpan& where, Pattern* pattern, const StringRef& name)
					: Pattern(PatternRememberTag, where)
					, pattern(pattern)
					, name(name){
				}
			};
			
			struct PatternNumber: public Pattern{
				StringRef name;

				PatternNumber(const SrcSpan& where, const StringRef& name)
					: Pattern(PatternNumberTag, where)
					, name(name){
				}
			};

			struct PatternString: public Pattern{
				StringRef name;

				PatternString(const SrcSpan& where, const StringRef& name)
					: Pattern(PatternStringTag, where)
					, name(name){
				}
			};

			struct PatternQuote: public Pattern{
				Expr* expr;

				PatternQuote(const SrcSpan& where, Expr* expr)
					: Pattern(PatternQuoteTag, where)
					, expr(expr){
				}
			};

			struct PatternTuple: public Pattern{
				Pattern* params;

				PatternTuple(const SrcSpan& where, Pattern* params)
					: Pattern(PatternTupleTag, where)
					, params(params){
				}
			};

			struct PatternCons: public Pattern{
				QualID* name;
				Pattern* params;

				PatternCons(const SrcSpan& where, QualID* name, Pattern* params)
					: Pattern(PatternConsTag, where)
					, name(name)
					, params(params){
				}
			};

			struct EnumConstructorNumber{
				SrcSpan where;
				u32 pointedConstructor;
				u32 constructorsCount;

				EnumConstructorNumber(const SrcSpan& where, u32 pointedConstructor, u32 constructorsCount)
					: where(where)
					, pointedConstructor(pointedConstructor)
					, constructorsCount(constructorsCount){					
				}
			};

			struct PatternEnum: public Pattern{
				EnumConstructorNumber cons;
				Pattern* params;

				PatternEnum(const SrcSpan& where, EnumConstructorNumber cons, Pattern* params)
					: Pattern(PatternEnumTag, where)
					, cons(cons)
					, params(params){
				}
			};

			struct PatternVar: public Pattern{
				StringRef name;

				PatternVar(const SrcSpan& where, const StringRef& name)
					: Pattern(PatternVarTag, where)
					, name(name){
				}
			};
		}
	}
}