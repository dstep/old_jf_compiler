#pragma once
#include "Type.h"

namespace jf{
	namespace ir{
		namespace instr{
			enum CoercionTag{
				CoercionLaterTag,
				CoercionIdTag,
				CoercionFromUndefTag,
				CoercionIntToDoubleTag,
				CoercionFloatToDoubleTag,
				CoercionIntToFloatTag,
				CoercionConstIntTag,
				CoercionConstFloatTag,
				CoercionConstDoubleTag,
				CoercionConstStringTag,
				CoercionToBaseClassTag,
				CoercionToClassImplementedTag,
				CoercionLiftMaybeTag,
				CoercionWrapMaybeTag,
				CoercionNullToMaybeTag
			};

			struct Coercion{
				CoercionTag tag;

				Coercion(CoercionTag tag)
					: tag(tag){
				}
			};
			#define PrimCoercion(t) \
				struct Coercion##t: public Coercion{ \
					static Coercion##t Instance; \
					static Coercion##t* Get(){ return &Instance; } \
					Coercion##t() \
						: Coercion(Coercion##t##Tag){ \
					} \
				};

			PrimCoercion(Later)
			PrimCoercion(Id)
			PrimCoercion(FromUndef)
			PrimCoercion(IntToDouble)
			PrimCoercion(FloatToDouble)

			#undef PrimCoercion

			struct CoercionConstInt: public Coercion{
				s32 value;

				CoercionConstInt(s32 value)
					: Coercion(CoercionConstIntTag)
					, value(value){
				}
			};

			struct CoercionConstFloat: public Coercion{
				float value;

				CoercionConstFloat(float value)
					: Coercion(CoercionConstFloatTag)
					, value(value){
				}
			};

			struct CoercionConstDouble: public Coercion{
				double value;

				CoercionConstDouble(double value)
					: Coercion(CoercionConstDoubleTag)
					, value(value){
				}
			};

			struct CoercionConstString: public Coercion{
				TypeStringLiteral* value;

				CoercionConstString(TypeStringLiteral* value)
					: Coercion(CoercionConstStringTag)
					, value(value){
				}
			};

			struct CoercionToBaseClass: public Coercion{
				ir::Class* from;
				ir::Class* to;

				CoercionToBaseClass(ir::Class* from, ir::Class* to)
					: Coercion(CoercionToBaseClassTag)
					, from(from)
					, to(to){
				}
			};

			struct CoercionToClassImplemented: public Coercion{
				ir::Class* from;
				ir::Interface* to;

				CoercionToClassImplemented(ir::Class* from, ir::Interface* to)
					: Coercion(CoercionToClassImplementedTag)
					, from(from)
					, to(to){
				}
			};

			struct CoercionLiftMaybe: public Coercion{
				Coercion* valueCoercion;
				instr::Type* fromValueType;
				instr::Type* toValueType;

				CoercionLiftMaybe(Coercion* valueCoercion, instr::Type* fromValueType, instr::Type* toValueType)
					: Coercion(CoercionLiftMaybeTag)
					, valueCoercion(valueCoercion)
					, fromValueType(fromValueType)
					, toValueType(toValueType){
				}
			};

			struct CoercionWrapMaybe: public Coercion{
				Coercion* valueCoercion;
				instr::Type* valueType;

				CoercionWrapMaybe(Coercion* valueCoercion, instr::Type* valueType)
					: Coercion(CoercionWrapMaybeTag)
					, valueCoercion(valueCoercion)
					, valueType(valueType){
				}
			};

			struct CoercionNullToMaybe: public Coercion{
				instr::Type* valueType;

				CoercionNullToMaybe(instr::Type* valueType)
					: Coercion(CoercionNullToMaybeTag)
					, valueType(valueType){
				}
			};
		}
	}
}