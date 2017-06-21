#pragma once
#include "ProjectSettings.h"
#include <Support/MemoryAPI.h>
#include <Support/Container/CappedArray.h>

namespace jf{
	namespace pipeline{
		class ProjectSettingsParseError{
		public:
			enum Type{
				#define SETTINGS_ERROR(a, ...) a,
				#include "ProjectSettingsParseErrors.inc"
			};

			ProjectSettingsParseError(Type type, u32 line, StringRef source);

			Type getType(){
				return type;
			}

			u32 getLine(){
				return line;
			}

			StringRef getSource(){
				return source;
			}

			const char* getQualCode(){
				return GetQualCode(type);
			}

			static const char* GetQualCode(Type type);
		private:
			Type type;
			u32 line;
			StringRef source;
		};

		class ProjectSettingsParser{
			static const size_t MaxReportedErrors = 32;
		public:
			ProjectSettings* parse(MemoryPoolSlice* pool, StringRef string);

			void reportError(ProjectSettingsParseError::Type type, u32 line, const StringRef& source);

			ArrayRef<ProjectSettingsParseError> getErrors(){
				return errors;
			}
		private:
			container::CappedArray<ProjectSettingsParseError, MaxReportedErrors> errors;
		};
	}
}