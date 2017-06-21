#include <Parser/LexerError.h>

namespace jf{
	namespace parser{
		static const char* LexerErrors[] = {
				#define LEXER_ERROR(e, ...) "LexerError." #e,
				#include <Parser/LexerErrors.inc>
				""
			};

		const char* LexerError::GetQualCode(Type type){
			return LexerErrors[type];
		}

		LexerError::LexerError(Type type, SrcSpan where, const StringRef& relatedText)
			: type(type)
			, where(where)
			, relatedText(relatedText){
		}
	}
}