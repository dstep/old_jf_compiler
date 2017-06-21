#pragma once
#include "Types.h"
#include "StringRef.h"

namespace jf{
	namespace format{
		struct integer{
			integer(u32 value);

			operator StringRef();

			StringRef str(){
				return buffer;
			}

			char buffer[32];
		};

		struct real{
			real(double value);

			operator StringRef();

			StringRef str(){
				return buffer;
			}

			char buffer[128];
		};
	}
}