#include <IR/Instr/Instr.h>
#include <IR/Instr/BasicBlock.h>
#include <Support/Container/ArrayList.h>
#include <Support/IntrusiveList.h>
#include <Support/Match.h>
#include <Support/Twine.h>
#include <Support/Format.h>
#include <IR/Instr/FunctionFrame.h>

namespace jf{
	namespace ir{
		namespace instr{
			InstrNoValue InstrNoValue::Instance;

			bool Instr::IsTerminator(Instr* instr){
				match(instr)
					rule(InstrBadCode, _)
						return true;
					erule
					rule(InstrReturn, _)
						return true;
					erule
					rule(InstrCondBranch, _)
						return true;
					erule
					rule(InstrUncondBranch, _)
						return true;
					erule
					rule(InstrBrMaybe, _)
						return true;
					erule
					defrule(_)
						return false;
					erule
				ematch
			}

			AssemblyPrinter::AssemblyPrinter(MemoryPoolSlice* tempPool, MemoryPoolSlice* hostPool)
				: tempPool(tempPool)
				, hostPool(hostPool)
				, lines(tempPool)
				, instrNames(tempPool)
				, blockNames(tempPool)
				, blocks(tempPool)
				, processedBlocks(0){
			}

			StringRef AssemblyPrinter::instrToName(u8* buffer, instr::Instr* instr){
				if ( instr == instr::InstrNoValue::Get() ){
					return "*";
				}
				size_t n = ::sprintf((char*)buffer, "%u", getInstrName(instr));
				return StringRef(buffer, n);
			}

			StringRef AssemblyPrinter::bbToName(u8* buffer, instr::BasicBlock* bb){
				size_t n = ::sprintf((char*)buffer, "label_%u", getBBName(bb));
				return StringRef(buffer, n);
			}

			StringRef AssemblyPrinter::coerceToName(instr::Coercion* coercion){
				
				if ( !coercion ){
					return "none";
				}else if ( coercion->tag == CoercionLaterTag ){
					return "@later";
				}else{
					match(coercion)
						rule(instr::CoercionConstDouble, coercion)
							return ("const_double " + format::real(coercion->value).str()).toString(tempPool);
						erule
						rule(instr::CoercionConstFloat, coercion)
							return ("const_float " + format::real(coercion->value).str()).toString(tempPool);
						erule
						rule(instr::CoercionConstInt, coercion)
							return ("const_int " + format::integer(coercion->value).str()).toString(tempPool);
						erule
						rule(instr::CoercionConstString, coercion)
							return ("const_string '" + coercion->value->value + "'").toString(tempPool);
						erule
						rule(instr::CoercionId, coercion)
							return "id";
						erule
						rule(instr::CoercionFloatToDouble, coercion)
							return "float_to_double";
						erule
						rule(instr::CoercionIntToDouble, coercion)
							return "int_to_double";
						erule
						rule(instr::CoercionToBaseClass, coercion)
							return ("to_base_class " + coercion->from->getName() + ", " + coercion->to->getName()).toString(tempPool);
						erule
						rule(instr::CoercionNullToMaybe, coercion)
							return "null_to_maybe";
						erule
						rule(instr::CoercionLiftMaybe, coercion)
							return ("lift_maybe_" + coerceToName(coercion->valueCoercion)).toString(tempPool);
						erule
						rule(instr::CoercionWrapMaybe, coercion)
							return ("wrap_maybe_" + coerceToName(coercion->valueCoercion)).toString(tempPool);
						erule
						nodefrule
					ematch
				}
			}

			StringRef AssemblyPrinter::compareOpToName(instr::InstrCompare::Operator op){
				switch ( op ){
				case InstrCompare::EQ: return "==";
				case InstrCompare::NE: return "<>";
				case InstrCompare::GT: return ">";
				case InstrCompare::LT: return "<";
				case InstrCompare::GE: return ">=";
				case InstrCompare::LE: return "<=";
				default: unreachable;
				}
			}

			StringRef AssemblyPrinter::compareToName(instr::CompareClass* compareClass){
				match(compareClass)
					#define PrimCompare(t) rule(Compare##t, compareClass) \
						return #t; \
						erule 
					#include <IR/Instr/PrimCompare.inc>

					rule(CompareNumeric, compareClass)
						return "numeric";
					erule
					rule(CompareEnum, compareClass)
						return "enum";
					erule
					rule(CompareStruct, compareClass)
						return "struct";
					erule
					rule(CompareUnnamedStruct, compareClass)
						return "unnamed-struct";
					erule
					rule(CompareUnnamedEnum, compareClass)
						return "unnamed-enum";
					erule
				ematch
				return "???";
			}

			void AssemblyPrinter::printBasicBlock(instr::BasicBlock* basicBlock){
				u8 destBuffer[64];

				getBBName(basicBlock);

				while ( processedBlocks < blocks.getSize() ){
					instr::BasicBlock* basicBlock = blocks.get(processedBlocks++);
					lines.push((bbToName(destBuffer, basicBlock) + ":").toString(hostPool));
					
					iterate_list(instr, basicBlock->getFirstInstr()){
						printInstr(instr);
					}
					if ( !basicBlock->hasTerminator() ){
						lines.push("\tno terminator");
					}else{
						printInstr(basicBlock->getTerminator());
					}
				}
			}

			template<class F, class T>
			StringRef AssemblyPrinter::makeParamsString(F& func, const ArrayRef<T>& params){
				ArrayList<StringRef> parts(tempPool);
				iterate_array(param, params){
					parts.push(func(param.get()));
				}

				size_t totalLength = 0;
				iterate_enumerable(part, parts){
					totalLength += part.get().getLength();
				}
				u8* buffer = (u8*)tempPool->allocate(totalLength);
				StringRef string = StringRef(buffer, totalLength);
				iterate_enumerable(part, parts){
					::memcpy(buffer, part.get().getData(), part.get().getLength());
					buffer += part.get().getLength();
				}

				return string;
			}

			void AssemblyPrinter::printInstr(instr::Instr* instr){
				u8 destBuffer[64];
				u8 src1[64];
				u8 src2[64];
				u8 bb1[64];
				u8 bb2[64];

				#define emmit(a) lines.push(("\t" + instrToName(destBuffer, instr) + " <- " + a).toString(hostPool))
				#define src1(t) instrToName(src1, t)
				#define src2(t) instrToName(src2, t)
				#define bb1(t) bbToName(bb1, t)
				#define bb2(t) bbToName(bb2, t)

				match(instr)
					rule(InstrBadCode, instr)
						emmit("badcode " + instr->message);
					erule
					rule(InstrConstUnit, instr)
						emmit("const_unit");
					erule
					rule(InstrConstTrue, instr)
						emmit("const_true");
					erule
					rule(InstrConstFalse, instr)
						emmit("const_false");
					erule
					rule(InstrReturn, instr)
						emmit("return " + src1(instr->value));
					erule
					rule(InstrParam, instr)
						emmit("param " + instr->param->getName());
					erule
					rule(InstrUncondBranch, instr)
						emmit("br " + bb1(instr->bb));
					erule
					rule(InstrCondBranch, instr)
						emmit("condbr " + src1(instr->condition) + ", " + bb1(instr->bbTrue) + ", " + bb2(instr->bbFalse));
					erule
					rule(InstrCoercion, instr)
						if ( instr->coercion == instr::CoercionId::Get() ){
							instrNames.set(instr, getInstrName(instr->value));
						}else if ( instr->value == instr::InstrNoValue::Get() ) {
							emmit(coerceToName(instr->coercion));
						}else{
							emmit("coerce " + src1(instr->value) + ", " + coerceToName(instr->coercion));
						}	
					erule
					rule(InstrAdd, instr)
						emmit("add " + src1(instr->lhs) + ", " + src2(instr->rhs));	
					erule
					rule(InstrCopy, instr)
						emmit("copy " + src1(instr->value));	
					erule
					rule(InstrReadLocal, instr)
						emmit("readlocal " + instr->localVar->name);
					erule
					rule(InstrWriteLocal, instr)
						emmit("writelocal " + instr->localVar->name + ", " + src2(instr->value));
					erule
					rule(InstrWriteClassField, instr)
						emmit("writeclassfield " + instr->field->getOwner()->getName() + "::" + instr->field->getName() + ", " + src1(instr->object) + ", " + src2(instr->value));
					erule

					
					rule(InstrCallClassMethod, instr)
						emmit("callclassmethod " + instr->method->getOwner()->getName() + "::" + instr->method->getName() + ", " 
							 + src1(instr->object) 
							 + makeParamsString([&](instr::Instr* instr){
									return (", " + src2(instr)).toString(tempPool);
								}, MakeArrayRef(instr->args, instr->argsCount)));
					erule
					rule(InstrCallEnumConstructor, instr)
						emmit("callenumcons " + instr->constructor->getName() 
							 + makeParamsString([&](instr::Instr* instr){
									return (", " + src2(instr)).toString(tempPool);
								}, MakeArrayRef(instr->args, instr->argsCount)));
					erule
					rule(InstrCallGlobal, instr)
						emmit("callglobal " + instr->function->getName() 
							 + makeParamsString([&](instr::Instr* instr){
									return (", " + src2(instr)).toString(tempPool);
								}, MakeArrayRef(instr->args, instr->argsCount)));
					erule
					rule(InstrPHI, instr)						
						emmit("phi " + makeParamsString([&](instr::InstrPHI::Inedge& inedge){
								return ("(" + bb1(inedge.bb) + ":" + src1(inedge.value) + ")").toString(tempPool);
							}, MakeArrayRef(instr->inedges, instr->inedgesCount)));
					erule
					rule(InstrIndexClassField, instr)
						emmit("indexclassfield " + instr->field->getOwner()->getName() + "::" + instr->field->getName() + ", " + src1(instr->object));
					erule
					rule(InstrCompare, instr)
						emmit("compare " + compareToName(instr->compareClass) + ", " + compareOpToName(instr->op) + ", " + src1(instr->lhs) + ", " + src2(instr->rhs));
					erule
					defrule(_)
						emmit("???unknowninst???");
					erule
				ematch
			}

			u32 AssemblyPrinter::getBBName(BasicBlock* block){
				u32& name = blockNames.getOrInsert(block);
				if ( !name ){
					name = (u32)blockNames.getSize();
					blocks.push(block);
				}
				return name;
			}

			u32 AssemblyPrinter::getInstrName(Instr* instr){
				u32& name = instrNames.getOrInsert(instr);
				if ( !name ){
					name = (u32)instrNames.getSize();
				}
				return name;
			}

			ArrayRef<StringRef> AssemblyPrinter::getListing(){
				return lines.slice(hostPool);
			}
		}
	}
}