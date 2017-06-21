#include <IR/Interface.h>
#include <IR/Module.h>

namespace jf{
	namespace ir{
		ReferencedSymbol InterfaceMethod::makeReference(){
			Space<ReferencedSymbol> symbol;
			symbol->fileName = owner->getOwner()->fileName;
			symbol->identifier = getName();
			symbol->localizableName = "Reference.InterfaceMethod";
			symbol->where = getSrcLoc();
			return *symbol;
		}
	}
}