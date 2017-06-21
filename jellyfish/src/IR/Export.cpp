#include <IR/Export.h>
#include <IR/Class.h>
#include <IR/Interface.h>
#include <IR/Struct.h>
#include <IR/Enum.h>
#include <IR/Module.h>
#include <IR/GlobalFunction.h>
#include <IR/GlobalVariable.h>
#include <Support/Macros.h>

namespace jf{
	namespace ir{
		SrcSpan ExportName::getSrcLoc(){
			switch ( kind ){
			case ExportKind::None:
			case ExportKind::ConstructorClash:
				return SrcSpan::Undefined();
			case ExportKind::Class:
				return ((Class*)reference)->getSrcLoc();
			case ExportKind::Interface:
				return ((Interface*)reference)->getSrcLoc();
			case ExportKind::Enum:
				return ((Enum*)reference)->getSrcLoc();
			case ExportKind::Struct:
				return ((Struct*)reference)->getSrcLoc();
			case ExportKind::Variable:
				return ((GlobalVariable*)reference)->getSrcLoc();
			case ExportKind::Function:
				return ((GlobalFunction*)reference)->getSrcLoc();
			case ExportKind::EnumConstructor:
				return ((EnumConstructor*)reference)->getSrcLoc();
			case ExportKind::Namespace:
				return SrcSpan::Undefined();
			default:
				unreachable;
			}
		}

		StringRef ExportName::getName(){
			switch ( kind ){
			case ExportKind::None:
			case ExportKind::ConstructorClash:
				return "";
			case ExportKind::Namespace:
				return ((Namespace*)reference)->getName();
			case ExportKind::Class:
				return ((Class*)reference)->getName();
			case ExportKind::Interface:
				return ((Interface*)reference)->getName();
			case ExportKind::Enum:
				return ((Enum*)reference)->getName();
			case ExportKind::Struct:
				return ((Struct*)reference)->getName();
			case ExportKind::Variable:
				return ((GlobalVariable*)reference)->getName();
			case ExportKind::Function:
				return ((GlobalFunction*)reference)->getName();
			case ExportKind::EnumConstructor:
				return ((EnumConstructor*)reference)->getName();
			default:
				unreachable;
			}
		}

		static const char* ExportKindNames[] = {
				"",
				"Reference.ConstructorClash",
				"Reference.EnumConstructor",
				"Reference.GlobalFunction",
				"Reference.GlobalVariable",
				"Reference.Enum",
				"Reference.Class",
				"Reference.Interface",
				"Reference.Struct",
				"Reference.Namespace"
			};

		StringRef ExportName::GetKindName(ExportKind::Value kind){
			return ExportKindNames[kind];
		}

		bool ExportName::isTypeReference(){
			switch ( kind ){
			case ExportKind::Enum:
			case ExportKind::Class:
			case ExportKind::Interface:
			case ExportKind::Struct:
				return true;
			}
			return false;
		}

		ExportUniverse::Value ExportName::GetUniverse(ExportKind::Value kind){
			switch ( kind ){
			case ExportKind::EnumConstructor:
			case ExportKind::ConstructorClash:
				return ExportUniverse::Constructors;
			case ExportKind::None:
				return ExportUniverse::None;
			case ExportKind::Enum:
			case ExportKind::Class:
			case ExportKind::Interface:
			case ExportKind::Struct:
			case ExportKind::Function:
			case ExportKind::Variable:
			case ExportKind::Namespace:
				return ExportUniverse::TopLevel;
			default: unreachable;
			}
		}

		ReferencedSymbol ExportName::makeSymbol(Module* owner){
			Space<ReferencedSymbol> symbol;
			if ( owner ){
				symbol->fileName = owner->fileName;
			}
			symbol->identifier = getName();
			symbol->localizableName = getKindName();
			symbol->where = getSrcLoc();
			return *symbol;
		}
	}
}