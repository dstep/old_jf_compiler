#include <Pipeline/ProjectSettingsParser.h>
#include <Support/String/ParseString.h>
#include <Support/String/ParseQualID.h>
#include <new>

namespace jf{
	namespace pipeline{
		static const char* ProjectSettingsParseErrorCodes[] = {
					#define SETTINGS_ERROR(a, ...) "ProjectSettings." #a,
					#include <Pipeline/ProjectSettingsParseErrors.inc>
				};				
		const char* ProjectSettingsParseError::GetQualCode(Type type){
			return ProjectSettingsParseErrorCodes[type];
		}

		ProjectSettingsParseError::ProjectSettingsParseError(Type type, u32 line, StringRef source)
			: type(type)
			, line(line)
			, source(source){
		}

		ProjectSettings* ProjectSettingsParser::parse(MemoryPoolSlice* pool, StringRef string){
			MemoryPoolSlice stack(GetMemoryPool());

			ProjectSettings* settings = new(pool->allocate(sizeof(ProjectSettings)))ProjectSettings;
			settings->main = nullptr;

 			string::LineCounter lineCounter(1);

			container::ArrayList<StringRef>* sources = container::CreateArray<StringRef>(&stack);
			container::ArrayList<StringRef>* archive = container::CreateArray<StringRef>(&stack);
			container::ArrayList<Archive*>* archives = container::CreateArray<Archive*>(&stack);
			bool hasIntermediate = false;
			bool hasMain = false;

			errors.clear();

			auto errorReporting = [this, &lineCounter](string::ParseError::Value error, const StringRef& string){
										switch ( error ){
										case string::ParseError::UnterminatedDoubleQuote:
										case string::ParseError::UnterminatedSingleQuote:
											this->reportError(ProjectSettingsParseError::UndefinedCommand, lineCounter.getCurrentLine(), string);
										break;
										case string::ParseError::InvalidEscapeSequence:
											this->reportError(ProjectSettingsParseError::InvalidEscapeSequence, lineCounter.getCurrentLine(), string);
										break;
										default:
											this->reportError(ProjectSettingsParseError::MalformedInputString, lineCounter.getCurrentLine(), string);
										break;
										}										
									};

			size_t i, j = 0, n = string.getLength();
			for ( i = 0; i <= n; i++ ){
				if ( i == n || string.getData()[i] == '\n' || string.getData()[i] == '\r' ){
					if ( i > j ){						
						StringRef line(string.getData() + j, i - j);
						string::SkipWhile(string::PredicateWhitespace, line);						
						if ( line.getLength() > 0 ){
							if ( line.getData()[0] == '#' ){								
							}else{
								StringRef command = string::ParseWord(pool, stack, line, errorReporting);
								string::SkipWhile(string::PredicateWhitespace, line);
								if ( command == "source" ){
									bool hasParam = false;
									while ( !line.isEmpty() ){
										if ( line.getData()[0] == '#' ){
											break;
										}
										StringRef param = string::ParseWord(pool, stack, line, errorReporting);
										string::SkipWhile(string::PredicateWhitespace, line);
										sources->push(param);
										hasParam = true;
									}
									if ( !hasParam ){
										reportError(ProjectSettingsParseError::NoSourceGiven, lineCounter.getCurrentLine(), "");
									}
								}else if ( command == "intermediate" ){
									while ( !line.isEmpty() ){
										if ( line.getData()[0] == '#' ){
											break;
										}
										StringRef param = string::ParseWord(pool, stack, line, errorReporting);
										string::SkipWhile(string::PredicateWhitespace, line);
										if ( !hasIntermediate ){
											settings->itermediate = param;
											hasIntermediate = true;
										}else{
											reportError(ProjectSettingsParseError::MultipleIntermediatePaths, lineCounter.getCurrentLine(), param);
											break;
										}
									}
									if ( !hasIntermediate ){
										reportError(ProjectSettingsParseError::IntermediatePathNotGiven, lineCounter.getCurrentLine(), "");
									}
								}else if ( command == "archive" ){
									while ( !line.isEmpty() ){
										if ( line.getData()[0] == '#' ){
											break;
										}
										StringRef param = string::ParseWord(pool, stack, line, errorReporting);
										string::SkipWhile(string::PredicateWhitespace, line);
										archive->push(param);
									}
									if ( archive->getSize() == 0 ){
										reportError(ProjectSettingsParseError::ArchiveTargetNotGiven, lineCounter.getCurrentLine(), "");
									}else if ( archive->getSize() == 1 ){
										reportError(ProjectSettingsParseError::ArchiveSourceNotGiven, lineCounter.getCurrentLine(), "");
									}else{
										StringRef output = archive->get(0);
										ArrayRef<StringRef> sources = archive->slice(pool, 1);
										Archive* archive = new(pool->allocate(sizeof(Archive)))Archive;
										archive->output = output;
										archive->sources = sources;
										archives->push(archive);
									}
									archive->clear();
								}else if ( command == "main" ){
									if ( !line.isEmpty() ){
										if ( line.getData()[0] != '#' ){
											QualID* param = QualID::Parse(pool, stack, line, errorReporting);
											string::SkipWhile(string::PredicateWhitespace, line);
											if ( param->getPartsCount() < 2 ){
												reportError(ProjectSettingsParseError::MainMustBeQualified, lineCounter.getCurrentLine(), param->asString());												
											}else if ( !hasMain ){
												settings->main = param;
												hasMain = true;
											}else{
												reportError(ProjectSettingsParseError::MultipleMainFunctions, lineCounter.getCurrentLine(), param->asString());
											}
											if ( !line.isEmpty() && line.getData()[0] != '#' ){
												reportError(ProjectSettingsParseError::ExtraCharactersAfterQualID, lineCounter.getCurrentLine(), line);
											}
										}
									}
									if ( !hasMain ){
										reportError(ProjectSettingsParseError::MainFunctionNotGiven, lineCounter.getCurrentLine(), "");
									}
								}else{
									reportError(ProjectSettingsParseError::UndefinedCommand, lineCounter.getCurrentLine(), command);
								}
							}
						}
					}
					j = i + 1;
				}
				if ( i < n ){
					lineCounter.count(string.getData()[i]);
				}
			}
			
			settings->sources = sources->slice(pool);
			settings->archives = archives->slice(pool);
			return settings;
		}

		void ProjectSettingsParser::reportError(ProjectSettingsParseError::Type type, u32 line, const StringRef& source){
			errors.push(ProjectSettingsParseError(type, line, source));
		}
	}
}