#include <Pipeline/ModuleContextJob.h>

namespace jf{
	namespace pipeline{
		ModuleContextJob::ModuleContextJob(ModuleContext* module)
			: module(module){
		}

		ModuleContextJob::~ModuleContextJob(){
		}
	}
}