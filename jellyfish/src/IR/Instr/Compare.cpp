#include <IR/Instr/Compare.h>

namespace jf{
	namespace ir{
		namespace instr{
			#define PrimCompare(t) Compare##t Compare##t::Instance;
			#include <IR/Instr/PrimCompare.inc>
		}
	}
}