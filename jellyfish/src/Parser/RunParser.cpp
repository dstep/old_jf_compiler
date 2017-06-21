#include <Parser/RunParser.h>
#include "../parsx/parsx_parser.h"

namespace jf{
	namespace parser{
		ast::Module* ParseModule(MemoryPoolSlice* declPool, MemoryPoolSlice* symPool, MemoryPoolSlice* defPool, MemoryPoolSlice& tempPool, container::ArrayList<Token>* tokens, container::ArrayList<ParserError>* errors){
			parsx::ParserContext* context = (parsx::ParserContext*)tempPool.allocate(sizeof(parsx::ParserContext));
			
			new(&context->tokens)parsx::parsx_token_queue(&tempPool);
			new(&context->peek)parsx::parsx_token_queue(&tempPool);
			new(&context->ll)parsx::parsx_stack(&tempPool);
			new(&context->actions)parsx::parsx_queue(&tempPool);
			new(&context->values)parsx::parsx_datastack(&tempPool);
			new(&context->lexer)parsx::parsx_lexer(tokens);
			new(&context->custom)parsx::parsx_custom(declPool, symPool, defPool, &tempPool, errors);

			return parsx::parse::ParseModule(*context);
		}
	}
}