#pragma once 
#include "StringRef.h"
#include "MemoryAPI.h"

namespace jf{
	class QualID{
	public:
		const StringRef& asString() const{
			return string;
		}

		const StringRef& getPart(size_t index) const{
			return parts[index];
		}

		size_t getPartsCount() const{
			return partsCount;
		}

		QualID* slice(MemoryPoolSlice* hostPool, size_t from = 0, size_t to = std::numeric_limits<size_t>::max());
		/**
		* Include ParseQualID.h for definition
		*/
		template<class ErrorReporting>
		static QualID* Parse(MemoryPoolSlice* hostPool, MemoryPoolSlice& tempPool, StringRef& source, ErrorReporting& errorReporting);

		StringRef string;
		size_t partsCount;
		#pragma warning(push)
		#pragma warning(disable:4200)
		StringRef parts[0];
		#pragma warning(pop)
	};
}