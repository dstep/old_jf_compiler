#pragma once
#include <IR/Instr/Instr.h>

namespace jf{
	namespace ir{
		namespace compiler{
			struct Value{
				instr::Instr* producer;
				instr::Type* type;

				Value()
					: producer(nullptr)
					, type(nullptr){
				}

				Value(instr::Instr* producer, instr::Type* type)
					: producer(producer)
					, type(type){
				}
			};

			struct TemplateInstance{
				instr::BuiltinFunction::Template* function;
				#pragma warning(push)
				#pragma warning(disable:4200)
				instr::Type* args[];
				#pragma warning(pop)

				TemplateInstance(instr::BuiltinFunction::Template* function)
					: function(function){
				}
			};

			struct Reference{
				enum Kind{
					None,
					Namespace,
					Class,
					Interface,
					Enum,
					Struct,
					UpValue,
					GlobalFunction,
					GlobalVariable,
					EnumConstructor,
					ClassMethod,
					ClassField,
					InterfaceMethod,
					StructField,
					Expression,
					LocalVariable,
					BuiltinFunction,
					BuiltinInstance
				} kind;
				
				void* reference;
				Space<Value> value;

				Reference(Kind kind)
					: kind(kind){
				}

				Reference(Kind kind, void* reference)
					: kind(kind)
					, reference(reference){
				}

				Reference(Kind kind, const Value& value)
					: kind(kind)
					, value(value){
				}

				Reference(Kind kind, void* reference, const Value& value)
					: kind(kind)
					, reference(reference)
					, value(value){
				}
			};
		}
	}
}