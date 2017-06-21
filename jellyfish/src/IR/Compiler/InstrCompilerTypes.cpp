#define TheHostPool parent->hostPool
#define TheTempPool parent->tempPool
#define TheInstrCompiler this
#define TheDiagnostic parent->stream
#include <IR/Compiler/InstrCompilerCommon.h>

namespace jf{
	namespace ir{
		namespace compiler{
			static ir::Class* findCommonBaseClass(ir::Class* left, ir::Class* right){
				while ( left->getLevel() > right->getLevel() ){
					left = left->getExtends()->getTargetClass();
				}
				while ( right->getLevel() > left->getLevel() ){
					right = right->getExtends()->getTargetClass();
				}
				while ( true ){
					if ( left == right ){
						return left;
					}
					if ( left->getLevel() == 0 ){
						return nullptr;
					}
					left = left->getExtends()->getTargetClass();
					right = right->getExtends()->getTargetClass();
				}
			}

			instr::Type* InstrCompiler::mergeTypes(const SrcSpan& where, instr::Type* left, instr::Type* right){
				left = left->getRepr();
				right = right->getRepr();

				if ( parent->areTypesEqual(left, right) ){
					return left;
				}else{
					if ( left->isNumericClass() && right->isNumericClass() ){
						return makeNumericType();
					}
					match(right)
						rule(instr::TypeNull, right)
							match(left)
								rule(instr::TypeOptional, left)									
									return left;
								erule
								defrule(_)
									return alloc(instr::TypeOptional)(left);
								erule
							ematch
						erule
						rule(instr::TypeOptional, right)
							match(left)
								rule(instr::TypeOptional, left)									
									instr::Type* valueType = mergeTypes(where, left->valueType, right->valueType);
									if ( valueType ){
										return alloc(instr::TypeOptional)(valueType);
									}else{
										return nullptr;
									}
								erule
								defrule(_)
									instr::Type* valueType = mergeTypes(where, left, right->valueType);
									if ( valueType ){
										return alloc(instr::TypeOptional)(valueType);
									}else{
										return nullptr;
									}
								erule
							ematch
						erule
					ematch
					match(left)
						rule(instr::TypeNull, left)									
							return alloc(instr::TypeOptional)(right);
						erule
						rule(instr::TypeOptional, left)
							instr::Type* valueType = mergeTypes(where, left->valueType, right);
							if ( valueType ){
								return alloc(instr::TypeOptional)(valueType);
							}else{
								return nullptr;
							}
						erule
						rule(instr::TypeClass, left)
							match(right)
								rule(instr::TypeClass, right)
									ir::Class* class_ = findCommonBaseClass(left->class_, right->class_);
									if ( class_ ){
										return alloc(instr::TypeClass)(class_);
									}else{
										return nullptr;
									}
								erule
							ematch
						erule
					ematch
					return nullptr;
				}
			}

			instr::Type* InstrCompiler::unifyTypes(const SrcSpan& where, instr::Type* left, instr::Type* right){
				left = left->getRepr();
				right = right->getRepr();

				if ( parent->areTypesEqual(left, right) ){
					return left;
				}else{				
					report_error(where, NotUnification, );
					return nullptr;
				}
			}

			bool InstrCompiler::isTypeShouldBeCopied(instr::Type* type){
				type = type->getRepr();

				match(type)
					rule(instr::TypeUnnamedStruct, _)
						return true;
					erule
					rule(instr::TypeStruct, _)
						return true;
					erule
					defrule(_)
						return false;
					erule
				ematch
			}

			instr::Type* InstrCompiler::mergeTypesArithOperator(instr::Type* left, instr::Type* right){
				left = left->getRepr();
				right = right->getRepr();

				if ( left->tag == instr::TypeDoubleTag || right->tag == instr::TypeDoubleTag ){
					return instr::TypeDouble::Get();
				}else if ( (left->tag == instr::TypeIntTag && right->tag == instr::TypeFloatTag)
					|| (left->tag == instr::TypeFloatTag && right->tag == instr::TypeIntTag) ){
					return instr::TypeDouble::Get();
				}else{
					instr::TypeNumeric* numericTy = makeNumericType();
					parent->addTypeEdge(left, numericTy);
					parent->addTypeEdge(right, numericTy);
					return numericTy;
				}
			}

			instr::TypeNumeric* InstrCompiler::makeNumericType(){
				instr::TypeNumeric* type = alloc(instr::TypeNumeric)();
				numericTypes.push(type);
				return type;
			}

			instr::Type* InstrCompiler::makeValidStorageType(instr::Type* type){
				type = type->getRepr();
				match(type)
					rule(instr::TypeNumber, _)
						return makeNumericType();
					erule
					rule(instr::TypeNumeric, _)
						return makeNumericType();
					erule
				ematch
				return type;
			}

			class NumericTypesSolver{
			public:
				NumericTypesSolver(MemoryPoolSlice* tempPool, MemoryPoolSlice* hostPool)
					: tempPool(tempPool)
					, hostPool(hostPool)
					, stack(tempPool)
					, order(tempPool)
					, index(1){
				}

				void visit(instr::TypeNumeric* type){
					instr::Type* repr = type->getRepr();
					match(type)
						rule(instr::TypeNumeric, type)
							if ( !type->index ){
								strongconnect(type);
							}
						erule
					ematch
				}

				void propagateInRank(){
					size_t n = order.getSize();
					for( size_t i = n - 1; i < n; i-- ){
						auto w = order.get(i);
						for ( auto outedge = w->outedges; outedge; outedge = outedge->nextOutedge ){
							auto v = outedge->inv;
							instr::Type* type = v->getRepr();
							match(type)
								rule(instr::TypeNumeric, type)
									type->inRank = instr::TypeNumberRank::MergeInRank(w->inRank, type->inRank);
								erule
							ematch
						}
					}
				}

				void propagateOutRank(){
					iterate_enumerable(type, order){
						auto w = type.get();
						for ( auto inedge = w->inedges; inedge; inedge = inedge->nextInedge ){
							auto v = inedge->outv;
							instr::Type* type = v->getRepr();
							match(type)
								rule(instr::TypeNumeric, type)
									type->outRank = instr::TypeNumberRank::MergeOutRank(w->outRank, type->outRank);
								erule
							ematch
						}
					}
				}

				void solve(){
					iterate_enumerable(type, order){
						auto w = type.get();		
						if ( w->realConstraint ){
							if ( w->inRank == instr::TypeNumberRank::Int ){
								w->inRank = instr::TypeNumberRank::Double;
							}
						}
					}
					propagateInRank();
					propagateOutRank();
					iterate_enumerable(type, order){
						auto w = type.get();						
						if ( w->outRank == instr::TypeNumberRank::Any && w->outRank != instr::TypeNumberRank::Constant && !w->outedges ){
							w->outRank = w->inRank;
						}						
					}
					propagateOutRank();
				}
			private:
				void strongconnect(instr::TypeNumeric* v){
					v->index = v->lowlink = index;
					index++;
					v->onstack = true;
					stack.push(v);

					for ( auto outedge = v->outedges; outedge; outedge = outedge->nextOutedge ){
						auto w = outedge->inv;
						instr::Type* type = w->getRepr();
						match(type)
							rule(instr::TypeNumeric, type)
								w = type;
								if ( !w->index ){
									strongconnect(w);
									v->lowlink = std::min(v->lowlink, w->lowlink);
								}else if ( w->onstack ){
									v->lowlink = std::min(v->lowlink, w->lowlink);
								}
							erule
						ematch						
					}

					if ( v->lowlink == v->index ){
						size_t begin = stack.getSize();
						do{
							begin--;
						}while(stack.get(begin) != v);

						size_t end = stack.getSize();
						for ( size_t i = begin + 1; i < end; i++ ){
							v = unify(v, stack.get(i));
						}

						while ( stack.getSize() > begin ){
							stack.get(stack.getSize() - 1)->onstack = false;
							stack.pop();
						}

						order.push(v);
					}
				}

				instr::TypeNumeric* unify(instr::TypeNumeric* left, instr::TypeNumeric* right){
					left->inRank = instr::TypeNumberRank::MergeInRank(left->inRank, right->inRank);
					left->outRank = instr::TypeNumberRank::MergeOutRank(left->outRank, right->outRank);
					right->parent = left;
					left->realConstraint |= right->realConstraint;
					return left;
				}
				
				u16 index;
				MemoryPoolSlice* tempPool;
				MemoryPoolSlice* hostPool;
				ArrayList<instr::TypeNumeric*> stack;
				ArrayList<instr::TypeNumeric*> order;
			};

			void InstrCompiler::satisfyNumericTypes(){
				NumericTypesSolver solver(parent->tempPool, parent->hostPool);
				iterate_enumerable(type, numericTypes){
					solver.visit(type.get());
				}
				solver.solve();
				iterate_enumerable(type, numericTypes){
					match((type.get()->getRepr()))
						rule(instr::TypeNumeric, type)
							if ( type->outRank != instr::TypeNumberRank::Any ){
								if ( type->realConstraint && type->outRank == instr::TypeNumberRank::Int ){
									type->parent = instr::TypeDouble::Get();
								}else{
									type->parent = instr::TypeNumberRank::GetTypeByRank(type->outRank);
								}
							}else{
								type->parent = instr::TypeDouble::Get();
							}

							if ( !type->parent ){
								type->parent = instr::TypeDouble::Get();
							}
						erule
					ematch	
				}
			}

		}
	}
}