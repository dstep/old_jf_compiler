#pragma once

namespace jf{
	namespace ir{
		namespace compiler{
			namespace ControlFlow{
				enum Value{
					AlwaysTerminate,
					AlwaysPass,
					MayTerminate,
					NeverReaches
				};

				Value concat(Value first, Value second);
				Value merge(Value left, Value right);
			}
		}
	}
}