#pragma once
#include "../Ordering.h"
#include "../MemoryPool.h"
#include "../Macros.h"

namespace jf{
	#define FROZEN_NODE_BIT 0x8000U
	namespace container{
		template<class K, class V, Ordering::Value(*Ord)(const K&, const K&)>
		class SearchTree{
			struct Node{
				K key;
				short height;
				unsigned short size;
				V value;				
				Node* left;
				Node* right;				
			};

			Node* root;

			force_inline 
			Node* makeNodeWriteable(MemoryPoolSlice* pool, Node* node){
				if ( node->height & FROZEN_NODE_BIT ){
					Node* copy = (Node*)pool->allocate(sizeof(Node));
					*copy = *node;
					copy->height &= ~FROZEN_NODE_BIT;
					return copy;
				}else{
					return node;
				}
			}

			force_inline
			int getNodeHeight(Node* node){
				return node ? (node->height & ~FROZEN_NODE_BIT) + 1 : 0;
			}

			force_inline
			void updateNodeHeight(Node* node){
				int heightLeft = getNodeHeight(node->left);
				int heightRight = getNodeHeight(node->right);
				node->height = heightLeft > heightRight ? heightLeft : heightRight;
			}

			force_inline
			int getNodeBalance(Node* node){
				return getNodeHeight(node->left) - getNodeHeight(node->right);
			}

			force_inline
			Node* rotateLeft(MemoryPoolSlice* pool, Node* node){
				Node* child = node->left;
				Node* alpha = child->left;
				Node* beta = child->right;
				Node* gamma = node->right;
				Node* new_child = makeNodeWriteable(pool, node);
				new_child->left = beta;
				new_child->right = gamma;
				updateNodeHeight(new_child);
				node = makeNodeWriteable(pool, child);
				node->left = alpha;
				node->right = new_child;
				updateNodeHeight(node);
				return node;
			}

			force_inline
			Node* rotateRight(MemoryPoolSlice* pool, Node* node){
				Node* alpha = node->left;
				Node* child = node->right;
				Node* beta = child->left;
				Node* gamma = child->right;
				Node* new_child = makeNodeWriteable(pool, node);
				new_child->left = alpha;
				new_child->right = beta;
				updateNodeHeight(new_child);
				node = makeNodeWriteable(pool, child);
				node->left = new_child;
				node->right = gamma;
				updateNodeHeight(node);
				return node;
			}

			Node* extractRightmost(Node* node, MemoryPoolSlice* pool, Node** rightmost){
				if ( node->right ){
					node = makeNodeWriteable(pool, node);
					node->right = extractRightmost(node->right, pool, rightmost);
					updateNodeHeight(node);
					if ( getNodeBalance(node) > 1 ){
						if ( getNodeBalance(node->left) < 0 ){
							node->left = rotateRight(pool, node->left);
							updateNodeHeight(node);
						}
						node = rotateLeft(pool, node);
					}
					return node;
				}else{
					*rightmost = node;
					return node->left;
				}
			}

			Node* remove(Node* node, MemoryPoolSlice* pool, const K& key){
				if ( !node ){
					return nullptr;
				}else{
					Ordering::Value ord = Ord(key, node->key);
					if ( ord == Ordering::Lt ){
						Node* left = remove(node->left, pool, key);
						node = makeNodeWriteable(pool, node);
						node->left = left;
						updateNodeHeight(node);
						if ( getNodeBalance(node) < -1 ){
							if ( getNodeBalance(node->right) > 0 ){
								node->right = rotateLeft(pool, node->right);
								updateNodeHeight(node);
							}
							node = rotateRight(pool, node);
						}
						return node;
					}else if ( ord == Ordering::Gt ){
						Node* right = remove(node->right, pool, key);
						node = makeNodeWriteable(pool, node);
						node->right = right;
						updateNodeHeight(node);
						if ( getNodeBalance(node) > 1 ){
							if ( getNodeBalance(node->left) < 0 ){
								node->left = rotateRight(pool, node->left);
								updateNodeHeight(node);
							}
							node = rotateLeft(pool, node);
						}
						return node;
					}else{
						if ( node->left && node->right ){
							Node* rightmostLeft;
							Node* left = extractRightmost(node->left, pool, &rightmostLeft);
							Node* right = node->right;
							node = makeNodeWriteable(pool, rightmostLeft);
							node->left = left;
							node->right = right;
							updateNodeHeight(node);
							if ( getNodeBalance(node) < -1 ){
								if ( getNodeBalance(node->right) > 0 ){
									node->right = rotateLeft(pool, node->right);
									updateNodeHeight(node);
								}
								node = rotateRight(pool, node);
							}
							return node;
						}else if ( node->left ){
							return node->left;
						}else{
							return node->right;
						}
					}
				}
			}

			Node* insert(Node* node, MemoryPoolSlice* pool, const K& key, const V& v){
				if ( !node ){
					node = (Node*)pool->allocate(sizeof(Node));
					node->key = key;
					node->value = v;
					node->height = 0;
					node->left = nullptr;
					node->right = nullptr;
					return node;
				}else{
					Ordering::Value ord = Ord(key, node->key);
					if ( ord == Ordering::Lt ){
						Node* left = insert(node->left, pool, key, v);
						node = makeNodeWriteable(pool, node);
						node->left = left;
						updateNodeHeight(node);
						if ( getNodeBalance(node) > 1 ){
							if ( getNodeBalance(node->left) < 0 ){
								node->left = rotateRight(pool, node->left);
								updateNodeHeight(node);
							}
							node = rotateLeft(pool, node);
						}
						return node;
					}else if ( ord == Ordering::Gt ){
						Node* right = insert(node->right, pool, key, v);
						node = makeNodeWriteable(pool, node);
						node->right = right;
						updateNodeHeight(node);
						if ( getNodeBalance(node) < -1 ){
							if ( getNodeBalance(node->right) > 0 ){
								node->right = rotateLeft(pool, node->right);
								updateNodeHeight(node);
							}
							node = rotateRight(pool, node);
						}
						return node;
					}else{
						node = makeNodeWriteable(pool, node);
						node->value = v;
						return node;
					}
				}
			}

			void freeze(Node* node){
				if ( node ){
					if ( !(node->height & FROZEN_NODE_BIT) ){
						node->height |= FROZEN_NODE_BIT;
						freeze(node->left);
						freeze(node->right);
						node->size = (unsigned short)(calculateSize(node->left) + calculateSize(node->right) + 1);
					}
				}
			}

			Node* replace(MemoryPoolSlice* pool, const K& key, const V& value, Node* node){
				Ordering::Value ord = Ord(key, node->key);
				if ( ord == Ordering::Lt ){
					node = makeNodeWriteable(pool, node);
					node->left = replace(pool, key, value, node->left);
				}else if ( ord == Ordering::Gt ){
					node = makeNodeWriteable(pool, node);
					node->right = replace(pool, key, value, node->right);
				}else{
					node = makeNodeWriteable(pool, node);
					node->key = key;
					node->value = value;
				}

				return node;
			}

			size_t calculateSize(Node* node) const{
				if ( !node ){
					return 0;
				}
				if ( node->height & FROZEN_NODE_BIT ){
					return node->size;
				}
				return 1 + calculateSize(node->left) + calculateSize(node->right);
			}
			
			template<class Visitor>
			void traverseInorder(Node* node, Visitor& visitor) const{
				if ( node ){
					traverseInorder(node->left, visitor);
					visitor(node->key, node->value);
					traverseInorder(node->right, visitor);
				}
			}

		public:
			SearchTree()
				: root(nullptr){
			}

			bool isEmpty() const{
				return !root;
			}

			void freeze(){
				freeze(root);
			}

			void add(MemoryPoolSlice* pool, const K& key, const V& v){
				root = insert(root, pool, key, v);
			}

			void addOrReplace(MemoryPoolSlice* pool, const K& key, const V& v){
				if ( !has(key) ){
					add(pool, key, v);
				}else{
					replace(pool, key, v);
				}
			}

			void remove(MemoryPoolSlice* pool, const K& key){
				root = remove(root, pool, key);
			}

			size_t calculateSize() const{
				return calculateSize(root);
			}

			template<class Visitor>
			void traverseInorder(Visitor& visitor) const{
				traverseInorder(root, visitor);
			}

			bool has(const K& key){
				Node* node = root;
				while ( node ){
					Ordering::Value ord = Ord(key, node->key);
					if ( ord == Ordering::Eq ){
						return true;
					}else if ( ord == Ordering::Lt ){
						node = node->left;
					}else{
						node = node->right;
					}
				}
				return false;
			}

			V find(const K& key) const{
				Node* node = root;
				while ( node ){
					Ordering::Value ord = Ord(key, node->key);
					if ( ord == Ordering::Eq ){
						return node->value;
					}else if ( ord == Ordering::Lt ){
						node = node->left;
					}else{
						node = node->right;
					}
				}
				return V();
			}

			void replace(MemoryPoolSlice* pool, const K& key, const V& value){
				root = replace(pool, key, value, root);
			}

			V& getOrInsert(MemoryPoolSlice* pool, const K& key){
				Node* node = root;
				while ( node ){
					Ordering::Value ord = Ord(key, node->key);
					if ( ord == Ordering::Eq ){
						return node->value;
					}else if ( ord == Ordering::Lt ){
						node = node->left;
					}else{
						node = node->right;
					}
				}
				root = insert(root, pool, key, V());
				node = root;
				while ( node ){
					Ordering::Value ord = Ord(key, node->key);
					if ( ord == Ordering::Eq ){
						return node->value;
					}else if ( ord == Ordering::Lt ){
						node = node->left;
					}else{
						node = node->right;
					}
				}
				unreachable;
			}
		};
	}

	using container::SearchTree;
	#undef FROZEN_NODE_BIT
}