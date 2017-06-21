#pragma once

namespace jf{
	template<class A, class B>
	class Pair{
	public:
		Pair()
			: first()
			, second(){
		}

		Pair(const A& a, const B& b)
			: first(a)
			, second(b){			
		}

		bool operator==(const Pair<A,B>& other) const{
			return first == other.first && second == other.second;
		}

		A first;
		B second;
	};

	template<class A, class B>
	Pair<A,B> MakePair(const A& a, const B& b){
		return Pair<A,B>(a, b);
	}
}