#include <Parser/RunLexer.h>
#include <Parser/LexerImpl.h>

namespace jf{
	namespace parser{
		void RunLexer(const StringRef& input, MemoryPoolSlice* hostPool, MemoryPoolSlice* stringLiteralPool, MemoryPoolSlice& tempPool, container::ArrayList<Token>* tokens, container::ArrayList<LexerError>* errors){
			Lexer lexer(hostPool, stringLiteralPool, tempPool, tokens, errors);
			lexx_run(&lexer, input.getData(), input.getLength());
		}
	}
}