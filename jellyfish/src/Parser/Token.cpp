#include <Parser/Token.h>

namespace jf{
	namespace parser{
		static const char* TokenNames[] = {
				#define TOKEN(t, ...) "Token." #t,
				#include <Parser/TokenTypes.inc>
				""
			};

		const char* Token::GetName(Token::Type type){
			return TokenNames[type];
		}

		Token Token::GenerateToken(const Token& before, Type type){
			Token token(before);
			token.where = SrcSpan(before.where.from(), before.where.from());
			token.type = type;
			token.data = nullptr;
			return token;
		}

		Token Token::ReplaceToken(const Token& instead, Type type){
			Token token = GenerateToken(instead, type);
			token.where = instead.where;
			return token;
		}
	}
}