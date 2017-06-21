#pragma once 
#include <Support/SourceLoc.h>
#include <Support/StringRef.h>
#include "Token.h"

namespace jf{
	namespace parser{
		struct ParserErrorExpected{
			ParserErrorExpected* next;
			const char* expected;
		};

		class ParserError{
		public:
			enum Type{
				#define PARSER_ERROR(e, ...) e,
				#include "ParserErrors.inc"
			};

			ParserError(Type type, SrcSpan where, const Token& relatedToken, const Token& secondToken = Token());

			void addExpected(MemoryPoolSlice* pool, const char* expected);

			Type getType(){
				return type;
			}

			SrcSpan getSrcLoc(){
				return where;
			}

			Token getRelatedToken(){
				return relatedToken;
			}

			Token getSecondToken(){
				return secondToken;
			}

			const char* getQualCode(){
				return GetQualCode(type);
			}

			ParserErrorExpected* getExpected(){
				return expected;
			}

			static const char* GetQualCode(Type type);
		private:
			Type type;
			SrcSpan where;
			Token relatedToken, secondToken;
			ParserErrorExpected* expected;
		};
	}
}