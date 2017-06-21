#include <Support/File/FileSystem.h>
#include <Support/Obligation.h>

#if defined(JF_PLATFORM_WIN)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlwapi.h>
#include <Support/Platform/Windows.h>
namespace jf{
	namespace file{
		FileCacheRecord::FileCacheRecord()
			: valid(false){
		}

		void FileCacheRecord::reset(){
			valid = false;
		}

		void FileCacheRecord::set(u64 timestamp){
			valid = true;
			this->timestamp = timestamp;
		}

		FileStatus::Value WriteFile(MemoryPoolSlice& tempPool, StringRef path, StringRef content){
			HANDLE handle;
			{
				MemoryPoolSlice slice(tempPool);
				handle = CreateFileW(platform::Widen(&slice, path), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
			}
			if ( handle == INVALID_HANDLE_VALUE ){
				DWORD error = GetLastError();
				switch ( error ){
				case ERROR_FILE_NOT_FOUND:
				case ERROR_PATH_NOT_FOUND:{
					return FileStatus::NotFound;
				}break;
				case ERROR_ACCESS_DENIED:
				default:{
					return FileStatus::NotAccessible;
				}break;
				}
			}else{
				obligation([handle](){ CloseHandle(handle); });
				DWORD bytesWritten = 0;
				if ( !::WriteFile(handle, content.getData(), content.getLength(), &bytesWritten, NULL) || bytesWritten != content.getLength() ){
					return FileStatus::NotAccessible;
				}
				return FileStatus::OK;
			}
		}

		FileStatus::Value ReadFile(MemoryPoolSlice* hostPool, StringRef path, FileCacheRecord& cacheRecord, StringRef& output, size_t maxReadFileSize, size_t extraBufferSize){
			HANDLE handle;
			{
				MemoryPoolSlice slice(*hostPool);
				handle = CreateFileW(platform::Widen(&slice, path), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
			}
			if ( handle == INVALID_HANDLE_VALUE ){
				DWORD error = GetLastError();
				switch ( error ){
				case ERROR_FILE_NOT_FOUND:
				case ERROR_PATH_NOT_FOUND:{
					return FileStatus::NotFound;
				}break;
				case ERROR_ACCESS_DENIED:
				default:{
					return FileStatus::NotAccessible;
				}break;
				}
			}else{
				obligation([handle](){ CloseHandle(handle); });

				BY_HANDLE_FILE_INFORMATION fileInformation;
				if ( !GetFileInformationByHandle(handle, &fileInformation) ){
					return FileStatus::NotAccessible;
				}

				u64 timestamp = ((u64)fileInformation.ftLastWriteTime.dwLowDateTime) | (((u64)fileInformation.ftLastWriteTime.dwHighDateTime) << 32);
				if ( cacheRecord.isValid() && timestamp == cacheRecord.getTimestamp() ){
					return FileStatus::NotModified;
				}else{
					u64 fileSize = ((u64)fileInformation.nFileSizeLow) | (((u64)fileInformation.nFileSizeHigh) << 32);
					if ( fileSize > maxReadFileSize ){
						return FileStatus::FileTooLarge;
					}
					u32 readSize = (u32)fileSize;
					u8* buffer = (u8*)hostPool->allocate(extraBufferSize + readSize);
					DWORD read;
					if ( !::ReadFile(handle, buffer, (DWORD)fileSize, &read, NULL) || read != fileSize ){
						return FileStatus::NotAccessible;
					}
					::memset(buffer + fileSize, 0, extraBufferSize);
					output = StringRef(buffer, readSize);
					cacheRecord.set(timestamp);
					return FileStatus::OK;
				}
			}
		}

		StringRef ResolveCurrentPath(MemoryPoolSlice* hostPool, MemoryPoolSlice& tempPool, const StringRef& path){
			wchar_t buffer[MAX_PATH];
			wchar_t* widePath = platform::Widen(&tempPool, path);
			DWORD result = GetFullPathNameW(widePath, MAX_PATH, buffer, NULL);
			if ( result > MAX_PATH ){
				wchar_t* buffer = (wchar_t*)tempPool.allocateArray(sizeof(wchar_t), result);
				result = GetFullPathNameW(widePath, result, buffer, NULL);
				if ( result == 0 ){
					return path.slice(hostPool);
				}else{
					return platform::Narrow(hostPool, buffer);
				}
			}else{
				if ( result == 0 ){
					return path.slice(hostPool);
				}else{
					return platform::Narrow(hostPool, buffer);
				}
			}
		}

		StringRef ResolvePath(MemoryPoolSlice* hostPool, MemoryPoolSlice& tempPool, const StringRef& basePath, const StringRef& relativePath){
			wchar_t buffer[MAX_PATH];
			if ( PathCombineW(buffer, platform::Widen(&tempPool, basePath), platform::Widen(&tempPool, relativePath)) ){
				return platform::Narrow(hostPool, buffer);	
			}else{
				throw std::runtime_error("Unable to resolve path");
			}
		}

		bool IsDirectory(const StringRef& path){	
			MemoryPoolSlice stack(GetMemoryPool());		
			return PathIsDirectoryW(platform::Widen(&stack, path)) != FALSE;
		}

		bool IsPathsEqual(const StringRef& path1, const StringRef& path2){
			MemoryPoolSlice stack(GetMemoryPool());	
			wchar_t buffer1[MAX_PATH];
			wchar_t buffer2[MAX_PATH];
			PathCanonicalizeW(buffer1, platform::Widen(&stack, path1));
			PathCanonicalizeW(buffer2, platform::Widen(&stack, path2));
			return !StrCmpW(buffer1, buffer2);
		}

		StringRef MakePathRelativeToDirectory(MemoryPoolSlice* hostPool, MemoryPoolSlice& tempPool, const StringRef& relativeFrom, const StringRef& relativeTo){
			wchar_t buffer[MAX_PATH];
			if ( PathRelativePathToW(buffer, platform::Widen(&tempPool, relativeFrom), FILE_ATTRIBUTE_DIRECTORY, platform::Widen(&tempPool, relativeTo), 0) ){
				return platform::Narrow(hostPool, buffer);	
			}
			return relativeTo;
		}
	}
}
#endif