#include <IR/Class.h>
#include <IR/Module.h>

namespace jf{
	namespace ir{
		static const char* ClassMemberName[] = {
				"Reference.ClassMethod",
				"Reference.ClassConstructor",
				"Reference.ClassField"
			};

		StringRef ClassMember::GetKindName(ClassMemberTag tag){
			return ClassMemberName[tag];
		}

		ReferencedSymbol ClassMember::makeReference(){
			Space<ReferencedSymbol> symbol;
			symbol->fileName = owner->getOwner()->fileName;
			symbol->identifier = getName();
			symbol->localizableName = getKindName();
			symbol->where = getSrcLoc();
			return *symbol;
		}

		ReferencedSymbol Class::makeSymbol(){
			Space<ReferencedSymbol> symbol;
			symbol->fileName = owner->fileName;
			symbol->identifier = getName();
			symbol->localizableName = "Reference.Class";
			symbol->where = getSrcLoc();
			return *symbol;
		}
	}
}