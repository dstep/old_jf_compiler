#include <Support/Platform/Windows.h>
#include <Support/MemoryAPI.h>

namespace jf{
	namespace platform{
		wchar_t* Widen(MemoryPoolSlice* pool, const StringRef& string){
			if ( string.getLength() == 0 ){
				return L"";
			}else{
				int length = string.getLength() > INT_MAX ? INT_MAX : (int)string.getLength();
				int countChars = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)string.getData(), length, nullptr, 0);
				if ( countChars > 0 ){
					wchar_t* wideString = (wchar_t*)pool->allocateArray(sizeof(wchar_t), countChars + 1);
					MultiByteToWideChar(CP_UTF8, 0, (LPCCH)string.getData(), length, wideString, countChars);
					wideString[countChars] = L'\0';
					return wideString;
				}else{
					//TODO:: copy only ascii
					return L"";
				}
			}
		}

		StringRef Narrow(MemoryPoolSlice* pool, wchar_t* wideString){
			int wideLength = lstrlenW(wideString);
			if ( wideLength == 0 ){
				return StringRef();
			}else{
				int countChars = WideCharToMultiByte(CP_UTF8, 0, wideString, wideLength, nullptr, 0, NULL, NULL);
				if ( countChars > 0 ){
					u8* string = (u8*)pool->allocate(countChars);
					WideCharToMultiByte(CP_UTF8, 0, wideString, wideLength, (LPSTR)string, countChars, NULL, NULL);
					return StringRef(string, countChars);
				}else{
					return StringRef();
				}
			}
		}
	}
}