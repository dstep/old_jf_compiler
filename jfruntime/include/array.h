#include "runtime.h"

struct JFArray{
	void* objheader;
	void* valueInfo;
	jfint valueSize;
	jfint capacity;
	jfint size;
	uint8_t* data;
};

JFAPI JFArray* __jf_empty_array(jfint valueSize, void* valueInfo);

JFAPI void* __jf_array_ref(JFArray* array, jfint index);
JFAPI jfint __jf_array_size(JFArray* array);
JFAPI void* __jf_array_push(JFArray* array);
JFAPI void __jf_array_pop(JFArray* array);
JFAPI void __jf_array_clear(JFArray* array);