#include <Parser/RunLexer.h>
#include <Support/Container/ArrayList.h>
#include <Support/String/ParseString.h>

namespace jf{
	namespace parser{
		class Lexer{
		public:
			Lexer(MemoryPoolSlice* hostPool, MemoryPoolSlice* stringLiteralPool, MemoryPoolSlice& tempPool, container::ArrayList<Token>* tokens, container::ArrayList<LexerError>* errors)
				: hostPool(hostPool)
				, tempPool(tempPool)
				, stringLiteralPool(stringLiteralPool)
				, bufferContent(&tempPool)
				, bufferStart(SrcLoc::Undefined())
				, tokens(tokens)
				, errors(errors){

				line = 1;
				col = 0;
			}

			~Lexer(){
				tokens->push(Token(Token::EndOfFile, SrcSpan(SrcLoc(line, col), SrcLoc(line, col))));
			}

			void countKeyword(Token::Type type, size_t length){
				tokens->push(Token(type, SrcSpan(line, col, line, (u32)(col + length))));
				col += (u32)length;
			}

			void countAndCopyASCII(Token::Type type, const u8* start, size_t length){
				tokens->push(Token(type, SrcSpan(line, col, line, (u32)(col + length)), makeToken(start, length)));
				col += (u32)length;
			}

			void countChars(size_t length){
				col += (u32)length;
			}

			void countNewline(){
				col = 0;
				line++;
			}

			void countUnexpected(const u8* data, size_t length){
				SrcLoc start(line, col);
				countCodepoints(data, length);
				SrcLoc end(line, col);
				reportError(LexerError(LexerError::InvalidSequence, SrcSpan(start, end), StringRef(data, length)));
			}

			void bufferCodepoints(const u8* data, size_t length){
				countCodepoints(data, length);
				for ( size_t i = 0; i < length; i++ ){
					bufferContent.push(data[i]);
				}
			}

			void countCodepoints(const u8* data, size_t length){
				for ( size_t i = 0; i < length; i++ ){
					if ( data[i] == '\n' ){
						if ( i < length && data[i + 1] == '\r' ){
							i++;
						}
						countNewline();
					}else if ( data[i] == '\r' ){
						if ( i < length && data[i + 1] == '\n' ){
							i++;
						}
						countNewline();
					}else if ( data[i] < 128 ){
						col++;
					}else if ( data[i] < 128 + 64 ){
						i++;
					}else if ( data[i] < 128 + 64 + 32 ){
						col++;
						i++;
					}else if ( data[i] < 128 + 64 + 32 + 16 ){
						col++;
						i += 2;
					}else if ( data[i] < 128 + 64 + 32 + 16 + 8 ){
						col++;
						i += 3;
					}else if ( data[i] < 128 + 64 + 32 + 16 + 8 + 4 ){
						col++;
						i += 4;
					}else{
						col++;
						i += 5;
					}
				}
			}

			void bufferUTF8(u32 codepoint){
				string::UTF8EncodeCodepoint(bufferContent, codepoint);
			}

			void bufferUTF8FromHex(const u8* hexdigits, size_t count){
				u32 value = 0;
				bool valid = true;
				for ( size_t i = 0; i < count; i++ ){
					value = (value << 4) | string::ParseHex(hexdigits[i], &valid);
				}
				if ( !valid ){
					reportError(LexerError(LexerError::InvalidSequence, SrcSpan(line, col, line, col), StringRef(hexdigits, count)));
				}
				bufferUTF8(value);
			}

			void reportError(const LexerError& error){
				if ( errors->getSize() < MaxReportedLexerErrors ){
					errors->push(error);
				}
			}

			void reportHere(LexerError::Type type){
				reportError(LexerError(type, SrcSpan(line, col, line, col), StringRef()));
			}

			void beginBuffer(){
				bufferStart = SrcLoc(line, col);
			}

			void endBuffer(Token::Type type){
				ArrayRef<u8> contents = bufferContent.slice(stringLiteralPool);
				tokens->push(Token(type, SrcSpan(bufferStart, SrcLoc(line, col)), makeToken(contents.getRaw(), contents.getSize())));
				bufferContent.clear();
			}
		private:
			TokenData* makeToken(const u8* start, size_t length){
				return new(hostPool->allocate(sizeof(TokenData)))TokenData(start, length);
			}

			SrcLoc bufferStart;

			container::ArrayList<Token>* tokens;
			container::ArrayList<LexerError>* errors;

			container::ArrayList<u8> bufferContent;

			MemoryPoolSlice* hostPool;
			MemoryPoolSlice* stringLiteralPool;
			MemoryPoolSlice& tempPool;

			u32 line;
			u32 col;
		};
	}
}

void lexx_run(jf::parser::Lexer* lexer, const jf::u8* data, size_t size);