#pragma once
#include "Type.h"

namespace jf{
	namespace ir{
		namespace instr{
			enum CompareClassTag{
				#define PrimCompare(t) Compare##t##Tag,
				#include "PrimCompare.inc"

				CompareNumericTag,
				CompareEnumTag,
				CompareStructTag,
				CompareUnnamedEnumTag,
				CompareUnnamedStructTag
			};

			struct CompareClass{
				CompareClassTag tag;

				CompareClass(CompareClassTag tag)
					: tag(tag){
				}
			};

			#define PrimCompare(t) struct Compare##t: public CompareClass{ \
				static Compare##t Instance; \
				static Compare##t* Get(){ return &Instance; } \
				Compare##t():CompareClass(Compare##t##Tag){} \
				};
			#include "PrimCompare.inc"

			struct CompareNumeric: public CompareClass{
				instr::Type* type;

				CompareNumeric(instr::Type* type)
					: CompareClass(CompareNumericTag)
					, type(type){
				}
			};

			struct CompareEnum: public CompareClass{
				ir::Enum* enum_;

				CompareEnum(ir::Enum* enum_)
					: CompareClass(CompareEnumTag)
					, enum_(enum_){
				}
			};

			struct CompareStruct: public CompareClass{
				ir::Struct* struct_;

				CompareStruct(ir::Struct* struct_)
					: CompareClass(CompareStructTag)
					, struct_(struct_){
				}
			};

			struct CompareUnnamedStruct: public CompareClass{
				instr::TypeUnnamedStruct* struct_;

				CompareUnnamedStruct(instr::TypeUnnamedStruct* struct_)
					: CompareClass(CompareUnnamedStructTag)
					, struct_(struct_){
				}
			};

			struct CompareUnnamedEnum: public CompareClass{
				instr::TypeUnnamedEnum* enum_;

				CompareUnnamedEnum(instr::TypeUnnamedEnum* enum_)
					: CompareClass(CompareUnnamedEnumTag)
					, enum_(enum_){
				}
			};
		}
	}
} 