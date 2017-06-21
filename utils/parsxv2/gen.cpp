parsx_symbol_state(3,p,double);
parsx_symbol_state(6,e,double);
parsx_symbol_state(1,t,double);
parsx_symbol_state(16,S,double);
#if defined(parsx_impl)
	short parsx_table[parsx_max_token_id + 1][20] = {0};
	struct parsx_parse_table_gen{parsx_parse_table_gen(){
		parsx_table[parsx_max_token_id][2] = 1;
		parsx_table[parsx_max_token_id][4] = 2;
		parsx_table[parsx_max_token_id][7] = 3;
		parsx_table[parsx_max_token_id][9] = 4;
		parsx_table[parsx_max_token_id][10] = 5;
		parsx_table[parsx_max_token_id][12] = 6;
		parsx_table[parsx_max_token_id][17] = 7;
		parsx_table[parsx_max_token_id][19] = 8;
		parsx_table[parsx_max_token_id][20] = 9;
		parsx_table[parsx_token(NUM)][1] = 10;
		parsx_table[parsx_token(LPAREN)][1] = 11;
		parsx_table[parsx_token(MULT)][2] = 12;
		parsx_table[parsx_token(DIV)][2] = 13;
		parsx_table[parsx_token(NUM)][3] = 14;
		parsx_table[parsx_token(LPAREN)][3] = 15;
		parsx_table[parsx_token(MINUS)][5] = 16;
		parsx_table[parsx_token(NUM)][6] = 17;
		parsx_table[parsx_token(LPAREN)][6] = 18;
		parsx_table[parsx_token(DIV)][8] = 19;
		parsx_table[parsx_token(MULT)][11] = 20;
		parsx_table[parsx_token(LPAREN)][13] = 21;
		parsx_table[parsx_token(PLUS)][14] = 22;
		parsx_table[parsx_token(RPAREN)][15] = 23;
		parsx_table[parsx_token(NUM)][16] = 24;
		parsx_table[parsx_token(LPAREN)][16] = 25;
		parsx_table[parsx_token(NUM)][18] = 26;
		parsx_table[parsx_token(MINUS)][19] = 27;
		parsx_table[parsx_token(PLUS)][19] = 28;
		parsx_table[parsx_token(MULT)][20] = 29;
		parsx_table[parsx_token(MINUS)][20] = 30;
		parsx_table[parsx_token(PLUS)][20] = 31;
		parsx_table[parsx_token(DIV)][20] = 32;
	}};
	const parsx_parse_table_gen parsx_init_table;
	const short parsx_rule_state_table[] = {
		2, 0, 
		4, 0, 
		7, 0, 
		9, 0, 
		10, 0, 
		12, 0, 
		17, 0, 
		19, 0, 
		20, 0, 
		1, 2, 0, 
		1, 6, 15, 4, 2, 0, 
		2, 3, 17, 2, 0, 
		2, 3, 7, 2, 0, 
		3, 0, 
		3, 6, 15, 4, 0, 
		5, 0, 
		6, 20, 0, 
		6, 6, 15, 4, 20, 0, 
		8, 0, 
		11, 0, 
		13, 0, 
		14, 0, 
		15, 0, 
		16, 20, 0, 
		16, 6, 15, 4, 20, 0, 
		18, 0, 
		19, 1, 9, 19, 0, 
		19, 1, 10, 19, 0, 
		20, 3, 17, 2, 0, 
		20, 1, 9, 19, 0, 
		20, 1, 10, 19, 0, 
		20, 3, 7, 2, 0, 
	};
	const short parsx_rule_state_table_index[] = {
		0, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 21, 27, 32, 37, 39, 44, 46, 49, 55, 57, 59, 61, 63, 65, 68, 74, 76, 81, 86, 91, 96, 101, 
	};
	parsx_step_func_begin()
		while( parsx_has_state ){
			State parsx_current_state_ = parsx_current_state;
			Action parsx_taken_action = parsx_table[parsx_lookahead_token][parsx_current_state_];
			if ( parsx_taken_action == 0 ) return false;
			parsx_queue_action(parsx_taken_action);
			parsx_pop_state();
			const short* parsx_pushed_states = parsx_rule_state_table + parsx_rule_state_table_index[parsx_taken_action];
			while ( *(++parsx_pushed_states) ) parsx_push_state(*parsx_pushed_states);
			if ( parsx_taken_action > 9 ) return true;
		}
	parsx_step_func_end()
	parsx_commit_func_begin()
		while ( parsx_has_queued_action ){
			Action parsx_action = parsx_pop_queued_action;
			switch ( parsx_action ){
				case 0:{
				}break;
				case 1:{
				}break;
				case 2:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						double _parsx_2 = parsx_pop_value(double);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(double, _parsx_2);
					}
				}break;
				case 3:{
					{
						double _parsx_3 = parsx_pop_value(double);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						double _parsx_1 = parsx_pop_value(double);
						parsx_push_value(double, _parsx_1 / _parsx_3);
					}
				}break;
				case 4:{
					{
						double _parsx_3 = parsx_pop_value(double);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						double _parsx_1 = parsx_pop_value(double);
						parsx_push_value(double, _parsx_1 - _parsx_3);
					}
				}break;
				case 5:{
					{
						double _parsx_3 = parsx_pop_value(double);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						double _parsx_1 = parsx_pop_value(double);
						parsx_push_value(double, _parsx_1 + _parsx_3);
					}
				}break;
				case 6:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(double, _parsx_1.value);
					}
				}break;
				case 7:{
					{
						double _parsx_3 = parsx_pop_value(double);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						double _parsx_1 = parsx_pop_value(double);
						parsx_push_value(double, _parsx_1 * _parsx_3);
					}
				}break;
				case 8:{
				}break;
				case 9:{
				}break;
				case 10:{
					parsx_commit_token();
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(double, _parsx_1.value);
					}
				}break;
				case 11:{
					parsx_commit_token();
				}break;
				case 12:{
					parsx_commit_token();
				}break;
				case 13:{
					parsx_commit_token();
				}break;
				case 14:{
					parsx_commit_token();
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(double, _parsx_1.value);
					}
				}break;
				case 15:{
					parsx_commit_token();
				}break;
				case 16:{
					parsx_commit_token();
				}break;
				case 17:{
					parsx_commit_token();
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(double, _parsx_1.value);
					}
				}break;
				case 18:{
					parsx_commit_token();
				}break;
				case 19:{
					parsx_commit_token();
				}break;
				case 20:{
					parsx_commit_token();
				}break;
				case 21:{
					parsx_commit_token();
				}break;
				case 22:{
					parsx_commit_token();
				}break;
				case 23:{
					parsx_commit_token();
				}break;
				case 24:{
					parsx_commit_token();
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(double, _parsx_1.value);
					}
				}break;
				case 25:{
					parsx_commit_token();
				}break;
				case 26:{
					parsx_commit_token();
				}break;
				case 27:{
					parsx_commit_token();
				}break;
				case 28:{
					parsx_commit_token();
				}break;
				case 29:{
					parsx_commit_token();
				}break;
				case 30:{
					parsx_commit_token();
				}break;
				case 31:{
					parsx_commit_token();
				}break;
				case 32:{
					parsx_commit_token();
				}break;
			}
			if ( parsx_action > 9 ){
				return true;
			}
		}
	parsx_commit_func_end()
	parsx_undo_func_begin()
		while ( parsx_has_queued_action ){
			Action parsx_action = parsx_pop_last_queued_action;
			const short* parsx_pushed_states = parsx_rule_state_table + parsx_rule_state_table_index[parsx_action];
			const short parsx_pushed_state = *parsx_pushed_states;
			while ( *(++parsx_pushed_states) ) parsx_pop_state();
			parsx_push_state(parsx_pushed_state);
			if ( parsx_action > 9 ){
				parsx_unshift_token();
			}
		}
	parsx_undo_func_end()
	parsx_sync_cost_func_begin()
	parsx_sync_cost_func_end()
	parsx_sync_func_begin()
	parsx_sync_func_end()
#endif

