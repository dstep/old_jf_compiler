#include <Support/SafeMath.h>
#include <Support/Macros.h>
#include <Support/Types.h>

namespace jf{
	u64 addWithCarry(u64 a, u64 b, u64* carry){
		if ( a + b < a ){
			(*carry)++;
		}
		return a + b;
	}

	u64 subtractWithCarry(u64 a, u64 b, u64* carry){
		if ( b > a ){
			(*carry)--;
		}
		return a - b;
	}

	u64 multiplyWithCarry(u64 a, u64 b, u64* carry){
		if ( a < (1ull << 32) && b < (1ull << 32) ){
			return a * b;
		}

		u64 p1 = (a >> 32), q1 = (a & 0xffffffffull);
		u64 p2 = (b >> 32), q2 = (b & 0xffffffffull);

		u64 p1p2 = p1 * p2;
		u64 p1q2 = p1 * q2;
		u64 q1p2 = q1 * p2;
		u64 q1q2 = q1 * q2;

		u64 low = q1q2 & 0xffffffffull;
		u64 lowCarry = (q1q2 >> 32);

		u64 midCarry = 0; 
		u64 midCarryHi = 0;
		u64 mid = addWithCarry(p1q2, q1p2, &midCarryHi);
		mid = addWithCarry(mid, lowCarry, &midCarryHi);

		midCarry = (mid >> 32) + (midCarryHi << 32);
		mid = mid & 0xffffffffull;

		u64 high = midCarry + p1p2;

		*carry = high;
		return (low | (mid << 32));
	}

	u32 addWithCarry(u32 a, u32 b, u32* carry){
		if ( a + b < a ){
			(*carry)++;
		}
		return a + b;
	}

	u32 subtractWithCarry(u32 a, u32 b, u32* carry){
		if ( b > a ){
			(*carry)--;
		}
		return a - b;
	}

	u32 multiplyWithCarry(u32 a, u32 b, u32* carry){
		u64 result = (u64)a * (u64)b;
		*carry = (result >> 32);
		return (u32)(result & 0xffffffffull);
	}
}