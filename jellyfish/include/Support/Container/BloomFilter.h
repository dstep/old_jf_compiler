#pragma once
#include <cstdlib>
#include <Support/Types.h>

namespace jf{
	namespace container{
		static const u64 UniformAVariables[64] = {
				912520538894619633ULL,
				817652547277852424ULL,
				913802888549794629ULL,
				882027280580761601ULL,
				364206111585161388ULL,
				1035193545297804770ULL,
				1064933096850410844ULL,
				321534166725042042ULL,
				1031145698540824341ULL,
				545589131117807596ULL,
				963901473917674767ULL,
				160405433645531408ULL,
				447560430784911592ULL,
				404571782037539612ULL,
				726302182462452747ULL,
				363679497045833021ULL,
				704549439929684174ULL,
				485688483496165495ULL,
				333997817821978961ULL,
				991428448177359507ULL,
				1133268900742124731ULL,
				664415028394683352ULL,
				124052937000964619ULL,
				627382664035023533ULL,
				515331329772843026ULL,
				840646004692110812ULL,
				208568361588654142ULL,
				24096641423857715ULL,
				500803644009764737ULL,
				1134009114845650401ULL,
				542768064650908779ULL,
				1036328394895883405ULL,
				555438361325828386ULL,
				883825129758318865ULL,
				38371520871103393ULL,
				343410934912129919ULL,
				200474490978978044ULL,
				765030047901730162ULL,
				400449229915371137ULL,
				1144010063652991917ULL,
				454137310890432713ULL,
				37154981505823941ULL,
				363120879966493209ULL,
				643495876655370773ULL,
				899507432860239644ULL,
				1072483285126392051ULL,
				68992926303839133ULL,
				419779101383953966ULL,
				725103966684365525ULL,
				157652264060308768ULL,
				15806113207772881ULL,
				801811296439532599ULL,
				662981622618325989ULL,
				180764016040578068ULL,
				872256519005365408ULL,
				291495756664589130ULL,
				136204976917743870ULL,
				1057395182407830459ULL,
				773439714229282906ULL,
				275568467559843610ULL,
				134259505381805376ULL,
				290165638442093041ULL,
				1126891512037029804ULL,
				171991953850597242ULL
			};

		template<size_t BitSize, size_t HashFuncs>
		class BloomFilter{
		public:
			struct Hash{
				size_t hashes[HashFuncs];
			};

			BloomFilter(){
				::memset(mask, 0, WordsSize * sizeof(size_t));
			}

			BloomFilter(const BloomFilter& left, const BloomFilter& right){
				for ( size_t i = 0; i < WordsSize; i++ ){
					mask[i] = left.mask[i] | right.mask[i];
				}
			}

			bool has(const Hash& hash){
				for ( size_t i = 0; i < HashFuncs; i++ ){
					size_t bit = hash.hashes[i] % BitSize;
					size_t word = bit / (sizeof(size_t) * 8);
					size_t wordBit = bit % (sizeof(size_t) * 8);
					if ( !(mask[word] & (((size_t)1) << wordBit)) ){
						return false;
					}
				}
				return true;
			}

			void put(const Hash& hash){
				for ( size_t i = 0; i < HashFuncs; i++ ){
					size_t bit = hash.hashes[i] % BitSize;
					size_t word = bit / (sizeof(size_t) * 8);
					size_t wordBit = bit % (sizeof(size_t) * 8);
					mask[word] |= ((size_t)1) << wordBit;
				}
			}

			static Hash hash(const u8* bytes, size_t length){
				Hash hash;
				for ( size_t i = 0; i < HashFuncs; i++ ){
					hash.hashes[i] = hash::universal_hash(bytes, length, UniformAVariables[i]);
				}
				return hash;
			} 
		private:
			static const size_t WordsSize = (BitSize + sizeof(size_t) * 8 - 1) / (sizeof(size_t) * 8);
			size_t mask[WordsSize];
		};
	}

	using container::BloomFilter;
}