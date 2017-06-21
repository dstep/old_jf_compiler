#include "runtime.h"
#include "bootstrap.h"

#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include <cstdint>
#include <ctime>

#include <gl/freeglut.h>

static uint64_t RandomValue = time(NULL);

static uint32_t randomInt(){
	static uint64_t A = 6364136223846793005;
	static uint64_t C = 1442695040888963407;

	RandomValue = A * RandomValue + C;

	return (uint32_t)RandomValue;
}

JFAPI 
void _print(jfstring string){
	size_t length;
	uint8_t* data;
	string->parse(&length, &data);
	fprintf(stdout, "%.*s\n", (int)length, data);
}

JFAPI
double _random(){
	uint32_t a = randomInt();
	uint32_t b = randomInt();

	double p1 = (double)(a / (double)(1ULL << 32));
	double p2 = b / (double)(1ULL << 32)  / (double)(1ULL << 32);

	double value = p1 + p2;

	return value; 
}
