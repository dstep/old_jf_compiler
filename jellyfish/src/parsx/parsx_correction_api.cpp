struct SingleCorrection{
	int totalLength;

	enum{
		Inactive,
		Remove,
		Insert,
		Replace,
		Swap
	} type;
	int pos;
	parsx_token_id token;
	bool reversed;

	SingleCorrection(){
		this->type = Inactive;
		this->reversed = false;
	}

	SingleCorrection(int length){
		this->totalLength = length;
		this->type = Inactive;
		this->pos = 0;
		this->reversed = true;
	}

	bool isActive(){
		return type != Inactive;
	}

	inline
	bool nextToken(){
		do{
			token = parsx_next_token_id(token);
			if ( parsx_valid_token_id(token) ){
				return true;
			}else if ( parsx_max_token_id < token ){
				return false;
			}
		}while(true);
	}

	bool advanceType(){
		switch ( type ){
		case Inactive:{
			if ( totalLength == 0 ){
				type = Insert;
				pos = 0;
				token = parsx_min_token_id;
			}else{
				type = Swap;
				pos = reversed ? pos = totalLength - 2 : 0;
				if ( totalLength < 2 ){
					return advanceType();
				}				
			}
			return true;
		}break;			
		case Swap:{			
			type = Insert;
			pos = reversed ? pos = totalLength : 0;
			token = parsx_min_token_id;
		}break;		
		case Insert:{
			type = Replace;
			pos = reversed ? pos = totalLength - 1 : 0;
			token = parsx_min_token_id;	
			if ( totalLength == 0 ){
				return false;
			}		
		}break;
		case Replace:{
			type = Remove;
			pos = reversed ? pos = totalLength - 1: 0;
		}break;
		case Remove:{
			return false;
		}break;	
		}
		return true;
	}

	bool next(){
		switch ( type ){
		case Inactive:{
			return advanceType();
		}break;
		case Remove:{
			if ( reversed ){
				if ( pos > 0 ){
					pos--;
				}else{
					return advanceType();
				}
			}else{
				if ( pos < totalLength - 1 ){
					pos++;
				}else{
					return advanceType();
				}
			}
			return true;
		}break;
		
		case Replace:{
			if ( !nextToken() ){
				token = parsx_min_token_id;
				if ( reversed ){
					if ( pos > 0 ){
						pos--;
					}else{
						return advanceType();
					}
				}else{
					if ( pos < totalLength - 1 ){
						pos++;
					}else{
						return advanceType();
					}
				}
			}
			return true;
		}break;
		case Swap:{
			if ( reversed ){
				if ( pos > 0 ){
					pos--;
				}else{
					return advanceType();
				}
			}else{
				if ( pos < totalLength - 2 ){
					pos++;
				}else{
					return advanceType();
				}
			}
			return true;
		}break;
		case Insert:{			
			if ( !nextToken() ){
				token = parsx_min_token_id;
				if ( reversed ){
					if ( pos > 0 ){
						pos--;
					}else{
						return advanceType();
					}
				}else{
					if ( pos < totalLength ){
						pos++;
					}else{
						return advanceType();
					}
				}
			}
			
			return true;
		}break;
		}
		return false;
	}

	void reset(){
		this->type = Inactive;
		this->pos = 0;
		this->reversed = true;
		next();
	}

	void initFrom(SingleCorrection parent, int extraLength){
		int parentLength = 0;
		switch ( parent.type ){
		case Inactive:{
			parentLength = parent.totalLength;
		}break;
		case Remove:{
			parentLength = parent.totalLength - parent.pos - 1;
		}break;
		case Insert:{
			parentLength = parent.totalLength - parent.pos;
		}break;
		case Replace:{
			parentLength = parent.totalLength - parent.pos - 1;
		}break;
		case Swap:{
			parentLength = parent.totalLength - parent.pos - 2;
		}break;
		}
		totalLength = parentLength + extraLength;
		type = Inactive;
		pos = 0;
	}
};

struct CorrectionState;

struct Correction{
	int activeCorrections;
	int additionalLength;
	SingleCorrection corrections[parsx_max_corrections | 2];

	void init(CorrectionState& state);

	bool next(){
		if ( parsx_max_corrections == 0 ){
			return false;
		}
		if ( corrections[activeCorrections - 1].next() ){
			return true;
		}else{
			int i = activeCorrections - 2;
			for ( ; i >= 0; i-- ){
				if ( corrections[i].next() ){
					break;
				}
			}
			if ( i < 0 ){
				if ( activeCorrections < parsx_max_corrections ){
					activeCorrections++;
					corrections[0].reset();
					i = 0;
				}else{
					return false;
				}
			}
			for ( int j = i + 1; j < activeCorrections; j++ ){
				corrections[j].initFrom(corrections[j - 1], j == 1 ? additionalLength : 0);
				if ( !corrections[j].next() ){
					return false;
				}
			}
			return true;
		}
	}
};

struct CorrectionState{
	parsx_token_type* buffer;
	parsx_token_type* output;
	parsx_token_type followToken;
	int size;

	int L;
	int M;
};

void Correction::init(CorrectionState& state){
	activeCorrections = 1;
	corrections[0] = SingleCorrection(state.L);
	additionalLength = state.M;
}

template<bool Report>
int generateCandidate(Correction& correction, CorrectionState& state, ParserContext& parsx_ctx){
	parsx_token_type* buffer = state.buffer;
	parsx_token_type* bufferEnd = state.buffer + state.L + state.M;
	parsx_token_type* output = state.output;
	int out = 0;

	state.size = 0;

	int cost = 0;

	SingleCorrection* sc = correction.corrections;
	while ( sc != correction.corrections + correction.activeCorrections ){
		int pos = 0;
		while ( pos < sc->pos ){
			pos++;
			*output = *buffer;
			output++;
			buffer++;
			state.size++;
		}
		switch( sc->type ){
		case SingleCorrection::Remove:{
			if ( Report ){
				parsx_report_remove(parsx_ctx.custom, (*buffer));
			}
			buffer++;			
			cost += parsx_correction_remove_cost;
		}break;
		case SingleCorrection::Insert:{
			*output = parsx_generate_fake_token(parsx_ctx.custom, buffer == bufferEnd ? state.followToken : *buffer, sc->token);
			if ( Report ){
				parsx_report_insert_before(parsx_ctx.custom, (buffer == bufferEnd ? state.followToken : *buffer), (*output));
			}
			output++;
			state.size++;
			cost += parsx_correction_insert_cost;
		}break;
		case SingleCorrection::Replace:{
			*output = parsx_generate_replace_token(parsx_ctx.custom, *buffer, sc->token);
			if ( Report ){
				parsx_report_replace(parsx_ctx.custom, (*buffer), (*output));
			}
			output++;
			buffer++;
			state.size++;
			cost += parsx_correction_replace_cost;
		}break;
		case SingleCorrection::Swap:{
			output[0] = buffer[1];
			output[1] = buffer[0];
			if ( Report ){
				parsx_report_swap(parsx_ctx.custom, buffer[0], buffer[1]);
			}
			output += 2;
			buffer += 2;
			state.size += 2;
			cost += parsx_correction_swap_cost;
		}break;
		}
		sc++;
	}

	while ( buffer != bufferEnd ){
		*output = *buffer;
		buffer++;
		output++;
		state.size++;
	}
	return cost;
}

int parsx_input_matched_score = 1000000;

int updateScore(Correction correction, CorrectionState& state, int baseScore){
	if ( baseScore == parsx_input_matched_score ){
		return parsx_input_matched_score;
	}

	int pos = 0;
	int score = 0;
	int reserve = 0;
	int advance = 0;
	SingleCorrection* sc = correction.corrections;
	while ( sc != correction.corrections + correction.activeCorrections ){
		if ( advance + sc->pos > baseScore ){
			break;
		}
		if ( sc->pos > 0 ){
			score += sc->pos;
			advance += sc->pos;	
			if ( reserve ){
				score += reserve;
				reserve = 0;
			}
		}
		switch( sc->type ){
		case SingleCorrection::Remove:{
			reserve++;			
		}break;
		case SingleCorrection::Insert:{
			advance++;			
		}break;
		case SingleCorrection::Replace:{	
			reserve++;
			advance++;	
		}break;
		case SingleCorrection::Swap:{	
			advance += 2;
			reserve += 2;
		}break;
		}
		sc++;
	}
	if ( advance < baseScore ){
		if ( reserve ){
			score += reserve;
		}
		score += baseScore - advance;
	}
	return score;
}

int testCandidate(CorrectionState correction, ParserContext& ctx){
	parsx_token_type* tokens = correction.output;
	int size = correction.size;
	int maxSize = size;
	while ( true ){
		if ( size == 0 ){
			break;
		}		
		if ( parse_step(ctx, *tokens) ){
			if ( parsx_token_get_id((*tokens)) == parsx_eof_token ){
				parse_step(ctx, *tokens);
			}
			tokens++;
			size--;
		}else{
			undo_all(ctx, nullptr);
			return maxSize - size;
		}
	}
	if ( ctx.ll.isEmpty() ){
		undo_all(ctx, nullptr);
		return parsx_input_matched_score;
	}
	undo_all(ctx, nullptr);
	return maxSize;
}