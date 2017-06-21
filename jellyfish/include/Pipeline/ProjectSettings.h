#pragma once 
#include <Support/StringRef.h>
#include <Support/ArrayRef.h>
#include <Support/QualID.h>
#include "Target.h"
#include "Archive.h"

namespace jf{
	namespace pipeline{
		struct ProjectSettings{
			ArrayRef<StringRef> sources;
			StringRef itermediate;			
			QualID* main;		
			ArrayRef<Archive*> archives;
		};
	}
}