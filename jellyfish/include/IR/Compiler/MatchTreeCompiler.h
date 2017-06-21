#pragma once
#include <IR/Instr/Type.h>
#include "InstrCompiler.h"
#include <Support/Container/ArrayList.h>
#include "MatchTree.h"


namespace jf{
	namespace ir{
		namespace compiler{
			class MatchTreeCompiler{
			public:
				MatchTreeCompiler(InstrCompiler* parent, MemoryPoolSlice* tempPool, MemoryPoolSlice* hostPool);

				MatchValue* addValue(instr::Type* type);

				void addCase(const SrcSpan& where, parser::ast::Pattern* patterns);
				MatchNodeSuccess* addGuardedAction(const SrcSpan& where, parser::ast::Expr* guard);
				MatchNodeSuccess* addDefaultAction(const SrcSpan& where);

				MatchNode* getRootNode();
				MatchNodeFail* getFailNode();

				void compileTreeNode(MatchNode* node);
			private:
				void compilePattern(parser::ast::Pattern* pattern, MatchValue* value);

				void updateMatchTree(MatchNode* successNode);

				MatchNodeSuccess* createNewSuccessNode(const SrcSpan& where, MatchTreeRemember* remember);

				MatchNode* updateMatchTree(MatchNode* node, MatchNode* successNode);

				MatchNode* root;

				MatchNodeFail* failNode;

				MatchValue* getMatchValueOptionalValue(MatchValue* value);

				InstrCompiler* parent;
				MemoryPoolSlice* tempPool;
				MemoryPoolSlice* hostPool;
				ArrayList<MatchValue*> values;
				ArrayList<MatchNodeSuccess*> successNodes;

				MatchTreeRemember* remember;

				MatchAssumption* assumptions;
				MatchAssumption* lastAssumption;

				PtrHash<MatchValue, MatchValue*> maybeValues;

				void addAssumption(MatchAssumption* assumption);

				MatchAssumption* extractAssumption(MatchAssumption* assumption);
				void restoreAssumption(MatchAssumption* assumption);
			};
		}
	}
}