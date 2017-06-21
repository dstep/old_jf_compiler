#pragma once
#include <Support/IntrusiveList.h>
#include "Instr.h"

namespace jf{
	namespace ir{
		namespace instr{
			class BasicBlock{
			public:
				BasicBlock* next;

				BasicBlock()
					: terminator(nullptr)
					, next(nullptr){
				}

				void append(Instr* instr){
					if ( terminator ){
						return;
					}

					if ( Instr::IsTerminator(instr) ){
						terminator = instr;
					}else{
						instrs = instrs.append(instr);
					}
				}

				bool hasTerminator(){
					return terminator != nullptr;
				}

				Instr* getTerminator(){
					return terminator;
				}

				Instr* getFirstInstr(){
					return instrs.first;
				}
			private:
				List<Instr> instrs;
				Instr* terminator;
			};
		}
	}
}