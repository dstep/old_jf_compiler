#pragma once
#include <Support/SourceLoc.h>
#include <Support/StringRef.h>
#include <Support/Container/HashMap.h>
#include <Support/Container/ArrayList.h>
#include <IR/FunctionSignature.h>
#include "Coercion.h"
#include "Builtin.h"
#include "Compare.h"
#include <IR/GlobalFunction.h>

namespace jf{
	namespace ir{
		namespace instr{
			class BasicBlock;
			struct Type;
			namespace BuiltinFunction{
				struct Template;
			}

			enum InstrTag{
				InstrNoValueTag,
				InstrBadCodeTag,
				InstrConstUnitTag,
				InstrConstTrueTag,
				InstrConstFalseTag,
				InstrReturnTag,
				InstrCondBranchTag,
				InstrUncondBranchTag,
				InstrBrMaybeTag,
				InstrUnwrapMaybeTag,
				InstrCoercionTag,
				InstrParamTag,
				InstrThisParamTag,
				InstrLocalVarTag,
				InstrUpValueTag,
				InstrCallBuiltinFunctionTag,
				InstrAddTag,
				InstrReadLocalTag,
				InstrCopyTag,
				InstrIndexClassFieldTag,
				InstrCallClassMethodTag,
				InstrCallInterfaceMethodTag,
				InstrCallEnumConstructorTag,
				InstrCallGlobalTag,
				InstrWriteLocalTag,
				InstrWriteClassFieldTag,
				InstrCompareTag,
				InstrNewObjectTag,
				InstrContinueConstructorTag,
				InstrFinalizeConstructorTag,
				InstrPHITag,
			};

			struct Instr{
				Instr* next;
				InstrTag tag;
				u32 frameIndex;

				Instr(InstrTag tag)
					: tag(tag)
					, next(nullptr)
					, frameIndex(0){
				}

				static bool IsTerminator(Instr* instr);
			};

			struct InstrNoValue: public Instr{
				static InstrNoValue Instance;
				static InstrNoValue* Get(){
					return &Instance;
				}

				InstrNoValue()
					:Instr(InstrNoValueTag){
				}
			};

			struct InstrBadCode: public Instr{
				SrcSpan where;
				StringRef message;

				InstrBadCode(const SrcSpan& where, const StringRef& message)
					: Instr(InstrBadCodeTag)
					, where(where)
					, message(message){
				}
			};

			struct InstrConstUnit: public Instr{
				InstrConstUnit()
					: Instr(InstrConstUnitTag){
				}
			};

			struct InstrConstTrue: public Instr{
				InstrConstTrue()
					: Instr(InstrConstTrueTag){
				}
			};

			struct InstrConstFalse: public Instr{
				InstrConstFalse()
					: Instr(InstrConstFalseTag){
				}
			};

			struct InstrReturn: public Instr{
				Instr* value;

				InstrReturn(Instr* value)
					: Instr(InstrReturnTag)
					, value(value){
				}
			};

			struct InstrCondBranch: public Instr{
				Instr* condition;
				BasicBlock* bbTrue;
				BasicBlock* bbFalse;

				InstrCondBranch(Instr* condition, BasicBlock* bbTrue, BasicBlock* bbFalse)
					: Instr(InstrCondBranchTag)
					, condition(condition)
					, bbTrue(bbTrue)
					, bbFalse(bbFalse){
				}
			};

			struct InstrCoercion: public Instr{
				Instr* value;
				Coercion* coercion;

				InstrCoercion(Instr* value)
					: Instr(InstrCoercionTag)
					, value(value)
					, coercion(nullptr){
				}

				InstrCoercion(Instr* value, Coercion* coercion)
					: Instr(InstrCoercionTag)
					, value(value)
					, coercion(coercion){
				}
			};

			struct InstrUncondBranch: public Instr{
				BasicBlock* bb;

				InstrUncondBranch(BasicBlock* bb)
					: Instr(InstrUncondBranchTag)
					, bb(bb){
				}
			};
			
			struct InstrAdd: public Instr{
				instr::Instr* lhs;
				instr::Instr* rhs;

				InstrAdd(instr::Instr* lhs,	instr::Instr* rhs)
					: Instr(InstrAddTag)
					, lhs(lhs)
					, rhs(rhs){
				}
			};

			struct InstrParam: public Instr{
				instr::Type* type;
				ir::Param* param;
				instr::FunctionFrame* owner;

				InstrParam(instr::FunctionFrame* owner, ir::Param* param, instr::Type* type)
					: Instr(InstrParamTag)
					, owner(owner)
					, param(param)
					, type(type){
				}
			};

			struct InstrUpValue: public Instr{
				FunctionFrame* frame;
				size_t index;
				instr::Instr* capturedInstr;
				instr::Type* type;

				InstrUpValue(FunctionFrame* frame, size_t index, instr::Instr* capturedInstr, instr::Type* type)
					: Instr(InstrUpValueTag)
					, capturedInstr(capturedInstr)
					, frame(frame)
					, index(index)
					, type(type){
				}
			};

			struct InstrCopy: public Instr{
				Instr* value;

				InstrCopy(Instr* value)
					: Instr(InstrCopyTag)
					, value(value){
				}
			};

			struct LocalVar;
			
			struct InstrReadLocal: public Instr{
				LocalVar* localVar;

				InstrReadLocal(LocalVar* localVar)
					: Instr(InstrReadLocalTag)
					, localVar(localVar){
				}
			};

			struct InstrThisParam: public Instr{
				ir::Class* class_;

				InstrThisParam(ir::Class* class_)
					: Instr(InstrThisParamTag)
					, class_(class_){
				}
			};

			struct ConstructorRecord{
				ConstructorRecord* next;
				ir::ClassConstructor* constructor;
				size_t argsCount;
				#pragma warning(push)
				#pragma warning(disable:4200)
				Instr* args[];
				#pragma warning(pop)

				ConstructorRecord(ir::ClassConstructor* constructor, size_t argsCount)
					: next(nullptr)
					, constructor(constructor)
					, argsCount(argsCount){
				}
			};

			struct InstrNewObject: public Instr{
				ir::Class* class_;
				ConstructorRecord* constructorRecord;

				InstrNewObject(ir::Class* class_, ConstructorRecord* constructorRecord)
					: Instr(InstrNewObjectTag)
					, class_(class_)
					, constructorRecord(constructorRecord){
				}
			};

			struct InstrContinueConstructor: public Instr{
				ConstructorRecord* constructorRecord;
				FunctionFrame* closureFrame;
				bool leaf;

				InstrContinueConstructor(ConstructorRecord* constructorRecord, FunctionFrame* closureFrame, bool leaf)
					: Instr(InstrContinueConstructorTag)
					, constructorRecord(constructorRecord)
					, closureFrame(closureFrame)
					, leaf(leaf){
				}
			};

			struct InstrFinalizeConstructor: public Instr{
				ir::Class* class_;
				Instr* object;

				InstrFinalizeConstructor(ir::Class* class_, Instr* object)
					: Instr(InstrFinalizeConstructorTag)
					, class_(class_)
					, object(object){
				}
			};

			struct InstrUnwrapMaybe: public Instr{
				Instr* value;
				Type* valueType;

				InstrUnwrapMaybe(Type* valueType, Instr* value)
					: Instr(InstrUnwrapMaybeTag)
					, valueType(valueType)
					, value(value){
				}
			};

			struct InstrBrMaybe: public Instr{
				Type* valueType;
				Instr* value;
				BasicBlock* bbNull;
				BasicBlock* bbValue;

				InstrBrMaybe(Type* valueType, Instr* value, BasicBlock* bbNull, BasicBlock* bbValue)
					: Instr(InstrBrMaybeTag)
					, valueType(valueType)
					, value(value)
					, bbNull(bbNull)
					, bbValue(bbValue){
				}
			};

			struct InstrPHI: public Instr{
				size_t inedgesCount;

				struct Inedge{
					BasicBlock* bb;
					Instr* value;

					Inedge(){
					}

					Inedge(BasicBlock* bb, Instr* value)
						: bb(bb)
						, value(value){
					}
				};
				#pragma warning(push)
				#pragma warning(disable:4200)
				Inedge inedges[];
				#pragma warning(pop)

				InstrPHI(size_t inedgesCount)
					: Instr(InstrPHITag)
					, inedgesCount(inedgesCount){
				}
			};

			struct InstrCallBuiltinFunction: public Instr{
				BuiltinFunction::Template* function;
				ArrayRef<instr::Type*> typeArgs;			
				
				Instr* object;
				size_t argsCount;
				#pragma warning(push)
				#pragma warning(disable:4200)
				Instr* args[];
				#pragma warning(pop)

				InstrCallBuiltinFunction(BuiltinFunction::Template* function, size_t argsCount)
					: Instr(InstrCallBuiltinFunctionTag)
					, argsCount(argsCount)
					, function(function){
				}
			};

			struct InstrCallClassMethod: public Instr{
				ir::ClassMethod* method;
				Instr* object;
				
				size_t argsCount;
				#pragma warning(push)
				#pragma warning(disable:4200)
				Instr* args[];
				#pragma warning(pop)

				InstrCallClassMethod(ir::ClassMethod* method, Instr* object, size_t argsCount)
					: Instr(InstrCallClassMethodTag)
					, argsCount(argsCount)
					, method(method)
					, object(object){
				}
			};

			struct InstrCallInterfaceMethod: public Instr{
				ir::InterfaceMethod* method;
				Instr* object;
				
				size_t argsCount;
				#pragma warning(push)
				#pragma warning(disable:4200)
				Instr* args[];
				#pragma warning(pop)

				InstrCallInterfaceMethod(ir::InterfaceMethod* method, Instr* object, size_t argsCount)
					: Instr(InstrCallInterfaceMethodTag)
					, argsCount(argsCount)
					, method(method)
					, object(object){
				}
			};

			struct InstrCallEnumConstructor: public Instr{
				ir::EnumConstructor* constructor;
				
				size_t argsCount;
				#pragma warning(push)
				#pragma warning(disable:4200)
				Instr* args[];
				#pragma warning(pop)

				InstrCallEnumConstructor(ir::EnumConstructor* constructor, size_t argsCount)
					: Instr(InstrCallEnumConstructorTag)
					, argsCount(argsCount)
					, constructor(constructor){
				}
			};

			struct InstrCallGlobal: public Instr{
				ir::GlobalFunction* function;
				
				size_t argsCount;
				#pragma warning(push)
				#pragma warning(disable:4200)
				Instr* args[];
				#pragma warning(pop)

				InstrCallGlobal(ir::GlobalFunction* function, size_t argsCount)
					: Instr(InstrCallGlobalTag)
					, argsCount(argsCount)
					, function(function){
				}
			};

			class FunctionFrame;
			
			struct LocalVar{
				LocalVar* next;
				u32 index;
				FunctionFrame* owner;
				instr::Type* type;
				StringRef name;
				SrcSpan where;
							
				LocalVar(FunctionFrame* owner, u32 index, const SrcSpan& where, const StringRef& name, instr::Type* type)
					: owner(owner)
					, index(index)
					, next(nullptr)
					, type(type)
					, name(name)
					, where(where){
				}
			};

			struct InstrIndexClassField: public Instr{
				Instr* object;
				ir::ClassField* field;

				InstrIndexClassField(Instr* object, ir::ClassField* field)
					: Instr(InstrIndexClassFieldTag)
					, object(object)
					, field(field){
				}
			};

			struct InstrWriteLocal: public Instr{
				LocalVar* localVar;
				Instr* value;

				InstrWriteLocal(LocalVar* localVar, Instr* value)
					: Instr(InstrWriteLocalTag)
					, localVar(localVar)
					, value(value){
				}
			};

			struct InstrWriteClassField: public Instr{
				ir::ClassField* field;
				Instr* object;
				Instr* value;

				InstrWriteClassField(ir::ClassField* field, Instr* object, Instr* value)
					: Instr(InstrWriteClassFieldTag)
					, field(field)
					, object(object)
					, value(value){
				}
			};

		
			struct InstrCompare: public Instr{
				enum Operator{
					EQ,
					NE,
					LT,
					GT,
					LE,
					GE
				} op;
				Instr* lhs;
				Instr* rhs;
				CompareClass* compareClass;
				
				InstrCompare(Operator op, Instr* lhs, Instr* rhs, CompareClass* compareClass)
					: Instr(InstrCompareTag)
					, op(op)
					, lhs(lhs)
					, rhs(rhs)
					, compareClass(compareClass){
				}
			};

			//TODO:: move to separate module
			class BasicBlock;

			class AssemblyPrinter{
			public:
				AssemblyPrinter(MemoryPoolSlice* tempPool, MemoryPoolSlice* hostPool);

				void printBasicBlock(instr::BasicBlock* basicBlock);
				void printInstr(instr::Instr* instr);

				ArrayRef<StringRef> getListing();

				u32 getBBName(BasicBlock* block);
				u32 getInstrName(Instr* instr);
			private:
				StringRef instrToName(u8* buffer, instr::Instr* instr);
				StringRef bbToName(u8* buffer, instr::BasicBlock* bb);
				StringRef coerceToName(instr::Coercion* coercion);
				StringRef compareToName(instr::CompareClass* compareClass);
				StringRef compareOpToName(instr::InstrCompare::Operator op);

				template<class F, class T>
				StringRef makeParamsString(F& func, const ArrayRef<T>& params);

				MemoryPoolSlice* tempPool;
				MemoryPoolSlice* hostPool;
				ArrayList<StringRef> lines;
				size_t processedBlocks;
				ArrayList<BasicBlock*> blocks;
				PtrHash<Instr, u32> instrNames;
				PtrHash<BasicBlock, u32> blockNames;
			};
		}
	}
}