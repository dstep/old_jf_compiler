#include <IR/Compiler/MatchTreeCompiler.h>


#define TheHostPool parent->hostPool
#define TheTempPool parent->tempPool
#define TheInstrCompiler this
#define TheDiagnostic parent->stream
#include <IR/Compiler/InstrCompilerCommon.h>

namespace jf{
	namespace ir{
		namespace compiler{
			enum ResponsibleCompiler{
				NoCompiler,
				NameCompiler,
				NormalFormCompiler,
				ReferenceCompiler
			};

			ResponsibleCompiler GetResponsibleCompiler(ast::Expr* ast){
				switch ( ast->tag ){
				case ast::ExprIDTag: 
				case ast::ExprSubscriptTag:
				case ast::ExprInstanceTag:
					return NameCompiler;

				case ast::ExprIfTag: 
					return ReferenceCompiler;

				case ast::ExprCoerceTag:
				case ast::ExprBinOpTag:
				case ast::ExprUnOpTag: 
				case ast::ExprNumberTag: 
				case ast::ExprStringTag: 
				case ast::ExprNullTag: 
				case ast::ExprTrueTag: 
				case ast::ExprFalseTag: 
				case ast::ExprUnitTag: 
				case ast::ExprCallTag:
				case ast::ExprNewTag:
					return  NormalFormCompiler;

				default: return NoCompiler;
				}
			}


			namespace ControlFlow{
				
				Value concat(Value first, Value second){
					if ( first == NeverReaches ){
						return NeverReaches;
					}
					if ( second == NeverReaches ){
						if ( first == AlwaysPass ){
							return NeverReaches;
						}else{
							return AlwaysTerminate;
						}
					}

					if ( first == AlwaysTerminate || second == AlwaysTerminate ){
						return AlwaysTerminate;
					}
					if ( first == MayTerminate || second == MayTerminate ){
						return MayTerminate;
					}
					return AlwaysPass;
				}

				Value merge(Value left, Value right){
					if ( left == NeverReaches ){
						return right;
					}
					if ( right == NeverReaches ){
						return left;
					}
					if ( left == AlwaysPass && right == AlwaysPass ){
						return AlwaysPass;
					}
					if ( left == AlwaysTerminate && right == AlwaysTerminate ){
						return AlwaysTerminate;
					}
					return MayTerminate;
				}
			}

			InstrCompiler::InstrCompiler(ModuleInstrCompiler* parent)
				: parent(parent)
				, scope(nullptr, parent->tempPool)
				, coercionLater(parent->tempPool)
				, numericTypes(parent->tempPool)
				, thisObject(nullptr)
				, currentFrame(nullptr)
				, typeVarIndex(0){
			}

			InstrCompilerState InstrCompiler::beginFunctionFrame(){
				InstrCompilerState state;
				state.block = currentBasicBlock;
				state.frame = currentFrame;

				currentFrame = alloc(instr::FunctionFrame)(currentFrame);

				LexicalScopeState* lexicalScopeState = temp(LexicalScopeState)();

				scope.pushState(lexicalScopeState);

				currentBasicBlock = makeBasicBlock();
				currentFrame->setEntry(currentBasicBlock);

				thisObjectFrameValue = Value();

				return state;			
			}

			instr::FunctionFrame* InstrCompiler::endFunctionFrame(const SrcSpan& where, const InstrCompilerState& state){				
				if ( currentBasicBlock && !currentBasicBlock->hasTerminator() ){
					if ( currentFrame->getExpectedReturn()->tag != instr::TypeUnitTag ){
						report_error(where, NoReturnFromFunctionReturningNonUnit, );
						emmit(InstrBadCode, SrcSpan::Undefined(), "No return value");
					}else{
						emmit(InstrReturn, emmit(InstrConstUnit));
					}
				}

				instr::FunctionFrame* oldFrame = currentFrame;
				currentFrame = state.frame;
				currentBasicBlock = state.block;
				
				scope.popState();

				return oldFrame;
			}

			void InstrCompiler::useThisObject(ir::Class* class_){
				thisObject = class_;
				instr::Type* type = alloc(instr::TypeClass)(class_);
				thisObjectValue = Value(emmit(InstrThisParam, class_), type);
				thisObjectFrame = currentFrame;
				thisObjectFrameValue = thisObjectValue;
			}

			Value InstrCompiler::getThisObject(){
				if ( !thisObject ){
					return Value();
				}
				if ( !thisObjectFrameValue.producer ){
					thisObjectFrameValue.producer = currentFrame->addUpValue(parent->hostPool, thisObjectFrame, thisObjectValue.producer, thisObjectValue.type);
					thisObjectFrameValue.type = thisObjectValue.type;
				}
				return thisObjectFrameValue;
			}

			void InstrCompiler::useConstructorSemantic(ir::Class* fromClass, ir::Class* targetClass){
				currentFrame->setConstructorSemantic(fromClass, targetClass);
				useThisObject(targetClass);
			}

			void InstrCompiler::useSignature(FunctionSignature* signature){
				currentFrame->setExpectedReturn(parent->buildType(signature->getReturnType()));

				size_t n = signature->getParamsCount();
				for ( size_t i = 0; i < n; i++ ){					
					auto param = signature->getParam(i);
					auto instr = emmit(InstrParam, currentFrame, param, parent->buildType(param->getType()));

					scope.add(param->getName(), LexicalScopeReference(ScopeReferenceKind::FunctionParam, instr));
				}
			}

			void InstrCompiler::run(parser::ast::Stmt* ast){
				compileSequence(ast);
			}

			void InstrCompiler::compileSequence(parser::ast::Stmt* ast){
				iterate_list(stmt, ast){
					if ( scope.shouldReportUnreachableCode() ){
						report_error(ast->where, UnreachableCode, );
					}
					compileStmt(stmt);
				}
			}

			void InstrCompiler::compileStmt(parser::ast::Stmt* ast){
				match(ast)
					rule(ast::StmtVar, ast)
						instr::Type* type = nullptr;
						if ( ast->type ){
							type = parent->buildType(ast->type);
						}

						Value value;
						if ( ast->expr ){
							if ( type ){
								value = compileCoerceNormalForm(ast->expr, type);
							}else{
								value = compileNormalForm(ast->expr, nullptr);
								type = makeValidStorageType(value.type);
								value = makeCoercion(ast->expr->where, value, type);
							}
						}

						iterate_list(name, ast->names){
							instr::LocalVar* localVar = currentFrame->addLocalVariable
								(
									parent->hostPool, 
									name->where,
									name->id,
									type
								);
							if ( value.producer ){
								emmit(InstrWriteLocal, localVar, value.producer);
							}
							scope.add(name->id, LexicalScopeReference(ScopeReferenceKind::LocalVariable, localVar));
						}
					erule
					rule(ast::StmtAssign, ast)
						ArrayList<Reference> references(parent->tempPool);
						ArrayList<Value> values(parent->tempPool);

						iterate_list(lhs, ast->lhs){
							references.push(compileNameForm(lhs->expr, nullptr));
						}

						size_t i = 0;
						iterate_list(rhs, ast->rhs){
							if ( i <= references.getSize() ){
								instr::Type* type = getReferenceType(references.get(i));
								if ( type ){
									values.push(compileCoerceNormalForm(rhs->expr, type));
								}else{
									values.push(compileNormalForm(rhs->expr, nullptr));
								}
							}else{
								values.push(compileNormalForm(rhs->expr, nullptr));
							}
							i++;
						}

						i = 0;
						iterate_list(lhs, ast->lhs){
							if ( i < values.getSize() ){
								writeReference(lhs->expr->where, references.get(i), values.get(i));
							}
							i++;
						}

						if ( references.getSize() != values.getSize() ){
							report_error(ast->where, AssignLHSAndRHSCountMismatch, .parameter<Integer>("lhs", references.getSize()).parameter<Integer>("rhs", values.getSize()));
						}
					erule
					rule(ast::StmtEval, ast)
						instr::Type* hintType = nullptr;
						switch ( ast->kind ){
						case ast::StmtEval::Naked:{
							hintType = instr::TypeUnit::Get();
						}break;
						case ast::StmtEval::Return:{
							hintType = currentFrame->getExpectedReturn();
						}break;
						}
						
						switch ( ast->kind ){
						case ast::StmtEval::Naked:{
							Value value = compileReferenceForm(ast->expr, hintType);
							if ( value.type != instr::TypeUnit::Get() && value.type != instr::TypeError::Get() ){
								report_error(ast->where, NakedExprWithValueType, );
							}
						}break;
						case ast::StmtEval::Eval:{
							compileReferenceForm(ast->expr, hintType);
						}break;
						case ast::StmtEval::Raise:{
							assert(false);
							emmit(InstrBadCode, ast->where, "Not implemented");
						}break;
						case ast::StmtEval::Return:{
							Value value = compileCoerceNormalForm(ast->expr, hintType);
							emmit(InstrReturn, value.producer);
						}break;
						}
					erule
					rule(ast::StmtBlock, ast)
						LexicalScopeState state;
						scope.pushState(&state);
						compileSequence(ast->stmts);
						scope.popState();
						scope.concatState(&state);
					erule
					rule(ast::StmtMatch, ast)						
						ArrayList<Value> values(parent->tempPool);

						ArrayList< Pair<MatchNodeSuccess*, ast::Stmt*> > branches(parent->tempPool);

						iterate_list(value, ast->values){
							values.push(compileNormalForm(value->expr, nullptr));
						}

						MatchTreeCompiler compiler(this, parent->tempPool, parent->tempPool);
						iterate_enumerable(value, values){
							compiler.addValue(value.get().type)->value = value.get();
						}

						iterate_list(case_, ast->cases){
							compiler.addCase(case_->where, case_->patterns);
							iterate_list(branch, case_->branches){
								if ( !branch->guard ){
									branches.push(MakePair(compiler.addDefaultAction(branch->where), branch->action));
								}else{
									branches.push(MakePair(compiler.addGuardedAction(branch->where, branch->guard), branch->action));
								}
							}
						}

						MatchNode* root = compiler.getRootNode();
						compileMatchTreeNode(root);

						MatchNodeFail* failNode = compiler.getFailNode();

						LexicalScopeState unifiedState;

						iterate_enumerable(branch, branches){
							MatchNodeSuccess* node = branch.get().first;
							ast::Stmt* stmt = branch.get().second;
							if ( !node->incomings ){
								report_error(node->where, UnreachableMatchBranch, );
							}else{
								size_t incomingsCount = countList(node->incomings.first);
								if ( incomingsCount == 1 ){
									currentBasicBlock = node->incomings.first->bb;

									LexicalScopeState state;
									scope.pushState(&state);
									auto value = node->incomings.first->values;
									for ( auto remember = node->remember; remember; remember = remember->prev, value = value->next ){
										LexicalTemporary* temporary = alloc(LexicalTemporary)(remember->where, remember->name, remember->value->type, value->value.producer, currentFrame);
										scope.add(remember->name, LexicalScopeReference(ScopeReferenceKind::Temporary, temporary));
									}
									compileSequence(stmt);
									scope.popState();
									scope.mergeStates(&unifiedState, &state);
								}else{
									instr::BasicBlock* bb = makeBasicBlock();
									iterate_list(incoming, node->incomings.first){
										currentBasicBlock = incoming->bb;
										emmit(InstrUncondBranch, bb);
									}
									currentBasicBlock = bb;
																		
									LexicalScopeState state;
									scope.pushState(&state);
									for ( auto remember = node->remember; remember; remember = remember->prev ){
										instr::InstrPHI* phi = new(parent->hostPool->allocateDynamic(sizeof(instr::InstrPHI), sizeof(instr::InstrPHI::Inedge), incomingsCount))instr::InstrPHI(incomingsCount);
										size_t index = 0;
										iterate_list(incoming, node->incomings.first){
											phi->inedges[index++] = instr::InstrPHI::Inedge(incoming->bb, incoming->values->value.producer);
											incoming->values = incoming->values->next;
										}
										addInstr(phi);
										LexicalTemporary* temporary = alloc(LexicalTemporary)(remember->where, remember->name, remember->value->type, phi, currentFrame);
										scope.add(remember->name, LexicalScopeReference(ScopeReferenceKind::Temporary, temporary));
									}
									compileSequence(stmt);
									scope.popState();
									scope.mergeStates(&unifiedState, &state);
								}

								addMatchFailNodeIncoming(failNode);
							}
						}

						if ( failNode->incomings.first ){
							if ( failNode->incomings.first->next ){
								instr::BasicBlock* bb = makeBasicBlock();
								iterate_list(incoming, failNode->incomings.first){
									currentBasicBlock = incoming->bb;
									emmit(InstrUncondBranch, bb);
								}
								currentBasicBlock = bb;
							}else{
								currentBasicBlock = failNode->incomings.first->bb;
							}
						}

						scope.concatState(&unifiedState);
					erule
					rule(ast::StmtRepeat, ast)						
						instr::BasicBlock* bodyBB = makeBasicBlock();
						instr::BasicBlock* exitBB = nullptr;

						instr::BasicBlock* entryBB = bodyBB;

						emmit(InstrUncondBranch, bodyBB);

						currentBasicBlock = bodyBB;
						LexicalScopeState loopState;
						scope.pushState(&loopState);
						compileSequence(ast->stmts);
						scope.popState();

						scope.concatState(&loopState);

						compileControlFlow(ast->cond, &exitBB, &bodyBB);

						if ( currentBasicBlock ){
							emmit(InstrUncondBranch, entryBB);
						}
						
						currentBasicBlock = exitBB;
					erule
					rule(ast::StmtWhile, ast)
						instr::BasicBlock* condBB = makeBasicBlock();
						instr::BasicBlock* bodyBB = nullptr;
						instr::BasicBlock* exitBB = nullptr;

						emmit(InstrUncondBranch, condBB);

						currentBasicBlock = condBB;
						compileControlFlow(ast->cond, &bodyBB, &exitBB);
						
						currentBasicBlock = bodyBB;
						LexicalScopeState loopState;
						scope.pushState(&loopState);
						compileSequence(ast->stmts);
						scope.popState();
						if ( currentBasicBlock ){
							emmit(InstrUncondBranch, condBB);
						}

						LexicalScopeState notEnterLoopState;
						scope.pushState(&notEnterLoopState);
						scope.popState();

						currentBasicBlock = exitBB;

						if ( bodyBB && exitBB ){
							scope.mergeStates(&loopState, &notEnterLoopState);
							scope.concatState(&loopState);
						}else if ( bodyBB ){
							scope.concatState(&loopState);
						}else if ( exitBB ){
							scope.concatState(&notEnterLoopState);
						}
					erule
					rule(ast::StmtConstruct, ast)
						if ( currentFrame->isConstructor() ){
							ir::Class* base = currentFrame->getConstructorBase();
							ir::Class* target = currentFrame->getConstructorTarget();
							ast::ConstructorStringPart* consString = ast->consString;
							ast::ConstructorStringPart* lastConsString = ast->consString;
							List<instr::ConstructorRecord> records;		
							
							ir::Class* currentClass = target->getBaseClass();
							iterate_list(cons, ast->consString){
								if ( currentClass == base ){
									report_error(cons->where, TooDeepConstructor, .parameter("class", currentClass->makeSymbol()));
									break;	
								}
								ir::ClassConstructor* constructor = findLocalConstructor(ast->where, currentClass, cons->name);
								ir::Class* class_ = constructor->getBaseClass();
								currentClass = class_;
								size_t paramsCount = countList(consString->params);
								records = records.prepend(new(parent->hostPool->allocateDynamic(sizeof(instr::ConstructorRecord), sizeof(instr::Instr*), paramsCount))instr::ConstructorRecord(constructor, paramsCount));
								lastConsString = consString;
								consString = consString->prev;	
							}

							if ( currentClass != base ){
								if ( currentClass && base ){
									report_error(ast->where, ConstructedClassMismatch, 
										.parameter("class", currentClass->makeSymbol())
										.parameter("base", base->makeSymbol()));
								}else if ( currentClass ){
									report_error(ast->where, ConstructedClassMismatch, 
										.parameter("class", currentClass->makeSymbol()));
								}else{
									report_error(ast->where, ConstructedClassMismatch, 
										.parameter("base", base->makeSymbol()));
								}
							}

							PtrHash<ir::ClassField, u32> usedNames(parent->tempPool);
							InstrCompilerState compilerState;

							bool leaf = target->getBaseClass() == nullptr;

							if ( !leaf ){
								compilerState = beginFunctionFrame();
							}

							iterate_list(assign, ast->pairs){								
								Value value = compileNormalForm(assign->value, nullptr);
								iterate_list(name, assign->names){									
									ir::ClassMember* member = target->getMembersMap().find(name->id);
									bool memberUsed = false;
									if ( member ){
										match(member)
											rule(ir::ClassField, member)
												if ( member->getOwner() == target ){ 
													Value coercedValue = makeCoercion(name->where, value, parent->buildType(member->getType()));
													emmit(InstrWriteClassField, member, getThisObject().producer, coercedValue.producer);
													usedNames.set(member, 1);
												}else{
													report_error(name->where, InitializedFieldNotBelongToClass, .parameter("field", member->makeReference()).parameter("class", target->makeSymbol()));
												}
												memberUsed = true;
											erule
										ematch
									}
									if ( !memberUsed ){
										report_error(name->where, NotClassField, .parameter<StringLiteral>("name", name->id));
									}
								}								
							}

							ir::Class* observedClass = target;
							iterate_array(field, observedClass->getFields()){
								if ( !usedNames.get(&field.get()) ){
									report_error(ast->where, FieldNotInitialized, .parameter("field", field.get().makeReference()));
								}
							}

							emmit(InstrFinalizeConstructor, target, getThisObject().producer);

							if ( !leaf ){
								emmit(InstrReturn, emmit(InstrConstUnit));
							}

							instr::FunctionFrame* closureFrame = leaf ? nullptr : endFunctionFrame(SrcSpan(ast->where.to(), ast->where.to()), compilerState);
						
							consString = lastConsString;
							instr::ConstructorRecord* record = records.first;
							while ( consString ){
								compileArguments(consString->where, record->args, consString->params, record->constructor->getSignature()->getParams());
								record = record->next;
								consString = consString->next;
							}

							emmit(InstrContinueConstructor, records, closureFrame, leaf);
						}else{
							report_error(ast->where, ConstructStmtInNonConstructor, );
						}
					erule
					rule(ast::StmtIf, ast)
						instr::BasicBlock* ifTrue = nullptr;
						instr::BasicBlock* ifFalse = nullptr;

						compileControlFlow(ast->cond, &ifTrue, &ifFalse);

						instr::BasicBlock* joinBB = nullptr;

						LexicalScopeState trueState, falseState;
						scope.pushState(&trueState);
						currentBasicBlock = ifTrue;
						compileSequence(ast->then);
						scope.popState();
						if ( currentBasicBlock && !currentBasicBlock->hasTerminator() ){
							if ( !joinBB ){
								joinBB = makeBasicBlock();
							}
							emmit(InstrUncondBranch, joinBB);
						}

						currentBasicBlock = ifFalse;
						scope.pushState(&falseState);
						compileSequence(ast->else_);
						scope.popState();
						if ( currentBasicBlock && !currentBasicBlock->hasTerminator() ){
							if ( !joinBB ){
								joinBB = makeBasicBlock();
							}
							emmit(InstrUncondBranch, joinBB);
						}

						currentBasicBlock = joinBB;

						if ( ifTrue && ifFalse ){
							scope.mergeStates(&trueState, &falseState);
							scope.concatState(&trueState);
						}else if ( ifTrue ){
							scope.concatState(&trueState);
						}else if ( ifFalse ){
							scope.concatState(&falseState);
						}
					erule
					defrule(_)
						assert(false);
					erule
				ematch
			}

			void InstrCompiler::compileMatchTreeNode(MatchNode* node){
				match(node)
					rule(MatchNodeCondition, node)
						instr::BasicBlock* bbTrue = nullptr;
						instr::BasicBlock* bbFalse = nullptr;

						LexicalScopeState state;
						scope.pushState(&state);

						for ( auto remember = node->remember; remember; remember = remember->prev ){
							LexicalTemporary* temporary = alloc(LexicalTemporary)(remember->where, remember->name, remember->value->type, remember->value->value.producer, currentFrame);
							scope.add(remember->name, LexicalScopeReference(ScopeReferenceKind::Temporary, temporary));
						}

						compileControlFlow(node->expr, &bbTrue, &bbFalse);
						scope.popState();

						currentBasicBlock = bbTrue;
						compileMatchTreeNode(node->nodeTrue);

						currentBasicBlock = bbFalse;
						compileMatchTreeNode(node->nodeFalse);
					erule
					rule(MatchNodeMaybe, node)
						instr::BasicBlock* bbNull = makeBasicBlock();
						instr::BasicBlock* bbValue = makeBasicBlock();
						emmit(InstrBrMaybe, ((instr::TypeOptional*)node->value->type)->valueType, node->value->value.producer, bbNull, bbValue);
						currentBasicBlock = bbNull;
						compileMatchTreeNode(node->nodeNull);

						currentBasicBlock = bbValue;
						if ( node->valueValue ){
							instr::Instr* instr = emmit(InstrUnwrapMaybe, node->valueValue->type, node->value->value.producer);
							node->valueValue->value = Value(instr, node->valueValue->type);
						}
						compileMatchTreeNode(node->nodeValue);
					erule
					rule(MatchNodeFail, node)
						addMatchFailNodeIncoming(node);
					erule
					rule(MatchNodeSuccess, node)
						addMatchSuccessNodeIncoming(node);
					erule
				ematch
			}

			void InstrCompiler::addMatchSuccessNodeIncoming(MatchNodeSuccess* node){
				if ( currentBasicBlock && !currentBasicBlock->hasTerminator() ){
					List<MatchSuccessIncomingValue> values;
					for(auto remember = node->remember; remember; remember = remember->prev){
						values = values.append(temp(MatchSuccessIncomingValue)(remember->value->value));
					}
					node->incomings = node->incomings.append(temp(MatchSuccessIncoming)(currentBasicBlock, values));
					currentBasicBlock = nullptr;
				}
			}

			void InstrCompiler::addMatchFailNodeIncoming(MatchNodeFail* node){
				if ( currentBasicBlock && !currentBasicBlock->hasTerminator() ){
					node->incomings = node->incomings.append(temp(MatchFailNodeIncoming)(currentBasicBlock));
					currentBasicBlock = nullptr;
				}
			}

			Reference InstrCompiler::compileNameForm(parser::ast::Expr* ast, instr::Type* hintType){
				match(ast)
					rule(ast::ExprInstance, ast)
						Reference lhsReference = compileNameForm(ast->lhs, nullptr);
						switch ( lhsReference.kind ){
						case Reference::BuiltinFunction:{
							instr::BuiltinFunction::Template* function = (instr::BuiltinFunction::Template*)lhsReference.reference;
							if ( function->typeParams.getSize() == 0 ){
								report_error(ast->where, NotTemplateInstance, );
							}else{
								size_t argsCount = countList(ast->params);
								if ( function->typeParams.getSize() != argsCount ){
									report_error
										(
											ast->where, 
											TemplateArgumentCountMismatch, 
											.parameter<Integer>("expected", function->params.getSize())
											.parameter<Integer>("actual", argsCount)
										);
								}else{
									TemplateInstance* instance = new(TheHostPool->allocateDynamic(sizeof(TemplateInstance), sizeof(instr::Type*), argsCount))TemplateInstance(function);
									size_t index = 0;
									bool success = true;
									iterate_list(arg, ast->params){
										instr::Type* type = parent->buildType(arg->type);
										switch ( function->typeParams[index]->constraint ){
										case instr::TypeTemplateVar::Numeric:{
											if ( !type->isNumericClass() ){
												report_error
													(
														arg->type->where, 
														TemplateTypeNotNumeric,
														.parameter<PlainString>("type", instr::ShowType(TheTempPool, *TheTempPool, type))
													);
												success = false;
											}
										}break;
										case instr::TypeTemplateVar::Real:{
											if ( type != instr::TypeFloat::Get() && type != instr::TypeDouble::Get() ){
												report_error
													(
														arg->type->where, 
														TemplateTypeNotReal,
														.parameter<PlainString>("type", instr::ShowType(TheTempPool, *TheTempPool, type))
													);
												success = false;
											}
										}break;
										}
										instance->args[index] = type;
										index++;
									}
									if ( success ){
										return Reference(Reference::BuiltinInstance, instance, *lhsReference.value);
									}
								}
							}
						}break;
						default:{
							report_error(ast->where, NotTemplateInstance, );
						}break;
						}
						return Reference(Reference::None);
					erule
					rule(ast::ExprID, ast)
						auto lexicalReference = scope.find(ast->content);
						switch ( lexicalReference.kind ){
						case ScopeReferenceKind::None:{
							if ( thisObject ){
								if ( ast->content == "this" ){
									return Reference(Reference::Expression, getThisObject());
								}

								ir::ClassMember* member = thisObject->getMembersMap().find(ast->content);
								if ( member ){
									match(member)
										rule(ir::ClassMethod, method)
											return Reference(Reference::ClassMethod, method, getThisObject());
										erule
										rule(ir::ClassField, field)
											return Reference(Reference::ClassField, field, getThisObject()); 
										erule
									ematch
								}
							}

							auto builtin = instr::FindBuiltinFunction(ast->content);
							if ( builtin ){
								return Reference(Reference::BuiltinFunction, builtin);
							}

							auto name = parent->findName(ast->where, ast->content);
							switch ( name.first.kind ){
							case ExportKind::Class: return Reference(Reference::Class, name.first.reference);
							case ExportKind::Interface: return Reference(Reference::Interface, name.first.reference);
							case ExportKind::Enum: return Reference(Reference::Enum, name.first.reference);
							case ExportKind::Struct: return Reference(Reference::Struct, name.first.reference);
							case ExportKind::Function: return Reference(Reference::GlobalFunction, name.first.reference);
							case ExportKind::Variable: return Reference(Reference::GlobalVariable, name.first.reference);
							case ExportKind::Namespace: return Reference(Reference::Namespace, name.first.reference);
							case ExportKind::EnumConstructor: return Reference(Reference::EnumConstructor, name.first.reference);
							default:{
								report_error(ast->where, UnresolvedIdentifier, .parameter<StringLiteral>("name", ast->content));
								return Reference(Reference::None);
							}break;
							}							
						}break;
						case ScopeReferenceKind::FunctionParam:{
							instr::InstrParam* param = (instr::InstrParam*)lexicalReference.reference;
							if ( param->owner != currentFrame ){
								return Reference(Reference::UpValue, Value(currentFrame->addUpValue(parent->hostPool, param->owner, param, param->type), param->type));
							}else{
								return Reference(Reference::Expression, Value(param, param->type));
							}
						}break;
						case ScopeReferenceKind::Temporary:{
							LexicalTemporary* temporary = (LexicalTemporary*)lexicalReference.reference;
							if ( temporary->frame != currentFrame ){
								return Reference(Reference::UpValue, Value(currentFrame->addUpValue(parent->hostPool, temporary->frame, temporary->producer, temporary->type), temporary->type));
							}else{
								return Reference(Reference::Expression, Value(temporary->producer, temporary->type));
							}
						}break;
						case ScopeReferenceKind::LocalVariable:{
							return Reference(Reference::LocalVariable, lexicalReference.reference);
						}break;
						default: unreachable;
						}
					erule
					rule(ast::ExprSubscript, ast)
						Reference lhsReference = compileNameForm(ast->lhs, nullptr);
						switch ( lhsReference.kind ){
						case Reference::Namespace:{
							ir::Namespace* ns = (ir::Namespace*)lhsReference.reference;
							auto name = parent->findName(ast->where, ns, ast->id);
							
							switch ( name.first.kind ){
							case ExportKind::Class: return Reference(Reference::Class, name.first.reference);
							case ExportKind::Interface: return Reference(Reference::Interface, name.first.reference);
							case ExportKind::Enum: return Reference(Reference::Enum, name.first.reference);
							case ExportKind::Struct: return Reference(Reference::Struct, name.first.reference);
							case ExportKind::Function: return Reference(Reference::GlobalFunction, name.first.reference);
							case ExportKind::Variable: return Reference(Reference::GlobalVariable, name.first.reference);
							case ExportKind::EnumConstructor: return Reference(Reference::EnumConstructor, name.first.reference);
							default:{
								report_error(ast->where, UnresolvedIdentifier, .parameter<StringLiteral>("name", ast->id));
								return Reference(Reference::None);
							}break;
							}
						}break;
						case Reference::Enum:{
							ir::Enum* enum_ = (ir::Enum*)lhsReference.reference;
							ir::EnumConstructor* constructor = enum_->getConstructorMap()->get(ast->id);
							if ( constructor ){
								return Reference(Reference::EnumConstructor, constructor);
							}else{
								report_error(ast->where, NoSuchEnumConstructor, .parameter<StringLiteral>("name", ast->id));
								return Reference(Reference::None);
							}
						}break;
						case Reference::Expression:{
							Value lhsValue = *lhsReference.value;
							return typeFieldLookup(ast->where, lhsValue, ast->id, hintType);
						}break;
						default:{
							Value lhsValue = makeReferenceValueFromName(ast->lhs->where, lhsReference);
							return typeFieldLookup(ast->where, lhsValue, ast->id, hintType);
						}break;
						}
					erule
					defrule(_)
						return Reference(Reference::Expression, compileReferenceForm(ast, hintType));
					erule
				ematch
			}

			instr::Type* InstrCompiler::getReferenceType(Reference reference){
				switch ( reference.kind ){
				case Reference::LocalVariable: return ((instr::LocalVar*)reference.reference)->type;
				case Reference::ClassField: return parent->buildType(((ir::ClassField*)reference.reference)->getType());
				default: return nullptr;
				}
			}

			void InstrCompiler::writeReference(const SrcSpan& where, Reference reference, const Value& value){
				switch ( reference.kind ){
				case Reference::LocalVariable:{
					instr::LocalVar* localVar = (instr::LocalVar*)reference.reference;
					currentFrame->addCapturedVariable(parent->hostPool, localVar);
					emmit(InstrWriteLocal, localVar, value.producer);
				}break;
				case Reference::ClassField:{
					emmit(InstrWriteClassField, (ir::ClassField*)reference.reference, reference.value->producer, value.producer);
				}break;
				default:{
				}break;
				}
			}

			Value InstrCompiler::makeReferenceValueFromName(const SrcSpan& where, Reference nameForm){
				switch ( nameForm.kind ){
				case Reference::LocalVariable:{
					instr::LocalVar* localVar = (instr::LocalVar*)nameForm.reference;
					currentFrame->addCapturedVariable(parent->hostPool, localVar);
					return Value(emmit(InstrReadLocal, localVar), localVar->type);
				}break;
				case Reference::EnumConstructor:{
					ir::EnumConstructor* constructor = (ir::EnumConstructor*)nameForm.reference;
					if ( constructor->getParams().getSize() == 0 ){
						return Value(emmit(InstrCallEnumConstructor, constructor, 0), alloc(instr::TypeEnum)(constructor->getOwner()));
					}else{
						report_error(where, EnumConstructorAsValue, .parameter<StringLiteral>("name", constructor->getName()));
						return Value(emmit(InstrBadCode, where, "Not Referencable object used"), instr::TypeUndef::Get());
					}
				}break;
				case Reference::UpValue:{
					return *nameForm.value;
				}break;
				case Reference::Expression:{
					return *nameForm.value;
				}break;
				case Reference::ClassField:{
					ir::ClassField* field = (ir::ClassField*)nameForm.reference;
					return Value(emmit(InstrIndexClassField, nameForm.value->producer, field), parent->buildType(field->getType()));
				}break;
				default:{
					report_error(where, NotAReferencableObject, );
					return Value(emmit(InstrBadCode, where, "Not Referencable object used"), instr::TypeUndef::Get());
				}break;
				}
			}

			Reference InstrCompiler::typeFieldLookup(const SrcSpan& where, const Value& value, const StringRef& name, instr::Type* hintType){
				instr::Type* valueType = value.type->getRepr();

				match(valueType)
					rule(instr::TypeInterface, valueType)
						ir::Interface* interface = valueType->interface;
						ir::InterfaceMethod* method = interface->getMethodMap().find(name);
						if ( !method ){
							report_error
								(
									where, 
									NoInterfaceMethod, 
									.parameter<StringLiteral>("name", name)
									.parameter("reference", ir::ExportName(ir::ExportKind::Interface, interface).makeSymbol(interface->getOwner()))
								);
							return Reference(Reference::None);
						}else{
							return Reference(Reference::InterfaceMethod, method, value);
						}
					erule
					rule(instr::TypeClass, valueType)
						ir::Class* class_ = valueType->class_;
						ir::ClassMember* member = class_->getMembersMap().find(name);
						if ( !member ){
							report_error
								(
									where, 
									NoClassMember, 
									.parameter<StringLiteral>("name", name)
									.parameter("reference", ir::ExportName(ir::ExportKind::Class, class_).makeSymbol(class_->getOwner()))
								);
							return Reference(Reference::None);
						}else{
							match(member)
								rule(ir::ClassMethod, member)
									return Reference(Reference::ClassMethod, member, value);
								erule
								rule(ir::ClassField, member)
									return Reference(Reference::ClassField, member, value);
								erule
								nodefrule
							ematch
						}
					erule
					rule(instr::TypeBytes, type)
						instr::BuiltinFunction::Template* function = instr::FindPropertyBytes(name);
						if ( !function ){
							report_error
								(
									where, 
									NoBytesMember, 
									.parameter<StringLiteral>("name", name)
								);
							return Reference(Reference::None);
						}else{
							return Reference(Reference::BuiltinFunction, function, value);
						}
					erule
					rule(instr::TypeArray, type)
						instr::BuiltinFunction::Template* function = instr::FindPropertyArray(name);
						if ( !function ){
							report_error
								(
									where, 
									NoArrayMember, 
									.parameter<StringLiteral>("name", name)
								);
							return Reference(Reference::None);
						}else{
							return Reference(Reference::BuiltinFunction, function, value);
						}
					erule
					defrule(_)
						report_error
								(
									where, 
									NoSuchField, 
									.parameter<StringLiteral>("name", name)
								);
						return Reference(Reference::None);
					erule
				ematch
			}

			Value InstrCompiler::compileReferenceForm(parser::ast::Expr* ast, instr::Type* hintType){
				if ( GetResponsibleCompiler(ast) == NameCompiler ){
					Reference nameForm = compileNameForm(ast, hintType);
					return makeReferenceValueFromName(ast->where, nameForm);
				}else if ( GetResponsibleCompiler(ast) == NormalFormCompiler ){
					return compileNormalForm(ast, hintType);
				}else{
					match(ast)					
						rule(ast::ExprIf, ast)
							instr::BasicBlock* ifTrue = nullptr;
							instr::BasicBlock* ifFalse = nullptr;
							compileControlFlow(ast->cond, &ifTrue, &ifFalse);

							Value trueValue, falseValue;
							
							currentBasicBlock = ifTrue;
							trueValue = compileReferenceForm(ast->then, hintType);
							ifTrue = currentBasicBlock;
							
							currentBasicBlock = ifFalse;
							falseValue = compileReferenceForm(ast->else_, hintType);
							ifFalse = currentBasicBlock;

							instr::Type* type = mergeTypes(ast->where, trueValue.type, falseValue.type);

							currentBasicBlock = ifTrue;
							trueValue = makeCoercion(ast->then->where, trueValue, type);

							currentBasicBlock = ifFalse;
							falseValue = makeCoercion(ast->else_->where, falseValue, type);

							if ( ifTrue && ifFalse && !ifTrue->hasTerminator() && !ifFalse->hasTerminator() ){
								if ( type ){
									instr::BasicBlock* joinBB = makeBasicBlock();

									currentBasicBlock = ifTrue;
									emmit(InstrUncondBranch, joinBB);

									currentBasicBlock = ifFalse;
									emmit(InstrUncondBranch, joinBB);

									currentBasicBlock = joinBB;

									instr::InstrPHI* phi = new(parent->hostPool->allocateDynamic(sizeof(instr::InstrPHI), sizeof(instr::InstrPHI::Inedge), 2))instr::InstrPHI(2);
									phi->inedges[0] = instr::InstrPHI::Inedge(ifTrue, trueValue.producer);									
									phi->inedges[1] = instr::InstrPHI::Inedge(ifFalse, falseValue.producer);
									addInstr(phi);

									return Value(phi, type);
								}else{
									return Value(emmit(InstrBadCode, ast->where, "No unification for If"), instr::TypeUndef::Get());
								}								
							}else{
								if ( !ifTrue || ifTrue->hasTerminator() ){
									currentBasicBlock = ifFalse;
									return falseValue;
								}else{
									currentBasicBlock = ifTrue;
									return trueValue;
								}
							}
						erule
						defrule(_)
							return Value(emmit(InstrBadCode, ast->where, "Not implemented"), instr::TypeUndef::Get());
						erule
					ematch
				}
			}

			void InstrCompiler::compileControlFlow(parser::ast::Expr* ast, instr::BasicBlock** ifTrue, instr::BasicBlock** ifFalse){
				match(ast)
					rule(ast::ExprTrue, ast)
						if ( *ifTrue ){
							emmit(InstrUncondBranch, *ifTrue);
						}else{
							*ifTrue = currentBasicBlock;
						}
						return;
					erule
					rule(ast::ExprFalse, ast)
						if ( *ifFalse ){
							emmit(InstrUncondBranch, *ifFalse);
						}else{
							*ifFalse = currentBasicBlock;
						}
						return;
					erule
					rule(ast::ExprBinOp, ast)
						if ( ast->id == ast::ExprBinOp::Or ){
							instr::BasicBlock* ifFirstFail = nullptr;
							compileControlFlow(ast->lhs, ifTrue, &ifFirstFail);
							if ( ifFirstFail ){
								currentBasicBlock = ifFirstFail;
								compileControlFlow(ast->rhs, ifTrue, ifFalse);
							}else{
								currentBasicBlock = nullptr;
								instr::BasicBlock* ifTrue = nullptr;
								instr::BasicBlock* ifFalse = nullptr;
								compileControlFlow(ast->rhs, &ifTrue, &ifFalse);
							}
							return;
						}else if ( ast->id == ast::ExprBinOp::And ){
							instr::BasicBlock* ifFirstSucceed = nullptr;
							compileControlFlow(ast->lhs, &ifFirstSucceed, ifFalse);
							if ( ifFirstSucceed ){
								currentBasicBlock = ifFirstSucceed;
								compileControlFlow(ast->rhs, ifTrue, ifFalse);
							}else{
								currentBasicBlock = nullptr;
								instr::BasicBlock* ifTrue = nullptr;
								instr::BasicBlock* ifFalse = nullptr;
								compileControlFlow(ast->rhs, &ifTrue, &ifFalse);
							}
							return;
						}
					erule
					rule(ast::ExprUnOp, ast)
						if ( ast->id == ast::ExprUnOp::Not ){
							compileControlFlow(ast->operand, ifFalse, ifTrue);
						}
						return;
					erule
				ematch

				Value condValue = compileCoerceNormalForm(ast, instr::TypeBool::Get());
				if ( !*ifTrue ){
					*ifTrue = makeBasicBlock();
				}
				if ( !*ifFalse ){
					*ifFalse = makeBasicBlock();
				}
				emmit(InstrCondBranch, condValue.producer, *ifTrue, *ifFalse);
			}

			Value InstrCompiler::compileCoerceNormalForm(parser::ast::Expr* ast, instr::Type* type){
				return makeCoercion(ast->where, compileNormalForm(ast, type), type);
			}

			Value InstrCompiler::compileNormalForm(parser::ast::Expr* ast, instr::Type* hintType){
				if ( GetResponsibleCompiler(ast) == NameCompiler || GetResponsibleCompiler(ast) == ReferenceCompiler ){
					Value referenceForm = compileReferenceForm(ast, hintType);
					if ( isTypeShouldBeCopied(referenceForm.type) ){
						return Value(emmit(InstrCopy, referenceForm.producer), referenceForm.type);
					}else{
						return referenceForm;
					}
				}else if ( GetResponsibleCompiler(ast) == NormalFormCompiler ){
					match(ast)
						rule(ast::ExprTrue, ast)
							return Value(emmit(InstrConstTrue), instr::TypeBool::Get());
						erule
						rule(ast::ExprFalse, ast)
							return Value(emmit(InstrConstFalse), instr::TypeBool::Get());
						erule
						rule(ast::ExprUnit, ast)
							return Value(emmit(InstrConstUnit), instr::TypeUnit::Get());
						erule
						rule(ast::ExprNull, ast)
							return Value(instr::InstrNoValue::Get(), instr::TypeNull::Get());
						erule
						rule(ast::ExprNumber, ast)
							return Value(instr::InstrNoValue::Get(), alloc(instr::TypeNumber)(ast->where, ast->content));
						erule
						rule(ast::ExprString, ast)
							return Value(instr::InstrNoValue::Get(), alloc(instr::TypeStringLiteral)(ast->content));
						erule
						rule(ast::ExprCoerce, ast)
							return compileCoerceNormalForm(ast->expr, parent->buildType(ast->type));
						erule
						rule(ast::ExprNew, ast)
							auto qid = ast->id;
							auto constructorResolve = findConstructor(qid);
							if ( constructorResolve.first && constructorResolve.second ){
								ast::ConstructorStringPart* consString = ast->consString;
								ast::ConstructorStringPart* lastConsString = consString;
								List<instr::ConstructorRecord> records;								
								ir::Class* currentClass = constructorResolve.first;
								while ( consString ){
									if ( !currentClass ){
										report_error(consString->where, AlreadyConstructed, );
										return Value(emmit(InstrBadCode, ast->where, "no constructor"), instr::TypeUndef::Get());
									}
									ir::ClassConstructor* constructor = consString->prev ? findLocalConstructor(consString->where, currentClass, consString->name) : constructorResolve.second;
									if ( !constructor ){
										return Value(emmit(InstrBadCode, ast->where, "no constructor"), instr::TypeUndef::Get());
									}
									ir::Class* class_ = constructor->getBaseClass();
									currentClass = class_;
									size_t paramsCount = countList(consString->params);
									records = records.prepend(new(parent->hostPool->allocateDynamic(sizeof(instr::ConstructorRecord), sizeof(instr::Instr*), paramsCount))instr::ConstructorRecord(constructor, paramsCount));
									lastConsString = consString;
									consString = consString->prev;									
								}
								if ( currentClass ){
									report_error
										(
											ast->where, 
											NotFullConstructor,
											.parameter("class", ExportName(ExportKind::Class, currentClass).makeSymbol(currentClass->getOwner()))
										);
									return Value(emmit(InstrBadCode, ast->where, "not full constructor"), instr::TypeUndef::Get());
								}
								instr::InstrNewObject* newObject = alloc(instr::InstrNewObject)(constructorResolve.first, records.first);
								consString = lastConsString;
								instr::ConstructorRecord* record = records.first;
								while ( consString ){
									compileArguments(consString->where, record->args, consString->params, record->constructor->getSignature()->getParams());
									record = record->next;
									consString = consString->next;
								}
								addInstr(newObject);
								return Value(newObject, alloc(instr::TypeClass)(constructorResolve.first));
							}else{
								return Value(emmit(InstrBadCode, ast->where, "no constructor"), instr::TypeUndef::Get());
							}
						erule
						rule(ast::ExprCall, ast)
							Reference callee = compileNameForm(ast->callee, nullptr);
							size_t argsCount = countList(ast->params);
							switch ( callee.kind ){
							case Reference::None:{
								return Value(emmit(InstrBadCode, ast->where, "No Reference To Call"), instr::TypeUndef::Get());
							}break;
							case Reference::EnumConstructor:{
								ir::EnumConstructor* constructor = (ir::EnumConstructor*)callee.reference;
								instr::InstrCallEnumConstructor* callInstr =
									new
										(
											parent->hostPool->allocateDynamic
												(
													sizeof(instr::InstrCallEnumConstructor), 
													sizeof(instr::Instr*), 
													constructor->getParams().getSize()
												)
										)
										instr::InstrCallEnumConstructor(constructor, constructor->getParams().getSize());
								compileArguments(ast->where, callInstr->args, ast->params, constructor->getParams());
								addInstr(callInstr);
								return Value(callInstr, alloc(instr::TypeEnum)(constructor->getOwner()));
							}break;
							case Reference::BuiltinFunction:{
								return makeCallBuiltin(ast->where, (instr::BuiltinFunction::Template*)callee.reference, nullptr, *callee.value, ast->params, hintType);
							}break;
							case Reference::BuiltinInstance:{
								TemplateInstance* instance = (TemplateInstance*)callee.reference;
								return makeCallBuiltin(ast->where, instance->function, instance->args, *callee.value, ast->params, hintType);
							}break;
							case Reference::GlobalFunction:{
								ir::GlobalFunction* function = (ir::GlobalFunction*)callee.reference;
								instr::InstrCallGlobal* callInstr =
									new
										(
											parent->hostPool->allocateDynamic
												(
													sizeof(instr::InstrCallGlobal), 
													sizeof(instr::Instr*), 
													function->getSignature()->getParamsCount()
												)
										)
										instr::InstrCallGlobal(function, function->getSignature()->getParamsCount());
								compileArguments(ast->where, callInstr->args, ast->params, function->getSignature()->getParams());
								addInstr(callInstr);
								return Value(callInstr, parent->buildType(function->getSignature()->getReturnType()));
							}break;
							case Reference::InterfaceMethod:{
								ir::InterfaceMethod* method = (ir::InterfaceMethod*)callee.reference;
								instr::InstrCallInterfaceMethod* callInstr = 
									new
										(
											parent->hostPool->allocateDynamic
												(
													sizeof(instr::InstrCallInterfaceMethod), 
													sizeof(instr::Instr*), 
													method->getSignature()->getParamsCount()
												)
										)
										instr::InstrCallInterfaceMethod(method, callee.value->producer, method->getSignature()->getParamsCount());
								compileArguments(ast->where, callInstr->args, ast->params, method->getSignature()->getParams());
								addInstr(callInstr);
								return Value(callInstr, parent->buildType(method->getSignature()->getReturnType()));
							}break;
							case Reference::ClassMethod:{
								ir::ClassMethod* method = (ir::ClassMethod*)callee.reference;
								instr::InstrCallClassMethod* callInstr = 
									new
										(
											parent->hostPool->allocateDynamic
												(
													sizeof(instr::InstrCallClassMethod), 
													sizeof(instr::Instr*), 
													method->getSignature()->getParamsCount()
												)
										)
										instr::InstrCallClassMethod(method, callee.value->producer, method->getSignature()->getParamsCount());
								compileArguments(ast->where, callInstr->args, ast->params, method->getSignature()->getParams());
								addInstr(callInstr);
								return Value(callInstr, parent->buildType(method->getSignature()->getReturnType()));
							}break;
							default:{
								//TODO::
								unreachable;
							}break;
							}

							
						erule
						rule(ast::ExprUnOp, ast)
							switch ( ast->id ){
							case ast::ExprUnOp::Not:{
								ast::ExprList list(ast->operand);
								return makeCallBuiltin(ast->where, &instr::BuiltinFunction::Not, nullptr, Value(), &list, hintType);
							}break;
							case ast::ExprUnOp::Negate:{
								ast::ExprList list(ast->operand);
								return makeCallBuiltin(ast->where, &instr::BuiltinFunction::Negate, nullptr, Value(), &list, hintType);
							}break;
							default:{
								unreachable;
							}break;
							}
						erule
						rule(ast::ExprBinOp, ast)
							switch ( ast->id ){
							case ast::ExprBinOp::EQ:
							case ast::ExprBinOp::NE:
							case ast::ExprBinOp::LT:
							case ast::ExprBinOp::GT:
							case ast::ExprBinOp::LE:
							case ast::ExprBinOp::GE:{
								Value lhsValue = compileNormalForm(ast->lhs, nullptr);
								Value rhsValue = compileNormalForm(ast->rhs, nullptr);

								instr::InstrCompare::Operator op;
								switch ( ast->id ){
								case ast::ExprBinOp::EQ: op = instr::InstrCompare::EQ; break;
								case ast::ExprBinOp::NE: op = instr::InstrCompare::NE; break;
								case ast::ExprBinOp::LT: op = instr::InstrCompare::LT; break;
								case ast::ExprBinOp::GT: op = instr::InstrCompare::GT; break;
								case ast::ExprBinOp::LE: op = instr::InstrCompare::LE; break;
								case ast::ExprBinOp::GE: op = instr::InstrCompare::GE; break;
								default: unreachable;
								}
								
								return makeComparison(ast->where, op, lhsValue, rhsValue);
							}break;								
							case ast::ExprBinOp::And:
							case ast::ExprBinOp::Or:{
								Value lhsValue = compileCoerceNormalForm(ast->lhs, instr::TypeBool::Get());

								instr::BasicBlock* currentBlock = currentBasicBlock;

								instr::BasicBlock* ifTrue = makeBasicBlock();
								instr::BasicBlock* ifFalse = makeBasicBlock();
								emmit(InstrCondBranch, lhsValue.producer, ifTrue, ifFalse);
								if ( ast->id == ast::ExprBinOp::Or ){
									currentBasicBlock = ifFalse;
									Value rhsValue = compileCoerceNormalForm(ast->rhs, instr::TypeBool::Get());
									emmit(InstrUncondBranch, ifTrue);

									currentBasicBlock = ifTrue;

									instr::InstrPHI* phi = new(parent->hostPool->allocateDynamic(sizeof(instr::InstrPHI), sizeof(instr::InstrPHI::Inedge), 2))instr::InstrPHI(2);
									phi->inedges[0] = instr::InstrPHI::Inedge(currentBlock, lhsValue.producer);									
									phi->inedges[1] = instr::InstrPHI::Inedge(ifFalse, rhsValue.producer);
									addInstr(phi);

									return Value(phi, instr::TypeBool::Get());
								}else{
									currentBasicBlock = ifTrue;
									Value rhsValue = compileCoerceNormalForm(ast->rhs, instr::TypeBool::Get());
									emmit(InstrUncondBranch, ifTrue);

									currentBasicBlock = ifFalse;
									instr::InstrPHI* phi = new(parent->hostPool->allocateDynamic(sizeof(instr::InstrPHI), sizeof(instr::InstrPHI::Inedge), 2))instr::InstrPHI(2);
									phi->inedges[0] = instr::InstrPHI::Inedge(currentBlock, lhsValue.producer);									
									phi->inedges[1] = instr::InstrPHI::Inedge(ifTrue, rhsValue.producer);
									addInstr(phi);

									return Value(phi, instr::TypeBool::Get());
								}
							}break;
							case ast::ExprBinOp::Concat:{
								ast::ExprList first(ast->lhs);
								ast::ExprList second(ast->rhs);
								first.next = &second;
								return makeCallBuiltin(ast->where, &instr::BuiltinFunction::Concat, nullptr, Value(), &first, hintType);
							}break;
							case ast::ExprBinOp::Plus:
							case ast::ExprBinOp::Minus:
							case ast::ExprBinOp::Div:
							case ast::ExprBinOp::Mult:
							case ast::ExprBinOp::Rem:{
								ast::ExprList first(ast->lhs);
								ast::ExprList second(ast->rhs);
								first.next = &second;

								instr::BuiltinFunction::Template* function;
								switch ( ast->id ){
								case ast::ExprBinOp::Plus: function = &instr::BuiltinFunction::Plus; break;
								case ast::ExprBinOp::Minus: function = &instr::BuiltinFunction::Minus; break;
								case ast::ExprBinOp::Div: function = &instr::BuiltinFunction::Divide; break;
								case ast::ExprBinOp::Mult: function = &instr::BuiltinFunction::Multiply; break;
								case ast::ExprBinOp::Rem: function = &instr::BuiltinFunction::Remainder; break;
								default: unreachable;
								}

								return makeCallBuiltin(ast->where, function, nullptr, Value(), &first, hintType);
							}break;
							default:
								unreachable;
							}
						erule
						nodefrule;
					ematch
				}else{
					return Value(emmit(InstrBadCode, ast->where, "Not implemented"), instr::TypeUndef::Get());
				}
			}

			Value InstrCompiler::makeCoercion(const SrcSpan& where, const Value& from, instr::Type* to){
				if ( parent->areTypesEqual(from.type, to) ){
					return Value(from.producer, to);
				}else{
					instr::Coercion* coercion = parent->findCoercion(from.type, to);
					if ( !coercion ){
						report_error
							(
								where,
								NoCoercion, 
								.parameter<PlainString>("from", instr::ShowType(parent->tempPool, *parent->tempPool, from.type))
								.parameter<PlainString>("to", instr::ShowType(parent->tempPool, *parent->tempPool, to))
							);
						return Value(emmit(InstrBadCode, where, "No Coercion"), to);
					}else if ( coercion == instr::CoercionId::Get() ){
						return Value(from.producer, to);
					}else{
						instr::InstrCoercion* instr = (instr::InstrCoercion*)emmit(InstrCoercion, from.producer, coercion);
						coercionLater.push(CoercionLater(where, instr, from.type, to));
						return Value(instr, to);
					}
				}
			}

			instr::Instr* InstrCompiler::addInstr(instr::Instr* instr){
				if ( currentBasicBlock ){
					currentBasicBlock->append(instr);
					instr->frameIndex = currentFrame->takeNextInstrIndex();
				}
				return instr;
			}

			Value InstrCompiler::makeCallBuiltin(const SrcSpan& where, instr::BuiltinFunction::Template* function, instr::Type** instance, Value thisObject, ast::ExprList* args, instr::Type* hintType){
				if ( !instance ){
					instance = (instr::Type**)TheHostPool->allocateArray(sizeof(instr::Type*), function->typeParams.getSize());
					for ( size_t i = 0; i < function->typeParams.getSize(); i++ ){
						instance[i] = nullptr;
					}
				}
				ArrayRef<instr::Type*> typeArgs(instance, function->typeParams.getSize());
				
				iterate_array(typeParam, function->typeParams){
					if ( !instance[typeParam.getIndex()] ){
						switch ( typeParam.get()->constraint ){
						case instr::TypeTemplateVar::Unconstrainted:{
							typeArgs.getRaw()[typeParam.getIndex()] = alloc(instr::TypeVar)(typeParam.get()->name, typeVarIndex++);		
						}break;
						case instr::TypeTemplateVar::Real:
						case instr::TypeTemplateVar::Numeric:{
							instr::TypeNumeric* type = makeNumericType();
							type->realConstraint = typeParam.get()->constraint == instr::TypeTemplateVar::Real;
							typeArgs.getRaw()[typeParam.getIndex()] = type;
						}break;
						}
					}
				}

				if ( function->thisObjectType && thisObject.producer ){
					thisObject = makeCoercion(where, thisObject, parent->specializeType(where, typeArgs, function->thisObjectType, thisObject.type));
				}

				instr::InstrCallBuiltinFunction* callInstr = new(TheHostPool->allocateDynamic(sizeof(instr::InstrCallBuiltinFunction), sizeof(instr::Instr*), function->params.getSize()))instr::InstrCallBuiltinFunction(function, function->params.getSize());
				callInstr->object = thisObject.producer;

				ArrayList<instr::Type*> specParams(TheTempPool);
				iterate_array(param, function->params){
					specParams.push(parent->specializeType(where, typeArgs, param.get(), nullptr));
				}
				
				compileArguments(where, callInstr->args, args, specParams.asFlatArray(TheTempPool));
				callInstr->typeArgs = typeArgs;
				addInstr(callInstr);
				
				Value result(callInstr, parent->specializeType(where, typeArgs, function->result, hintType));

				return result;
			}

			Value InstrCompiler::compileBuiltinArg(instr::Type* param, parser::ast::Expr* expr){
				return compileCoerceNormalForm(expr, param);
			}

			void InstrCompiler::compileArguments(const SrcSpan& where, instr::Instr** values, ast::ExprList* arguments, const ArrayRef<ir::Param>& params){
				size_t argsCount = countList(arguments);
				size_t paramsCount = params.getSize();
				if ( paramsCount != argsCount ){
					report_error(where, ArgumentsCountMismatch, .parameter<Integer>("actual", argsCount).parameter<Integer>("expected", paramsCount));
				}
				size_t index = 0;
				iterate_list(arg, arguments){
					if ( index < paramsCount ){
						Value argValue = compileCoerceNormalForm(arg->expr, parent->buildType(params.get(index).getType()));
						values[index] = argValue.producer;
					}else{
						compileNormalForm(arg->expr, nullptr);
					}
					index++;
				}
				while ( index < paramsCount ){
					values[index] = emmit(InstrBadCode, where, "Missing param");
					index++;
				}
			}

			void InstrCompiler::compileArguments(const SrcSpan& where, instr::Instr** values, parser::ast::ExprList* arguments, const ArrayRef<ir::instr::Type*>& params){
				//TODO:: merge with prev
				size_t argsCount = countList(arguments);
				size_t paramsCount = params.getSize();
				if ( paramsCount != argsCount ){
					report_error(where, ArgumentsCountMismatch, .parameter<Integer>("actual", argsCount).parameter<Integer>("expected", paramsCount));
				}
				size_t index = 0;
				iterate_list(arg, arguments){
					if ( index < paramsCount ){
						Value argValue = compileCoerceNormalForm(arg->expr, params.get(index));
						values[index] = argValue.producer;
					}else{
						compileNormalForm(arg->expr, nullptr);
					}
					index++;
				}
				while ( index < paramsCount ){
					values[index] = emmit(InstrBadCode, where, "Missing param");
					index++;
				}
			}

			ir::ClassConstructor* InstrCompiler::findLocalConstructor(const SrcSpan& where, ir::Class* class_, const StringRef& name){
				ir::ClassConstructor* constructor = class_->getOwnConstructorMap()->get(name);
				if ( !constructor ){
					report_error
						(
							where,
							NoClassConstructor,
							.parameter("class", class_->makeSymbol())
							.parameter<StringLiteral>("name", name)
						);
				}
				return constructor;
			}

			Pair<ir::Class*, ir::ClassConstructor*> InstrCompiler::findConstructor(parser::ast::QualID* qid){
				if ( qid->prev ){
					if ( qid->prev->prev ){
						if ( qid->prev->prev->prev ){
							report_error(qid->where, MalformedConstructorName, );
						}else{
							//namespace.class.constructor
							//TODO::
						}
					}else{
						//class.constructor
						//TODO::
					}
				}else{
					//constructor or class<.default_constructor>
					auto name = parent->findName(qid->where, qid->id);
					if ( name.first ){
						switch ( name.first.kind ){
						case ExportKind::Class:{
							ir::Class* class_ = (ir::Class*)name.first.reference;
							ir::ClassConstructor* constructor = class_->getAllConstructorsMap().find(qid->id);
							if ( constructor ){
								return Pair<ir::Class*, ir::ClassConstructor*>(class_, constructor);
							}else{
								report_error
									(
										qid->where, 
										ClassNotHaveDefaultConstructor, 
										.parameter("class", name.first.makeSymbol(name.second))
										.parameter<StringLiteral>("name", qid->id)
									);
								return Pair<ir::Class*, ir::ClassConstructor*>();
							}
						}break;
						}
					}
				}
				return Pair<ir::Class*, ir::ClassConstructor*>();
			}

			
			
			void InstrCompiler::satisfyLaters(){
				satisfyNumericTypes();
						
				iterate_enumerable(coerce, coercionLater){
					instr::Coercion* coercion = parent->findCoercion(coerce.get().left, coerce.get().right);
					coerce.get().coerceInstr->coercion = coercion;
					if ( !coercion ){
						report_error
							(
								coerce.get().where,
								NoCoercion, 
								.parameter<PlainString>("from", instr::ShowType(parent->tempPool, *parent->tempPool, coerce.get().left->getRepr()))
								.parameter<PlainString>("to", instr::ShowType(parent->tempPool, *parent->tempPool, coerce.get().right->getRepr()))
							);
					}
				}
			}

			Value InstrCompiler::makeComparison(const SrcSpan& where, instr::InstrCompare::Operator op, const Value& lhs, const Value& rhs){
				CompareTriple compareTriple = findCompareClass(where, lhs.type, rhs.type);
				if ( compareTriple.compareClass ){
					Value lhsValue = lhs;
					Value rhsValue = rhs;
					if ( compareTriple.leftType ){
						lhsValue = makeCoercion(where, lhsValue, compareTriple.leftType);
					}
					if ( compareTriple.rightType ){
						rhsValue = makeCoercion(where, rhsValue, compareTriple.rightType);
					}
					return Value(emmit(InstrCompare, op, lhsValue.producer, rhsValue.producer, compareTriple.compareClass), instr::TypeBool::Get());
				}else{
					report_error
						(	
							where, 
							NoComparison, 
							.parameter<PlainString>("lhs", instr::ShowType(parent->tempPool, *parent->tempPool, lhs.type))
							.parameter<PlainString>("rhs", instr::ShowType(parent->tempPool, *parent->tempPool, rhs.type))
						);
					return Value(emmit(InstrBadCode, where, "No comparison"), instr::TypeBool::Get());
				}
			}

			CompareTriple InstrCompiler::findCompareClass(const SrcSpan& where, instr::Type* left, instr::Type* right){
				left = left->getRepr();
				right = right->getRepr();

				if ( left == instr::TypeUndef::Get() || right == instr::TypeUndef::Get() ){
					return CompareTriple(instr::CompareUndef::Get());
				}

				if ( left->isNumericClass() && right->isNumericClass() ){
					instr::Type* type = makeNumericType();
					parent->addTypeEdge(left, type);
					parent->addTypeEdge(right, type);
					return CompareTriple(alloc(instr::CompareNumeric)(type), type);
				}

				if ( (left->tag == instr::TypeClassTag || left->tag == instr::TypeInterfaceTag)
					&& (right->tag == instr::TypeClassTag || right->tag == instr::TypeInterfaceTag) ){
					return instr::CompareObject::Get();
				}

				if ( (left->tag == instr::TypeStringTag || left->tag == instr::TypeStringLiteralTag)
					&& (right->tag == instr::TypeStringTag || right->tag == instr::TypeStringLiteralTag) ){
					return CompareTriple(instr::CompareString::Get(), instr::TypeString::Get());
				}

				match(left)
					rule(instr::TypeUnit, left)
						match(right)
							rule(instr::TypeUnit, right)
								return instr::CompareUnit::Get();
							erule
						ematch
					erule
					rule(instr::TypeBool, left)
						match(right)
							rule(instr::TypeBool, right)
								return instr::CompareBool::Get();
							erule
						ematch
					erule
					rule(instr::TypeBytes, left)
						match(right)
							rule(instr::TypeBytes, right)
								return instr::CompareBytes::Get();
							erule
						ematch
					erule
					rule(instr::TypeEnum, left)
						match(right)
							rule(instr::TypeEnum, right)
								if ( left->enum_ == right->enum_ ){
									return alloc(instr::CompareEnum)(left->enum_);
								}
							erule
						ematch
					erule
					rule(instr::TypeStruct, left)
						match(right)
							rule(instr::TypeStruct, right)
								if ( left->struct_ == right->struct_ ){
									return alloc(instr::CompareStruct)(left->struct_);
								}
							erule
						ematch
					erule
					rule(instr::TypeUnnamedStruct, left)
						match(right)
							rule(instr::TypeUnnamedStruct, right)
								if ( parent->areTypesEqual(left, right) ){
									return alloc(instr::CompareUnnamedStruct)(left);
								}
							erule
						ematch
					erule
					rule(instr::TypeUnnamedEnum, left)
						match(right)
							rule(instr::TypeUnnamedEnum, right)
								if ( parent->areTypesEqual(left, right) ){
									return alloc(instr::CompareUnnamedEnum)(left);
								}
							erule
						ematch
					erule
				ematch

				return nullptr;
			}

			instr::BasicBlock* InstrCompiler::makeBasicBlock(){
				instr::BasicBlock* bb = alloc(instr::BasicBlock)();
				currentFrame->addBasicBlock(bb);
				return bb;
			}
		}
	}
}