#pragma once
#include <Support/Diagnostic.h>
#include <Support/MemoryAPI.h>
#include <Parser/AST/AST.h>
#include <IR/Instr/Coercion.h>
#include "../Module.h"

namespace jf{
	namespace ir{
		namespace compiler{
			class InstrCompiler;

			class ModuleInstrCompiler{
			public:
				ModuleInstrCompiler(IDiagnosticStream* stream, MemoryPoolSlice* tempPool, MemoryPoolSlice* hostPool);

				void run(Module* module);				
			private:
				instr::Type* specializeType(const SrcSpan& where, ArrayRef<instr::Type*> typeTemplateVars, instr::Type* type, instr::Type* hintType);

				bool makeOverride(FunctionSignature* baseSignature, const ReferencedSymbol& baseReference, ClassMethod* overrider, instr::Coercion*& retValCoercion, ArrayRef<instr::Coercion*>& paramCoercions);

				bool areTypesEqual(instr::Type* left, instr::Type* right);
				instr::Coercion* findCoercion(instr::Type* from, instr::Type* to);
				bool unifyTypes(instr::Type* left, instr::Type* right);

				s32 parseInt(const SrcSpan& where, const StringRef& content);
				float parseFloat(const SrcSpan& where, const StringRef& content);
				double parseDouble(const SrcSpan& where, const StringRef& content);

				void addTypeEdge(instr::Type* outv, instr::Type* inv);
				void mergeInedge(instr::TypeNumeric* target, instr::Type* in);
				void mergeOutedge(instr::TypeNumeric* target, instr::Type* out);
				
				instr::Type* buildType(ir::Type type);
				instr::Type* buildType(parser::ast::Type* ast);
				
				instr::Type* buildTypeFromExportName(const SrcSpan& where, const StringRef& id, Pair<ExportName, ir::Module*> name);
				Pair<ExportName, ir::Module*> findName(const SrcSpan& where, const StringRef& name);
				Pair<ExportName, ir::Module*> findName(const SrcSpan& where, ir::Namespace* ns, const StringRef& name);

				IDiagnosticStream* stream;
				MemoryPoolSlice* hostPool;
				MemoryPoolSlice* tempPool;
				Module* module;

				friend class InstrCompiler;
				friend class TypingContext;
			};
		}
	}
}