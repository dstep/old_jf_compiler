#pragma once

#include "NamedObject.h"
#include "FunctionSignature.h"
#include "Import.h"
#include <Support/Threading/Dataflow.h>

namespace jf{
	namespace ir{
		class Interface;

		class InterfaceMethod: public NamedObject{
		public:
			InterfaceMethod(Interface* owner, const SrcSpan& where, const StringRef& name, FunctionSignature* signature)
				: NamedObject(where, name)
				, owner(owner)
				, signature(signature){
			}

			FunctionSignature* getSignature(){
				return signature;
			}

			Interface* getOwner(){
				return owner;
			}

			ReferencedSymbol makeReference();
		private:
			Interface* owner;
			FunctionSignature* signature;
		};

		class ImplementsInterface{
		public:
			typedef SearchTree< Interface*,bool,Ordering::Compare<Interface*> > Map;

			ImplementsInterface(const SrcSpan& where, ImportName* importName)
				: where(where)
				, importName(importName){
			}

			const SrcSpan& getSrcLoc(){
				return where;
			}

			ImportName* getImportName(){
				return importName;
			}		
			
			threading::Dependency* getDependency(){
				return &dependency;
			}	

			Interface* getBaseInterface(){
				Interface* targetInterface = getTargetInterface();
				if ( targetInterface && dependency.satisfied ){
					return targetInterface;
				}
				return nullptr;
			}

			Interface* getTargetInterface(){
				if ( importName && importName->getResolution() ){
					return (Interface*)importName->getResolution().reference;
				}
				return nullptr;
			}
		private:
			SrcSpan where;
			ImportName* importName;
			threading::Dependency dependency;
		};

		class Interface: public NamedObject{
		public:
			typedef SearchTree<StringRef, InterfaceMethod*, StringRef::Compare> MethodMap;

			Interface(Module* owner, const SrcSpan& where, const StringRef& name, const ArrayRef<ImplementsInterface>& extends, const ArrayRef<InterfaceMethod>& methods)
				: NamedObject(where, name)
				, owner(owner)
				, extends(extends)
				, methods(methods){
			}

			Module* getOwner(){
				return owner;
			}

			const ArrayRef<InterfaceMethod>& getMethods(){
				return methods;
			}

			const ArrayRef<ImplementsInterface>& getExtends(){
				return extends;
			}

			threading::DataflowJob* getDataflowJob(){
				return &dataflowJob;
			}

			const ImplementsInterface::Map& getImplementsMap(){
				return implementsMap;
			}

			void setImplementsMap(const ImplementsInterface::Map& implementsMap){
				this->implementsMap = implementsMap;
			}

			const MethodMap& getMethodMap(){
				return methodMap;
			}

			void setMethodMap(const MethodMap& methodMap){
				this->methodMap = methodMap;
			}
		private:
			Module* owner;
			ArrayRef<ImplementsInterface> extends;
			ArrayRef<InterfaceMethod> methods;
			threading::DataflowJob dataflowJob;

			ImplementsInterface::Map implementsMap;
			MethodMap methodMap;
		};
	}
}