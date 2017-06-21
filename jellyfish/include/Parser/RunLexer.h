#pragma once
#include <Support/ArrayRef.h>
#include <Support/Container/ArrayList.h>
#include "LexerError.h"
#include "Token.h"

namespace jf{
	namespace parser{
		static const u32 TabLength = 4;
		static const u32 MaxReportedLexerErrors = 32;
		void RunLexer(const StringRef& input, MemoryPoolSlice* hostPool, MemoryPoolSlice* stringLiteralPool, MemoryPoolSlice& tempPool, container::ArrayList<Token>* tokens, container::ArrayList<LexerError>* errors);
	}
}