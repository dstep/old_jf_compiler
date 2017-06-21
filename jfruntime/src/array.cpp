#include <array.h>
#include <intrinsics.h>
#include <cstdlib>
#include <cstring>

JFAPI JFArray* __jf_empty_array(jfint valueSize, void* valueInfo){
	char* buffer = (char*)__jf_allocate_object(sizeof(JFArray) + valueSize * 4);
	JFArray* array = (JFArray*)buffer;
	array->data = (uint8_t*)(buffer + sizeof(JFArray));

	array->capacity = 4;
	array->size = 0;
	array->valueInfo = valueInfo;
	array->valueSize = valueSize;
	
	return array;
}

JFAPI void* __jf_array_ref(JFArray* array, jfint index){
	if ( (size_t)index >= array->size ){
		__jf_fatal_error("Array index out of bounds");
	}
	return array->data + array->valueSize * index;
}

JFAPI jfint __jf_array_size(JFArray* array){
	return array->size;
}

JFAPI void* __jf_array_push(JFArray* array){
	if ( array->size == array->capacity ){
		jfint bufferSize = array->capacity * array->valueSize;
		jfint newBufferSize = array->capacity * 2 * array->valueSize;
		if ( newBufferSize < bufferSize ){
			__jf_fatal_error("Array buffer size too large");
		}
		uint8_t* newData = (uint8_t*)__jf_allocate_region(newBufferSize);
		::memcpy(newData, array->data, bufferSize);
		array->capacity = array->capacity * 2;
	}
	array->size++;
	return array->data + array->valueSize * (array->size - 1);
}

JFAPI void __jf_array_pop(JFArray* array){
	array->size--;
}

JFAPI void __jf_array_clear(JFArray* array){
	array->size = 0;
}