#pragma once
#include <Support/ArrayRef.h>
#include <Support/StringRef.h>

namespace jf{
	namespace pipeline{
		struct Archive{
			ArrayRef<StringRef> sources;
			StringRef output;
		};
	}
}