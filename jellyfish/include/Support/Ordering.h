#pragma once

namespace jf{
	namespace Ordering{
		enum Value{
			Lt = -1,
			Eq = 0,
			Gt = 1
		};

		template<class T>
		Ordering::Value Compare(const T& left, const T& right){
			if ( left < right ){
				return Ordering::Lt;
			}else if ( left > right ){
				return Ordering::Gt;
			}else{
				return Ordering::Eq;
			}
		}
	}
}