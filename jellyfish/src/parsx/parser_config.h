#pragma once

#include <Parser/RunParser.h>
#include <Parser/Token.h>
#include <Parser/ParserError.h>
#include <Support/Container/ArrayList.h>
#include <stdexcept>

#include <Parser/AST/AST.h>
namespace parsx{
	using namespace jf;
	using namespace parser::ast;
}

namespace jf{
	namespace parser{
		class ParserException: public std::runtime_error{
		public:
			ParserException(ParserError::Type type) : std::runtime_error(ParserError::GetQualCode(type)){}
		};

		#define LARGE_SYMBOL_THRESHOLD 64
		#define SYMBOL_PAGE_SIZE 1024

		struct SymbolPage{
			u8* buffer;
			u8* bufferTop;

			SymbolPage()
				: buffer(nullptr)
				, bufferTop(nullptr){
			}
		};

		struct ParserCustom{
			MemoryPoolSlice* declPool;
			MemoryPoolSlice* defPool;
			MemoryPoolSlice* symPool;
			MemoryPoolSlice* tempPool;
			container::ArrayList<ParserError>* errors;
			ParserError* unexpectedError;
			SrcLoc lastSrcLoc;

			ParserCustom(MemoryPoolSlice* declPool, MemoryPoolSlice* defPool, MemoryPoolSlice* symPool, MemoryPoolSlice* tempPool, container::ArrayList<ParserError>* errors)
				: declPool(declPool)
				, defPool(defPool)
				, symPool(symPool)
				, tempPool(tempPool)
				, errors(errors)
				, unexpectedError(nullptr)
				, lastSrcLoc(1, 0){
				parseDeclaration();
			}

			void beginUnexpectedError(const Token& t){
				unexpectedError = pushError(ParserError(ParserError::UnexpectedToken, t.where, t)); 
			}

			void endUnexpectedError(){
				unexpectedError = nullptr;
			}

			ParserError* pushError(const ParserError& error){
				if ( errors->getSize() < MaxReportedParserErrors ){
					errors->push(error);
					return &errors->get(errors->getSize() - 1);
				}
				return nullptr;
			}

			StringRef copySymbol(const Token& token){
				if ( !token.data ){
					return StringRef();
				}else{
					u8* buffer;
					size_t length = token.data->length;
					if ( length > LARGE_SYMBOL_THRESHOLD ){
						if ( currentPool == declPool ){
							buffer = (u8*)symPool->allocate(token.data->length);
						}else{
							buffer = (u8*)defPool->allocate(token.data->length);
						}
					}else{
						if ( (size_t)(currentPage->bufferTop - currentPage->buffer) < length ){
							currentPage->buffer = (u8*)(currentPool == declPool ? symPool : defPool)->allocate(SYMBOL_PAGE_SIZE);
							currentPage->bufferTop = currentPage->buffer + SYMBOL_PAGE_SIZE;
						}
						buffer = currentPage->buffer;
						currentPage->buffer += length;
					}
					::memcpy(buffer, token.data->data, length);
					return StringRef(buffer, token.data->length);
				}
			}

			StringRef passSymbol(const Token& token){
				if ( !token.data ){
					return StringRef();
				}else{
					return StringRef(token.data->data, token.data->length);
				}
			}

			SrcSpan fromToHere(const SrcLoc& from){
				if ( lastSrcLoc < from ){
					return SrcSpan(from, from);
				}
				return SrcSpan(from, lastSrcLoc);
			}

			void parseDeclaration(){
				currentPool = declPool;
				currentPage = &declPage;
			}

			void parseDefinition(){
				currentPool = defPool;
				currentPage = &defPage;
			}

			MemoryPoolSlice* currentPool;
			SymbolPage* currentPage;
			SymbolPage defPage;
			SymbolPage declPage;
		};

		#define use_decl parsx_ud.parseDeclaration();
		#define use_def parsx_ud.parseDefinition();

		#define alloc(t) new(parsx_ud.currentPool->allocate(sizeof(t)))t
		#define sym(t) parsx_ud.copySymbol(t)
		#define lit(t) parsx_ud.passSymbol(t)
		#define to_here(from) parsx_ud.fromToHere(from)
		
		template<class T>
		class ParsxStackAdapter: public container::ArrayList<T>{
		public:
			ParsxStackAdapter(MemoryPoolSlice* pool)
				: ArrayList(pool){
			}

			bool isEmpty(){
				return getSize() == 0;
			}

			const T& getTop(){
				return ((T*)topChunk->buffer)[chunkFill - 1];
			}
		};

		template<class T>
		class ParsxQueue{
		public:
			const static size_t InitialSize = 1024;
			ParsxQueue(MemoryPoolSlice* pool)
				: pool(pool)
				, bufferFirst((T*)pool->allocateArray(sizeof(T), InitialSize))
				, bufferLast(bufferFirst + InitialSize - 1)
				, first(bufferFirst)
				, last(bufferLast)
				, size(0)
				, capacity(InitialSize){
			}

			bool isEmpty(){
				return size == 0;
			}

			const T& getFirst(){
				return *first;
			}

			const T& getLast(){
				return *last;
			}

			const T& takeLast(){
				T* prevLast = last;
				last--;
				if ( last < bufferFirst ){
					last = bufferLast;
				}
				size--;
				return *prevLast;
			}

			const T& takeFirst(){
				T* prevFirst = first;
				first++;
				if ( first > bufferLast ){
					first = bufferFirst;
				}
				size--;
				return *prevFirst;
			}

			void putLast(const T& t){
				if ( size == capacity ){
					grow();
				}
				last++;
				if ( last > bufferLast ){
					last = bufferFirst;
				}
				*last = t;
				size++;
			}

			void putFirst(const T& t){
				if ( size == capacity ){
					grow();
				}
				first--;
				if ( first < bufferFirst ){
					first = bufferLast;
				}
				*first = t;
				size++;
			}

			size_t getSize(){
				return size;
			}
		private:
			void grow(){
				T* newBuffer = (T*)pool->allocateArray(sizeof(T), capacity * 2);
				::memcpy(newBuffer, bufferFirst, sizeof(T) * size);
				bufferFirst = newBuffer;
				capacity *= 2;
				bufferLast = newBuffer + sizeof(T) * (capacity - 1);
				first = bufferFirst;
				last = bufferFirst + size - 1;
			}

			MemoryPoolSlice* pool;

			T* bufferFirst;
			T* bufferLast;

			T* first;
			T* last;

			size_t size;
			size_t capacity;
		};

		class ParsxLexer{
		public:
			ParsxLexer(container::ArrayList<Token>* tokens)
				: tokens(tokens)
				, enumerator(tokens->enumerate()){
			}

			bool isEndOfFile(){
				return (enumerator.getIndex() == tokens->getSize() - 1);
			}

			const Token& getToken(){
				auto& token = enumerator.get();
				if ( enumerator.getIndex() != tokens->getSize() - 1 ){
					enumerator.advance();
				}
				return token;
			}
		private:
			container::ArrayList<Token>* tokens;
			container::ArrayList<Token>::Enumerator enumerator;
		};

		class ParsxDataStack{
		public:
			const static size_t InitialSize = 1024 * 1024;

			ParsxDataStack(MemoryPoolSlice* pool)
				: bufferBegin((u8*)pool->allocate(InitialSize))
				, pool(pool){
				buffer = bufferBegin;
				bufferEnd = bufferBegin + InitialSize;
			}

			void* push(size_t size){
				if ( buffer + size > bufferEnd ){
					grow(size);
				}
				u8* ret = buffer;
				buffer += size;
				return ret;
			}

			void* pop(size_t size){
				buffer -= size;
				return buffer;
			}
		private:
			MemoryPoolSlice* pool;

			void grow(size_t growSize){
				size_t oldSize = bufferEnd - bufferBegin;
				size_t newSize = oldSize * 2;
				if ( newSize < oldSize + growSize ){
					newSize = oldSize + growSize;
				}
				u8* newBuffer = (u8*)pool->allocate(newSize);
				::memcpy(newBuffer, bufferBegin, buffer - bufferBegin);
				buffer = (buffer - bufferBegin) + newBuffer;
				bufferEnd = newBuffer + newSize;
				bufferBegin = newBuffer;
			}

			u8* buffer;
			u8* bufferBegin;
			u8* bufferEnd;
		};
	}
}

//All parsx stuff will be placed into this namespace:
#define parsx_namespace parsx
//Generated parser core file
#define parsx_core "parser_core.cpp"
//Converts token name seen in parser (t) into the token type value
#define parsx_token(t) jf::parser::Token::t
//Defines the type of single 'token'
#define parsx_token_type jf::parser::Token
//Defines type for token identity
#define parsx_token_id jf::parser::Token::Type
//Converts parsx_token_type into parsx_token_id
#define parsx_token_get_id(t) t.type
//Token value for 'end of file' token
#define parsx_eof_token jf::parser::Token::EndOfFile
//Special token value
#define parsx_invalid_token jf::parser::Token::Count
//Type of expected symbols
#define parsx_expect_type char*
//Convert expected name to expected type
#define parsx_expect_name(t) #t
#define parsx_expect_token(t) jf::parser::Token::GetName(parsx_token(t))

#define parsx_token_value(t) (parsx_ud.lastSrcLoc = t.where.to(), t)

//Iteration on the token ids
#define parsx_min_token_id (parsx_token_id)0
#define parsx_next_token_id(t) (parsx_token_id)(t + 1)
#define parsx_max_token_id parsx_invalid_token
#define parsx_valid_token_id(t) ((t) < parsx_max_token_id)

//Generate parsx_token_type value with specific id after token prev
#define parsx_generate_fake_token(ud, next, id) jf::parser::Token::GenerateToken(next, id)
#define parsx_generate_replace_token(ud, tok, id) jf::parser::Token::ReplaceToken(tok, id)

#define parsx_max_backtrack 5
#define parsx_max_lookahead 5
#define parsx_max_corrections 1
#define parsx_min_advance_to_accept_correction 2

#define parsx_correction_remove_cost 3
#define parsx_correction_swap_cost 4
#define parsx_correction_insert_cost 2
#define parsx_correction_replace_cost 4

#define parsx_report_panic_mode(ud, tok) 

#define parsx_report_insert_before(ud, before, tok) ud.pushError(jf::parser::ParserError(jf::parser::ParserError::MissingToken, before.where, before, tok));
#define parsx_report_replace(ud, tok, newtok) ud.pushError(jf::parser::ParserError(jf::parser::ParserError::ReplaceToken, tok.where, tok, newtok));
#define parsx_report_remove(ud, tok)  ud.pushError(jf::parser::ParserError(jf::parser::ParserError::MisplacedToken, tok.where, tok));
#define parsx_report_swap(ud, tok1, tok2) ud.pushError(jf::parser::ParserError(jf::parser::ParserError::SwapTokens, jf::SrcSpan(tok1.where.from(), tok2.where.to()), tok1, tok2));

#define parsx_report_sync_insert(ud, before, tok) 
#define parsx_report_sync_skip(ud, tok)

#define parsx_report_error_begin(ud, t) ud.beginUnexpectedError(t);
#define parsx_error_add_expect(ud, t) if ( ud.unexpectedError ) ud.unexpectedError->addExpected(ud.tempPool, t);
#define parsx_report_error_end(ud) ud.endUnexpectedError();

#define parsx_cant_sync() abort()

//If parsx_apply_first_correction is defined, then parser will accept any correction (coarser corrections)
//#define parsx_apply_first_correction

namespace parsx_namespace{
	typedef jf::parser::ParsxQueue<int> parsx_queue;
	typedef jf::parser::ParsxStackAdapter<int> parsx_stack;
	typedef jf::parser::ParsxQueue<parsx_token_type> parsx_token_queue;
	typedef jf::parser::ParsxDataStack parsx_datastack;
	typedef jf::parser::ParsxLexer parsx_lexer;
	typedef jf::parser::ParserCustom parsx_custom;
}