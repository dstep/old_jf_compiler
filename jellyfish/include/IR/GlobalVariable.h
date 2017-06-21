#pragma once
#include "Definition.h"
#include "NamedObject.h"
#include "Type.h"

namespace jf{	
	namespace ir{
		class GlobalVariable: public NamedObject{
		public:
			GlobalVariable(const SrcSpan& where, const StringRef& name, const Type& type, Initializer* initializer)
				: NamedObject(where, name)
				, type(type)
				, initializer(initializer){
			}

			const Type& getType(){
				return type;
			}

			Initializer* getInitializer(){
				return initializer;
			}
		private:
			Type type;
			Initializer* initializer;
		};
	}
}