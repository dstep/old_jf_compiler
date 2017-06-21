#pragma once
#include "ModuleContext.h"

namespace jf{
	namespace pipeline{
		class ModuleContext;

		class ModuleContextJob{
		public:
			ModuleContextJob(ModuleContext* module);
			~ModuleContextJob();

			virtual void run() = 0;
		protected:
			ModuleContext* module;

		private:
			friend class ModuleContext;
			ModuleContextJob* nextJob;
		};
	}
}