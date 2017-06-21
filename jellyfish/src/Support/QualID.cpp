#include <Support/QualID.h>

namespace jf{
	QualID* QualID::slice(MemoryPoolSlice* hostPool, size_t from, size_t to){
		if ( to > partsCount ){
			to = partsCount;
		}
		if ( from >= to ){
			return nullptr;
		}
		const u8* stringStart = parts[from].getData();
		const u8* stringEnd = parts[to - 1].getData() + parts[to - 1].getLength();
		size_t sliceParts = to - from;
		u8* buffer = (u8*)hostPool->allocateDynamic(sizeof(QualID) + (stringEnd - stringStart), sizeof(StringRef), sliceParts);
		QualID* qid = (QualID*)buffer;
		u8* stringBuffer = buffer + sizeof(QualID) + sizeof(StringRef) * sliceParts;
		::memcpy(stringBuffer, stringStart, stringEnd - stringStart);
		qid->string = StringRef(stringBuffer, stringEnd - stringStart);
		qid->partsCount = sliceParts;
		for ( size_t i = from; i < to; i++ ){
			qid->parts[i - from] = StringRef(stringBuffer, parts[i].getLength());
			stringBuffer += parts[i].getLength() + 1;
		}
		return qid;
	}
}