#pragma once
#include <Support/StringRef.h>
#include "Instr.h"

namespace jf{
	namespace ir{
		namespace instr{
			namespace BuiltinFunction{
				namespace ID{
					enum Value{
						Not,
						Negate,
						Plus,
						Minus,
						Multiply,
						Divide,
						Remainder,
						Concat,

						NearbyInt,
						NearbyFloat,

						Round,
						Ceil,
						Floor,
						Trunc,

						Sqrt,

						EmptyArray,
						ArrayPush,
						ArrayPop,
						ArrayClear,
						ArraySet,
						ArrayGet,
						ArraySize,

						AllocateBytes,
						BytesWriteFloat,
						BytesWriteU16
					};
				}

				struct Template{
					ID::Value id;
					instr::Type* result;
					instr::Type* thisObjectType;
					ArrayRef<instr::TypeTemplateVar*> typeParams;
					ArrayRef<instr::Type*> params;

					Template(ID::Value id, const ArrayRef<instr::TypeTemplateVar*>& typeParams, instr::Type* result, instr::Type* thisObjectType, const ArrayRef<instr::Type*>& params)
						: id(id)
						, result(result)
						, thisObjectType(thisObjectType)
						, typeParams(typeParams)
						, params(params){
					}
				};

				extern Template Not;

				extern Template Negate;

				extern Template Plus;
				extern Template Minus; 
				extern Template Multiply; 
				extern Template Divide; 
				extern Template Remainder; 

				extern Template Concat; 

				extern Template NearbyInt; 
				extern Template NearbyFloat; 

				extern Template Round; 
				extern Template Ceil; 
				extern Template Floor; 
				extern Template Trunc; 

				extern Template Sqrt;

				extern Template EmptyArray;

				extern Template ArrayPush;
				extern Template ArrayPop;
				extern Template ArrayClear;
				extern Template ArraySet;
				extern Template ArrayGet;
				extern Template ArraySize;

				extern Template AllocateBytes;

				extern Template BytesWriteFloat;
				extern Template BytesWriteU16;
			};

			BuiltinFunction::Template* FindBuiltinFunction(const StringRef& name);

			BuiltinFunction::Template* FindPropertyArray(const StringRef& name);

			BuiltinFunction::Template* FindPropertyBytes(const StringRef& name);
		}
	}
}