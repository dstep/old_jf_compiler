#include <cstdio>
#include <iostream>
#include <string>

extern "C"{
	void _print(std::string* str){
		printf("%s\n", str->c_str());
	}

	std::string* _input(){
		char buffer[1024];
		std::cin.getline(buffer, 1023);
		return new std::string(buffer);
	}

	std::string* _fmt(double value){
		char buffer[1024];
		sprintf(buffer, "%lf", value);
		return new std::string(buffer);
	}

	void _break(std::string* message){
		printf("Debug Break: %s\n", message->c_str());
		_CrtDbgBreak();
	}

	std::string* __jf_make_string(const char* s, __int32 length){
		return new std::string(s, length);
	}

	std::string* __jf_string_concat(std::string* a, std::string* b){
		return new std::string(*a + *b);
	}

	bool __jf_string_equal(std::string* a, std::string* b){
		return *a == *b;
	}
};

extern "C" void __jf_main();

int main(){
	__jf_main();
	system("pause");
	return 0;
}