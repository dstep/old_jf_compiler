#pragma once
#include "../QualID.h"
#include "ParseString.h"
#include "../Container/ArrayList.h"

namespace jf{
	inline bool AlphaPredicate(const u8* data, size_t size){
		if ( size == 0 ){
			return false;
		}
		return (data[0] >= 'a' && data[0] <= 'z') || (data[0] >= 'A' && data[0] <= 'Z');
	}

	inline bool AlphaNumUnderscopePredicate(const u8* data, size_t size){
		if ( size == 0 ){
			return false;
		}
		return (data[0] >= 'a' && data[0] <= 'z') || (data[0] >= 'A' && data[0] <= 'Z') || (data[0] >= '0' && data[0] <= '9') || (data[0] == '_');
	}

	inline bool PeriodPredicate(const u8* data, size_t size){
		if ( size == 0 ){
			return false;
		}
		return (data[0] == '.');
	}

	template<class ErrorReporting>
	QualID* QualID::Parse(MemoryPoolSlice* hostPool, MemoryPoolSlice& tempPool, StringRef& source, ErrorReporting& errorReporting){
		using namespace string;
		SkipWhile(PredicateWhitespace, source);
		container::ArrayList<StringRef> parts(&tempPool); 
		const u8* data = source.getData();
		size_t size = source.getLength();
		size_t totalLength = 0;
		while ( true ){
			if ( AlphaPredicate(data, size) ){
				const u8* wordStart = data;
				data++;
				size--;
				while ( AlphaNumUnderscopePredicate(data, size) ){
					data++;
					size--;
				}
				parts.push(StringRef(wordStart, data - wordStart));
				totalLength += (data - wordStart);
				source = StringRef(data, size);
				SkipWhile(PredicateWhitespace, source);
				if ( PeriodPredicate(source.getData(), source.getLength()) ){
					source = StringRef(source.getData() + 1, source.getLength() - 1);
					SkipWhile(PredicateWhitespace, source);
					data = source.getData();
					size = source.getLength();
				}else{
					break;
				}
			}else{
				errorReporting(ParseError::ExpectedIdentifier, source);
				break;
			}
		}
		size_t partsCount = parts.getSize();
		if ( partsCount == 0 ){
			errorReporting(ParseError::EmptyQualID, source);
			return nullptr;
		}
		totalLength += (partsCount - 1);
		u8* buffer = (u8*)hostPool->allocateDynamic(sizeof(QualID) + totalLength, sizeof(StringRef), partsCount);  
		u8* string = buffer + sizeof(QualID) + sizeof(StringRef) * partsCount;
		QualID* qid = (QualID*)buffer;
		qid->string = StringRef(string, totalLength);
		auto e = parts.enumerate();
		qid->partsCount = partsCount;
		qid->parts[0] = StringRef(string, e.get().getLength());
		::memcpy(string, e.get().getData(), e.get().getLength());
		string += e.get().getLength();
		e.advance();
		while ( e.hasNext() ){
			*string = '.';
			string++;
			::memcpy(string, e.get().getData(), e.get().getLength());
			qid->parts[e.getIndex()] = StringRef(string, e.get().getLength());
			string += e.get().getLength();
			e.advance();
		}
		return qid;
	}
}