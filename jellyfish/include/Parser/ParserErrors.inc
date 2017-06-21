#if !defined(PARSER_ERROR)
#error Define PARSER_ERROR first
#endif

PARSER_ERROR(MisplacedToken)
PARSER_ERROR(MissingToken)
PARSER_ERROR(SwapTokens)
PARSER_ERROR(ReplaceToken)
PARSER_ERROR(UnexpectedToken)

#undef PARSER_ERROR