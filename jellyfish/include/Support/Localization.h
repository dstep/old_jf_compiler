#pragma once
#include "StringRef.h"
#include "MemoryAPI.h"
#include "Container/SearchTree.h"
#include "SourceLoc.h"

namespace jf{
	enum LocalizedStringNodeTag{
		LocalizedStringPlainTag,
		LocalizedStringParamTag,
		LocalizedStringIfTag
	};

	struct LocalizedStringNode{
		LocalizedStringNodeTag tag;
		LocalizedStringNode* next;

		LocalizedStringNode(LocalizedStringNodeTag tag)
			: tag(tag)
			, next(nullptr){
		}
	};

	struct LocalizedStringPlain: public LocalizedStringNode{
		StringRef string;

		LocalizedStringPlain(StringRef string)
			: LocalizedStringNode(LocalizedStringPlainTag)
			, string(string){
		}
	};

	struct LocalizedStringParam: public LocalizedStringNode{
		StringRef param;
		StringRef separator;
		StringRef alt;

		LocalizedStringParam(const StringRef& param, const StringRef& separator, const StringRef& alt)
			: LocalizedStringNode(LocalizedStringParamTag)
			, param(param)
			, separator(separator)
			, alt(alt){
		}
	};

	struct LocalizedStringIf: public LocalizedStringNode{
		StringRef param;
		LocalizedStringNode* ifGiven;
		LocalizedStringNode* ifNotGiven;

		LocalizedStringIf(const StringRef& param, LocalizedStringNode* ifGiven, LocalizedStringNode* ifNotGiven)
			: LocalizedStringNode(LocalizedStringIfTag)
			, param(param)
			, ifGiven(ifGiven)
			, ifNotGiven(ifNotGiven){
		}
	};

	struct StringLiteral{
	public:
		StringLiteral(const StringRef& value)
			: value(value){
		}

		StringRef value;
	};

	struct PlainString{
	public:
		PlainString(const StringRef& value)
			: value(value){
		}

		PlainString(const char* value)
			: value(value){
		}

		StringRef value;
	};

	struct Integer{
		Integer(u64 value)
			: value(value){
		}
		
		u64 value;
	};

	struct ReferencedSymbol{
		StringRef localizableName;
		StringRef identifier;
		StringRef fileName;
		SrcSpan where;

		ReferencedSymbol(const StringRef& localizableName, const StringRef& identifier, const StringRef& fileName, const SrcSpan& where)
			: localizableName(localizableName)
			, identifier(identifier)
			, fileName(fileName)
			, where(where){
		}
	};

	class ILocalizationParamVisitor{
	public:
		virtual void visitLocalizableString(const StringRef& key, const StringRef& localizableString) = 0;

		virtual void visitValue(const StringRef& key, const SrcSpan& value) = 0;
		virtual void visitValue(const StringRef& key, const StringLiteral& value) = 0;
		virtual void visitValue(const StringRef& key, const PlainString& value) = 0;
		virtual void visitValue(const StringRef& key, const Integer& value) = 0;
		virtual void visitValue(const StringRef& key, const ReferencedSymbol& value) = 0;
	};

	class ILocalizationParamProvider{
	public:
		virtual void accept(ILocalizationParamVisitor& visitor) = 0;
	};

	class LocalizationParseError{
	public:
		LocalizationParseError(const StringRef& relatedText);

		StringRef getRelatedText(){
			return relatedText;
		}
	private:
		StringRef relatedText;
	};

	class LocalizationParseErrorParams: public ILocalizationParamProvider{
	public:
		LocalizationParseErrorParams(const StringRef& key, LocalizationParseError* error)
			: key(key)
			, error(error){			
		}

		void accept(ILocalizationParamVisitor& visitor){
			visitor.visitValue("string_id", PlainString(key));
			if ( !error->getRelatedText().isEmpty() ){
				visitor.visitValue("related_text", StringLiteral(error->getRelatedText()));
			}
		}
	private:
		StringRef key;
		LocalizationParseError* error;
	};

	class LocalizationDictionary: private OwnedPool<>{
	public:
		LocalizationDictionary();

		StringRef makeLocalizedString(MemoryPoolSlice* hostPool, MemoryPoolSlice& tempPool, const StringRef& code, ILocalizationParamProvider& params);
		LocalizedStringNode* getLocalizedString(const StringRef& code);

		LocalizationParseError* addLocalization(const StringRef& key, const StringRef& value);
	private:
		LocalizedStringNode* parseLocalizationString(const u8* data, size_t length, size_t& i, bool& wasError);

		LocalizationParseError error;
		container::SearchTree<StringRef, LocalizedStringNode*, StringRef::Compare> strings; 
	};
}