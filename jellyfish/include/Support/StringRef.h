#pragma once

#include "Types.h"
#include "Ordering.h"
#include "ArrayRef.h"
#include "MemoryPool.h"
#include <cstring>

namespace jf{
	class StringRef{
	public:
		StringRef()
			: length(0)
			, data(nullptr){
		}

		StringRef(const char* str)
			: length(::strlen(str))
			, data((u8*)str){
		}

		template<size_t N>
		StringRef(const char (&str) [N])
			: length(N - 1)
			, data(str){		
		}

		StringRef(const ArrayRef<u8>& array)
			: length(array.getSize())
			, data(array.getRaw()){
		}

		StringRef(const u8* data, size_t length)
			: data(data)
			, length(length){
		}

		size_t getLength() const{
			return length;
		}

		const u8* getData() const{
			return data;
		}

		bool operator==(const StringRef& other) const{
			if ( length != other.length ){
				return false;
			}
			return ::memcmp(data, other.data,length) == 0;
		}

		bool isEmpty() const{
			return length == 0;
		}

		static Ordering::Value Compare(const StringRef& left, const StringRef& right){
			size_t length = left.length < right.length ? left.length : right.length;
			for ( size_t i = 0; i < length; i++ ){
				if ( left.data[i] < right.data[i] ){
					return Ordering::Lt;
				}else if ( left.data[i] > right.data[i] ){
					return Ordering::Gt;
				}
			}
			if ( left.length < right.length ){
				return Ordering::Lt;
			}else if ( left.length > right.length ){
				return Ordering::Gt;
			}
			return Ordering::Eq;
		}

		StringRef slice(MemoryPoolSlice* pool) const{
			u8* buffer = (u8*)pool->allocate(length);
			::memcpy(buffer, data, length);
			return StringRef(buffer, length);
		}
	private:
		size_t length;
		const u8* data;
	};
}