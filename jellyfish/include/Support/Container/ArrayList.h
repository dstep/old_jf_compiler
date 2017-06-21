#pragma once
#include "../MemoryAPI.h"
#include "../ArrayRef.h"

namespace jf{
	namespace container{
		template<class V>
		class ArrayList{
			static const size_t InitialMemoryAllocation = 8 * 1024;
			static const size_t SmallPoolSize = 8 > InitialMemoryAllocation / sizeof(V) ? 8 : InitialMemoryAllocation / sizeof(V);
			struct Chunk{
				Chunk* next;
				Chunk* prev;
				u8 buffer[sizeof(V) * SmallPoolSize];
			};
		public:
			ArrayList(MemoryPoolSlice* pool)
				: pool(pool)
				, chunkFill(0)
				, chunkSize(SmallPoolSize)
				, topChunk(&smallChunk){
				smallChunk.prev = nullptr;
				smallChunk.next = nullptr;
			}

			void push(const V& value){
				if ( chunkFill < chunkSize ){
					((V*)topChunk->buffer)[chunkFill] = value;
					chunkFill++;					
				}else{
					if ( !topChunk->next ){
						Chunk* nextChunk = (Chunk*)pool->allocateDynamic(sizeof(Chunk), (chunkSize * 2 - SmallPoolSize), sizeof(V));
						nextChunk->prev = topChunk;
						nextChunk->next = nullptr;
						topChunk->next = nextChunk;
						topChunk = nextChunk;
					}else{
						topChunk = topChunk->next;
					}
					((V*)topChunk->buffer)[0] = value;
					chunkSize <<= 1;
					chunkFill = 1;
				}
			}

			void set(size_t index, const V& value){
				size_t size = getSize();
				size_t chunkTop = chunkSize - SmallPoolSize;
				size_t currentChunkSize = chunkSize;
				Chunk* chunk = topChunk;
				while ( index < chunkTop ){
					currentChunkSize >>= 1;
					chunk = chunk->prev;
					chunkTop -= currentChunkSize;
				}
				((V*)chunk->buffer)[index - chunkTop] = value;
			}

			V& getLast(){
				return ((V*)topChunk->buffer)[chunkFill - 1];
			}

			V takeLast(){
				V v = ((V*)topChunk->buffer)[chunkFill - 1];
				pop();
				return v;
			}

			V& get(size_t index){
				size_t size = getSize();
				size_t chunkTop = chunkSize - SmallPoolSize;
				size_t currentChunkSize = chunkSize;
				Chunk* chunk = topChunk;
				while ( index < chunkTop ){
					currentChunkSize >>= 1;
					chunk = chunk->prev;
					chunkTop -= currentChunkSize;
				}
				return ((V*)chunk->buffer)[index - chunkTop];
			}

			const V& get(size_t index) const{
				size_t size = getSize();
				size_t chunkTop = chunkSize - SmallPoolSize;
				size_t currentChunkSize = chunkSize;
				Chunk* chunk = topChunk;
				while ( index < chunkTop ){
					currentChunkSize >>= 1;
					chunk = chunk->prev;
					chunkTop -= currentChunkSize;
				}
				return ((V*)chunk->buffer)[index - chunkTop];
			}

			void pop(){
				if ( chunkFill == 0 ){
					topChunk = topChunk->prev;
					chunkSize >>= 1;
					chunkFill = chunkSize;
				}else{
					chunkFill--;
				}
			}

			size_t getSize() const{
				return chunkSize - SmallPoolSize + chunkFill;
			}

			void clear(){
				while ( topChunk->prev ){
					topChunk = topChunk->prev;
					chunkSize >>= 1;
					chunkFill = chunkSize;
				}
				chunkFill = 0;
			}

			class Enumerator{
			private:
				Enumerator(ArrayList<V>* array, size_t from)
					: array(array){
					chunk = array->topChunk;
					chunkSize = array->chunkSize;
					while ( chunk->prev ){
						chunk = chunk->prev;
						chunkSize >>= 1;
					}
					index = from;
					while ( index >= chunkSize * 2 - SmallPoolSize ){
						chunk = chunk->next;
						chunkSize <<= 1;
					}
				}
			public:
				bool hasNext() const{
					return index < array->getSize();
				}

				void advance(){
					index++;
					if ( index >= chunkSize * 2 - SmallPoolSize ){
						chunk = chunk->next;
						chunkSize <<= 1;
					}
				}

				V& get() const{
					return ((V*)chunk->buffer)[index - chunkSize + SmallPoolSize];
				}

				size_t getIndex() const{
					return index;
				}
			private:
				ArrayList<V>* array;
				Chunk* chunk;
				size_t chunkSize;
				size_t index;		

				friend class ArrayList<V>;
			};

			Enumerator enumerate(size_t from = 0){
				return Enumerator(this, from);
			}

			ArrayRef<V> asFlatArray(MemoryPoolSlice* pool){
				if ( chunkSize == SmallPoolSize ){
					return ArrayRef<V>((V*)topChunk->buffer, chunkFill);
				}else{
					return slice(pool);
				}
			}

			ArrayRef<V> slice(MemoryPoolSlice* pool, size_t from = 0, size_t to = std::numeric_limits<size_t>::max()){
				size_t size = getSize();
				if ( from >= size ){
					return ArrayRef<V>();
				}				
				if ( to > size ){
					to = size;
				}
				if ( from >= to ){
					return ArrayRef<V>();
				}
				size = to - from;
				V* values = (V*)pool->allocateArray(sizeof(V), size);
				size_t count = 0;
				for ( auto e = enumerate(from); count < size; e.advance(), count++ ){
					values[e.getIndex() - from] = e.get();
				}
				return ArrayRef<V>(values, size);
			}
		protected:
			MemoryPoolSlice* pool;
						
			Chunk* topChunk;
			size_t chunkFill, chunkSize;
			Chunk smallChunk;
		};

		template<class V>
		ArrayList<V>* CreateArray(MemoryPoolSlice* pool){
			return new(pool->allocate(sizeof(ArrayList<V>)))ArrayList<V>(pool);
		}
	}	

	using container::ArrayList;
}