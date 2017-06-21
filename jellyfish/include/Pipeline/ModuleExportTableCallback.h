#pragma once
#include <IR/Module.h>

namespace jf{
	namespace pipeline{
		class ModuleContext;

		class IModuleExportTableCallback{
		public:
			IModuleExportTableCallback()
				: next(nullptr){
			}

			virtual void onReady(ir::Module* module) = 0;
			virtual void onNeverReady() = 0;
		private:
			IModuleExportTableCallback* next;
			friend class ModuleContext;
		};
	}
}
