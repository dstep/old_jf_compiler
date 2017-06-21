#pragma once
#include <Support/StringRef.h>
#include <Support/File/FileSystem.h>
#include <IR/Module.h>

namespace jf{
	namespace pipeline{
		enum ModuleObjectTag{
			SourceModuleObjectTag
		};

		struct ModuleObject{
			ModuleObjectTag tag;

			StringRef filePath;
			OwnedPool<> irPool;
			OwnedPool<> symbolPool;
			OwnedPool<> definitionPool;
			OwnedPool<> resolutionPool;
			OwnedPool<> instrPool;
			ir::Module* module;

			ModuleObject(ModuleObjectTag tag)
				: tag(tag)
				, module(nullptr){
			}
		};

		struct SourceModuleObject: public ModuleObject{			
			file::FileCacheRecord cacheRecord;
			
			SourceModuleObject()
				: ModuleObject(SourceModuleObjectTag)
				{
			}
		};
	}
}