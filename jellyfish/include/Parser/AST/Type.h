#pragma once
#include "Common.h"

namespace jf{
	namespace parser{
		namespace ast{
			enum TypeTag{
				TypePrimTag,
				TypeTupleTag,
				TypeUnionTag,
				TypeOptionalTag,
				TypeReferenceTag,
				TypeFunctionTag,
				TypeMissingTag
			};

			struct Type{
				TypeTag tag;
				SrcSpan where;

				Type(TypeTag tag, const SrcSpan& where)
					: tag(tag)
					, where(where){
				}
			};
			
			struct TypeList{
				TypeList* next;
				Type* type;

				TypeList(Type* type)
					: type(type)
					, next(nullptr){
				}
			};

			struct TypePrim: public Type{
				enum ID{
					Unit,
					Undef,
					Bool,
					Int,
					Float,
					Double,
					String,
					Bytes
				} id;

				TypePrim(const SrcSpan& where, ID id)
					: Type(TypePrimTag, where)
					, id(id){
				}
			};

			struct TypeMissing: public Type{
				TypeMissing(SrcLoc where)
					: Type(TypeMissingTag, SrcSpan(where, where)){
				}
			};

			struct TypeTuple: public Type{
				TypeList* types;

				TypeTuple(const SrcSpan& where, TypeList* types)
					: Type(TypeTupleTag, where)
					, types(types){
				}
			};

			struct TypeUnion: public Type{
				TypeList* types;

				TypeUnion(const SrcSpan& where, TypeList* types)
					: Type(TypeUnionTag, where)
					, types(types){
				}
			};

			struct TypeFunction: public Type{
				TypeList* param;
				Type* result;

				TypeFunction(const SrcSpan& where, TypeList* param, Type* result)
					: Type(TypeFunctionTag, where)
					, param(param)
					, result(result){
				}
			};

			struct TypeOptional: public Type{
				Type* type;

				TypeOptional(const SrcSpan& where, Type* type)
					: Type(TypeOptionalTag, where)
					, type(type){
				}
			};

			enum TypeReferenceNodeTag{
				TypeReferenceLeafTag,
				TypeReferenceSubscriptTag,
				TypeReferenceInstanceTag
			};

			struct TypeReferenceNode{	
				TypeReferenceNodeTag tag;

				TypeReferenceNode(TypeReferenceNodeTag tag)
					: tag(tag){
				}
			};

			struct TypeReferenceLeaf: public TypeReferenceNode{
				StringRef id;

				TypeReferenceLeaf(const StringRef& id)
					: TypeReferenceNode(TypeReferenceLeafTag)
					, id(id){
				}
			};

			struct TypeReferenceSubscript: public TypeReferenceNode{
				TypeReferenceNode* lhs;
				StringRef id;

				TypeReferenceSubscript(TypeReferenceNode* lhs, const StringRef& id)
					: TypeReferenceNode(TypeReferenceSubscriptTag)
					, lhs(lhs)
					, id(id){
				}
			};

			struct TypeReferenceInstance: public TypeReferenceNode{
				TypeReferenceNode* lhs;
				TypeList* params;

				TypeReferenceInstance(TypeReferenceNode* lhs, TypeList* params)
					: TypeReferenceNode(TypeReferenceInstanceTag)
					, lhs(lhs)
					, params(params){
				}
			};

			struct TypeReference: public Type{
				TypeReferenceNode* node;

				TypeReference(const SrcSpan& where, TypeReferenceNode* node)
					: Type(TypeReferenceTag, where)
					, node(node){
				}
			};
		}
	}
}