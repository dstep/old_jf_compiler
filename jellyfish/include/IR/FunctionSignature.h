#pragma once
#include "NamedObject.h"
#include "Type.h"

namespace jf{
	namespace ir{
		class Param: public NamedObject{
		public:
			Param(const SrcSpan& where, const StringRef& name, const Type& type)
				: NamedObject(where, name)
				, type(type){
			}

			const Type& getType() const{
				return type;
			}
		private:
			Type type;
		};

		class FunctionSignature{
		public:
			FunctionSignature(const Type& returnType, size_t paramsCount)
				: returnType(returnType)
				, paramsCount(paramsCount){
			}

			size_t getParamsCount() const{
				return paramsCount;
			}

			ArrayRef<Param> getParams(){
				return ArrayRef<Param>((Param*)params, paramsCount);
			}

			const Type& getReturnType() const{
				return returnType;
			}

			Param* getParam(size_t index){
				return ((Param*)params) + index;
			}
		private:
			Type returnType;
			size_t paramsCount;
			#pragma warning(push)
			#pragma warning(disable:4200)
			u8 params[0];
			#pragma warning(pop)
		};
	}
}