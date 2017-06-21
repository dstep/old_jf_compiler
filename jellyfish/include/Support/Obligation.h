#pragma once

namespace jf{
	template<class FType>
	class Obligation{
	public:
		Obligation()
			: fun()
			, borrowed(true){
		}

		Obligation(const FType& fun)
			: fun(fun)
			, borrowed(false){
		}

		Obligation(Obligation<FType>&& other)
			: fun(other.fun)
			, borrowed(other.borrowed){
			other.borrowed = true;
		}

		~Obligation(){
			if ( !borrowed ){
				fun();
			}
		}

		const Obligation& operator=(Obligation<FType>&& other){
			if ( !borrowed ){
				fun();
			}
			fun = other.fun;
			borrowed = other.borrowed;
			other.borrowed = true;
			return *this;
		}
	private:
		Obligation(const Obligation<FType>& other);
		const Obligation& operator=(const Obligation<FType>& other);

		bool borrowed;
		FType fun;
	};

	template<class FType>
	Obligation<FType> createObligation(FType& fun){
		return Obligation<FType>(fun);
	}

	#define obligation(fn) auto obligation_##__LINE__##_##__COUNTER__ = createObligation(fn)
}