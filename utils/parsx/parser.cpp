parsx_step_func_begin()
	for(;;){
		switch ( parsx_current_state ){
		case 1:{ //Token +
			switch ( parsx_lookahead_token ){
				case parsx_token(+):{
					parsx_queue_action(1);
					parsx_pop_state();
					parsx_shift_token();
					return true;
				}break;
				default:{
					return false;
				}break;
			}
		}break;
		case 2:{ //Token num
			switch ( parsx_lookahead_token ){
				case parsx_token(num):{
					parsx_queue_action(2);
					parsx_pop_state();
					parsx_shift_token();
					return true;
				}break;
				default:{
					return false;
				}break;
			}
		}break;
		case 3:{ //Symbol e'rhs
			switch ( parsx_lookahead_token ){
				//Rule [+, num, (3)=>{ add($1, $3)}, e'rhs]
				case parsx_token(+):
				{
					parsx_queue_action(3);
					parsx_pop_state();
					parsx_push_state(3);
					parsx_push_state(6);
					parsx_push_state(2);
					parsx_push_state(1);
				}break;
				default:{
					return false;
				}break;
			}
		}break;
		case 4:{ //Symbol e'lhs
			switch ( parsx_lookahead_token ){
				//Rule [num, (1)=>{ num($1)}]
				case parsx_token(num):
				{
					parsx_queue_action(5);
					parsx_pop_state();
					parsx_push_state(7);
					parsx_push_state(2);
				}break;
				default:{
					return false;
				}break;
			}
		}break;
		case 5:{ //Symbol e
			switch ( parsx_lookahead_token ){
				//Rule [num, (1)=>{ num($1)}, e'rhs]
				case parsx_token(num):
				{
					parsx_queue_action(6);
					parsx_pop_state();
					parsx_push_state(3);
					parsx_push_state(7);
					parsx_push_state(2);
				}break;
				default:{
					return false;
				}break;
			}
		}break;
		case 6:{ //Action (3)=>{ add($1, $3)}
			parsx_queue_action(7);
		}break;
		case 7:{ //Action (1)=>{ num($1)}
			parsx_queue_action(8);
		}break;
		}
	}
parsx_step_func_end()


parsx_commit_func_begin()
	while ( parsx_has_queued_action ){
		switch ( parsx_pop_queued_action ){
			case 1{ //Token +
				parsx_commit_token()
				return true;
			}break;
			case 2{ //Token num
				parsx_commit_token()
				return true;
			}break;
			case 3{ //Symbol e'rhs rule [+, num, (3)=>{ add($1, $3)}, e'rhs]
			}break;
			case 4{ //Symbol e'rhs rule []
			}break;
			case 5{ //Symbol e'lhs rule [num, (1)=>{ num($1)}]
			}break;
			case 6{ //Symbol e rule [num, (1)=>{ num($1)}, e'rhs]
			}break;
			case 7{ //action (3)=>{ add($1, $3)}
				parsx_run_action(3,  add($1, $3))
			}break;
			case 8{ //action (1)=>{ num($1)}
				parsx_run_action(1,  num($1))
			}break;
		}
	}
	return false;
parsx_commit_func_end()


parsx_undo_func_begin()
	while ( parsx_has_queued_action ){
		switch ( parsx_pop_last_queued_action ){
			case 1{ //Token +
				parsx_unshift_token();
			}break;
			case 2{ //Token num
				parsx_unshift_token();
			}break;
			case 3{ //Symbol e'rhs rule [+, num, (3)=>{ add($1, $3)}, e'rhs]
				parsx_pop_state();
				parsx_pop_state();
				parsx_pop_state();
				parsx_pop_state();
				parsx_push_state(3);
			}break;
			case 4{ //Symbol e'rhs rule []
				parsx_push_state(3);
			}break;
			case 5{ //Symbol e'lhs rule [num, (1)=>{ num($1)}]
				parsx_pop_state();
				parsx_pop_state();
				parsx_push_state(4);
			}break;
			case 6{ //Symbol e rule [num, (1)=>{ num($1)}, e'rhs]
				parsx_pop_state();
				parsx_pop_state();
				parsx_pop_state();
				parsx_push_state(5);
			}break;
			case 7{ //action (3)=>{ add($1, $3)}
				parsx_push_state(6);
			}break;
			case 8{ //action (1)=>{ num($1)}
				parsx_push_state(7);
			}break;
		}
	}
	return false;
parsx_undo_func_end()
