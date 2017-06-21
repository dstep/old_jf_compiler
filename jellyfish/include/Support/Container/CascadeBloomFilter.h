#pragma once
#include <Support/ArrayRef.h>
#include <Support/MemoryPool.h>

namespace jf{
	namespace container{
		template<class BloomFilter, class T>
		class CascadeBloomFilter{
		public:
			template<class V, class BloomFilterConstructor, class BloomElementExtractor>
			CascadeBloomFilter(const ArrayRef<V>& elements, const BloomFilterConstructor& constructor, const BloomElementExtractor& extractor, MemoryPoolSlice* pool){
				root = makeNode<V, BloomFilterConstructor, BloomElementExtractor>(elements, constructor, extractor, pool);
			}

			template<class Func>
			void visitElements(const typename BloomFilter::Hash& hash, Func& func){
				visitElements(root, hash, func);
			}
		private:
			struct BloomFilterNode;

			template<class V, class BloomFilterConstructor, class BloomElementExtractor>
			BloomFilterNode* makeNode(const ArrayRef<V>& elements, const BloomFilterConstructor& constructor, const BloomElementExtractor& extractor, MemoryPoolSlice* pool){
				if ( elements.getSize() == 0 ){
					return nullptr;
				}else if ( elements.getSize() == 1 ){
					BloomFilterNode* node = (BloomFilterNode*)pool->allocate(sizeof(BloomFilterNode));
					constructor(&node->filter, elements.get(0));
					node->leaf = true;
					node->element = extractor(elements.get(0));
					return node;
				}else{
					size_t i = elements.getSize() / 2;
					BloomFilterNode* node = (BloomFilterNode*)pool->allocate(sizeof(BloomFilterNode));
					node->child.left = makeNode(elements.slice(0, i), constructor, extractor, pool);
					node->child.right = makeNode(elements.slice(i, elements.getSize()), constructor, extractor, pool);
					new(&node->filter)BloomFilter(node->child.left->filter, node->child.right->filter);
					node->leaf = false;
					return node;
				}
			}

			template<class Func>
			void visitElements(BloomFilterNode* node, const typename BloomFilter::Hash& hash, Func& func){
				if ( !node ){
					return;
				}
				if ( node->filter.has(hash) ){
					if ( node->leaf ){
						func(node->element);
					}else{
						visitElements(node->child.left, hash, func);
						visitElements(node->child.right, hash, func); 
					}
				}
			}

			struct BloomFilterNode{
				BloomFilter filter;				
				union{
					T element;
					struct{
						BloomFilterNode* left;
						BloomFilterNode* right;
					} child;
				};
				bool leaf;
			};
			BloomFilterNode* root;
		};
	}

	using container::CascadeBloomFilter;
}