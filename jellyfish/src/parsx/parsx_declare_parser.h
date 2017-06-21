namespace parsx_namespace{
	typedef int State;
	typedef int Action;

	#define parsx_symbol_state(state, Symbol, type) namespace States{static const State Symbol = state;} namespace parse{ type Parse##Symbol(ParserContext& parsx_ctx); }
	#if !defined(parsx_core)
	#error Define parsx_core
	#endif
	

	struct ParserContext{
		//shifted but not consumed tokens
		//limited to backtrack + lookahead + 2 + max_corrections
		parsx_token_queue tokens;
		//peek is limited to backtrack + lookahead + 2 + max_corrections
		parsx_token_queue peek;

		//shifted but not applied actions
		//limited to some value related with tokens and grammar depth
		parsx_queue actions;

		parsx_stack ll;
		parsx_datastack values;

		parsx_lexer lexer;

		parsx_custom custom;
	};

	#include parsx_core
	#undef parsx_symbol_state

	void parse_general(ParserContext& ctx);
}


