#pragma once
#include "../StringRef.h"
#include "../MemoryAPI.h"
#include "../Container/ArrayList.h"

namespace jf{
	namespace string{
		namespace ParseError{
			enum Value{
				UnterminatedSingleQuote,
				UnterminatedDoubleQuote,
				InvalidEscapeSequence,
				ExpectedIdentifier,
				EmptyQualID
			};
		}

		struct LineCounter{
			u32 line;
			u32 expectNewline;

			LineCounter(u32 line)
				: line(line)
				, expectNewline(0){
			}

			void count(u8 character){
				if ( character == '\n' ){
					if ( expectNewline == 1 ){
						expectNewline = 0;
						line++;
					}else{
						expectNewline = 2;
					}
				}else if ( character == '\r' ){
					if ( expectNewline == 2 ){
						expectNewline = 0;
						line++;
					}else{
						expectNewline = 1;
					}
				}else{
					expectNewline = 0;
				}
			}

			u32 getCurrentLine(){
				return line;
			}
		};

		inline bool PredicateWhitespace(const u8* data, size_t length){
			if ( length == 0 ){
				return false;
			}
			switch ( *data ){
			case 0x09:case 0x0A:case 0x0B:case 0x0C:case 0x0D:case 0x20:case 0x85:case 0xA0:
				return true;
			}
			return false;
		}

		inline bool PredicateWhitespaceOrQuote(const u8* data, size_t length){
			if ( length == 0 ){
				return false;
			}
			switch ( *data ){
			case '"':
			case '\'':return true;
			}
			return PredicateWhitespace(data, length);
		}

		inline bool PredicateSingleQuote(const u8* data, size_t length){
			if ( length == 0 ){
				return false;
			}
			if ( *data == '\'' ){
				return true;
			}
			return false;
		}

		inline bool PredicateDoubleQuote(const u8* data, size_t length){
			if ( length == 0 ){
				return false;
			}
			if ( *data == '"' ){
				return true;
			}
			return false;
		}
		
		template<typename SkipPredicate> 
		void SkipWhile(SkipPredicate& predicate, StringRef& source){
			const u8* data = source.getData();
			size_t length = source.getLength();
			while ( length && predicate(data, length) ){
				data++;
				length--;
			}
			source = StringRef(data, length);
		}

		inline u32 ParseHex(u8 ch, bool* valid){
			if ( ch >= '0' && ch <= '9' ){
				return ch - '0';
			}else if ( ch >= 'a' && ch <= 'f' ){
				return ch - 'a' + 10;
			}else if ( ch >= 'A' && ch <= 'F' ){
				return ch - 'A' + 10;
			}else{
				*valid = false;
				return 0;
			}
		}

		inline void UTF8EncodeCodepoint(container::ArrayList<u8>& output, u32 codepoint){
			u8 sixtets[6];
			if ( codepoint < (1U << 8U) ){
				output.push(codepoint);
			}else{
				u32 i = 5;
				do{
					i--;
					sixtets[i] = codepoint & 63;
					codepoint >>= 6;
				}while(codepoint);
			
				u8 byte = codepoint;
				switch ( i ){
				case 0: byte |= 128 + 64 + 32 + 16 + 8 + 4; break;
				case 1: byte |= 128 + 64 + 32 + 16 + 8; break;
				case 2: byte |= 128 + 64 + 32 + 16; break;
				case 3: byte |= 128 + 64 + 32; break;
				case 4: byte |= 128 + 64; break;
				}
				output.push(byte);
				for ( ; i < 6; i++ ){
					output.push(128 + sixtets[i]);
				}	
			}
		}

		/**
		* Parses the string from the supplied source.
		*/
		template<typename StopPredicate, typename ErrorReporting>
		StringRef ParseString(MemoryPoolSlice* hostPool, MemoryPoolSlice& tempPool, StringRef& source, StopPredicate& predicate, ErrorReporting& reporting){
			container::ArrayList<u8> result(&tempPool);
			const u8* data = source.getData();
			size_t length = source.getLength();
			#define advance() (data++,length--)
			#define advance_n(n) (data += n,length -= n)
			while ( length && !predicate(data, length) ){
				switch ( data[0] ){
				case '\\':{
					if ( length > 1 ){
						switch ( data[1] ){
						case '\\':
							result.push('\\');
							advance_n(2);
						break;
						case 'n':
							result.push('\n');
							advance_n(2);
						break;
						case 'r':
							result.push('\r');
							advance_n(2);
						break;
						case 't':
							result.push('\t');
							advance_n(2);
						break;
						case '0':
							result.push('\0');
							advance_n(2);
						break;
						case '"':
							result.push('"');
							advance_n(2);
						break;
						case '\'':
							result.push('\'');
							advance_n(2);
						break;
						case 'x':{
							if ( length >= 4 ){
								bool valid = true;
								u32 high = ParseHex(data[2], &valid);
								u32 low = ParseHex(data[3], &valid);
								if ( valid ){
									UTF8EncodeCodepoint(result, (high << 4) | low);
								}else{
									reporting(ParseError::InvalidEscapeSequence, StringRef(data, 4));
								}
								advance_n(4);
							}else{
								reporting(ParseError::InvalidEscapeSequence, StringRef(data, length));
								length = 0;
							}
						}break;
						case 'u':{
							if ( length >= 6 ){
								bool valid = true;
								u32 h0 = ParseHex(data[2], &valid);
								u32 h1 = ParseHex(data[3], &valid);
								u32 h2 = ParseHex(data[4], &valid);
								u32 h3 = ParseHex(data[5], &valid);
								if ( valid ){
									UTF8EncodeCodepoint(result, (h0 << 12) | (h1 << 8) | (h2 << 4) | h3);
								}else{
									reporting(ParseError::InvalidEscapeSequence, StringRef(data, 6));
								}
								advance_n(6);
							}else{
								reporting(ParseError::InvalidEscapeSequence, StringRef(data, length));
								length = 0;
							}
						}break;
						case 'U':{
							if ( length >= 10 ){
								bool valid = true;
								u32 h0 = ParseHex(data[2], &valid);
								u32 h1 = ParseHex(data[3], &valid);
								u32 h2 = ParseHex(data[4], &valid);
								u32 h3 = ParseHex(data[5], &valid);
								u32 h4 = ParseHex(data[6], &valid);
								u32 h5 = ParseHex(data[7], &valid);
								u32 h6 = ParseHex(data[8], &valid);
								u32 h7 = ParseHex(data[9], &valid);
								if ( valid ){
									UTF8EncodeCodepoint(result, (h0 << 28) | (h1 << 24) | (h2 << 20) | (h3 << 16) | (h4 << 12) | (h5 << 8) | (h6 << 4) | h7);
								}else{
									reporting(ParseError::InvalidEscapeSequence, StringRef(data, 10));
								}
								advance_n(10);
							}else{
								reporting(ParseError::InvalidEscapeSequence, StringRef(data, length));
								length = 0;
							}
						}
						default:{
							reporting(ParseError::InvalidEscapeSequence, StringRef(data, 2));
							advance();
							advance();
						}break;
						}
					}else{
						reporting(ParseError::InvalidEscapeSequence, StringRef(data, length));
						advance();
					}
				}break;
				default:{
					result.push(*data);
					advance();
				}break;
				}
			}
			#undef advance
			#undef advance_n
			source = StringRef(data, length);
			return result.slice(hostPool);
		}

		/**
		* Parses the next word from the supplied source.
		* Skips all whitespace characters from the start
		*/
		template<class ErrorReportig>
		StringRef ParseWord(MemoryPoolSlice* hostPool, MemoryPoolSlice& tempPool, StringRef& source, ErrorReportig& reporting){
			SkipWhile(PredicateWhitespace, source);
			if ( source.getLength() == 0 ){
				return StringRef();
			}else{
				if ( source.getData()[0] == '"' ){
					source = StringRef(source.getData() + 1, source.getLength() - 1);
					StringRef string = ParseString(hostPool, tempPool, source, PredicateDoubleQuote, reporting);
					if ( PredicateDoubleQuote(source.getData(), source.getLength()) ){
						source = StringRef(source.getData() + 1, source.getLength() - 1);
					}else{
						reporting(ParseError::UnterminatedSingleQuote, source);
					}
					return string;
				}else if ( source.getData()[0] == '\'' ){
					source = StringRef(source.getData() + 1, source.getLength() - 1);
					StringRef string = ParseString(hostPool, tempPool, source, PredicateSingleQuote, reporting);
					if ( PredicateSingleQuote(source.getData(), source.getLength()) ){
						source = StringRef(source.getData() + 1, source.getLength() - 1);
					}else{
						reporting(ParseError::UnterminatedDoubleQuote, source);
					}
					return string;
				}else{
					return ParseString(hostPool, tempPool, source, PredicateWhitespaceOrQuote, reporting);
				}
			}			
		}		
	}
}