#include <cstdio>
#include <string>
#include <iostream>
#include <Windows.h>

#define JFAPI extern "C" __declspec(dllexport)

JFAPI
void (*__jf_main) () = nullptr;

void fatal_error(const char* msg){
	fprintf(stderr, "Fatal: %s\n", msg);
	exit(1);
}

int main(){
	printf("Runner started\n");
	if ( __jf_main ){
		printf("Running main function (%p)\n", __jf_main);
		__jf_main();
	}else{
		fatal_error("No main function registered");
	}
	
	return 0;
}