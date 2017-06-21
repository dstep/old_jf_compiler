#pragma once
#include "Types.h"

namespace jf{
	typedef u32 hash_t;

	namespace hash{
		inline hash_t mix(hash_t b, hash_t c){
			hash_t a = 0xd3af7e37u;
			a=a-b;  a=a-c;  a=a^(c >> 13);
			b=b-c;  b=b-a;  b=b^(a << 8);
			c=c-a;  c=c-b;  c=c^(b >> 13);
			a=a-b;  a=a-c;  a=a^(c >> 12);
			b=b-c;  b=b-a;  b=b^(a << 16);
			c=c-a;  c=c-b;  c=c^(b >> 5);
			a=a-b;  a=a-c;  a=a^(c >> 3);
			b=b-c;  b=b-a;  b=b^(a << 10);
			c=c-a;  c=c-b;  c=c^(b >> 15);
			return c;
		}

		template<size_t length>
		hash_t bytes(const u8* bytes){
		#if defined(USE_JENKINS_HASH)
			hash_t hash, i;
			for(hash = i = 0; i < length; ++i)
			{
				hash += bytes[i];
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}
			hash += (hash << 3);
			hash ^= (hash >> 11);
			hash += (hash << 15);
			return hash;
		#else
			static const uint32_t c1 = 0xcc9e2d51;
			static const uint32_t c2 = 0x1b873593;
			static const uint32_t r1 = 15;
			static const uint32_t r2 = 13;
			static const uint32_t m = 5;
			static const uint32_t n = 0xe6546b64;
 
			uint32_t hash = 0xd3af7e37u;
 
			const int nblocks = length / 4;
			const uint32_t *blocks = (const uint32_t *)bytes;
			int i;
			for (i = 0; i < nblocks; i++) {
				uint32_t k = blocks[i];
				k *= c1;
				k = (k << r1) | (k >> (32 - r1));
				k *= c2;
 
				hash ^= k;
				hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
			}
 
			const uint8_t *tail = (const uint8_t *) (bytes + nblocks * 4);
			uint32_t k1 = 0;
 
			switch (length & 3) {
			case 3:
				k1 ^= tail[2] << 16;
			case 2:
				k1 ^= tail[1] << 8;
			case 1:
				k1 ^= tail[0];
 
				k1 *= c1;
				k1 = (k1 << r1) | (k1 >> (32 - r1));
				k1 *= c2;
				hash ^= k1;
			}
 
			hash ^= length;
			hash ^= (hash >> 16);
			hash *= 0x85ebca6b;
			hash ^= (hash >> 13);
			hash *= 0xc2b2ae35;
			hash ^= (hash >> 16);
 
			return hash;
	#endif
		}

		inline
		hash_t bytes(const u8* bytes, size_t length){
		#if defined(USE_JENKINS_HASH)
			hash_t hash, i;
			for(hash = i = 0; i < length; ++i)
			{
				hash += bytes[i];
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}
			hash += (hash << 3);
			hash ^= (hash >> 11);
			hash += (hash << 15);
			return hash;
		#else
			static const uint32_t c1 = 0xcc9e2d51;
			static const uint32_t c2 = 0x1b873593;
			static const uint32_t r1 = 15;
			static const uint32_t r2 = 13;
			static const uint32_t m = 5;
			static const uint32_t n = 0xe6546b64;
 
			uint32_t hash = 0xd3af7e37u;
 
			const size_t nblocks = length / 4;
			const uint32_t *blocks = (const uint32_t *)bytes;
			int i;
			for (i = 0; i < nblocks; i++) {
				uint32_t k = blocks[i];
				k *= c1;
				k = (k << r1) | (k >> (32 - r1));
				k *= c2;
 
				hash ^= k;
				hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
			}
 
			const uint8_t *tail = (const uint8_t *) (bytes + nblocks * 4);
			uint32_t k1 = 0;
 
			switch (length & 3) {
			case 3:
				k1 ^= tail[2] << 16;
			case 2:
				k1 ^= tail[1] << 8;
			case 1:
				k1 ^= tail[0];
 
				k1 *= c1;
				k1 = (k1 << r1) | (k1 >> (32 - r1));
				k1 *= c2;
				hash ^= k1;
			}
 
			hash ^= length;
			hash ^= (hash >> 16);
			hash *= 0x85ebca6b;
			hash ^= (hash >> 13);
			hash *= 0xc2b2ae35;
			hash ^= (hash >> 16);
 
			return hash;
	#endif
		}
		
		inline hash_t universal_hash(const u8* bytes, size_t length, u64 a){
			const u64 LargeMesennePrime = (1ULL << 61ULL) - 1;
			u64 h = (0x1b873593ULL * a) & LargeMesennePrime;
			for ( size_t i = 0; i < length; i++ ){
				h = (h * a + bytes[i]) & LargeMesennePrime;
			}
			return (hash_t)h;
		}

		inline hash_t pointer(const void* ptr){
		#if defined(JF_POINTER_32BIT)
			hash_t a = (hash_t)ptr;
			a = (a+0x7ed55d16) + (a<<12);
			a = (a^0xc761c23c) ^ (a>>19);
			a = (a+0x165667b1) + (a<<5);
			a = (a+0xd3a2646c) ^ (a<<9);
			a = (a+0xfd7046c5) + (a<<3);
			a = (a^0xb55a4f09) ^ (a>>16);
			return a;
		#elif defined(JF_POINTER_64BIT)
			u64 key = (u64)ptr;
			key = (~key) + (key << 18); // key = (key << 18) - key - 1;
			key = key ^ (key >> 31);
			key = key * 21; // key = (key + (key << 2)) + (key << 4);
			key = key ^ (key >> 11);
			key = key + (key << 6);
			key = key ^ (key >> 22);
			return (hash_t)key;
		#else
			return bytes(&ptr, sizeof(ptr));
		#endif
		}
	}
}