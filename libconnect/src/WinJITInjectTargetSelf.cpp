#include <WinJITInjectTargetSelf.h>
#include <Windows.h>
#include <map>
#include <vector>
#include <Psapi.h>

namespace jf{
	namespace connect{
		class WinJITInjectTargetSelf: public IJITInjectTarget{
			struct Page{
				void* addr;
				size_t size;
			};
		public:		
			WinJITInjectTargetSelf(MainFunc* mainPtr)
				: mainPtr(mainPtr){
				DWORD bytesNeeded = 0;				
				modules.resize(64);
				if ( EnumProcessModulesEx(GetCurrentProcess(), &modules.at(0), (DWORD)(sizeof(HMODULE) * modules.size()), &bytesNeeded, LIST_MODULES_ALL) != FALSE ){
					modules.resize(bytesNeeded / sizeof(HMODULE));
					EnumProcessModulesEx(GetCurrentProcess(), &modules.at(0), bytesNeeded, &bytesNeeded, LIST_MODULES_ALL);
				}else{
					modules.resize(0);
				}
			}
				
			Addr allocateCodePage(Size size, Size align){
				void* addr = VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
				if ( addr ){
					Page page;
					page.addr = addr;
					page.size = size;
					pages.insert(std::make_pair((Addr)addr, page));
					return (Addr)addr;
				}else{
					return 0;
				}
			}

			Addr allocateDataPage(Size size, Size align, bool readOnly){
				void* addr = VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
				if ( addr ){
					Page page;
					page.addr = addr;
					page.size = size;
					pages.insert(std::make_pair((Addr)addr, page));
					return (Addr)addr;
				}else{
					return 0;
				}
			}

			void freePage(Addr addr){
				Page* page = findPage(addr);
				if ( page ){
					VirtualFree(page->addr, page->size, MEM_RELEASE);
					pages.erase(addr);
				}
			}

			Addr querySymbol(const char* name){
				for ( auto& module : modules ){
					FARPROC proc = GetProcAddress(module, name);
					if ( proc ){
						return (Addr)proc;
					}
				}
				return 0;
			}
			
			Size writeMemory(Addr addr, Size size, const void* data){
				Page* page = findPageContainingAddress(addr);
				if ( page ){
					Size availSize = (Size)page->size + (Addr)page->addr - addr;
					if ( availSize < size ){
						return 0;
					}
					::memcpy((void*)addr, data, size);
					return size;
				}
				return 0;
			}

			Size readMemory(Addr addr, Size size, void* buffer){
				Page* page = findPageContainingAddress(addr);
				if ( page ){
					Size availSize = (Size)page->size + (Addr)page->addr - addr;
					if ( availSize < size ){
						return 0;
					}
					::memcpy(buffer, (void*)addr, size);
					return size;
				}
				return 0;
			}

			void commitPage(Addr addr, bool code, bool readOnly){
				Page* page = findPage(addr);
				if ( page ){
					DWORD oldProtect;
					DWORD newProtect;
					if ( code ){
						newProtect = PAGE_EXECUTE;
					}else if ( readOnly ){
						newProtect = PAGE_READONLY;
					}else{
						newProtect = PAGE_READWRITE;
					}
					VirtualProtect(page->addr, page->size, newProtect, &oldProtect);
				}
			}

			void submitMain(Addr addr){
				*mainPtr = (MainFunc)addr;
			}
		private:
			Page* findPageContainingAddress(Addr addr){
				auto it = pages.upper_bound(addr);
				if ( it != pages.begin() ){
					it--;				
					Page* page = &it->second;
					if ( (Addr)page->addr + page->size >= addr ){
						return page;
					}
				}
				return nullptr;
			}

			Page* findPage(Addr addr){
				auto it = pages.find(addr);
				if ( it == pages.end() ){
					return nullptr;
				}
				return &it->second;
			}

			MainFunc* mainPtr;

			std::vector<HMODULE> modules;
			std::map<Addr, Page> pages;
		};

		IJITInjectTarget* CreateWinJITTargetSelf(IJITInjectTarget::MainFunc* funcPtr){
			return new WinJITInjectTargetSelf(funcPtr);
		}

		void DestroyWinJITTargetSelf(IJITInjectTarget* target){
			delete (WinJITInjectTargetSelf*)target;
		}
	}
}