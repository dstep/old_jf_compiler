#pragma once

#include <Support/Container/HashMap.h>
#include "NamedObject.h"
#include "Type.h"

namespace jf{
	namespace ir{
		class StructField: public NamedObject{
		public:
			StructField(const SrcSpan& where, const StringRef& name, Type type)
				: NamedObject(where, name)
				, type(type){
			}

			const Type& getType(){
				return type;
			}
		private:
			Type type;
		};

		class Struct: public NamedObject{
		public:
			Struct(Module* owner, const SrcSpan& where, const StringRef& name, const ArrayRef<StructField>& fields, StringMap<StructField*>* fieldMap)
				: NamedObject(where, name)
				, owner(owner)
				, fields(fields)
				, fieldMap(fieldMap){
			}

			const ArrayRef<StructField>& getFields(){
				return fields;
			}

			StringMap<StructField*>* getFieldMap(){
				return fieldMap;
			}

			Module* getOwner(){
				return owner;
			}
		private:
			Module* owner;
			ArrayRef<StructField> fields;
			StringMap<StructField*>* fieldMap;
		};
	}
}