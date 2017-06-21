#pragma once
#include <Support/Types.h>

namespace jf{
	u64 addWithCarry(u64 a, u64 b, u64* carry);
	u64 subtractWithCarry(u64 a, u64 b, u64* carry);
	u64 multiplyWithCarry(u64 a, u64 b, u64* carry);

	u32 addWithCarry(u32 a, u32 b, u32* carry);
	u32 subtractWithCarry(u32 a, u32 b, u32* carry);
	u32 multiplyWithCarry(u32 a, u32 b, u32* carry);
}