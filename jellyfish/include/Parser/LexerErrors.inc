#if !defined(LEXER_ERROR)
#error Define LEXER_ERROR first
#endif

LEXER_ERROR(InvalidSequence)
LEXER_ERROR(UnterminatedComment)
LEXER_ERROR(UnterminatedStringLiteral)

#undef LEXER_ERROR