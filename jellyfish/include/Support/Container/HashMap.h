#pragma once
#include "../MemoryAPI.h"
#include "../Hash.h"
#include "../StringRef.h"
#include "../Pair.h"

namespace jf{
	namespace container{
		template<class T>
		bool default_cmp(const T& t1, const T& t2){
			return t1 == t2;
		}

		template<class T>
		hash_t default_hash(const T& t){
			return hash::bytes<sizeof(t)>((const u8*)&t);
		}

		template<class T>
		hash_t default_hash(T* const & t){
			return hash::pointer(t);
		}

		template<class T>
		hash_t hash_pointer(T* const & t){
			return hash::pointer(t);
		}

		inline hash_t hash_string(const StringRef& string){
			return hash::bytes(string.getData(), string.getLength());
		}

		template<class A, class B>
		hash_t default_hash(const Pair<A,B>& t){
			return hash::mix(default_hash(t.first), default_hash(t.second));
		}
		
		template<class K, class V, hash_t(*Hash)(const K&) = default_hash,  bool(*Cmp)(const K&, const K&) = default_cmp>
		class HashMap{
		private:
			#define INITIAL_SIZE 4
			#define PAIRS_PER_BUCKET 4
			#define GROW_FACTOR 2
			struct Pair{
				K key;
				V value;
			};
			struct Bucket{
				union{
					Bucket* next;
					size_t load;
				};
				Pair pairs[PAIRS_PER_BUCKET];
			};
		public:
			HashMap(MemoryPoolSlice* pool)
				: pool(pool)
				, size(0)
				, buckets((Bucket*)buffer)
				, bucketsCount(INITIAL_SIZE)
				, freeBuckets(nullptr){
				for ( size_t i = 0; i < bucketsCount; i++ ){
					buckets[i].load = 0;
				}
			}

			V& set(const K& key, const V& value){
				if ( size > PAIRS_PER_BUCKET * bucketsCount * GROW_FACTOR ){
					grow();
				}
				hash_t hash = Hash(key) % bucketsCount;
				Bucket* bucket = buckets + hash;
				while ( true ){
					if ( bucket->load > PAIRS_PER_BUCKET ){
						for ( size_t i = 0; i < PAIRS_PER_BUCKET; i++ ){
							if ( Cmp(bucket->pairs[i].key, key) ){
								bucket->pairs[i].value = value;
								return bucket->pairs[i].value;
							}
						}
						bucket = bucket->next;
					}else{
						for ( size_t i = 0; i < bucket->load; i++ ){
							if ( Cmp(bucket->pairs[i].key, key) ){
								bucket->pairs[i].value = value;
								return bucket->pairs[i].value;
							}
						}
						if ( bucket->load < PAIRS_PER_BUCKET ){
							size_t i = bucket->load;
							bucket->pairs[i].key = key;
							bucket->pairs[i].value = value;
							bucket->load++;
							size++;
							return bucket->pairs[i].value;
						}else{
							bucket->next = takeFreeBucket();
							bucket = bucket->next;
							bucket->load = 1;
							bucket->pairs[0].key = key;
							bucket->pairs[0].value = value;
							size++;
							return bucket->pairs[0].value;
						}
					}
				}
			}

			V& getOrInsert(const K& key){
				if ( size > PAIRS_PER_BUCKET * bucketsCount * GROW_FACTOR ){
					grow();
				}
				hash_t hash = Hash(key) % bucketsCount;
				Bucket* bucket = buckets + hash;
				while ( true ){
					if ( bucket->load > PAIRS_PER_BUCKET ){
						for ( size_t i = 0; i < PAIRS_PER_BUCKET; i++ ){
							if ( Cmp(bucket->pairs[i].key, key) ){
								return bucket->pairs[i].value;
							}
						}
						bucket = bucket->next;
					}else{
						for ( size_t i = 0; i < bucket->load; i++ ){
							if ( Cmp(bucket->pairs[i].key, key) ){
								return bucket->pairs[i].value;
							}
						}
						if ( bucket->load < PAIRS_PER_BUCKET ){
							size_t i = bucket->load;
							bucket->pairs[i].key = key;
							bucket->pairs[i].value = V();
							bucket->load++;
							size++;
							return bucket->pairs[i].value;
						}else{
							bucket->next = takeFreeBucket();
							bucket = bucket->next;
							bucket->load = 1;
							bucket->pairs[0].key = key;
							bucket->pairs[0].value = V();
							size++;
							return bucket->pairs[0].value;
						}
					}
				}
			}

			V get(const K& key){
				hash_t hash = Hash(key) % bucketsCount;
				Bucket* bucket = buckets + hash;
				while ( true ){
					if ( bucket->load > PAIRS_PER_BUCKET ){
						for ( size_t i = 0; i < PAIRS_PER_BUCKET; i++ ){
							if ( Cmp(bucket->pairs[i].key, key) ){
								return bucket->pairs[i].value;
							}
						}
						bucket = bucket->next;
					}else{
						for ( size_t i = 0; i < bucket->load; i++ ){
							if ( Cmp(bucket->pairs[i].key, key) ){
								return bucket->pairs[i].value;
							}
						}
						return V();
					}
				}
			}
						
			bool has(const K& key){
				hash_t hash = Hash(key) % bucketsCount;
				Bucket* bucket = buckets + hash;
				while ( true ){
					if ( bucket->load > PAIRS_PER_BUCKET ){
						for ( size_t i = 0; i < PAIRS_PER_BUCKET; i++ ){
							if ( Cmp(bucket->pairs[i].key, key) ){
								return true;
							}
						}
						bucket = bucket->next;
					}else{
						for ( size_t i = 0; i < bucket->load; i++ ){
							if ( Cmp(bucket->pairs[i].key, key) ){
								return true;
							}
						}
						return false;
					}
				}
			}

			size_t getSize(){
				return size;
			}

			class Enumerator{
			public:
				Enumerator(HashMap<K,V,Hash,Cmp>* map)
					: map(map)
					, globalIndex(0)
					, pairIndex(0){
					if ( map->size == 0 ){
						current = nullptr;
						globalIndex = map->bucketsCount;
					}else{
						current = nullptr;
						currentBucket = map->buckets;
						current = &currentBucket->pairs[pairIndex];
						if ( !currentBucket->load ){
							advance();
						}
					}
				}

				bool hasNext() const{
					return globalIndex < map->bucketsCount;
				}

				void advance(){					
					pairIndex++;
					if ( pairIndex >= currentBucket->load ){
						pairIndex = 0;
						globalIndex++;
						for ( ; globalIndex < map->bucketsCount && map->buckets[globalIndex].load == 0; globalIndex++ ){
						}
						currentBucket = &map->buckets[globalIndex];
					}else if ( pairIndex >= 4 ){
						pairIndex = 0;
						currentBucket = currentBucket->next;
					}
					current = &currentBucket->pairs[pairIndex];
				}

				const K& getKey(){
					return current->key;
				}

				V& getValue(){
					return current->value;
				}
			private:
				HashMap<K,V,Hash,Cmp>* map;
				Pair* current;
				Bucket* currentBucket;
				size_t pairIndex;
				size_t globalIndex;
			};

			Enumerator enumerate(){
				return Enumerator(this);
			}

			void clear(){
				for ( size_t i = 0; i < bucketsCount; i++ ){
					if ( buckets[i].load > 4 ){
						recursivelyFreeBuckets(buckets[i].next);
					}
					buckets[i].load = 0;
				}
			}
		private:
			void insert(Bucket* bucket, Pair& pair){
				while ( true ){
					if ( bucket->load < PAIRS_PER_BUCKET ){
						size_t i = bucket->load;
						bucket->pairs[i] = pair;
						bucket->load++;
						return;
					}else if ( bucket->load == PAIRS_PER_BUCKET ){
						bucket->next = takeFreeBucket();
						bucket = bucket->next;
						bucket->load = 1;
						bucket->pairs[0] = pair;
						return;
					}else{
						bucket = bucket->next;
					}
				}
			}

			void recursivelyFreeBuckets(Bucket* bucket){
				if ( bucket->load > 4 ){
					recursivelyFreeBuckets(bucket->next);
				}
				putFreeBucket(bucket);
			}

			void grow(){
				size_t newBucketsCount = bucketsCount * 2;
				Bucket* newBuckets = (Bucket*)pool->allocateArray(sizeof(Bucket), newBucketsCount);
				for ( size_t i = 0; i < newBucketsCount; i++ ){
					newBuckets[i].load = 0;
				}
				for ( size_t i = 0; i < bucketsCount; i++ ){
					Bucket* bucket = buckets + i;
					while ( true ){
						if ( bucket->load > PAIRS_PER_BUCKET ){
							for ( size_t i = 0; i < PAIRS_PER_BUCKET; i++ ){
								hash_t hash = Hash(bucket->pairs[i].key) % newBucketsCount;
								insert(newBuckets + hash, bucket->pairs[i]);
							}
							Bucket* old = bucket;
							bucket = bucket->next;
							putFreeBucket(old);
						}else{
							for ( size_t i = 0; i < bucket->load; i++ ){
								hash_t hash = Hash(bucket->pairs[i].key) % newBucketsCount;
								insert(newBuckets + hash, bucket->pairs[i]);
							}
							putFreeBucket(bucket);
							break;
						}
					}
				}
				buckets = newBuckets;
				bucketsCount = newBucketsCount;
			}

			void putFreeBucket(Bucket* bucket){
				bucket->next = freeBuckets;
				freeBuckets = bucket;
			}

			Bucket* takeFreeBucket(){
				if ( !freeBuckets ){
					return (Bucket*)pool->allocate(sizeof(Bucket));
				}else{
					Bucket* bucket = freeBuckets;
					freeBuckets = freeBuckets->next;
					return bucket;
				}
			}

			MemoryPoolSlice* pool;
			size_t size;
				
			size_t bucketsCount;
			Bucket* buckets;	
			Bucket* freeBuckets;

			u8 buffer[sizeof(Bucket) * INITIAL_SIZE];
		};

		template<class V>
		class StringMap: public HashMap< StringRef, V, hash_string, default_cmp<StringRef> >{
		public:
			StringMap(MemoryPoolSlice* pool)
				: HashMap(pool){
			}
		};

		template<class K, class V>
		class PtrHash: public HashMap< K*, V, hash_pointer<K>, default_cmp<K*> >{
		public:
			PtrHash(MemoryPoolSlice* pool)
				: HashMap(pool){
			}
		};
	}

	

	using container::HashMap;
	using container::StringMap;
	using container::PtrHash;
}