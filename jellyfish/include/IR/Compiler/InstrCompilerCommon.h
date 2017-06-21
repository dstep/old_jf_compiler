#pragma once

#include <IR/Compiler/InstrCompiler.h>
#include <IR/Compiler/ModuleInstrCompiler.h>
#include <Support/Match.h>

namespace jf{
	namespace ir{
		namespace compiler{
			using namespace parser;
			
			#define alloc(t) new(TheHostPool->allocate(sizeof(t)))t
			#define temp(t) new(TheTempPool->allocate(sizeof(t)))t

			#define emmit(t, ...) TheInstrCompiler->addInstr(alloc(instr::t)(__VA_ARGS__))
			#define terminator(t, ...) TheInstrCompiler->addTerminatorInstr(alloc(instr::t)(__VA_ARGS__)) 
			#define report_error(where, _code, params) TheDiagnostic->report \
							( \
								Subsystem("Compiler") \
									params \
									.at(where) \
									.type(DiagnosticType::Error) \
									.code("CompilerError." #_code) \
							) 
		}
	}
}