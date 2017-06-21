#pragma once
#include "MemoryAPI.h"

namespace jf{
	template<class V>
	class ArrayRef{
	public:
		explicit ArrayRef()
			: size(0){
		}

		ArrayRef(const V& value)
			: size(1)
			, values((V*)&value){
		}

		ArrayRef(V* values, size_t size)
			: values(values)
			, size(size){
		}

		template<size_t N>
		ArrayRef(V (&elts) [N])
			: values(elts)
			, size(N){
		}

		V& get(size_t index) const{
			return values[index];
		}

		V& operator[](size_t index) const{
			return values[index];
		}

		size_t getSize() const{
			return size;
		}

		V* getRaw() const{
			return values;
		}

		ArrayRef<V> copy(MemoryPoolSlice* pool) const{
			if ( size <= 0 ){
				return *this;
			}
			V* copy = (V*)pool->allocateArray(sizeof(V), size);
			::memcpy(copy, values, sizeof(V) * size);
			return ArrayRef<V>(copy, size);
		}

		ArrayRef<V> slice(size_t begin, size_t end = std::numeric_limits<size_t>::max()) const{
			if ( end > size ){
				end = size;
			}
			if ( begin > end ){
				begin = end;
			}
			return ArrayRef<V>(values + begin, end - begin);
		}

		struct Enumerator{
		public:
			Enumerator(V* values, size_t size)
				: values(values)
				, size(size)
				, i(0){
			}

			bool hasMore(){
				return i < size;
			}

			void advance(){
				i++;
			}

			size_t getIndex(){
				return i;
			}

			V& get(){
				return values[i];
			}
		private:
			size_t i;
			size_t size;
			V* values; 
		};

		Enumerator enumerate() const{
			return Enumerator(values, size);
		}
	protected:
		size_t size;
		V* values; 
	};

	template<class T>
	ArrayRef<T> MakeArrayRef(T* data, size_t size){
		return ArrayRef<T>(data, size);
	}
	
	#define iterate_array(name, array) for ( auto name = (array).enumerate(); name.hasMore(); name.advance() )
}