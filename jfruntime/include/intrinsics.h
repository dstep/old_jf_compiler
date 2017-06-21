#include "runtime.h"
#include <new>

JFAPI void __jf_string_concat(jfstring retdata, jfstring s1, jfstring s2);
JFAPI bool __jf_string_equal(jfstring a, jfstring b);

JFAPI float __jf_float_round(float);
JFAPI double __jf_double_round(double);

JFAPI float __jf_float_ceil(float);
JFAPI double __jf_double_ceil(double);

JFAPI float __jf_float_floor(float);
JFAPI double __jf_double_floor(double);

JFAPI float __jf_int_nearby_float(jfint);
JFAPI float __jf_double_nearby_float(double);
JFAPI jfint __jf_float_nearby_int(float);
JFAPI jfint __jf_double_nearby_int(double);

JFAPI float __jf_float_sqrt(float);
JFAPI double __jf_double_sqrt(double);

JFAPI void* __jf_allocate_object(jfint size);
JFAPI void* __jf_allocate_region(jfint size);

struct JFObligation{
	void* header;
	void* object;
	void (jfcc* func) (void* object);

	JFObligation(void* object, void (jfcc* func) (void*))
		: func(func)
		, object(object)
		, header(nullptr){
	}
};

template<class T>
struct JFFinalizer: public JFObligation{
	JFFinalizer(T* object)
		: JFObligation(object, (void (jfcc*) (void* object))T::Finalize){
	}
};

JFAPI JFObligation* __jf_allocate_obligation();

JFAPI void __jf_unwind_constructor_stack(void* closure, void* object);

JFAPI void __jf_fatal_error(const char* message);
JFAPI void __jf_warning(const char* message);

JFAPI void* __jf_allocate_bytes(jfint size);
JFAPI void __jf_write_float(jfint size, void* buffer, jfint offset, float value);
JFAPI void __jf_write_u16(jfint size, void* buffer, jfint offset, jfint value);

#define jfnew(t) new(__jf_allocate_object(sizeof(t)))t

#define jfnewfinalizer(t) new(__jf_allocate_obligation())JFFinalizer<t>