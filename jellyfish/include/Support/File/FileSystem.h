#pragma once
#include "../Types.h"
#include "../MemoryAPI.h"
#include "../StringRef.h"

namespace jf{
	namespace file{
		class FileCacheRecord{
		public:
			FileCacheRecord();

			void reset();
			void set(u64 timestamp);

			bool isValid(){
				return valid;
			}
			
			u64 getTimestamp(){
				return timestamp;
			}
		private:
			bool valid;
			u64 timestamp;
		};

		namespace FileStatus{
			enum Value{
				OK = 200,
				NotModified = 304,		
				NotFound = 404,
				NotAccessible = 403,
				FileTooLarge = 413
			};
		}

		FileStatus::Value ReadFile(MemoryPoolSlice* hostPool, StringRef path, FileCacheRecord& cacheRecord, StringRef& output, size_t maxReadFileSize, size_t extraBufferSize);
		FileStatus::Value WriteFile(MemoryPoolSlice& tempPool, StringRef path, StringRef content);
		StringRef ResolveCurrentPath(MemoryPoolSlice* hostPool, MemoryPoolSlice& tempPool, const StringRef& path);
		StringRef ResolvePath(MemoryPoolSlice* hostPool, MemoryPoolSlice& tempPool, const StringRef& basePath, const StringRef& relativePath);
		StringRef MakePathRelativeToDirectory(MemoryPoolSlice* hostPool, MemoryPoolSlice& tempPool, const StringRef& relativeFrom, const StringRef& relativeTo);
		bool IsPathsEqual(const StringRef& path1, const StringRef& path2);
		bool IsDirectory(const StringRef& path);
	}
}