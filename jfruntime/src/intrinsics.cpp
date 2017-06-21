#include "intrinsics.h"
#include <math.h>
#include <cstdlib>
#include <cstdio>

JFAPI void __jf_string_concat(jfstring retdata, jfstring s1, jfstring s2){
	uint32_t size1;
	uint32_t size2;
	uint8_t* data1;
	uint8_t* data2;

	if ( s1->bytes[0] < 128 ){
		if ( s2->bytes[0] < 128 ){
			size1 = s1->bytes[0];
			size2 = s2->bytes[0];			
			uint32_t size = size1 + size2;			
			if ( size <= 15 ){
				*retdata = *s1;
				retdata->bytes[0] = (uint8_t)size;
				::memcpy(retdata->bytes + size1 + 1, s2->bytes + 1, size2);
			}else{
				retdata->part.size = (uint32_t)size;
				retdata->part.hi[0] = 0x80;
				uint8_t* buffer = (uint8_t*)__jf_allocate_bytes(size);
				retdata->part.ptr = (uint64_t)buffer;
				::memcpy(buffer, s1->bytes + 1, size1);
				::memcpy(buffer + size1, s2->bytes + 1, size2);
			}
			return;
		}else{
			size1 = s1->bytes[0];
			size2 = s2->part.size;
			data1 = s1->bytes + 1;
			data2 = (uint8_t*)s2->part.ptr;
		}
	}else{
		if ( s2->bytes[0] < 128 ){
			size1 = s1->part.size;
			size2 = s2->bytes[0];
			data1 = (uint8_t*)s1->part.ptr;
			data2 = s2->bytes + 1;
		}else{
			size1 = s1->part.size;
			size2 = s2->part.size;
			data1 = (uint8_t*)s1->part.ptr;
			data2 = (uint8_t*)s2->part.ptr;
		}
	}

	if ( size1 + size2 < size1 ){
		__jf_fatal_error("too large string allocated");
	}
	uint32_t size = size1 + size2;
	retdata->part.size = size;
	retdata->part.hi[0] = 0x80;
	uint8_t* buffer = (uint8_t*)__jf_allocate_bytes(size);
	retdata->part.ptr = (uint64_t)buffer;
	::memcpy(buffer, data1, size1);
	::memcpy(buffer + size1, data2, size2);
}

JFAPI bool __jf_string_equal(jfstring s1, jfstring s2){
	uint32_t size1;
	uint32_t size2;
	uint8_t* data1;
	uint8_t* data2;
	if ( s1->bytes[0] < 128 ){
		size1 = s1->bytes[0];
		data1 = s1->bytes + 1;
	}else{
		size1 = s1->part.size;
		data1 = (uint8_t*)s1->part.ptr;
	}
	if ( s2->bytes[0] < 128 ){
		size2 = s2->bytes[0];
		data2 = s2->bytes + 1;
	}else{
		size2 = s2->part.size;
		data2 = (uint8_t*)s2->part.ptr;
	}
	if ( size1 != size2 ){
		return false;
	}
	return !::memcmp(data1, data2, size1);
}

JFAPI float __jf_float_round(float value){
	return ::floorf(value + 0.5f);
}

JFAPI double __jf_double_round(double value){
	return ::floor(value + 0.5);
}

JFAPI float __jf_float_ceil(float value){
	return ::ceilf(value);
}

JFAPI double __jf_double_ceil(double value){
	return ::ceil(value);
}

JFAPI float __jf_float_floor(float value){
	return ::floorf(value);
}

JFAPI double __jf_double_floor(double value){
	return ::floor(value);
}

JFAPI float __jf_int_nearby_float(jfint value){
	return (float)value;
}

JFAPI float __jf_double_nearby_float(double value){
	return (float)value;
}

JFAPI jfint __jf_float_nearby_int(float value){
	return (jfint)__jf_float_round(value);
}

JFAPI jfint __jf_double_nearby_int(double value){
	return (jfint)__jf_double_round(value);
}

JFAPI void* __jf_allocate_object(jfint size){
	return malloc(size);
}

JFAPI void* __jf_allocate_region(jfint size){
	return malloc(size);
}

JFAPI float __jf_float_sqrt(float value){
	return sqrt(value);
}

JFAPI double __jf_double_sqrt(double value){
	return sqrt(value);
}

struct ConstructorClosure{
	ConstructorClosure* next;
	void(_fastcall *func)(void* env);
	void* env;
};

JFAPI void __jf_unwind_constructor_stack(void* _closure, void* object){
	ConstructorClosure* closure = (ConstructorClosure*)_closure;
	while ( closure ){
		closure->func(closure->env);
		closure = closure->next;
	}
}

JFAPI void* __jf_allocate_bytes(jfint size){
	if ( size < 0 ){
		__jf_fatal_error("trying to allocate bytes object of negative size");	
	}
	if ( size == 0 ){
		return nullptr;
	}
	return malloc(size);
}

JFAPI void __jf_write_float(jfint _size, void* buffer, jfint _offset, float value){
	if ( _offset < 0 ){
		__jf_fatal_error("negative offset in writeFloat");	
	}
	size_t size = _size;
	size_t offset = _offset;
	if ( offset >= size || size - offset < 4 ){
		__jf_fatal_error("writeFloat: out of bounds");	
	}
	::memcpy(((uint8_t*)buffer) + offset, &value, sizeof(value));
}

JFAPI void __jf_write_u16(jfint _size, void* buffer, jfint _offset, jfint value){
	if ( _offset < 0 ){
		__jf_fatal_error("negative offset in writeU16");	
	}
	size_t size = _size;
	size_t offset = _offset;
	if ( offset >= size || size - offset < 2 ){
		__jf_fatal_error("writeU16: out of bounds");	
	}
	unsigned short data = (unsigned short)value;
	::memcpy(((uint8_t*)buffer) + offset, &data, sizeof(data));
}

JFAPI void __jf_fatal_error(const char* message){
	fprintf(stderr, "FATAL ERROR: %s", message);
	
	exit(1);
}

JFAPI void __jf_warning(const char* message){
	fprintf(stderr, "WARNING: %s", message);
}

JFAPI JFObligation* __jf_allocate_obligation(){
	JFObligation* obligation = (JFObligation*)malloc(sizeof(JFObligation));
	return obligation;
}