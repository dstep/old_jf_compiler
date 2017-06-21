#include <IR/Instr/Type.h>
#include <Support/Container/ArrayList.h>
#include <Support/Twine.h>
#include <Support/Match.h>
#include <Support/Format.h>
#include <IR/Class.h>
#include <IR/Module.h>

namespace jf{
	namespace ir{
		namespace instr{
			#define PrimType(t) Type##t Type##t::Instance;
			#include <IR/Instr/PrimTypes.inc>

			Type* BuildType(MemoryPoolSlice* pool, ir::Type type){
				#define alloc(t) new(pool->allocate(sizeof(t)))t

				if ( type.getTag() & TypeTagOptionalBit ){
					instr::Type* valueType = BuildType(pool, type.unwrapOptional());
					return alloc(instr::TypeOptional)(valueType);
				}
				switch ( type.getTag() ){
				case TypeTagUnit: return instr::TypeUnit::Get();
				case TypeTagUndef: return instr::TypeUndef::Get();
				case TypeTagBool: return instr::TypeBool::Get();
				case TypeTagInt: return instr::TypeInt::Get();
				case TypeTagFloat: return instr::TypeFloat::Get();
				case TypeTagDouble: return instr::TypeDouble::Get();
				case TypeTagString: return instr::TypeString::Get();
				case TypeTagBytes: return instr::TypeBytes::Get();
				case TypeTagError: return instr::TypeError::Get();
				case TypeTagArray:{
					ir::TypeList* typeList = (ir::TypeList*)type.getReference();
					instr::Type* valueType = BuildType(pool, typeList->getType(0));
					return alloc(instr::TypeArray)(valueType);
				}break;
				case TypeTagReference:{
					ir::ImportName* importName = (ir::ImportName*)type.getReference();
					auto& exportName = importName->getResolution();
					if ( exportName ){
						switch ( exportName.kind ){
						case ExportKind::Class: return alloc(instr::TypeClass)((ir::Class*)exportName.reference);
						case ExportKind::Interface: return alloc(instr::TypeInterface)((ir::Interface*)exportName.reference);
						case ExportKind::Enum: return alloc(instr::TypeEnum)((ir::Enum*)exportName.reference);
						case ExportKind::Struct: return alloc(instr::TypeStruct)((ir::Struct*)exportName.reference);
						}
					}
					return instr::TypeError::Get();
				}break;
				default: {
					assert(false);
					return instr::TypeError::Get();
				}break;
				}

				#undef alloc
			}
		
			struct ShowTypeOperation{
				ShowTypeOperation(MemoryPoolSlice* hostPool, MemoryPoolSlice* tempPool)
					: hostPool(hostPool)
					, tempPool(tempPool)
					, parts(tempPool){
				}

				void show(Type* type){
					match(type)
						rule(TypeUndef, type)
							emmit("undef");
						erule
						rule(TypeUnit, type)
							emmit("unit");
						erule
						rule(TypeBool, type)
							emmit("bool");
						erule
						rule(TypeInt, type)
							emmit("int");
						erule
						rule(TypeFloat, type)
							emmit("float");
						erule
						rule(TypeDouble, type)
							emmit("double");
						erule
						rule(TypeString, type)
							emmit("string");
						erule
						rule(TypeStringLiteral, type)
							emmit("string '" + type->value + "'");
						erule
						rule(TypeBytes, type)
							emmit("bytes");
						erule
						rule(TypeError, type)
							emmit("error-t");
						erule
						rule(TypeNull, type)
							emmit("null-t");
						erule
						rule(TypeNumber, type)
							emmit("constant number");
						erule
						rule(TypeNumeric, type)
							emmit("numeric");
						erule
						rule(TypeClass, type)
							emmit("class " + type->class_->getOwner()->qid->asString() + "::" + type->class_->getName() );
						erule
						rule(TypeInterface, type)
							emmit("interface " + type->interface->getOwner()->qid->asString() + "::" + type->interface->getName() );
						erule
						rule(TypeEnum, type)
							emmit("enum " + type->enum_->getOwner()->qid->asString() + "::" + type->enum_->getName() );
						erule
						rule(TypeStruct, type)
							emmit("struct " + type->struct_->getOwner()->qid->asString() + "::" + type->struct_->getName() );
						erule
						rule(TypeOptional, type)
							emmit("optional ");
							show(type->valueType);
						erule
						rule(TypeArray, type)
							emmit("array.<");
							show(type->valueType);
							emmit(">");
						erule
						rule(TypeSet, type)
							emmit("set.<");
							show(type->keyType);
							emmit(">");
						erule
						rule(TypeMap, type)
							emmit("map.<");
							show(type->keyType);
							emmit(",");
							show(type->valueType);
							emmit(">");
						erule
						rule(TypeUnnamedEnum, type)
							emmit("(");
							show(type->params[0]);
							for ( size_t i = 1; i < type->paramsCount; i++ ){
								emmit("|");
								show(type->params[i]);
							}
							emmit(")");
						erule
						rule(TypeUnnamedStruct, type)
							emmit("{");
							show(type->params[0]);
							for ( size_t i = 1; i < type->paramsCount; i++ ){
								emmit(",");
								show(type->params[i]);
							}
							emmit("}");
						erule
						rule(TypeVar, type)
							emmit("@");
							emmit(type->name);
							emmit(format::integer(type->index).str());
						erule
						rule(TypeFunction, type)
							emmit("(");
							for ( size_t i = 0; i < type->paramsCount; i++ ){
								if ( i > 0 ){
									emmit(",");
								}
								show(type->params[i]);
							}
							emmit(")->");
							show(type->returnType);
						erule
						defrule(_)
							assert(false);
						erule
					ematch
				}

				StringRef make(){
					size_t totalLength = 0;
					iterate_enumerable(part, parts){
						totalLength += part.get().getLength();
					}
					u8* buffer = (u8*)hostPool->allocate(totalLength);
					StringRef result(buffer, totalLength);

					iterate_enumerable(part, parts){
						::memcpy(buffer, part.get().getData(), part.get().getLength());
						buffer += part.get().getLength();
					}

					return result;
				}

				void emmit(const Twine& twine){
					parts.push(twine.toString(tempPool));
				}

				MemoryPoolSlice* hostPool;
				MemoryPoolSlice* tempPool;
				ArrayList<StringRef> parts;
			};

			StringRef ShowType(MemoryPoolSlice* hostPool, MemoryPoolSlice& tempPool, Type* type){
				ShowTypeOperation operation(hostPool, &tempPool);
				operation.show(type);
				return operation.make();
			}

			bool Type::isNumericClass(){
				Type* root = getRepr();
				switch ( root->tag ){
				case TypeNumberTag:
				case TypeIntTag:
				case TypeFloatTag:
				case TypeDoubleTag:
				case TypeNumericTag:
					return true;
				}
				return false;
			}

			Type* Type::getRepr(){
				match(this)
					rule(TypeNumeric, type)
						if ( type->parent == this ){
							return this;
						}
						Type* root = type->parent->getRepr();
						type->parent = root;
						return root;
					erule
					rule(TypeVar, type)
						if ( type->parent == this ){
							return this;
						}
						Type* root = type->parent->getRepr();
						type->parent = root;
						return root;
					erule
					defrule(_)
						return this;
					erule
				ematch
			}

			namespace TypeNumberRank{
				Value MergeInRank(Value left, Value right){
					if ( left == Float && right == Int ){
						return Double;
					}else if ( left == Int && right == Float ){
						return Double;
					}else if ( left < right ){
						return right;
					}else{
						return left;
					}
				}

				Value MergeOutRank(Value left, Value right){
					if ( left == Constant ){
						return right;
					}
					if ( left == Float && right == Int ){
						return Constant;
					}else if ( left == Int && right == Float ){
						return Constant;
					}else if ( left < right ){
						return left;
					}else{
						return right;
					}
				}

				Type* GetTypeByRank(Value rank){
					switch ( rank ){
					case Int: return instr::TypeInt::Get();
					case Float: return instr::TypeFloat::Get();
					case Double: return instr::TypeDouble::Get();
					default: return nullptr;
					}
				}
			};
		}
	}
}