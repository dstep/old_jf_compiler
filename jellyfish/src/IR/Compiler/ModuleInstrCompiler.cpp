#include <IR/Compiler/ModuleInstrCompiler.h>
#include <IR/Compiler/InstrCompiler.h>
#include <Support/Match.h>
#include <Support/Obligation.h>
namespace jf{
	namespace ir{
		namespace compiler{
			#define alloc(t) new(hostPool->allocate(sizeof(t)))t
			#define report_error(where, _code, params) stream->report \
							( \
								Subsystem("Compiler") \
									params \
									.at(where) \
									.type(DiagnosticType::Error) \
									.code("CompilerError." #_code) \
							) 

			ModuleInstrCompiler::ModuleInstrCompiler(IDiagnosticStream* stream, MemoryPoolSlice* tempPool, MemoryPoolSlice* hostPool)
				: stream(stream)
				, hostPool(hostPool)
				, tempPool(tempPool){
			}

			void ModuleInstrCompiler::run(Module* module){
				this->module = module;

				iterate_array(class_, module->classes){
					Class::ImplementMethodsMap implementMethodsMap;					
					class_.get()->getImplementsMap().traverseInorder([&](ir::Interface* interface,bool){							
							iterate_array(imethod_, interface->getMethods()){
								auto imethod = &imethod_.get();
								if ( !implementMethodsMap.has(imethod) ){
									auto member = class_.get()->getMembersMap().find(imethod->getName());
									bool overrideFound = false;								
									if ( member ){
										match(member)
											rule(ClassMethod, member)
												instr::Coercion* retValCoercion = nullptr;
												ArrayRef<instr::Coercion*> paramsCoercion;
												if ( makeOverride(imethod->getSignature(), imethod->makeReference(), member, retValCoercion, paramsCoercion) ){
													implementMethodsMap.add(hostPool, imethod, alloc(ir::ClassMethodImplements)(imethod, member, retValCoercion, paramsCoercion));
												}
												overrideFound = true;
											erule
										ematch
									}else{
										report_error(class_.get()->getSrcLoc(), NoInterfaceMethodImplementation, .parameter("method", imethod->makeReference()));
									}
								}
							}
						});
					class_.get()->setImplementMethodsMap(implementMethodsMap);

					iterate_array(method_, class_.get()->getMethods()){
						auto method = &method_.get();

						auto baseMethod = method->getBaseMethod();
						if ( baseMethod ){
							instr::Coercion* retValCoercion = nullptr;
							ArrayRef<instr::Coercion*> paramsCoercion;
							if ( makeOverride(baseMethod->getSignature(), baseMethod->makeReference(), method, retValCoercion, paramsCoercion) ){
								method->setOverride(alloc(ClassMethodOverride)(baseMethod, method, retValCoercion, paramsCoercion));
							}else{
								method->setOverride(nullptr);
							}
						}

						FunctionBody* body = method->getBody();
						match(body)
							rule(FunctionBodyCode, body)
								InstrCompiler compiler(this);
								InstrCompilerState state = compiler.beginFunctionFrame();
								compiler.useThisObject(class_.get());
								compiler.useSignature(method->getSignature());
								compiler.run(body->getAST());
								instr::FunctionFrame* frame = compiler.endFunctionFrame(SrcSpan(body->getSrcLoc().to(), body->getSrcLoc().to()), state);
								compiler.satisfyLaters();
								body->setFrame(frame);
							erule
						ematch
					}
					iterate_array(constructor_, class_.get()->getConstructors()){
						auto constructor = &constructor_.get();
						FunctionBody* body = constructor->getBody();
						match(body)
							rule(FunctionBodyCode, body)
								InstrCompiler compiler(this);
								InstrCompilerState state = compiler.beginFunctionFrame();								
								compiler.useConstructorSemantic(constructor->getBaseClass(), class_.get());
								compiler.useSignature(constructor->getSignature());
								compiler.run(body->getAST());
								instr::FunctionFrame* frame = compiler.endFunctionFrame(SrcSpan(body->getSrcLoc().to(), body->getSrcLoc().to()), state);
								compiler.satisfyLaters();
								body->setFrame(frame);
							erule
						ematch
					}
				}
				
				iterate_array(function, module->functions){
					auto& globalFunction = function.get();
					FunctionBody* body = globalFunction->getBody();
					match(body)
						rule(FunctionBodyCode, body)
							InstrCompiler compiler(this);
							InstrCompilerState state = compiler.beginFunctionFrame();
							compiler.useSignature(globalFunction->getSignature());
							compiler.run(body->getAST());
							instr::FunctionFrame* frame = compiler.endFunctionFrame(SrcSpan(body->getSrcLoc().to(), body->getSrcLoc().to()), state);
							compiler.satisfyLaters();
							body->setFrame(frame);
							/*
							if ( false ){
								MemoryPoolSlice stack(*tempPool);
								instr::AssemblyPrinter printer(&stack, &stack);
								printer.printBasicBlock(frame->getEntry());
								ArrayRef<StringRef> lines = printer.getListing();
								char filename[512];
								StringRef qid = module->qid->asString();
								StringRef name = globalFunction->getName();
								sprintf(filename, "dumps/dump_global_%.*s.%.*s.txt", qid.getLength(), qid.getData(), name.getLength(), name.getData());
								FILE* file = fopen(filename, "w");
								if ( file ){
									obligation([file](){ fclose(file); });

									iterate_array(line, lines){
										fprintf(file, "%.*s\n", line.get().getLength(), line.get().getData());
									}
								}
								char command[1024];
								sprintf(command, "start notepad \"%s\"", filename);
								system(command);
							}
							*/
						erule
					ematch
				}
			}

			bool ModuleInstrCompiler::makeOverride(FunctionSignature* baseSignature, const ReferencedSymbol& baseReference, ClassMethod* overrider, instr::Coercion*& retValCoercion, ArrayRef<instr::Coercion*>& paramCoercions){
				if ( baseSignature->getParamsCount() != overrider->getSignature()->getParamsCount() ){
					report_error
						(
							overrider->getSrcLoc(),
							IncompatibleOverride,
							.parameter("base", baseReference)
						);
					return false;
				}else{
					instr::Coercion** coercions = (instr::Coercion**)hostPool->allocateArray(sizeof(instr::Coercion*), overrider->getSignature()->getParamsCount());
					auto paramsOverride = overrider->getSignature()->getParams();
					bool success = true;
					iterate_array(paramBase, baseSignature->getParams()){
						auto paramOverride = paramsOverride.get(paramBase.getIndex());
						instr::Coercion* coercion = findCoercion(buildType(paramBase.get().getType()), buildType(paramOverride.getType()));
						if ( !coercion ){
							success = false;
						}
						coercions[paramBase.getIndex()] = coercion;
					}
					instr::Coercion* retValCoercion = findCoercion(buildType(overrider->getSignature()->getReturnType()), buildType(baseSignature->getReturnType())); 
					if ( !retValCoercion ){
						success = false;
					}
					if ( !success ){
						report_error
							(
								overrider->getSrcLoc(),
								IncompatibleOverride,
								.parameter("base", baseReference)
							);
						return false;
					}else{
						paramCoercions = MakeArrayRef(coercions, overrider->getSignature()->getParamsCount());
						return true;
					}
				}
			}

			instr::Type* ModuleInstrCompiler::buildType(parser::ast::Type* ast){
				using namespace parser;
				match(ast)
					rule(ast::TypePrim, ast)
						switch ( ast->id ){
						case ast::TypePrim::Undef: return instr::TypeUndef::Get();
						case ast::TypePrim::Unit: return instr::TypeUnit::Get();
						case ast::TypePrim::Bool: return instr::TypeBool::Get();
						case ast::TypePrim::Int: return instr::TypeInt::Get();
						case ast::TypePrim::Float: return instr::TypeFloat::Get();
						case ast::TypePrim::Double: return instr::TypeDouble::Get();
						case ast::TypePrim::String: return instr::TypeString::Get();
						case ast::TypePrim::Bytes: return instr::TypeBytes::Get();
						default: unreachable;
						}
					erule
					rule(ast::TypeTuple, ast)
						size_t paramsCount = countList(ast->types);
						if ( paramsCount == 0 ){
							return instr::TypeUnit::Get();
						}else if ( paramsCount == 1 ){
							return buildType(ast->types->type);
						}else{
							instr::TypeUnnamedStruct* typeStruct = new(hostPool->allocateDynamic(sizeof(instr::TypeUnnamedStruct), sizeof(instr::Type*), paramsCount))instr::TypeUnnamedStruct(paramsCount);
							size_t index = 0;
							iterate_list(type, ast->types){
								typeStruct->params[index++] = buildType(type->type);
							}
							return typeStruct;
						}
					erule
					rule(ast::TypeUnion, ast)
						size_t paramsCount = countList(ast->types);
						if ( paramsCount == 0 ){
							return instr::TypeUndef::Get();
						}else if ( paramsCount == 1 ){
							return buildType(ast->types->type);
						}else{
							instr::TypeUnnamedEnum* typeEnum = new(hostPool->allocateDynamic(sizeof(instr::TypeUnnamedEnum), sizeof(instr::Type*), paramsCount))instr::TypeUnnamedEnum(paramsCount);
							size_t index = 0;
							iterate_list(type, ast->types){
								typeEnum->params[index++] = buildType(type->type);
							}
							return typeEnum;
						}
					erule
					rule(ast::TypeMissing, ast)
						return instr::TypeError::Get();
					erule
					rule(ast::TypeOptional, ast)
						instr::Type* valueType = buildType(ast->type);
						if ( valueType->tag == instr::TypeOptionalTag ){
							return valueType;
						}else{
							return alloc(instr::TypeOptional)(valueType);
						}
					erule
					rule(ast::TypeFunction, ast)
						instr::Type* returnType = buildType(ast->result);
						size_t paramsCount = countList(ast->param);
						instr::TypeFunction* typeFunction = new(hostPool->allocateDynamic(sizeof(instr::TypeFunction), sizeof(instr::Type*), paramsCount))instr::TypeFunction(returnType, paramsCount);
						size_t index = 0;
						iterate_list(type, ast->param){
							typeFunction->params[index++] = buildType(type->type);
						}
						return typeFunction;
					erule
					rule(ast::TypeReference, ast)
						match(ast->node)
							rule(ast::TypeReferenceLeaf, node)
								auto name = findName(ast->where, node->id);
								return buildTypeFromExportName(ast->where, node->id, name);
							erule
							rule(ast::TypeReferenceSubscript, node)
								match(node->lhs)
									rule(ast::TypeReferenceLeaf, leaf)
										ir::Namespace* ns = module->namespaceMap->get(leaf->id);
										if ( ns ){
											return buildTypeFromExportName(ast->where, node->id, findName(ast->where, ns, node->id));
										}else{
											report_error(ast->where, NoSuchNamespace, .parameter<StringLiteral>("name", leaf->id));
											return instr::TypeError::Get();
										}
									erule
									defrule(_)
										report_error(ast->where, MalformedType, );
										return instr::TypeError::Get();
									erule
								ematch
							erule
							rule(ast::TypeReferenceInstance, node)
								match(node->lhs)
									rule(ast::TypeReferenceLeaf, leaf)
										if ( leaf->id == "map" ){
											if ( countList(node->params) != 2 ){
												report_error
													(
														ast->where, 
														InvalidTypeParamCount, 
														.parameter("expected", Integer(2))
														.parameter("actual", Integer(countList(node->params)))
													);
												return instr::TypeError::Get();
											}else{
												return alloc(instr::TypeMap)
													(
														buildType(node->params->type),
														buildType(node->params->next->type)
													);
											}
										}else if ( leaf->id == "set" ){
											if ( countList(node->params) != 1 ){
												report_error
													(
														ast->where, 
														InvalidTypeParamCount, 
														.parameter("expected", Integer(1))
														.parameter("actual", Integer(countList(node->params)))
													);
												return instr::TypeError::Get();
											}else{
												return alloc(instr::TypeSet)
													(
														buildType(node->params->type)
													);
											}
										}else if ( leaf->id == "array" ){
											if ( countList(node->params) != 1 ){
												report_error
													(
														ast->where, 
														InvalidTypeParamCount, 
														.parameter("expected", Integer(1))
														.parameter("actual", Integer(countList(node->params)))
													);
												return instr::TypeError::Get();
											}else{
												return alloc(instr::TypeArray)
													(
														buildType(node->params->type)
													);
											}
										}else{
											report_error(ast->where, InvalidTypeInstance, .parameter<StringLiteral>("name", leaf->id));
											return instr::TypeError::Get();
										}
									erule
									defrule(_)
										report_error(ast->where, MalformedType, );
										return instr::TypeError::Get();
									erule
								ematch
							erule
							nodefrule
						ematch
					erule
					nodefrule
				ematch
			}

			instr::Type* ModuleInstrCompiler::buildType(ir::Type type){
				return instr::BuildType(hostPool, type);
			}

			bool ModuleInstrCompiler::unifyTypes(instr::Type* left, instr::Type* right){
				left = left->getRepr();
				right = right->getRepr();

				if ( areTypesEqual(left, right) ){
					return true;
				}else{
					match(left)
						rule(instr::TypeVar, left)
							match(right)
								rule(instr::TypeVar, right)
									if ( left->rank < right->rank ){
										left->parent = right;
									}else if ( left->rank > right->rank ){
										right->parent = left;
									}else{
										left->parent = right;
										right->rank++;
									}
									return true;
								erule
								defrule(right)
									left->parent = right;
									return true;
								erule
							ematch
						erule
					ematch
					match(right)
						rule(instr::TypeVar, right)
							right->parent = left;
							return true;
						erule
					ematch
					return false;
				}				
			}
			
			bool ModuleInstrCompiler::areTypesEqual(instr::Type* left, instr::Type* right){
				left = left->getRepr();
				right = right->getRepr();

				if ( left == right ){
					return true;
				}else{
					match(left)
						rule(instr::TypeOptional, left)
							match(right)
								rule(instr::TypeOptional, right)
									return areTypesEqual(left->valueType, right->valueType);
								erule
							ematch
						erule
						rule(instr::TypeClass, left)
							match(right)
								rule(instr::TypeClass, right)
									return left->class_ == right->class_;
								erule
							ematch
						erule
						rule(instr::TypeInterface, left)
							match(right)
								rule(instr::TypeInterface, right)
									return left->interface == right->interface;
								erule
							ematch
						erule
						rule(instr::TypeStruct, left)
							match(right)
								rule(instr::TypeStruct, right)
									return left->struct_ == right->struct_;
								erule
							ematch
						erule
						rule(instr::TypeEnum, left)
							match(right)
								rule(instr::TypeEnum, right)
									return left->enum_ == right->enum_;
								erule
							ematch
						erule
						rule(instr::TypeSet, left)
							match(right)
								rule(instr::TypeSet, right)
									return areTypesEqual(left->keyType, right->keyType);
								erule
							ematch
						erule
						rule(instr::TypeMap, left)
							match(right)
								rule(instr::TypeMap, right)
									return areTypesEqual(left->keyType, right->keyType) &&
										areTypesEqual(left->valueType, right->valueType);
								erule
							ematch
						erule
						rule(instr::TypeArray, left)
							match(right)
								rule(instr::TypeArray, right)
									return areTypesEqual(left->valueType, right->valueType);
								erule
							ematch
						erule
						rule(instr::TypeUnnamedEnum, left)
							match(right)
								rule(instr::TypeUnnamedEnum, right)
									if ( left->paramsCount != right->paramsCount ){
										return false;
									}
									for ( size_t i = 0; i < left->paramsCount; i++ ){
										if ( !areTypesEqual(left->params[i], right->params[i]) ){
											return false;
										}
									}
									return true;
								erule
							ematch
						erule
						rule(instr::TypeUnnamedStruct, left)
							match(right)
								rule(instr::TypeUnnamedStruct, right)
									if ( left->paramsCount != right->paramsCount ){
										return false;
									}
									for ( size_t i = 0; i < left->paramsCount; i++ ){
										if ( !areTypesEqual(left->params[i], right->params[i]) ){
											return false;
										}
									}
									return true;
								erule
							ematch
						erule
						rule(instr::TypeFunction, left)
							match(right)
								rule(instr::TypeFunction, right)
									if ( left->paramsCount != right->paramsCount ){
										return false;
									}
									for ( size_t i = 0; i < left->paramsCount; i++ ){
										if ( !areTypesEqual(left->params[i], right->params[i]) ){
											return false;
										}
									}
									return areTypesEqual(left->returnType, right->returnType);
								erule
							ematch
						erule
					ematch
					return false;
				}
			}

			instr::Type* ModuleInstrCompiler::specializeType(const SrcSpan& where, ArrayRef<instr::Type*> typeTemplateVars, instr::Type* type, instr::Type* hintType){
				match(type)
					rule(instr::TypeTemplateVar, type)
						instr::Type* repr = typeTemplateVars.get(type->index);
						if ( !repr ){
							if ( hintType ){
								typeTemplateVars.getRaw()[type->index] = hintType;
								return hintType;
							}else{
								report_error(where, FailedToInferTemplateArgument, .parameter<Integer>("index", type->index + 1));
								return instr::TypeError::Get();
							}
						}else{
							return repr;
						}
					erule
					rule(instr::TypeArray, type)
						instr::Type* hintValueType = nullptr;
						if ( hintType ){
							match(hintType)
								rule(instr::TypeArray, hintType)
									hintValueType = hintType->valueType;
								erule
							ematch
						}
						instr::Type* valueType = specializeType(where, typeTemplateVars, type->valueType, hintValueType);
						if ( valueType == type->valueType ){
							return type;
						}else{
							return alloc(instr::TypeArray)(valueType);
						}
					erule
				ematch
				return type;
			}
			
			instr::Coercion* ModuleInstrCompiler::findCoercion(instr::Type* from, instr::Type* to){
				from = from->getRepr();
				to = to->getRepr();
				
				if ( areTypesEqual(from, to) ){
					return instr::CoercionId::Get();
				}else{
					if ( from->tag == instr::TypeUndefTag ){
						return instr::CoercionFromUndef::Get();
					}

					match(to)
						rule(instr::TypeNumeric, to)
							addTypeEdge(from, to);
							return instr::CoercionLater::Get();
						erule
					ematch
					
					match(from)
						rule(instr::TypeNumeric, from)
							addTypeEdge(from, to);
							return instr::CoercionLater::Get();
						erule
						rule(instr::TypeStringLiteral, from)
							match(to)
								rule(instr::TypeString, to)
									return alloc(instr::CoercionConstString)(from);
								erule
							ematch
						erule
						rule(instr::TypeArray, from)
							match(to)
								rule(instr::TypeArray, to)
									if ( unifyTypes(from->valueType, to->valueType) ){
										return instr::CoercionId::Get();
									}
								erule
							ematch
							return nullptr;
						erule
						rule(instr::TypeOptional, from)
							match(to)
								rule(instr::TypeOptional, to)
									instr::Coercion* valueCoercion = findCoercion(from->valueType, to->valueType);
									if ( valueCoercion == instr::CoercionId::Get() ){
										return valueCoercion;
									}else if ( !valueCoercion ){
										return valueCoercion;
									}else if ( valueCoercion == instr::CoercionLater::Get() ){
										return valueCoercion;
									}else{
										return alloc(instr::CoercionLiftMaybe)(valueCoercion, from->valueType, to->valueType);
									}
								erule
							ematch
						erule
						rule(instr::TypeNull, from)
							match(to)
								rule(instr::TypeOptional, to)
									return alloc(instr::CoercionNullToMaybe)(to->valueType);
								erule
							ematch
						erule
						rule(instr::TypeNumber, from)
							match(to)
								rule(instr::TypeInt, to)									
									return alloc(instr::CoercionConstInt)(parseInt(from->where, from->value));
								erule
								rule(instr::TypeFloat, to)
									return alloc(instr::CoercionConstFloat)(parseFloat(from->where, from->value));
								erule
								rule(instr::TypeDouble, to)
									return alloc(instr::CoercionConstDouble)(parseDouble(from->where, from->value));
								erule
							ematch
						erule
						rule(instr::TypeInt, from)
							match(to)
								rule(instr::TypeDouble, to)
									return instr::CoercionIntToDouble::Get();
								erule
							ematch
						erule
						rule(instr::TypeFloat, from)
							match(to)
								rule(instr::TypeDouble, to)
									return instr::CoercionFloatToDouble::Get();
								erule
							ematch
						erule
						rule(instr::TypeClass, from)
							match(to)
								rule(instr::TypeClass, to)
									if ( from->class_->getBasesMap().find(to->class_) ){
										return alloc(instr::CoercionToBaseClass)(from->class_, to->class_);
									}
								erule
								rule(instr::TypeInterface, to)
									if ( from->class_->getImplementsMap().find(to->interface) ){
										return alloc(instr::CoercionToClassImplemented)(from->class_, to->interface);
									}
								erule
							ematch
						erule
					ematch
					match(to)
						rule(instr::TypeOptional, to)
							instr::Coercion* valueCoercion = findCoercion(from, to->valueType);
							if ( !valueCoercion ){
								return valueCoercion;
							}else if ( valueCoercion == instr::CoercionLater::Get() ){
								return valueCoercion;
							}else{
								return alloc(instr::CoercionWrapMaybe)(valueCoercion, to->valueType);
							}
						erule
					ematch
					return nullptr;
				}
			}
			
			s32 ModuleInstrCompiler::parseInt(const SrcSpan& where, const StringRef& content){
				if ( content.getLength() > 12 ){
					report_error(where, NotIntConstant, .parameter<StringLiteral>("value", content));
					return 0;
				}
				char buffer[16];
				::memcpy(buffer, content.getData(), content.getLength());
				buffer[content.getLength()] = 0;
				s32 value;
				char ch;
				if ( sscanf(buffer, "%d%c", &value, &ch) != 1 ){
					report_error(where, NotIntConstant, .parameter<StringLiteral>("value", content));
					return 0;
				}
				return value;
			}

			float ModuleInstrCompiler::parseFloat(const SrcSpan& where, const StringRef& content){
				return (float)parseDouble(where, content);
			}

			double ModuleInstrCompiler::parseDouble(const SrcSpan& where, const StringRef& content){
				#define MAX_LEN 127
				if ( content.getLength() > MAX_LEN ){
					report_error(where, NoRealConstant, .parameter<StringLiteral>("value", content));
					return 0;
				}
				char buffer[MAX_LEN + 1];
				::memcpy(buffer, content.getData(), content.getLength());
				buffer[content.getLength()] = 0;
				double value;
				char ch;
				if ( sscanf(buffer, "%lf%c", &value, &ch) != 1 ){
					report_error(where, NoRealConstant, .parameter<StringLiteral>("value", content));
					return 0;
				}
				#undef MAX_LEN
				return value;
			}

			void ModuleInstrCompiler::addTypeEdge(instr::Type* outv, instr::Type* inv){
				inv = inv->getRepr();
				outv = outv->getRepr();
				match(inv)
					rule(instr::TypeNumeric, inv)
						match(outv)
							rule(instr::TypeNumeric, outv)
								alloc(instr::TypeEdge)(outv, inv);
							erule
							defrule(_)
								mergeInedge(inv, outv);
							erule
						ematch
					erule
					defrule(_)
						match(outv)
							rule(instr::TypeNumeric, outv)
								mergeOutedge(outv, inv);
							erule
							defrule(_)
								//TODO::?
								assert(false);
							erule
						ematch
					erule
				ematch
			}

			void ModuleInstrCompiler::mergeInedge(instr::TypeNumeric* target, instr::Type* in){
				match(in)
					rule(instr::TypeNumber, in)
						target->inRank = instr::TypeNumberRank::MergeInRank(target->inRank, instr::TypeNumberRank::Constant);
					erule
					rule(instr::TypeInt, in)
						target->inRank = instr::TypeNumberRank::MergeInRank(target->inRank, instr::TypeNumberRank::Int);
					erule
					rule(instr::TypeFloat, in)
						target->inRank = instr::TypeNumberRank::MergeInRank(target->inRank, instr::TypeNumberRank::Float);
					erule
					rule(instr::TypeDouble, in)
						target->inRank = instr::TypeNumberRank::MergeInRank(target->inRank, instr::TypeNumberRank::Double);
					erule
				ematch
			}

			void ModuleInstrCompiler::mergeOutedge(instr::TypeNumeric* target, instr::Type* out){
				match(out)
					rule(instr::TypeNumber, out)
						target->outRank = instr::TypeNumberRank::MergeOutRank(target->outRank, instr::TypeNumberRank::Constant);
					erule
					rule(instr::TypeInt, out)
						target->outRank = instr::TypeNumberRank::MergeOutRank(target->outRank, instr::TypeNumberRank::Int);
					erule
					rule(instr::TypeFloat, out)
						target->outRank = instr::TypeNumberRank::MergeOutRank(target->outRank, instr::TypeNumberRank::Float);
					erule
					rule(instr::TypeDouble, out)
						target->outRank = instr::TypeNumberRank::MergeOutRank(target->outRank, instr::TypeNumberRank::Double);
					erule
				ematch
			}

			instr::Type* ModuleInstrCompiler::buildTypeFromExportName(const SrcSpan& where, const StringRef& id, Pair<ExportName, ir::Module*> name){
				if ( name.first.isTypeReference() ){
					switch ( name.first.kind ){
					case ExportKind::Enum: return alloc(instr::TypeEnum)((ir::Enum*)name.first.reference);
					case ExportKind::Class: return alloc(instr::TypeClass)((ir::Class*)name.first.reference);
					case ExportKind::Interface: return alloc(instr::TypeInterface)((ir::Interface*)name.first.reference);
					case ExportKind::Struct: return alloc(instr::TypeStruct)((ir::Struct*)name.first.reference);
					default: unreachable;
					}
				}else {
					if ( name.first ){
						report_error(where, NotATypeName, .parameter<StringLiteral>("name", id).parameter("reference", name.first.makeSymbol(name.second)));
					}
					return instr::TypeError::Get();
				}
			}
			
			Pair<ExportName, ir::Module*> ModuleInstrCompiler::findName(const SrcSpan& where, const StringRef& name){
				ExportName result = module->exportMap->get(name);
				if ( result ){
					return MakePair(result, module);
				}
				Namespace* ns = module->namespaceMap->get(name);
				if ( ns ){
					return MakePair(ExportName(ExportKind::Namespace, ns), module);
				}
				return findName(where, module->namespaceMap->get(""), name);
			}

			class CandidatesProvider: public ILocalizationParamProvider{
			public:
				CandidatesProvider(ArrayList< Pair<ir::Module*, ir::ExportName> >& candidateNames)
					: candidateNames(candidateNames){
				}

				void accept(ILocalizationParamVisitor& visitor){
					for ( auto enumerator = candidateNames.enumerate(); enumerator.hasNext(); enumerator.advance() ){
						visitor.visitValue("candidate", enumerator.get().second.makeSymbol(enumerator.get().first));
					}
				}
			private:
				ArrayList< Pair<ir::Module*, ir::ExportName> >& candidateNames;
			};


			Pair<ExportName, ir::Module*> ModuleInstrCompiler::findName(const SrcSpan& where, ir::Namespace* ns, const StringRef& name){
				ExportName choosenName;
				ir::Module* choosenModule;
				ArrayList< Pair<ir::Module*, ir::ExportName> > candidateNames(tempPool);
				
				auto hash = ir::ExportTableHashName(name);
				ns->getFilter()->visitElements(hash, [&](ir::Module* module){
						ExportName exportName = module->exportMap->get(name);
						if ( exportName.getUniverse() > choosenName.getUniverse() ){
							choosenName = exportName;
							choosenModule = module;
							candidateNames.clear();
							candidateNames.push(MakePair(module, exportName));
						}else{
							switch ( choosenName.getUniverse() ){
							case ExportUniverse::None:{
								unreachable;
							}break;
							case ExportUniverse::Constructors:{
								choosenName = ExportName(ExportKind::ConstructorClash);
								if ( exportName ){
									candidateNames.push(MakePair(module, exportName));
								}
							}break;
							case ExportUniverse::TopLevel:{
								candidateNames.push(MakePair(module, exportName));
							}break;
							}
						}
					});
				if ( candidateNames.getSize() > 1 ){
					CandidatesProvider provider(candidateNames);
					report_error(where, AmbigiousName, .parameter<StringLiteral>("name", name).parameters(provider));
					return MakePair(ExportName(ExportKind::None), (ir::Module*)nullptr);
				}else if ( !choosenName ){
					report_error(where, UnresolvedName, .parameter<StringLiteral>("name", name));
					return MakePair(ExportName(ExportKind::None), (ir::Module*)nullptr);
				}else{
					return MakePair(choosenName, choosenModule);
				}
			}

		}
	}
}