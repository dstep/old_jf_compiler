#pragma once
#include "Function.h"
#include "Common.h"

namespace jf{
	namespace parser{
		namespace ast{
			struct Import{
				Import* next;
				SrcSpan where;
				QualID* qid;				
				StringRef as;
				
				Import(SrcSpan where, QualID* qid, const StringRef& as)
					: where(where)
					, qid(qid)
					, as(as)
					, next(nullptr){
				}
			};

			struct TopLevel;

			struct Module{
				Import* imports;
				TopLevel* topLevels;

				Module(Import* imports, TopLevel* topLevels)
					: imports(imports)
					, topLevels(topLevels){
				}
			};

			enum TopLevelTag{
				GlobalFunctionTag,
				GlobalVariableTag,
				InterfaceTag,
				StructTag,
				ClassTag,
				EnumTag
			};

			struct TopLevel{
				TopLevel* next;
				TopLevelTag tag;
				
				TopLevel(TopLevelTag tag)
					: tag(tag)
					, next(nullptr){
				}
			};

			struct GlobalFunction: public TopLevel{
				FunctionSignature* signature;
				FunctionBody* body;
				SrcSpan where;
				StringRef name;

				GlobalFunction(const SrcSpan& where, const StringRef& name, FunctionSignature* signature, FunctionBody* body)
					: TopLevel(GlobalFunctionTag)
					, where(where)
					, signature(signature)
					, body(body)
					, name(name){
				}
			};

			struct GlobalVariable: public TopLevel{
				SrcSpan where;
				StringRef name;
				Type* type;
				Expr* initializer;

				GlobalVariable(const SrcSpan& where, const StringRef& name, Type* type, Expr* initializer)
					: TopLevel(GlobalVariableTag)
					, where(where)
					, name(name)
					, type(type)
					, initializer(initializer){
				}
			};

			struct EnumConstructor{
				EnumConstructor* next;
				SrcSpan where;
				StringRef name;
				FunctionSignature* signature;

				EnumConstructor(const SrcSpan& where, const StringRef& name, FunctionSignature* signature)
					: where(where)
					, name(name)
					, signature(signature)
					, next(nullptr){
				}
			};

			struct Enum: public TopLevel{
				SrcSpan where;
				StringRef name;
				EnumConstructor* constructors;

				Enum(const SrcSpan& where, const StringRef& name, EnumConstructor* constructors)
					: TopLevel(EnumTag)
					, where(where)
					, name(name)
					, constructors(constructors){
				}
			};

			struct Implements{
				Implements* next;
				SrcSpan where;
				QualID* qid;

				Implements(const SrcSpan& where, QualID* qid)
					: next(nullptr)
					, where(where)
					, qid(qid){
				}
			};

			struct Extends{
				SrcSpan where;
				QualID* qid;

				Extends(const SrcSpan& where, QualID* qid)
					: where(where)
					, qid(qid){
				}
			};

			struct InterfaceMethod{
				InterfaceMethod* next;
				SrcSpan where;
				StringRef name;
				FunctionSignature* signature;

				InterfaceMethod(const SrcSpan& where, const StringRef& name, FunctionSignature* signature)
					: next(nullptr)
					, where(where)
					, name(name)
					, signature(signature){
				}
			};

			struct Interface: public TopLevel{
				SrcSpan where;
				StringRef name;
				Implements* implements;
				InterfaceMethod* methods;

				Interface(const SrcSpan& where, const StringRef& name, Implements* implements, InterfaceMethod* methods)
					: TopLevel(InterfaceTag)
					, where(where)
					, name(name)
					, implements(implements)
					, methods(methods){
				}
			};

			struct StructField{
				StructField* next;
				Name* names;
				Type* type;

				StructField(Name* names, Type* type)
					: next(nullptr)
					, names(names)
					, type(type){
				}
			};

			struct Struct: public TopLevel{
				SrcSpan where;
				StringRef name;
				StructField* fields;

				Struct(const SrcSpan& where, const StringRef& name, StructField* fields)
					: TopLevel(StructTag)
					, where(where)
					, name(name)
					, fields(fields){
				}
			};

			enum ClassMemberTag{
				ClassFieldTag,
				ClassMethodTag,
				ClassConstructorTag
			};

			struct ClassMember{
				ClassMember* next;
				ClassMemberTag tag;

				ClassMember(ClassMemberTag tag)
					: tag(tag){
				}
			};

			struct ClassField: public ClassMember{
				Name* names;
				Type* type;

				ClassField(Name* names, Type* type)
					: ClassMember(ClassFieldTag)
					, names(names)
					, type(type){
				}
			};

			struct ClassMethod: public ClassMember{
				enum Kind{
					Abstract,
					Method,
					Override
				} kind;
				SrcSpan where;
				StringRef name;
				FunctionSignature* signature;
				FunctionBody* body;

				ClassMethod(Kind kind, const SrcSpan& where, const StringRef& name, FunctionSignature* signature, FunctionBody* body)
					: ClassMember(ClassMethodTag)
					, kind(kind)
					, where(where)
					, name(name)
					, signature(signature)
					, body(body){
				}
			};

			struct ClassConstructor: public ClassMember{
				SrcSpan where;
				StringRef name;
				QualID* with;
				FunctionSignature* signature;
				FunctionBody* body;

				ClassConstructor(const SrcSpan& where, const StringRef& name, QualID* with, FunctionSignature* signature, FunctionBody* body)
					: ClassMember(ClassConstructorTag)
					, with(with)
					, where(where)
					, name(name)
					, signature(signature)
					, body(body){
				}
			};

			struct Class: public TopLevel{
				SrcSpan where;
				StringRef name;
				Extends* extends;
				Implements* implements;
				ClassMember* members;

				Class(const SrcSpan& where, const StringRef& name, Extends* extends, Implements* implements, ClassMember* members)
					: TopLevel(ClassTag)
					, where(where)
					, name(name)
					, extends(extends)
					, implements(implements)
					, members(members){
				}
			};
		}
	}
}