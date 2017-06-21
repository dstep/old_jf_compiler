#pragma once
#include <Support/StringRef.h>
#include <Support/SourceLoc.h>
#include <Support/Localization.h>

namespace jf{
	namespace ir{
		namespace ExportUniverse{
			enum Value{
				None = 0,
				Constructors,
				TopLevel
			};
		}

		namespace ExportKind{
			enum Value{
				None,
				ConstructorClash,
				EnumConstructor,
				Function,
				Variable,
				Enum,
				Class,
				Interface,
				Struct,
				Namespace
			};
		}

		class Module;

		struct ExportName{
			ExportKind::Value kind;
			void* reference;

			ExportName()
				: kind(ExportKind::None)
				, reference(nullptr){
			}

			ExportName(ExportKind::Value kind)
				: kind(kind)
				, reference(nullptr){
			}

			ExportName(ExportKind::Value kind, void* reference)
				: kind(kind)
				, reference(reference){
			}

			operator bool() const{
				return kind != ExportKind::None && kind != ExportKind::ConstructorClash;
			}

			ReferencedSymbol makeSymbol(Module* owner);

			bool isTypeReference();

			SrcSpan getSrcLoc();
			StringRef getName();

			StringRef getKindName(){
				return GetKindName(kind);
			}

			ExportUniverse::Value getUniverse(){
				return GetUniverse(kind);
			}

			static ExportUniverse::Value GetUniverse(ExportKind::Value kind);

			static StringRef GetKindName(ExportKind::Value kind);
		};
	}
}