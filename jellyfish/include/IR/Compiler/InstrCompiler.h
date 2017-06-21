#pragma once
#include <Support/Diagnostic.h>
#include <Support/MemoryAPI.h>
#include <Parser/AST/AST.h>
#include <IR/FunctionSignature.h>
#include <IR/Instr/FunctionFrame.h>
#include <IR/Instr/Instr.h>
#include <IR/Instr/BasicBlock.h>
#include "LexicalScope.h"
#include "ControlFlow.h"
#include "CompilerValue.h"
#include "MatchTree.h"

namespace jf{
	namespace ir{
		namespace compiler{
			class ModuleInstrCompiler;

			struct InstrCompilerState{
				instr::FunctionFrame* frame;
				instr::BasicBlock* block;
			};

			struct CoercionLater{
				SrcSpan where;
				instr::InstrCoercion* coerceInstr;
				instr::Type* left;
				instr::Type* right;

				CoercionLater(const SrcSpan& where, instr::InstrCoercion* coerceInstr, instr::Type* left, instr::Type* right)
					: where(where)
					, coerceInstr(coerceInstr)
					, left(left)
					, right(right){
				}
			};

			struct CompareTriple{
				instr::CompareClass* compareClass;
				instr::Type* leftType;
				instr::Type* rightType;

				CompareTriple(instr::CompareClass* compareClass)
					: compareClass(compareClass)
					, leftType(nullptr)
					, rightType(nullptr){
				}

				CompareTriple(instr::CompareClass* compareClass, instr::Type* type)
					: compareClass(compareClass)
					, leftType(type)
					, rightType(type){
				}

				CompareTriple(instr::CompareClass* compareClass, instr::Type* leftType, instr::Type* rightType)
					: compareClass(compareClass)
					, leftType(leftType)
					, rightType(rightType){
				}
			};

			class InstrCompiler{
			public:
				InstrCompiler(ModuleInstrCompiler* parent);

				InstrCompilerState beginFunctionFrame();
				instr::FunctionFrame* endFunctionFrame(const SrcSpan& where, const InstrCompilerState& state);

				void useSignature(FunctionSignature* signature);
				void useThisObject(ir::Class* class_);
				void useConstructorSemantic(ir::Class* fromClass, ir::Class* targetClass);
				void run(parser::ast::Stmt* ast);	
				
				instr::Instr* addInstr(instr::Instr* instr);

				void satisfyLaters();
			private:
				void compileSequence(parser::ast::Stmt* ast);
				void compileStmt(parser::ast::Stmt* ast);

				void compileMatchTreeNode(MatchNode* node);

				bool isTypeShouldBeCopied(instr::Type* type);

				void addMatchSuccessNodeIncoming(MatchNodeSuccess* node);
				void addMatchFailNodeIncoming(MatchNodeFail* node);

				instr::BasicBlock* makeBasicBlock();

				Pair<ir::Class*, ir::ClassConstructor*> findConstructor(parser::ast::QualID* qid);
				ir::ClassConstructor* findLocalConstructor(const SrcSpan& where, ir::Class* class_, const StringRef& name);
				Reference typeFieldLookup(const SrcSpan& where, const Value& value, const StringRef& name, instr::Type* hintType);

				Reference compileNameForm(parser::ast::Expr* ast, instr::Type* hintType);
				Value compileReferenceForm(parser::ast::Expr* ast, instr::Type* hintType);
				Value compileNormalForm(parser::ast::Expr* ast, instr::Type* hintType);
				Value compileCoerceNormalForm(parser::ast::Expr* ast, instr::Type* type);
				void compileControlFlow(parser::ast::Expr* ast, instr::BasicBlock** ifTrue, instr::BasicBlock** ifFalse);						
				Value makeCoercion(const SrcSpan& where, const Value& from, instr::Type* to);
				Value makeReferenceValueFromName(const SrcSpan& where, Reference reference);

				CompareTriple findCompareClass(const SrcSpan& where, instr::Type* left, instr::Type* right);
				Value makeComparison(const SrcSpan& where, instr::InstrCompare::Operator op, const Value& lhs, const Value& rhs);

				instr::Type* getReferenceType(Reference reference);
				void writeReference(const SrcSpan& where, Reference reference, const Value& value);

				void compileArguments(const SrcSpan& where, instr::Instr** values, parser::ast::ExprList* arguments, const ArrayRef<ir::Param>& params);
				void compileArguments(const SrcSpan& where, instr::Instr** values, parser::ast::ExprList* arguments, const ArrayRef<ir::instr::Type*>& params);

				Value makeCallBuiltin(const SrcSpan& where, instr::BuiltinFunction::Template* function, instr::Type** instance, Value thisObject, parser::ast::ExprList* arguments, instr::Type* hintType);
				Value compileBuiltinArg(instr::Type* param, parser::ast::Expr* expr);
				
				Value getThisObject();
				
				instr::Type* makeValidStorageType(instr::Type* type);

				instr::Type* mergeTypesArithOperator(instr::Type* left, instr::Type* right);

				instr::Type* unifyTypes(const SrcSpan& where, instr::Type* left, instr::Type* right);
				instr::Type* mergeTypes(const SrcSpan& where, instr::Type* left, instr::Type* right);
				
				instr::TypeNumeric* makeNumericType();
				
				void satisfyNumericTypes();

				ModuleInstrCompiler* parent;
				instr::FunctionFrame* currentFrame;

				u32 typeVarIndex;

				ir::Class* thisObject;

				instr::FunctionFrame* thisObjectFrame;
				Value thisObjectValue;

				Value thisObjectFrameValue;

				LexicalScope scope;

				instr::BasicBlock* currentBasicBlock;
				
				ArrayList<instr::TypeNumeric*> numericTypes;
				ArrayList<CoercionLater> coercionLater;
			};
		}
	}
}