#pragma once

#include "Macros.h"

namespace jf{
	#define match(x) {auto _match_target = x; switch ( _match_target->tag ){
	#define rule(t, n) case t##Tag:{auto n = (t*)_match_target;
	#define erule }break;
	#define defrule(n) default:{auto n = _match_target;
	#define nodefrule default:{unreachable;}break;
	#define ematch }}
}