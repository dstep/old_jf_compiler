#pragma once
#include "Import.h"
#include <Support/Container/HashMap.h>
#include "GlobalFunction.h"
#include "GlobalVariable.h"
#include "Interface.h"
#include "Class.h"
#include "Enum.h"
#include "Struct.h"
#include "Export.h"
#include "ImportBloomFilter.h"
#include <Support/Threading/Dataflow.h>

namespace jf{
	namespace ir{
		class Module{
		public:
			QualID* qid;
			StringRef fileName;

			ArrayRef<ImportModule*> imports;
			ArrayRef<Namespace*> namespaces;			
			StringMap<Namespace*>* namespaceMap;
			ArrayRef<ImportName*> importNames;

			StringMap<ExportName>* exportMap;
			ExportTableFilter exportFilter;

			ArrayRef<GlobalFunction*> functions;
			ArrayRef<GlobalVariable*> variables;
			ArrayRef<Interface*> interfaces;
			ArrayRef<Class*> classes;
			ArrayRef<Enum*> enums;
			ArrayRef<Struct*> structs;

			Module()
				: qid(nullptr)
				, exportMap(nullptr)
				, namespaceMap(nullptr){
			}
		};
	}
}