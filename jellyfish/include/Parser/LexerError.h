#pragma once 
#include <Support/SourceLoc.h>
#include <Support/StringRef.h>

namespace jf{
	namespace parser{
		class LexerError{
		public:
			enum Type{
				#define LEXER_ERROR(e, ...) e,
				#include "LexerErrors.inc"
			};

			LexerError(Type type, SrcSpan where, const StringRef& relatedText);

			Type getType(){
				return type;
			}

			SrcSpan getSrcLoc(){
				return where;
			}

			StringRef getRelatedText(){
				return relatedText;
			}

			const char* getQualCode(){
				return GetQualCode(type);
			}

			static const char* GetQualCode(Type type);
		private:
			Type type;
			SrcSpan where;
			StringRef relatedText;
		};
	}
}