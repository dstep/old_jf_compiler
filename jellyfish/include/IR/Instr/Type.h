#pragma once
#include <Support/Types.h>
#include <Support/StringRef.h>
#include <Support/SourceLoc.h>
#include <IR/Class.h>
#include <IR/Interface.h>
#include <IR/Enum.h>
#include <IR/Struct.h>

namespace jf{
	namespace ir{
		namespace instr{
			enum TypeTag{
			#define PrimType(t) Type##t##Tag,
				#include "PrimTypes.inc"

				TypeUnnamedStructTag,
				TypeUnnamedEnumTag,
				TypeFunctionTag,
				TypeOptionalTag,
				TypeNumberTag,
				TypeStringLiteralTag,

				TypeNumericTag,

				TypeClassTag,
				TypeStructTag,
				TypeInterfaceTag,
				TypeEnumTag,

				TypeSetTag,
				TypeMapTag,
				TypeArrayTag,

				TypeVarTag,
				TypeTemplateVarTag
			};

			struct Type;

			Type* BuildType(MemoryPoolSlice* pool, ir::Type type);

			struct Type{
				TypeTag tag;

				Type(TypeTag tag)
					: tag(tag){
				}

				Type* getRepr();
				bool isNumericClass();
			};

			#define PrimType(t) struct Type##t: public Type{Type##t():Type(Type##t##Tag){} static Type##t Instance; static Type##t* Get(){ return &Instance; }};
			#include "PrimTypes.inc"

			struct TypeEdge;

			namespace TypeNumberRank{
				enum Value{
					None = 0,
					Constant,
					Int,
					Float,
					Double,
					Any
				};

				Value MergeInRank(Value left, Value right);
				Value MergeOutRank(Value left, Value right);
				Type* GetTypeByRank(Value rank);
			};

			struct TypeNumeric: public Type{
				Type* parent;
				TypeEdge* inedges;
				TypeEdge* outedges;
				TypeNumberRank::Value inRank;
				TypeNumberRank::Value outRank;

				bool realConstraint;

				u16 lowlink, index;
				bool onstack;

				TypeNumeric()
					: Type(TypeNumericTag)
					, parent(this)
					, inedges(nullptr)
					, outedges(nullptr)
					, realConstraint(false)
					, inRank(TypeNumberRank::None)
					, outRank(TypeNumberRank::Any)
					, lowlink(0)
					, index(0)
					, onstack(false){
				}
			};

			struct TypeEdge{
				TypeNumeric* outv;
				TypeNumeric* inv;

				TypeEdge *nextInedge, *prevInedge;
				TypeEdge *nextOutedge, *prevOutedge;

				TypeEdge(TypeNumeric* outv, TypeNumeric* inv)
					: outv(outv)
					, inv(inv)
					, nextInedge(inv->inedges)
					, prevInedge(nullptr)
					, nextOutedge(outv->outedges)
					, prevOutedge(nullptr){
					if ( inv->inedges ){
						inv->inedges->prevInedge = this;
					}
					inv->inedges = this;
					if ( outv->outedges ){
						outv->outedges->prevOutedge = this;
					}
					outv->outedges = this;
				}					
			};

			struct TypeNumber: public Type{
				SrcSpan where;
				StringRef value;

				TypeNumber(const SrcSpan& where, const StringRef& value)
					: Type(TypeNumberTag)
					, value(value)
					, where(where){
				}
			};

			struct TypeStringLiteral: public Type{
				StringRef value;

				TypeStringLiteral(const StringRef& value)
					: Type(TypeStringLiteralTag)
					, value(value){
				}
			};
			
			struct TypeClass: public Type{
				ir::Class* class_;

				TypeClass(ir::Class* class_)
					: Type(TypeClassTag)
					, class_(class_){
				}
			};

			struct TypeVar: public Type{
				Type* parent;
				u32 rank;
				StringRef name;
				u32 index;

				TypeVar(const StringRef& name, u32 index)
					: Type(TypeVarTag)
					, parent(this)
					, name(name)
					, index(index)
					, rank(rank){
				}
			};

			struct TypeTemplateVar: public Type{
				u32 index;
				StringRef name;

				enum Constraint{
					Unconstrainted,
					Numeric,
					Real
				} constraint;
				
				TypeTemplateVar(u32 index, Constraint constraint, const StringRef& name)
					: Type(TypeTemplateVarTag)
					, constraint(constraint)
					, index(index)
					, name(name){
				}
			};

			struct TypeUnnamedStruct: public Type{
				size_t paramsCount;
				#pragma warning(push)
				#pragma warning(disable:4200)
				Type* params[];
				#pragma warning(pop)

				TypeUnnamedStruct(size_t paramsCount)
					: Type(TypeUnnamedStructTag)
					, paramsCount(paramsCount){
				}
			};

			struct TypeUnnamedEnum: public Type{
				size_t paramsCount;
				#pragma warning(push)
				#pragma warning(disable:4200)
				Type* params[];
				#pragma warning(pop)

				TypeUnnamedEnum(size_t paramsCount)
					: Type(TypeUnnamedEnumTag)
					, paramsCount(paramsCount){
				}
			};

			struct TypeFunction: public Type{
				Type* returnType;
				size_t paramsCount;
				#pragma warning(push)
				#pragma warning(disable:4200)
				Type* params[];
				#pragma warning(pop)

				TypeFunction(Type* returnType, size_t paramsCount)
					: Type(TypeFunctionTag)
					, paramsCount(paramsCount)
					, returnType(returnType){
				}
			};


			struct TypeInterface: public Type{
				ir::Interface* interface;

				TypeInterface(ir::Interface* interface)
					: Type(TypeInterfaceTag)
					, interface(interface){
				}
			};

			struct TypeStruct: public Type{
				ir::Struct* struct_;

				TypeStruct(ir::Struct* struct_)
					: Type(TypeStructTag)
					, struct_(struct_){
				}
			};

			struct TypeEnum: public Type{
				ir::Enum* enum_;

				TypeEnum(ir::Enum* enum_)
					: Type(TypeEnumTag)
					, enum_(enum_){
				}
			};

			struct TypeOptional: public Type{
				Type* valueType;

				TypeOptional(Type* valueType)
					: Type(TypeOptionalTag)
					, valueType(valueType){
				}
			};

			struct TypeSet: public Type{
				Type* keyType;

				TypeSet(Type* keyType)
					: Type(TypeSetTag)
					, keyType(keyType){
				}
			};

			struct TypeMap: public Type{				
				Type* keyType;
				Type* valueType;

				TypeMap(Type* keyType, Type* valueType)
					: Type(TypeMapTag)
					, keyType(keyType)
					, valueType(valueType){
				}
			};

			struct TypeArray: public Type{
				Type* valueType;

				TypeArray(Type* valueType)
					: Type(TypeArrayTag)
					, valueType(valueType){
				}
			};

			StringRef ShowType(MemoryPoolSlice* hostPool, MemoryPoolSlice& tempPool, Type* type);
		}
	}
}