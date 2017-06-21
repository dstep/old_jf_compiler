#pragma once
#include <Support/Types.h>

namespace jf{
	namespace ir{
		enum TypeTag{
			TypeTagError,
			TypeTagUnit,
			TypeTagUndef,
			TypeTagBool,
			TypeTagInt,
			TypeTagFloat,
			TypeTagDouble,
			TypeTagString,
			TypeTagBytes,
			TypeTagUnnamedStruct,
			TypeTagUnnamedUnion,
			TypeTagFunction,
			TypeTagReference,
			TypeTagMap,
			TypeTagSet,
			TypeTagArray,

			TypeTagOptionalBit = (1 << 30)
		};

		class Type{
		public:
			Type(TypeTag tag)
				: tag(tag)
				, reference(nullptr){
			}

			Type(TypeTag tag, void* reference)
				: tag(tag)
				, reference(reference){
			}

			void* getReference() const{
				return reference;
			}

			TypeTag getTag() const{
				return tag;
			}

			Type unwrapOptional() const{
				Type type = *this;
				type.tag = (TypeTag)(type.tag & ~TypeTagOptionalBit);
				return type;
			}

			Type wrapOptional() const{
				Type type = *this;
				type.tag = (TypeTag)(type.tag | TypeTagOptionalBit);
				return type;
			}
		private:
			TypeTag tag;
			void* reference;
		};

		class TypeList{
		public:
			TypeList(size_t count)
				: count(count){
			}

			size_t getCount(){
				return count;
			}

			Type& getType(size_t index){
				return ((Type*)types)[index];
			}
		private:
			size_t count;
			#pragma warning(push)
			#pragma warning(disable:4200)
			u8 types[0];
			#pragma warning(pop)
		};
	}
}