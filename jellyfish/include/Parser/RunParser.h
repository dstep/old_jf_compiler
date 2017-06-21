#pragma once
#include <Support/Container/ArrayList.h>
#include "Token.h"
#include "ParserError.h"
#include "AST/AST.h"

namespace jf{
	namespace parser{
		static const size_t MaxReportedParserErrors = 64;
		ast::Module* ParseModule(MemoryPoolSlice* declPool, MemoryPoolSlice* symPool, MemoryPoolSlice* defPool, MemoryPoolSlice& tempPool, container::ArrayList<Token>* tokens, container::ArrayList<ParserError>* errors);
	}
}