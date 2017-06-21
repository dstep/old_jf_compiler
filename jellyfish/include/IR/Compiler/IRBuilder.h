#pragma once
#include <Support/MemoryPool.h>
#include <Support/Container/HashMap.h>
#include <Support/Container/ArrayList.h>
#include <Parser/AST/AST.h>
#include <Support/QualID.h>
#include "../Type.h"
#include "../Import.h"
#include "../FunctionSignature.h"
#include "../Definition.h"
#include "../Module.h"
#include "../Export.h"
#include <Support/Diagnostic.h>

namespace jf{
	namespace ir{
		namespace compiler{
			class IRBuilder{
			public:
				IRBuilder(IDiagnosticStream* diagnostic, MemoryPoolSlice* tempPool, MemoryPoolSlice* irPool, MemoryPoolSlice* defPool);

				Module* build(parser::ast::Module* ast);
			private:
				QualID* buildQualID(parser::ast::QualID* qid);

				Type buildType(parser::ast::Type* ast);
				TypeList* buildTypeList(parser::ast::TypeList* ast);
				TypeList* buildTypeList(parser::ast::Type* type, parser::ast::TypeList* types);
				FunctionSignature* buildSignature(parser::ast::FunctionSignature* ast);
				ArrayRef<Param> buildParams(parser::ast::ParamGroup* ast);

				Initializer* buildInitializer(parser::ast::Expr* expr);
				FunctionBody* buildFunctionBody(parser::ast::FunctionBody* body);

				ImportName* buildImportName(ImportName::Usage usage, parser::ast::QualID* qid);

				void addExportName(const StringRef& name, ExportKind::Value kind, void* reference);

			private:
				IDiagnosticStream* diagnostic;

				MemoryPoolSlice* tempPool;
				MemoryPoolSlice* irPool;
				MemoryPoolSlice* defPool;

				StringMap<Namespace*>* namespaceMap;
				ArrayList<ImportName*> importNames;

				StringMap<ExportName>* exportMap;
			};
		}
	}
}