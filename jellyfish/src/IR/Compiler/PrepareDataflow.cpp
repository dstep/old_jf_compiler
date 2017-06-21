#include <IR/Compiler/PrepareDataflow.h>

namespace jf{
	namespace ir{
		namespace compiler{
			PrepareDataflow::PrepareDataflow(){
			}

			void PrepareDataflow::run(Module* module){
				this->module = module;

				iterate_array(interface, module->interfaces){
					new(interface.get()->getDataflowJob())threading::DataflowJob();
				}

				iterate_array(class_, module->classes){
					new(class_.get()->getDataflowJob())threading::DataflowJob();
				}
			}
		}
	}
}