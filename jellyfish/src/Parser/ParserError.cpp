#include <Parser/ParserError.h>

namespace jf{
	namespace parser{
		static const char* ParserErrors[] = {
				#define PARSER_ERROR(e, ...) "ParserError." #e,
				#include <Parser/ParserErrors.inc>
				""
			};

		const char* ParserError::GetQualCode(Type type){
			return ParserErrors[type];
		}

		ParserError::ParserError(Type type, SrcSpan where, const Token& relatedToken, const Token& secondToken)
			: type(type)
			, where(where)
			, relatedToken(relatedToken)
			, secondToken(secondToken)
			, expected(nullptr){
		}

		void ParserError::addExpected(MemoryPoolSlice* pool, const char* expected){
			ParserErrorExpected* myExpected = this->expected;
			while ( myExpected ){
				if ( !strcmp(myExpected->expected, expected) ){
					return;
				}
				myExpected = myExpected->next;
			}

			ParserErrorExpected* newExpected = (ParserErrorExpected*)pool->allocate(sizeof(ParserErrorExpected));
			newExpected->expected = expected;
			newExpected->next = this->expected;
			this->expected = newExpected;
		}
	}
}