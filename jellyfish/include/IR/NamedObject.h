#pragma once
#include <Support/StringRef.h>
#include <Support/SourceLoc.h>

namespace jf{
	namespace ir{
		class NamedObject{
		public:
			NamedObject(const SrcSpan& where, const StringRef& name)
				: where(where)
				, name(name){
			}

			const SrcSpan& getSrcLoc(){
				return where;
			}

			const StringRef& getName(){
				return name;
			}
		private:
			SrcSpan where;
			StringRef name;
		};
	}
}