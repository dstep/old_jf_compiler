#include <IR/Compiler/IRBuilder.h>
#include <Support/Container/HashMap.h>
#include <Support/Container/ArrayList.h>
#include <Support/Match.h>
#include <IR/Import.h>
#include <IR/Module.h>
#include <IR/Export.h>

namespace jf{
	namespace ir{
		namespace compiler{
			#define ir(t) new(irPool->allocate(sizeof(t)))t
			#define def(t) new(defPool->allocate(sizeof(t)))t
			#define tmp(t) new(tempPool->allocate(sizeof(t)))t

			using namespace parser;

			IRBuilder::IRBuilder(IDiagnosticStream* diagnostic, MemoryPoolSlice* tempPool, MemoryPoolSlice* irPool, MemoryPoolSlice* defPool)
				: tempPool(tempPool)
				, diagnostic(diagnostic)
				, irPool(irPool)
				, importNames(tempPool)
				, defPool(defPool){
			}

			size_t countFieldList(parser::ast::StructField* fields){
				size_t count = 0;
				iterate_list(field, fields){
					count += countList(field->names);
				}
				return count;
			}

			Module* IRBuilder::build(parser::ast::Module* ast){
				StringMap<ImportModule*> imports(tempPool);

				typedef HashMap<ImportModule*, bool> NamespaceContent;

				ArrayList<ImportModule*> importsList(tempPool);
				StringMap< NamespaceContent* > namespaces(tempPool);

				iterate_list(import, ast->imports){
					QualID* qid = buildQualID(import->qid);

					if ( !qid ){
						continue;
					}

					ImportModule* importModule = imports.get(qid->asString());
					if ( !importModule ){
						importModule = ir(ImportModule)(import->where, qid->slice(irPool));
						importsList.push(importModule);
						imports.set(importModule->getQID()->asString(), importModule);
					}

					NamespaceContent*& ns = namespaces.getOrInsert(import->as);
					if ( !ns ){
						ns = tmp(NamespaceContent)(tempPool);
					}
					bool& contains = ns->getOrInsert(importModule);
					if ( contains ){
						diagnostic->report
							(
								Subsystem("Compiler")
									.type(DiagnosticType::Error)
									.at(import->where)
									.code("CompilerError.NamespaceAlreadyContainsModule")
									.parameter_if<StringLiteral>(import->as.getLength() > 0, "namespace", import->as)
									.parameter<StringLiteral>("module", importModule->getQID()->asString())
							);
					}else{
						contains = true;
					}
				}

				Module* module = ir(Module);
			
				namespaceMap = ir(StringMap<Namespace*>)(irPool);
				ArrayList<Namespace*> namespaceList(tempPool);
			
				iterate_enumerable(namespaceContent, namespaces){
					ImportModule** modules = (ImportModule**)irPool->allocateArray(sizeof(ImportModule), namespaceContent.getValue()->getSize());
					ArrayRef<ImportModule*> modulesArray(modules, namespaceContent.getValue()->getSize());
					iterate_enumerable(module, (*namespaceContent.getValue())){
						*modules = module.getKey();
						modules++;
					}
					Namespace* namespace_ = ir(Namespace)(namespaceContent.getKey(), modulesArray);
					namespaceList.push(namespace_);
					namespaceMap->set(namespace_->getName(), namespace_);
				}

				if ( !namespaceMap->has("") ){
					Namespace* namespace_ = ir(Namespace)("", ArrayRef<ImportModule*>());
					namespaceList.push(namespace_);
					namespaceMap->set("", namespace_);
				}
			
				module->namespaces = namespaceList.slice(irPool);
				module->imports = importsList.slice(irPool);
				module->namespaceMap = namespaceMap;

				ArrayList<GlobalFunction*> functions(tempPool);
				ArrayList<GlobalVariable*> variables(tempPool);
				ArrayList<Enum*> enums(tempPool);
				ArrayList<Struct*> structs(tempPool);
				ArrayList<Class*> classes(tempPool);
				ArrayList<Interface*> interfaces(tempPool);

				exportMap = ir(StringMap<ExportName>)(irPool);
			
				iterate_list(topLevel, ast->topLevels){
					match(topLevel)
						rule(ast::GlobalFunction, topLevel)
							FunctionBody* body = buildFunctionBody(topLevel->body);
							FunctionSignature* signature = buildSignature(topLevel->signature);
							GlobalFunction* function = ir(GlobalFunction)(module, topLevel->where, topLevel->name, signature, body);
							functions.push(function);
							addExportName(function->getName(), ExportKind::Function, function);
						erule
						rule(ast::GlobalVariable, topLevel)
							Type type = buildType(topLevel->type);
							Initializer* initializer = buildInitializer(topLevel->initializer);
							GlobalVariable* variable = ir(GlobalVariable)(topLevel->where, topLevel->name, type, initializer);
							variables.push(variable);
							addExportName(variable->getName(), ExportKind::Variable, variable);
						erule
						rule(ast::Enum, topLevel)
							size_t constructorsCount = countList(topLevel->constructors);
							EnumConstructor* constructors = (EnumConstructor*)irPool->allocateArray(sizeof(EnumConstructor), constructorsCount);
							ArrayRef<EnumConstructor> constructorsArray(constructors, constructorsCount);
							StringMap<EnumConstructor*>* constructorsMap = ir(StringMap<EnumConstructor*>)(irPool);
							
							Enum* enum_ = ir(Enum)(module, topLevel->where, topLevel->name, constructorsArray, constructorsMap);

							iterate_list(ast, topLevel->constructors){
								new(constructors)EnumConstructor(enum_, ast->where, ast->name, ast->signature ? buildParams(ast->signature->params) : ArrayRef<Param>());
								if ( ast->name.getLength() > 0 ){
									EnumConstructor*& constructorSlot = constructorsMap->getOrInsert(ast->name);
									if ( constructorSlot ){
										diagnostic->report
											(
												Subsystem("Compiler")
													.type(DiagnosticType::Error)
													.at(ast->where)
													.code("CompilerError.DuplicateEnumConstructor")
													.parameter("name", StringLiteral(ast->name))
													.parameter("previous", constructorSlot->getSrcLoc())
											);
									}else{
										constructorSlot = constructors;
									}
								}
								addExportName(constructors->getName(), ExportKind::EnumConstructor, constructors);
								constructors++;
							}
							
							enums.push(enum_);
							addExportName(enum_->getName(), ExportKind::Enum, enum_);
						erule
						rule(ast::Struct, topLevel)
							size_t fieldsCount = countFieldList(topLevel->fields);
							StructField* fields = (StructField*)irPool->allocateArray(sizeof(StructField), fieldsCount);
							ArrayRef<StructField> fieldsArray(fields, fieldsCount);
							StringMap<StructField*>* fieldsMap = ir(StringMap<StructField*>)(irPool);
							iterate_list(ast, topLevel->fields){
								Type type = buildType(ast->type);
								iterate_list(name, ast->names){
									new(fields)StructField(name->where, name->id, type);
									if ( name->id.getLength() > 0 ){
										StructField*& fieldSlot = fieldsMap->getOrInsert(name->id);
										if ( fieldSlot ){
											diagnostic->report
												(
													Subsystem("Compiler")
														.type(DiagnosticType::Error)
														.at(name->where)
														.code("CompilerError.DuplicateStructField")
														.parameter("name", StringLiteral(name->id))
														.parameter("previous", fieldSlot->getSrcLoc())
												);
										}else{
											fieldSlot = fields;
										}
									}
									fields++;
								}
							}
							Struct* struct_ = ir(Struct)(module, topLevel->where, topLevel->name, fieldsArray, fieldsMap);
							structs.push(struct_);
							addExportName(struct_->getName(), ExportKind::Struct, struct_);
						erule
						rule(ast::Interface, topLevel)
							
							size_t extendsCount = countList(topLevel->implements);
							ImplementsInterface* extends = (ImplementsInterface*)irPool->allocateArray(sizeof(ImplementsInterface), extendsCount);
							ArrayRef<ImplementsInterface> extendsArray(extends, extendsCount);
							iterate_list(ast, topLevel->implements){
								new(extends++)ImplementsInterface(ast->where, buildImportName(ImportName::ExtendedInterface, ast->qid));
							}

							size_t methodsCount = countList(topLevel->methods);
							InterfaceMethod* methods = (InterfaceMethod*)irPool->allocateArray(sizeof(InterfaceMethod), methodsCount);
							ArrayRef<InterfaceMethod> methodsArray(methods, methodsCount);
							
							Interface* interface = ir(Interface)(module, topLevel->where, topLevel->name, extendsArray, methodsArray);
							
							iterate_list(ast, topLevel->methods){
								new(methods++)InterfaceMethod(interface, ast->where, ast->name, buildSignature(ast->signature));
							}

							interfaces.push(interface);
							addExportName(interface->getName(), ExportKind::Interface, interface);
						erule
						rule(ast::Class, topLevel)
							ClassExtends* extends = nullptr;
							if ( topLevel->extends ){
								extends = ir(ClassExtends)(topLevel->extends->where, buildImportName(ImportName::ExtendedClass, topLevel->extends->qid));
							}

							size_t implementsCount = countList(topLevel->implements);
							ImplementsInterface* implements = (ImplementsInterface*)irPool->allocateArray(sizeof(ImplementsInterface), implementsCount);
							ArrayRef<ImplementsInterface> implementsArray(implements, implementsCount);
							iterate_list(ast, topLevel->implements){
								new(implements++)ImplementsInterface(ast->where, buildImportName(ImportName::ImplementedInterface, ast->qid));
							}

							size_t constructorsCount = 0;
							size_t fieldsCount = 0;
							size_t methodsCount = 0;
						
							iterate_list(member, topLevel->members){
								match(member)
									rule(ast::ClassMethod, member)
										methodsCount++;
									erule
									rule(ast::ClassField, member)
										fieldsCount += countList(member->names);
									erule
									rule(ast::ClassConstructor, member)
										constructorsCount++;
									erule
								ematch
							}

							ClassMethod* methods = (ClassMethod*)irPool->allocateArray(sizeof(ClassMethod), methodsCount);
							ArrayRef<ClassMethod> methodsArray(methods, methodsCount);
							ClassField* fields = (ClassField*)irPool->allocateArray(sizeof(ClassField), fieldsCount);
							ArrayRef<ClassField> fieldsArray(fields, fieldsCount);
							ClassConstructor* constructors = (ClassConstructor*)irPool->allocateArray(sizeof(ClassConstructor), constructorsCount);
							ArrayRef<ClassConstructor> constructorsArray(constructors, constructorsCount);
							StringMap<ClassConstructor*>* constructorMap = new(irPool->allocate(sizeof(StringMap<ClassConstructor*>)))StringMap<ClassConstructor*>(irPool);

							Class* class_ = ir(Class)
								(
									module,
									topLevel->where, 
									topLevel->name,
									extends,
									implementsArray,
									methodsArray,
									fieldsArray,
									constructorsArray,
									constructorMap
								);

							iterate_list(member, topLevel->members){
								match(member)
									rule(ast::ClassMethod, member)
										ClassMethod::Kind kind;
										switch ( member->kind ){
										case ast::ClassMethod::Abstract: kind = ClassMethod::Abstract; break;
										case ast::ClassMethod::Method: kind = ClassMethod::Method; break;
										case ast::ClassMethod::Override: kind = ClassMethod::Override; break;
										default: unreachable;
										}
										new(methods++)ClassMethod(class_, member->where, member->name, kind, buildSignature(member->signature), buildFunctionBody(member->body));
									erule
									rule(ast::ClassField, member)
										Type type = buildType(member->type);
										iterate_list(name, member->names){
											new(fields++)ClassField(class_, name->where, name->id, type);
										}
									erule
									rule(ast::ClassConstructor, member)
										StringRef name = member->name.getLength() > 0 ? member->name : topLevel->name;
										new(constructors)ClassConstructor(class_, member->where, name, buildImportName(ImportName::ConstructorBase, member->with), buildSignature(member->signature), buildFunctionBody(member->body));
										ClassConstructor*& constructorSlot = constructorMap->getOrInsert(name);
										if ( constructorSlot ){
											diagnostic->report
												(
													Subsystem("Compiler")
														.type(DiagnosticType::Error)
														.at(member->where)
														.code("CompilerError.DuplicateClassConstructor")
														.parameter("name", StringLiteral(name))
														.parameter("previous", constructorSlot->getSrcLoc())
												);
										}else{
											constructorSlot = constructors;
										}
										constructors++;
									erule
								ematch
							}

							classes.push(class_);
							addExportName(class_->getName(), ExportKind::Class, class_);
						erule
					ematch
				}

				module->importNames = importNames.slice(irPool);

				module->functions = functions.slice(irPool);
				module->variables = variables.slice(irPool);
				module->enums = enums.slice(irPool);
				module->interfaces = interfaces.slice(irPool);
				module->classes = classes.slice(irPool);
				module->structs = structs.slice(irPool);

				module->exportMap = exportMap;

				iterate_enumerable(iterator, (*exportMap)){
					module->exportFilter.put(ExportTableHashName(iterator.getKey()));
				}

				return module;
			}

			QualID* IRBuilder::buildQualID(parser::ast::QualID* ast){
				size_t totalLength = 0;
				size_t partsCount = 0;
				for ( auto part = ast; part; part = part->prev ){
					totalLength += part->id.getLength();
					if ( part->id.getLength() == 0 ){
						return nullptr;
					}
					partsCount++;
				}
				totalLength += partsCount - 1;
				u8* buffer = (u8*)tempPool->allocateDynamic(sizeof(QualID) + totalLength, sizeof(StringRef), partsCount);
				u8* stringBuffer = buffer + sizeof(QualID) + sizeof(StringRef) * partsCount;
				QualID* qid = (QualID*)buffer;
				qid->string = StringRef(stringBuffer, totalLength);
				qid->partsCount = partsCount;
				stringBuffer += totalLength;
				size_t i = partsCount;
				for ( auto part = ast; part; part = part->prev ){
					size_t length = part->id.getLength();
					stringBuffer -= length;
					::memcpy(stringBuffer, part->id.getData(), length);
					qid->parts[--i] = StringRef(stringBuffer, length);
					if ( part->prev ){
						stringBuffer--;
						*stringBuffer = '.';
					}
				}
				return qid;
			}

			Type IRBuilder::buildType(parser::ast::Type* ast){
				match(ast)
					rule(ast::TypePrim, ast)
						switch ( ast->id ){
						case ast::TypePrim::Unit: return TypeTagUnit;
						case ast::TypePrim::Undef: return TypeTagUndef;
						case ast::TypePrim::Bool: return TypeTagBool;
						case ast::TypePrim::Int: return TypeTagInt;
						case ast::TypePrim::Float: return TypeTagFloat;
						case ast::TypePrim::Double: return TypeTagDouble;
						case ast::TypePrim::String: return TypeTagString;
						case ast::TypePrim::Bytes: return TypeTagBytes;
						default: unreachable;
						}
					erule
					rule(ast::TypeOptional, ast)
						return buildType(ast->type).wrapOptional();
					erule
					rule(ast::TypeMissing, ast)
						return TypeTagError;
					erule
					rule(ast::TypeUnion, ast)
						size_t count = countList(ast->types);
						if ( count == 0 ){
							return TypeTagUndef;
						}else if ( count == 1 ){
							return buildType(ast->types->type);
						}else{
							TypeList* typeList = buildTypeList(ast->types);
							return Type(TypeTagUnnamedUnion, typeList);
						}
					erule
					rule(ast::TypeTuple, ast)
						size_t count = countList(ast->types);
						if ( count == 0 ){
							return TypeTagUnit;
						}else if ( count == 1 ){
							return buildType(ast->types->type);
						}else{
							TypeList* typeList = buildTypeList(ast->types);
							return Type(TypeTagUnnamedStruct, typeList);
						}
					erule
					rule(ast::TypeFunction, ast)
						TypeList* typeList = buildTypeList(ast->result, ast->param);
						return Type(TypeTagFunction, typeList);
					erule
					rule(ast::TypeReference, ast)
						/*
						* Valid type reference is one of the following:
						*  array . < type >
						*  set . < type >
						*  map . < type, type >
						*
						*  Identifier (default namespace lookup)
						*  Namespace . Identifier (Namespace lookup)
						*/
						match(ast->node)
							rule(ast::TypeReferenceLeaf, node)
								Namespace* namespace_ = namespaceMap->get("");
								ImportName* importName = ir(ImportName)(ImportName::TypeReference, namespace_, ast->where, node->id);
								importNames.push(importName);
								return Type(TypeTagReference, importName);
							erule
							rule(ast::TypeReferenceInstance, node)
								match(node->lhs)
									rule(ast::TypeReferenceLeaf, leaf)
										TypeList* typeList = buildTypeList(node->params);
										if ( leaf->id == "array" ){
											if ( typeList->getCount() != 1 ){
												diagnostic->report
													(
														Subsystem("Compiler")
															.type(DiagnosticType::Error)
															.at(ast->where)
															.code("CompilerError.InvalidTypeParamCount")
															.parameter("expected", Integer(1))
															.parameter("actual", Integer(typeList->getCount()))
													);
											}
											return Type(TypeTagArray, typeList);
										}else if ( leaf->id == "map" ){
											if ( typeList->getCount() != 2 ){
												diagnostic->report
													(
														Subsystem("Compiler")
															.type(DiagnosticType::Error)
															.at(ast->where)
															.code("CompilerError.InvalidTypeParamCount")
															.parameter("expected", Integer(2))
															.parameter("actual", Integer(typeList->getCount()))
													);
											}
											return Type(TypeTagMap, typeList);
										}else if ( leaf->id == "set" ){
											if ( typeList->getCount() != 1 ){
												diagnostic->report
													(
														Subsystem("Compiler")
															.type(DiagnosticType::Error)
															.at(ast->where)
															.code("CompilerError.InvalidTypeParamCount")
															.parameter("expected", Integer(1))
															.parameter("actual", Integer(typeList->getCount()))
													);
											}
											return Type(TypeTagSet, typeList);
										}else{
											diagnostic->report
												(
													Subsystem("Compiler")
														.type(DiagnosticType::Error)
														.at(ast->where)
														.code("CompilerError.InvalidTypeInstance")
														.parameter("name", StringLiteral(leaf->id))
												);
										}
									erule
									defrule(_)
										diagnostic->report
											(
												Subsystem("Compiler")
													.type(DiagnosticType::Error)
													.at(ast->where)
													.code("CompilerError.MalformedType")
											);
									erule
								ematch
							erule
							rule(ast::TypeReferenceSubscript, node)
								match(node->lhs)
									rule(ast::TypeReferenceLeaf, leaf)
										Namespace* namespace_ = namespaceMap->get(leaf->id);
										if ( !namespace_ ){
											diagnostic->report
												(
													Subsystem("Compiler")
														.type(DiagnosticType::Error)
														.at(ast->where)
														.code("CompilerError.NoSuchNamespace")
														.parameter("name", StringLiteral(leaf->id))
												);
										}else{
											ImportName* importName = ir(ImportName)(ImportName::TypeReference, namespace_, ast->where, node->id);
											importNames.push(importName);
											return Type(TypeTagReference, importName);
										}
									erule
									defrule(_)
										diagnostic->report
											(
												Subsystem("Compiler")
													.type(DiagnosticType::Error)
													.at(ast->where)
													.code("CompilerError.MalformedType")
											);
									erule
								ematch
							erule
							nodefrule
						ematch
						return TypeTagError;
					erule
					nodefrule
				ematch
			}

			FunctionSignature* IRBuilder::buildSignature(parser::ast::FunctionSignature* ast){
				size_t paramsCount = 0;
				iterate_list(param, ast->params){
					if ( param->names ){
						paramsCount += countList(param->names);
					}else{
						paramsCount++;
					}
				}
				Type returnType = ast->returnType ? buildType(ast->returnType) : TypeTagUnit;
				FunctionSignature* signature = new(irPool->allocateDynamic(sizeof(FunctionSignature), sizeof(Param), paramsCount))FunctionSignature(returnType, paramsCount);
				size_t index = 0;
				iterate_list(param, ast->params){
					Type type = buildType(param->type);
					if ( param->names ){
						iterate_list(name, param->names){
							new(signature->getParam(index++))Param(name->where, name->id, type);
						}
					}else{
						new(signature->getParam(index++))Param(param->type->where, "", type);
					}
				}
				return signature;
			}

			ArrayRef<Param> IRBuilder::buildParams(parser::ast::ParamGroup* ast){
				size_t paramsCount = 0;
				iterate_list(param, ast){
					if ( param->names ){
						paramsCount += countList(param->names);
					}else{
						paramsCount++;
					}
				}
				Param* params = (Param*)irPool->allocateArray(sizeof(Param), paramsCount);
				ArrayRef<Param> returnValue(params, paramsCount);
				iterate_list(param, ast){
					Type type = buildType(param->type);
					if ( param->names ){
						iterate_list(name, param->names){
							new(params++)Param(name->where, name->id, type);
						}
					}else{
						new(params++)Param(param->type->where, "", type);
					}
				}
				return returnValue;
			}

			TypeList* IRBuilder::buildTypeList(parser::ast::Type* type, parser::ast::TypeList* types){
				size_t count = countList(types) + (type ? 1 : 0);
				TypeList* typeList = new(irPool->allocateDynamic(sizeof(TypeList), sizeof(Type), count))TypeList(count);
				size_t i = 0;
				if ( type ){
					typeList->getType(i++) = buildType(type);
				}
				iterate_list(type, types){
					typeList->getType(i++) = buildType(type->type);
				}
				return typeList;
			}

			TypeList* IRBuilder::buildTypeList(parser::ast::TypeList* ast){
				return buildTypeList(nullptr, ast);
			}

			Initializer* IRBuilder::buildInitializer(parser::ast::Expr* expr){
				return def(Initializer)(expr);
			}

			FunctionBody* IRBuilder::buildFunctionBody(parser::ast::FunctionBody* ast){
				if ( !ast ){
					return nullptr;
				}
				match(ast)
					rule(ast::FunctionBodyDefined, ast)
						return def(FunctionBodyCode)(ast->where, ast->stmt);
					erule
					rule(ast::FunctionBodyExpr, ast)
						return def(FunctionBodyCode)(ast->where, def(parser::ast::StmtEval)(ast->where, ast::StmtEval::Return, ast->expr));
					erule
					rule(ast::FunctionBodyImport, ast)
						return def(FunctionBodyFFI)(ast->where, ast->string);
					erule
					nodefrule
				ematch
			}

			ImportName* IRBuilder::buildImportName(ImportName::Usage usage, parser::ast::QualID* ast){
				if ( !ast ){
					return nullptr;
				}else if ( ast->prev ){
					if ( ast->prev->prev ){
						diagnostic->report
							(
								Subsystem("Compiler")
									.type(DiagnosticType::Error)
									.at(ast->where)
									.code("CompilerError.MalformedType")
							);
						return nullptr;
					}else{
						Namespace* namespace_ = namespaceMap->get(ast->prev->id);
						if ( !namespace_ ){
							diagnostic->report
								(
									Subsystem("Compiler")
										.type(DiagnosticType::Error)
										.at(ast->where)
										.code("CompilerError.NoSuchNamespace")
										.parameter("name", StringLiteral(ast->prev->id))
								);
							return nullptr;
						}else{
							ImportName* importName = ir(ImportName)(usage, namespace_, ast->where, ast->id);
							importNames.push(importName);
							return importName;
						}
					}
				}else{
					Namespace* namespace_ = namespaceMap->get("");
					ImportName* importName = ir(ImportName)(usage, namespace_, ast->where, ast->id);
					importNames.push(importName);
					return importName;
				}
			}

			SrcSpan getSourceLocFromReference(ExportKind::Value kind, void* reference){
				switch ( kind ){
				case ExportKind::EnumConstructor: return ((EnumConstructor*)reference)->getSrcLoc();
				case ExportKind::Enum: return ((Enum*)reference)->getSrcLoc();
				case ExportKind::Struct: return ((Struct*)reference)->getSrcLoc();
				case ExportKind::Interface: return ((Interface*)reference)->getSrcLoc();
				case ExportKind::Function: return ((GlobalFunction*)reference)->getSrcLoc();
				case ExportKind::Variable: return ((GlobalVariable*)reference)->getSrcLoc();
				case ExportKind::Class: return ((Class*)reference)->getSrcLoc();
				}
				return SrcSpan::Undefined();
			}

			void IRBuilder::addExportName(const StringRef& name, ExportKind::Value kind, void* reference){
				ExportName& exportName = exportMap->getOrInsert(name);
				if ( exportName.kind == ExportKind::None ){
					exportName = ExportName(kind, reference);
				}else if ( exportName.kind == ExportKind::EnumConstructor || exportName.kind == ExportKind::ConstructorClash ){
					if ( kind == ExportKind::EnumConstructor ){
						exportName.kind = ExportKind::ConstructorClash;
					}else{
						exportName = ExportName(kind, reference);
					}
				}else{
					if ( kind != ExportKind::EnumConstructor ){
						diagnostic->report
							(
								Subsystem("Compiler")
									.type(DiagnosticType::Error)
									.at(getSourceLocFromReference(kind, reference))
									.code("CompilerError.DuplicateTopLevelName")
									.parameter("name", StringLiteral(name))
									.parameter("previous", getSourceLocFromReference(exportName.kind, exportName.reference))
							);
					}
				}
			}
		}
	}
}