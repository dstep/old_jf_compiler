#pragma once
#include "../Types.h"
#include "../ArrayRef.h"

namespace jf{
	namespace container{
		template<class V, size_t Cap>
		class CappedArray{
		public:
			CappedArray()
				: size(0){
			}

			bool push(const V& value){
				if ( size < Cap ){
					((V*)buffer)[size++] = value;
					return true;
				}
				return false;
			}

			size_t getSize() const{
				return size;
			}

			V& get(size_t index){
				return ((V*)buffer)[index];
			}

			const V& get(size_t index) const{
				return ((V*)buffer)[index];
			}

			void clear(){
				size = 0;
			}

			operator ArrayRef<V>(){
				return ArrayRef<V>((V*)buffer, size);
			}
		private:
			size_t size;
			u8 buffer[Cap * sizeof(V)];
		};
	}
}