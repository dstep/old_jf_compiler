#pragma once

namespace jf{
	namespace pipeline{
		class Target{
		public:
			enum Type{
				Native
			};

			Type getType();
			ArrayRef<StringRef> getParams();
		};
	}
}