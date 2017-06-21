#include "parsx_declare_parser.h"
#include <cstdarg>

namespace parsx_namespace{
	#define parsx_step_func_begin() bool parse_step(ParserContext& parsx_ctx, parsx_token_type& parsx_la){
	#define parsx_step_func_end() return false;}

	#define parsx_commit_func_begin() bool commit_step(ParserContext& parsx_ctx){
	#define parsx_commit_func_end() return false;}

	#define parsx_expected_func_begin() void collect_expected(ParserContext& parsx_ctx, int parsx_state){
	#define parsx_expected_func_end() }

	#define parsx_expect_state parsx_state
	#define parsx_expect(t) parsx_error_add_expect(parsx_ctx.custom, t)

	#define parsx_undo_func_begin() int undo_all(ParserContext& parsx_ctx, parsx_token_type* parsx_undo_buffer){ int parsx_undo_count = 0;
	#define parsx_undo_func_end() return parsx_undo_count; }

	#define parsx_sync_mask_table_begin() SyncMask parsx_sync_mask[] = {
	#define parsx_sync_mask(...) SyncMask(__VA_ARGS__),
	#define parsx_sync_mask_table_end() };

	#define parsx_sync_cost_func_begin() int sync_cost(State parsx_state, parsx_token_id parsx_la){
	#define parsx_sync_token parsx_la
	#define parsx_sync_state parsx_state
	#define parsx_sync_cost_func_end() return 0;}

	#define parsx_sync_func_begin() void parsx_sync(ParserContext& parsx_ctx, parsx_token_type& parsx_la){
	#define parsx_sync_func_end() }

	#define parsx_pop_queued_action parsx_ctx.actions.takeFirst()
	#define parsx_pop_last_queued_action parsx_ctx.actions.takeLast()
	#define parsx_has_queued_action (!parsx_ctx.actions.isEmpty())
	#define parsx_lookahead_token parsx_token_get_id(parsx_la)
	#define parsx_current_state parsx_ctx.ll.getTop()
	#define parsx_has_state (!parsx_ctx.ll.isEmpty())

	#define parsx_unshift_token() {parsx_undo_count++; if ( parsx_undo_buffer ){*parsx_undo_buffer = parsx_ctx.tokens.takeLast(); parsx_undo_buffer--;} else { parsx_ctx.tokens.takeLast(); } }
	#define parsx_shift_token() { parsx_ctx.tokens.putLast(parsx_la); }

	#define parsx_queue_action(n) parsx_ctx.actions.putLast(n);
	#define parsx_push_state(n) parsx_ctx.ll.push(n);
	#define parsx_pop_state() parsx_ctx.ll.pop();

	#define parsx_push_value(t, v) *(t*)parsx_ctx.values.push(sizeof(t)) = v;
	#define parsx_pop_value(t) *(t*)parsx_ctx.values.pop(sizeof(t))

	#define parsx_commit_token() parsx_token_type parsx_tok = parsx_ctx.tokens.takeFirst(); parsx_push_value(parsx_token_type, parsx_token_value(parsx_tok));

	#define parsx_next_shifted (parsx_ctx.tokens.getFirst())

	#define parsx_pull_lex parsx_ctx.peek.putLast(parsx_ctx.lexer.getToken())
	#define parsx_peek() parsx_ctx.peek.isEmpty() ? (parsx_pull_lex, parsx_ctx.peek.getFirst()) : parsx_ctx.peek.getFirst()

	#define parsx_insert_token(t) { parsx_token_type parsx_tok = parsx_generate_fake_token(parsx_ctx.custom, parsx_peek(), parsx_token(t)); parsx_push_value(parsx_token_type, parsx_token_value(parsx_tok)); parsx_report_sync_insert(parsx_ctx.custom, parsx_peek(), parsx_tok); }
	#define parsx_symbol_state(a, b, c) namespace parse{ c Parse##b(ParserContext& parsx_ctx){ parsx_push_state(States::b); parse_general(parsx_ctx); return parsx_pop_value(c); } }

	#define parsx_ud parsx_ctx.custom

	struct SyncMask{
		static const size_t MaxTokenID = parsx_max_token_id;
		static const size_t BitsPerWord = sizeof(size_t) * 8;
		static const size_t Words = (MaxTokenID + BitsPerWord - 1) / BitsPerWord;

		SyncMask(){
			for ( size_t i = 0; i < Words; i++ ){
				mask[i] = 0;
			}
		}

		SyncMask(size_t count, ...){
			for ( size_t i = 0; i < Words; i++ ){
				mask[i] = 0;
			}
			va_list args;
			va_start(args, count);
			for ( size_t i = 0; i < count; i++ ){
				parsx_token_id token = va_arg(args, parsx_token_id);
				set(token);
			}
			va_end(args);
		}

		bool test(parsx_token_id id){
			size_t word = id / BitsPerWord;
			size_t bit = id % BitsPerWord;
			return (mask[word] & (((size_t)1) << bit)) != 0;
		}

		void set(parsx_token_id id){
			size_t word = id / BitsPerWord;
			size_t bit = id % BitsPerWord;
			mask[word] |= (((size_t)1) << bit);
		}

		void merge(const SyncMask& other){
			for ( size_t i = 0; i < Words; i++ ){
				mask[i] |= other.mask[i];
			}
		}

		size_t mask[Words];
	};
	 
	#define parsx_impl
	#pragma warning(push)
	#pragma warning(disable:4065)
	#include parsx_core
	#pragma warning(pop)
	#undef parsx_impl

	#include "parsx_correction_api.cpp"

	void parse_general(ParserContext& parsx_ctx){

		while ( true ){
			parsx_token_type token = parsx_peek();
			if ( parse_step(parsx_ctx, token) ){
				parsx_ctx.peek.takeFirst();
				while ( parsx_ctx.tokens.getSize() > parsx_max_backtrack ){
					commit_step(parsx_ctx);
				}
			}else{
				if ( parsx_token_get_id(token) == parsx_eof_token && parsx_ctx.lexer.isEndOfFile() && parsx_ctx.ll.isEmpty() ){
					//duplicate end-of-file token so we never deplet tokens
					parsx_ctx.tokens.putLast(token);
					while ( commit_step(parsx_ctx) ){
					}
					parsx_ctx.tokens.takeLast();
					return;
				}
				
				parsx_token_type buffer[parsx_max_backtrack + parsx_max_lookahead + 2];
				int backtrack = undo_all(parsx_ctx, buffer + parsx_max_backtrack - 1);

				//Sync mask needed for synchronization to sync-set of current state
				SyncMask stateSyncMask;
				size_t limit = parsx_ctx.ll.getSize();
				for ( size_t i = limit - 1; i < limit; i-- ){
					stateSyncMask.merge(parsx_sync_mask[parsx_ctx.ll.get(i)]);
				}

				int lookahead = 0;
				bool eofPeeked = false;
				size_t syncOn = 0;
				bool synced = false;
				parsx_token_type* bufferStart = buffer + parsx_max_backtrack - backtrack;
				for ( size_t i = 0; i < parsx_max_lookahead + 1; i++ ){
					parsx_token_type t = parsx_peek();
					parsx_ctx.peek.takeFirst();
					buffer[parsx_max_backtrack + i] = t;
					lookahead++;
					if ( parsx_token_get_id(t) == parsx_eof_token ){
						eofPeeked = true;
						break;
					}
					if ( !stateSyncMask.test(parsx_token_get_id(t)) && !synced ){
						syncOn = i;
					}		
				}
				parsx_token_type* bufferEnd = bufferStart + backtrack + lookahead;
				parsx_token_type candidate[parsx_max_backtrack + parsx_max_lookahead + 8];
				CorrectionState correctionState;
				correctionState.buffer = bufferStart;
				correctionState.output = candidate;
				correctionState.L = backtrack;
				correctionState.M = lookahead;
				correctionState.followToken = parsx_peek();

				if ( lookahead > 0 ){
					correctionState.L++;
					correctionState.M--;
				}

				Correction correction;
				correction.init(correctionState);
				correction.additionalLength = (int)syncOn;

				Correction bestMatch;
				int bestScore = backtrack;			
				int bestCost = 0;
				while ( correction.next() ){
					int cost = generateCandidate<false>(correction, correctionState, parsx_ctx);
					int score = updateScore(correction, correctionState, testCandidate(correctionState, parsx_ctx));
					if ( score > bestScore || (score == bestScore && cost < bestCost) ){
						if ( (score >= backtrack + lookahead || score - correction.activeCorrections >= backtrack) && score - backtrack >= parsx_min_advance_to_accept_correction ){
							bestScore = score;
							bestMatch = correction;
							bestCost = cost;
						}
					}
					#if defined(parsx_apply_first_correction)
					if ( bestScore == INPUT_MATCHED || (bestScore == lookahead + backtrack && !eofPeeked) ){
						break;
					}
					#endif
				}

				if ( bestScore > backtrack ){
					generateCandidate<true>(bestMatch, correctionState, parsx_ctx);
					for ( int i = correctionState.size - 1; i >= 0; i-- ){
						parsx_ctx.peek.putFirst(candidate[i]);
					}
				}else{					
					for ( int i = backtrack + lookahead - 1; i >= 0; i-- ){
						parsx_ctx.peek.putFirst(bufferStart[i]);
					}
					//panic mode
					while ( backtrack > 0 ){
						backtrack--;
						parsx_token_type t = parsx_peek();
						if ( parse_step(parsx_ctx, t) ){
							parsx_ctx.peek.takeFirst();						
						}else{							
							break;
						}
					}
					while ( !parsx_ctx.tokens.isEmpty() ){
						commit_step(parsx_ctx);
					}

					parsx_report_panic_mode(parsx_ctx.custom, parsx_peek());
					parsx_report_error_begin(parsx_ctx.custom, parsx_peek())
					size_t limit = parsx_ctx.ll.getSize();
					for ( size_t i = limit - 1; i < limit; i-- ){
						collect_expected(parsx_ctx, parsx_ctx.ll.get(i));
						if ( sync_cost(parsx_ctx.ll.get(i), parsx_invalid_token) > 0 ){
							break;
						}
					}
					parsx_report_error_end(parsx_ctx.custom)

					bool synced = false;
				
					SyncMask syncMask;
					for ( size_t i = limit - 1; i < limit; i-- ){
						syncMask.merge(parsx_sync_mask[parsx_ctx.ll.get(i)]);
					}

					while ( true ){
						parsx_token_type t = parsx_peek();
						if ( syncMask.test(parsx_token_get_id(t)) ){
							int cost = 0;
							int bestCost = INT_MAX;
							size_t bestPos = 0;
							size_t limit = parsx_ctx.ll.getSize();
							for ( size_t i = limit - 1; i < limit; i-- ){
								int skipCost = sync_cost(parsx_ctx.ll.get(i), parsx_invalid_token);
								if ( parsx_sync_mask[parsx_ctx.ll.get(i)].test(parsx_token_get_id(t)) ){
									int syncCost = cost + sync_cost(parsx_ctx.ll.get(i), parsx_token_get_id(t));
									if ( syncCost < bestCost ){
										bestCost = syncCost;
										bestPos = i;
									}
								}
								cost += skipCost;
								if ( cost >= bestCost ){
									break;
								}
							}
							if ( bestCost < INT_MAX ){
								parsx_token_type sync_t = parsx_generate_replace_token(parsx_ctx.custom, t, parsx_invalid_token);
								while ( parsx_ctx.ll.getSize() > (size_t)(bestPos + 1) ){									
									parsx_sync(parsx_ctx, sync_t);
								}
								while ( !parsx_ctx.actions.isEmpty() ){
									commit_step(parsx_ctx);
								}
								parsx_sync(parsx_ctx, t);
								synced = true;
								break;
							}else{
								parsx_report_sync_skip(parsx_ctx.custom, t);
								parsx_ctx.peek.takeFirst();
							}
						}else{
							parsx_report_sync_skip(parsx_ctx.custom, t);	
							if ( parsx_token_get_id(t) == parsx_eof_token ){
								while ( !parsx_ctx.ll.isEmpty() ){									
									parsx_sync(parsx_ctx, t);
								}
								synced = true;
								break;
							}		
							parsx_ctx.peek.takeFirst();
						}
					}

					while ( !parsx_ctx.tokens.isEmpty() ){
						commit_step(parsx_ctx);
					}

					if ( !synced ){
						parsx_cant_sync();
					}
				}

			}
		}
	}

}