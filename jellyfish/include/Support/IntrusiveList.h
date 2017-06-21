#pragma once

namespace jf{	
	template<class T>
	struct List{
		T* first;
		T* last;

		List()
			: first(nullptr)
			, last(nullptr){
		}

		List(T* singleton)
			: first(singleton)
			, last(singleton){
		}

		List(T* first, T* last)
			: first(first)
			, last(last){
		}

		List<T> prepend(T* t){
			if ( first ){
				t->next = first;
				return List<T>(t, last);
			}else{
				return List<T>(t, t);
			}					
		}

		List<T> append(T* t){
			if ( last ){
				last->next = t;
				return List<T>(first, t);
			}else{
				return List<T>(t, t);
			}					
		}

		operator T*(){
			return first;
		}

		void clear(){
			first = last = nullptr;
		}
	};

	template<class T>
	size_t countList(T* t){
		size_t n = 0;
		while ( t ){
			n++;
			t = t->next;
		}
		return n;
	}

	#define iterate_list(name, value) for ( auto name = value; name; name = name->next )
}