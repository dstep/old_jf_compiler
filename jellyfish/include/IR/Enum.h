#pragma once

#include <Support/Container/HashMap.h>
#include "NamedObject.h"
#include "Type.h"
#include "FunctionSignature.h"

namespace jf{
	namespace ir{
		class Enum;

		class EnumConstructor: public NamedObject{
		public:
			EnumConstructor(Enum* owner, const SrcSpan& where, const StringRef& name, ArrayRef<Param> params)
				: NamedObject(where, name)
				, owner(owner)
				, params(params){
			}

			const ArrayRef<Param>& getParams(){
				return params;
			}

			Enum* getOwner(){
				return owner;
			}
		private:
			Enum* owner;
			ArrayRef<Param> params;
		};

		class Enum: public NamedObject{
		public:
			Enum(Module* owner, const SrcSpan& where, const StringRef& name, const ArrayRef<EnumConstructor>& constructors, StringMap<EnumConstructor*>* constructorMap)
				: NamedObject(where, name)
				, owner(owner)
				, constructors(constructors)
				, constructorMap(constructorMap){
			}

			const ArrayRef<EnumConstructor>& getConstructors(){
				return constructors;
			}

			StringMap<EnumConstructor*>* getConstructorMap(){
				return constructorMap;
			}

			Module* getOwner(){
				return owner;
			}
		private:
			Module* owner;
			ArrayRef<EnumConstructor> constructors;
			StringMap<EnumConstructor*>* constructorMap;
		};
	}
}