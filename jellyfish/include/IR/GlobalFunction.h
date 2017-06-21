#pragma once
#include "FunctionSignature.h"
#include "NamedObject.h"
#include "Definition.h"

namespace jf{
	namespace ir{
		class GlobalFunction: public NamedObject{
		public:
			GlobalFunction(Module* owner, const SrcSpan& where, const StringRef& name, FunctionSignature* signature, FunctionBody* body)
				: NamedObject(where, name)
				, signature(signature)
				, body(body)
				, owner(owner){
			}

			FunctionSignature* getSignature(){
				return signature;
			}

			FunctionBody* getBody(){
				return body;
			}

			Module* getOwner(){
				return owner;
			}
		private:
			Module* owner;
			FunctionSignature* signature;
			FunctionBody* body;
		};
	}
}