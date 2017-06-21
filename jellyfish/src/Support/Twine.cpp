#include <Support/Macros.h>
#include <Support/Twine.h>
#include <string>

namespace jf{
	size_t Twine::calculateLength() const{
		switch(kind){
		case KindEmpty: 
			return 0;
		break;
		case KindCString:
			return strlen(c_string);
		break;
		case KindStringRef:
			return string->getLength();
		break;
		case KindConcat: 
			return concat.left->calculateLength() + concat.right->calculateLength();
		break;
		default:
			unreachable;
		break;
		}
	}
	
	Twine operator+(const Twine& lhs, const Twine& rhs){
		if ( lhs.kind == Twine::KindEmpty ){
			return rhs;
		}else if ( rhs.kind == Twine::KindEmpty ){
			return lhs;
		}else{
			return Twine(lhs, rhs);
		}
	}
}