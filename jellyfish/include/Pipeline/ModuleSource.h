#pragma once
#include <Support/StringRef.h>

namespace jf{
	namespace pipeline{
		enum ModuleSourceTag{
			ModuleSourceSrcPathTag
		};

		struct ModuleSource{
			ModuleSourceTag tag;

			ModuleSource(ModuleSourceTag tag)
				: tag(tag){
			}
		};

		struct ModuleSourceSrcPath: public ModuleSource{
			StringRef path;

			ModuleSourceSrcPath(StringRef path)
				: ModuleSource(ModuleSourceSrcPathTag)
				, path(path){
			}
		};
	}
}