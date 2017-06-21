#pragma once

#include <Support/Threading/Dataflow.h>
#include <Support/Ordering.h>
#include <Support/Container/HashMap.h>
#include "NamedObject.h"
#include "FunctionSignature.h"
#include "Type.h"
#include "Definition.h"
#include "Import.h"
#include "Interface.h"

namespace jf{
	namespace ir{
		namespace instr{
			struct Coercion;
		}

		class Class;

		enum ClassMemberTag{
			ClassMethodTag,
			ClassConstructorTag,
			ClassFieldTag
		};

		class ClassMember: public NamedObject{
		public:
			ClassMemberTag tag;

			ClassMember(ClassMemberTag tag, Class* owner, const SrcSpan& where, const StringRef& name)
				: owner(owner)
				, tag(tag)
				, NamedObject(where, name){
			}

			Class* getOwner(){
				return owner;
			}

			StringRef getKindName(){
				return GetKindName(tag);
			}

			static StringRef GetKindName(ClassMemberTag tag);

			ReferencedSymbol makeReference();
		private:
			Class* owner;
		};

		class ClassField: public ClassMember{
		public:
			ClassField(Class* owner, const SrcSpan& where, const StringRef& name, const Type& type)
				: ClassMember(ClassFieldTag, owner, where, name)
				, type(type){
			}

			const Type& getType(){
				return type;
			}
		private:
			Type type;
		};

		class Interface;
		class Class;

		class ClassMethodOverride;

		class ClassMethod: public ClassMember{
		public:
			enum Kind{
				Method,
				Abstract,
				Override
			};

			ClassMethod(Class* owner, SrcSpan where, StringRef name, Kind kind, FunctionSignature* signature, FunctionBody* body)
				: ClassMember(ClassMethodTag, owner, where, name)
				, kind(kind)
				, signature(signature)
				, body(body)
				, overrider(nullptr)
				, baseMethod(nullptr){
			}

			Kind getKind(){
				return kind;
			}

			FunctionSignature* getSignature(){
				return signature;
			}

			FunctionBody* getBody(){
				return body;
			}

			ClassMethodOverride* getOverride(){
				return overrider;
			}

			void setOverride(ClassMethodOverride* overrider){
				this->overrider = overrider;
			}

			ClassMethod* getBaseMethod(){
				return baseMethod;
			}

			void setBaseMethod(ClassMethod* baseMethod){
				this->baseMethod = baseMethod;
			}
		private:
			FunctionSignature* signature;
			FunctionBody* body;
			Kind kind;
			ClassMethod* baseMethod;
			ClassMethodOverride* overrider;
		};

		class ClassConstructor: public ClassMember{
		public:
			ClassConstructor(Class* owner, SrcSpan where, StringRef name, ImportName* baseName, FunctionSignature* signature, FunctionBody* body)
				: ClassMember(ClassConstructorTag, owner, where, name)
				, baseName(baseName)
				, signature(signature)
				, body(body)
				, baseClass(nullptr){
			}

			ImportName* getBaseName(){
				return baseName;
			}

			FunctionSignature* getSignature(){
				return signature;
			}

			void setBaseClass(Class* baseClass){
				this->baseClass = baseClass;
			}

			Class* getBaseClass(){
				return baseClass;
			}

			FunctionBody* getBody(){
				return body;
			}
		private:
			FunctionSignature* signature;
			FunctionBody* body;
			ImportName* baseName;
			Class* baseClass;
		};

		class ClassExtends{
		public:
			ClassExtends(const SrcSpan& where, ImportName* importName)
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

			Class* getBaseClass(){
				if ( dependency.satisfied ){
					return getTargetClass();
				}
				return nullptr;
			}

			Class* getTargetClass(){
				if ( importName && importName->getResolution() ){
					return (Class*)importName->getResolution().reference;
				}
				return nullptr;
			}
		private:
			SrcSpan where;
			ImportName* importName;
			threading::Dependency dependency;
		};

		class ClassMethodOverride{
		public:
			ClassMethodOverride(ClassMethod* base, ClassMethod* overrider, instr::Coercion* retValCoercion, const ArrayRef<instr::Coercion*>& paramCoercion)
				: base(base)
				, overrider(overrider)
				, retValCoercion(retValCoercion)
				, paramCoercion(paramCoercion){
			}

			ClassMethod* getBaseMethod(){
				return base;
			}

			ClassMethod* getOverrideMethod(){
				return overrider;
			}

			ArrayRef<instr::Coercion*> getParamCoercions(){
				return paramCoercion;
			}

			instr::Coercion* getRetValCoercion(){
				return retValCoercion;
			}
		private:
			ClassMethod* base;
			ClassMethod* overrider;
			instr::Coercion* retValCoercion;
			ArrayRef<instr::Coercion*> paramCoercion;
		};

		class ClassMethodImplements{
		public:
			ClassMethodImplements(InterfaceMethod* base, ClassMethod* overrider, instr::Coercion* retValCoercion, const ArrayRef<instr::Coercion*>& paramCoercion)
				: base(base)
				, overrider(overrider)
				, retValCoercion(retValCoercion)
				, paramCoercion(paramCoercion){
			}

			InterfaceMethod* getBaseMethod(){
				return base;
			}

			ClassMethod* getOverrideMethod(){
				return overrider;
			}

			ArrayRef<instr::Coercion*> getParamCoercions(){
				return paramCoercion;
			}

			instr::Coercion* getRetValCoercion(){
				return retValCoercion;
			}
		private:
			InterfaceMethod* base;
			ClassMethod* overrider;
			instr::Coercion* retValCoercion;
			ArrayRef<instr::Coercion*> paramCoercion;
		};

		class Class: public NamedObject{
		public:
			typedef SearchTree<StringRef, ClassMember*, StringRef::Compare> MembersMap;
			typedef SearchTree<ClassMember*, ClassMember*, Ordering::Compare<ClassMember*> > AbstractsMap;
			typedef SearchTree<Class*, u32, Ordering::Compare<Class*> > BasesMap;
			typedef SearchTree<StringRef, ClassConstructor*, StringRef::Compare> ConstructorsMap;
			typedef SearchTree<InterfaceMethod*, ClassMethodImplements*, Ordering::Compare<InterfaceMethod*> > ImplementMethodsMap;

			Class
				(
					Module* owner,
					const SrcSpan& where, 
					const StringRef& name, 
					ClassExtends* extends,
					const ArrayRef<ImplementsInterface>& implements,
					const ArrayRef<ClassMethod>& methods,
					const ArrayRef<ClassField>& fields,
					const ArrayRef<ClassConstructor>& constructors,
					StringMap<ClassConstructor*>* ownConstructorMap
				)
				: NamedObject(where, name)
				, owner(owner)
				, extends(extends)
				, implements(implements)
				, methods(methods)
				, fields(fields)
				, constructors(constructors)
				, ownConstructorMap(ownConstructorMap)
				, level(0){
			}

			ClassExtends* getExtends(){
				return extends;
			}

			const ArrayRef<ImplementsInterface>& getImplements(){
				return implements;
			}

			const ArrayRef<ClassMethod>& getMethods(){
				return methods;
			}

			const ArrayRef<ClassField>& getFields(){
				return fields;
			}

			const ArrayRef<ClassConstructor>& getConstructors(){
				return constructors;
			}

			StringMap<ClassConstructor*>* getOwnConstructorMap(){
				return ownConstructorMap;
			}

			ConstructorsMap& getAllConstructorsMap(){
				return allConstructorsMap;
			}

			threading::DataflowJob* getDataflowJob(){
				return &dataflowJob;
			}

			MembersMap getMembersMap(){
				return membersMap;
			}

			AbstractsMap getAbstractMap(){
				return abstractsMap;
			}

			BasesMap getBasesMap(){
				return basesMap;
			}

			Class* getBaseClass(){
				if ( extends ){
					return extends->getBaseClass();
				}
				return nullptr;
			}

			void setMembersMap(const MembersMap& membersMap){
				this->membersMap = membersMap;
			}

			void setAbstractsMap(const AbstractsMap& abstractsMap){
				this->abstractsMap = abstractsMap;
			}

			void setAllConstructorsMap(const ConstructorsMap& allConstructorsMap){
				this->allConstructorsMap = allConstructorsMap;
			}

			void setBasesMap(const BasesMap& basesMap){
				this->basesMap = basesMap;
			}

			void setImplementMethodsMap(const ImplementMethodsMap& map){
				this->implementMethodsMap = map;
			}

			Module* getOwner(){
				return owner;
			}

			const ImplementMethodsMap& getImplementMethodsMap(){
				return implementMethodsMap;
			}
			
			const ImplementsInterface::Map& getImplementsMap(){
				return implementsMap;
			}

			void setImplementsMap(const ImplementsInterface::Map& implementsMap){
				this->implementsMap = implementsMap;
			}

			u32 getLevel(){
				return level;
			}

			void setLevel(u32 level){
				this->level = level;
			}

			ReferencedSymbol makeSymbol();
		private:
			Module* owner;
			ClassExtends* extends;
			ArrayRef<ImplementsInterface> implements;
			ArrayRef<ClassMethod> methods;
			ArrayRef<ClassField> fields;
			ArrayRef<ClassConstructor> constructors;
			StringMap<ClassConstructor*>* ownConstructorMap;
			ConstructorsMap allConstructorsMap;
			MembersMap membersMap;
			AbstractsMap abstractsMap;
			BasesMap basesMap;
			ImplementsInterface::Map implementsMap;
			ImplementMethodsMap implementMethodsMap;
			threading::DataflowJob dataflowJob;
			u32 level;
		};
	}
}