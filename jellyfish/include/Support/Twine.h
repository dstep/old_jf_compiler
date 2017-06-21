#pragma once
#include "Types.h"
#include "StringRef.h"
#include "Macros.h"
#include "MemoryPool.h"
#include <string>

namespace jf{
	class Twine{
	public:
		Twine()
			: kind(KindEmpty){
		}

		Twine(const char* c_string)
			: kind(KindCString)
			, c_string(c_string){
		}

		Twine(const StringRef& string)
			: kind(string.getLength() == 0 ? KindEmpty : KindStringRef)
			, string(&string){
		}

		size_t calculateLength() const;

		void writeTo(u8* output) const{
			writeToAndModify(output);
		}

		StringRef toString(MemoryPoolSlice* stack) const{
			size_t size = calculateLength();
			u8* buffer = (u8*)stack->allocate(size);
			writeTo(buffer);
			return StringRef(buffer, size);
		}
	private:
		void writeToAndModify(u8*& output) const{
			switch ( kind ){
			case KindEmpty:
			break;
			case KindCString:{
				size_t n = strlen(c_string);
				::memcpy(output, c_string, n);
				output += n;
			}break;
			case KindStringRef:{
				size_t n = string->getLength();
				const u8* data = string->getData();
				::memcpy(output, data, n);
				output += n;
			}break;
			case KindConcat:{
				concat.left->writeToAndModify(output);
				concat.right->writeToAndModify(output);
			}break;			
			default:
				unreachable;
			break;
			}
		}

		Twine(const Twine& left, const Twine& right)
			: kind(KindConcat){
			concat.left = &left;
			concat.right = &right;
		}

		enum Kind{
			KindEmpty,
			KindCString,
			KindStringRef,
			KindConcat
		} kind;

		union{
			const char* c_string;
			const StringRef* string;

			struct{
				const Twine* left;
				const Twine* right;
			} concat;
		};

		friend Twine operator+(const Twine& lhs, const Twine& rhs);
	};
}