#include <IR/Instr/Coercion.h>

namespace jf{
	namespace ir{
		namespace instr{
			#define PrimCoercion(t) \
					Coercion##t Coercion##t::Instance; \

			PrimCoercion(Later)
			PrimCoercion(Id)
			PrimCoercion(FromUndef)
			PrimCoercion(IntToDouble)
			PrimCoercion(FloatToDouble)

			#undef PrimCoercion
		}
	}
}