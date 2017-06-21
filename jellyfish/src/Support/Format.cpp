#include <Support/Format.h>

namespace jf{
	namespace format{
		integer::integer(u32 value){
			//TODO:: fix
			sprintf(buffer, "%d", value);
		}

		integer::operator StringRef(){
			return StringRef(buffer);
		}

		real::real(double value){
			if ( _snprintf(buffer, sizeof(buffer), "%lf", value) <= 0 ){
				buffer[0] = '\0';
			}
		}

		real::operator StringRef(){
			return StringRef(buffer);
		}
	}
}