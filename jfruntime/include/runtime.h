#pragma once
#include <cstdint>
#include <string>

#if defined(BUILDING_JF_RUNTIME)
#define JFAPI extern "C" __declspec(dllexport)
#else
#define JFAPI extern "C" __declspec(dllimport)
#endif

typedef bool jfbool;
typedef int32_t jfint;
typedef float jffloat;
typedef double jfdouble;
typedef uint64_t jfu64;

#define jfcc __fastcall

JFAPI void initializeJFRuntime();

struct ObjectHeader{
	void (jfcc *gc_func) (void* object);
	void (jfcc *cast_func) (void* object, void* typeIdentity);
};

struct jfstringdata{
	union{
		uint8_t bytes[16];
		struct{
			uint8_t hi[4];
			uint32_t size;
			uint64_t ptr;
		} part;
	};

	void parse(size_t* length, uint8_t** data){
		if ( bytes[0] & 0x80 ){
			*length = part.size;
			*data = (uint8_t*)part.ptr;
		}else{
			*length = bytes[0];
			*data = bytes + 1;
		}
	}
};

typedef jfstringdata* jfstring;