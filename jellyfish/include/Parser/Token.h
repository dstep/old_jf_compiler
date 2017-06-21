#pragma once
#include <Support/SourceLoc.h>
#include <Support/Types.h>

namespace jf{
	namespace parser{
		struct TokenData{
			const u8* data;
			size_t length;

			TokenData(const u8* data, size_t length)
				: data(data)
				, length(length){
			}
		};

		struct Token{
			enum Type{
				#define TOKEN(t, ...) t,
				#include "TokenTypes.inc"
				Count,
				Undefined
			} type;
			SrcSpan where;
			TokenData* data;

			Token()
				: type(Undefined)
				, where(where)
				, data(nullptr){
			}

			Token(Type type, const SrcSpan& where)
				: type(type)
				, where(where)
				, data(nullptr){
			}

			Token(Type type, const SrcSpan& where, TokenData* data)
				: type(type)
				, where(where)
				, data(data){
			}

			const char* getName(){
				return GetName(type);
			}

			static const char* GetName(Type type);

			static Token GenerateToken(const Token& before, Type type);
			static Token ReplaceToken(const Token& instead, Type type);
		};
	}
}