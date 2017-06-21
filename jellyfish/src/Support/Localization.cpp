#include <Support/Localization.h>
#include <Support/Container/ArrayList.h>
#include <Support/Match.h>
#include <Support/Container/SearchTree.h>
#include <Support/Twine.h>

namespace jf{
	LocalizationParseError::LocalizationParseError(const StringRef& relatedText)
		: relatedText(relatedText){
	}

	LocalizationDictionary::LocalizationDictionary()
		: error(StringRef()){
	}

	struct ParamNode{
		ParamNode* next;
		StringRef string;
	};

	struct ParamNodePair{
		ParamNode* first;
		ParamNode* last;

		ParamNodePair()
			: first(nullptr)
			, last(nullptr){
		}
	};

	class EmptyProvider: public ILocalizationParamProvider{
	public:
		void accept(ILocalizationParamVisitor& visitor){
		}
	};
	
	class ReferenceProvider: public ILocalizationParamProvider{
	public:
		ReferenceProvider(const ReferencedSymbol* symbol)
			: symbol(symbol){
		}

		void accept(ILocalizationParamVisitor& visitor){
			if ( symbol->localizableName.getLength() > 0 ){
				visitor.visitLocalizableString("type", symbol->localizableName);
			}
			visitor.visitValue("file", PlainString(symbol->fileName));
			visitor.visitValue("where", symbol->where);
			if ( symbol->identifier.getLength() > 0 ){
				visitor.visitValue("identifier", StringLiteral(symbol->identifier));
			}
		}
	private:
		const ReferencedSymbol* symbol;
	};

	class ParamVisitor: public ILocalizationParamVisitor{
	public:
		ParamVisitor(LocalizationDictionary* dictionary, MemoryPoolSlice& tempPool)
			: dictionary(dictionary)
			, tempPool(tempPool){
		}

		void visitValue(const StringRef& key, const SrcSpan& value){
			char buffer[64];
			sprintf(buffer, "(%d,%d)", value.from().getLine(), value.from().getCol() + 1);
			insert(key, StringRef(buffer).slice(&tempPool));
		}

		void visitValue(const StringRef& key, const Integer& value){
			char buffer[64];
			sprintf(buffer, "%llu", value.value);
			insert(key, StringRef(buffer).slice(&tempPool));
		}

		void visitValue(const StringRef& key, const PlainString& string){
			insert(key, string.value.slice(&tempPool));
		}

		void visitValue(const StringRef& key, const StringLiteral& string){
			//TODO:: proper escaping
			insert(key, ("\"" + string.value + "\"").toString(&tempPool));
		}

		void visitValue(const StringRef& key, const ReferencedSymbol& value){
			ReferenceProvider provider(&value);
			insert(key, dictionary->makeLocalizedString(&tempPool, tempPool, "ReferencedSymbol", provider));
		}

		void visitLocalizableString(const StringRef& key, const StringRef& localizableString){
			EmptyProvider provider;
			insert(key, dictionary->makeLocalizedString(&tempPool, tempPool, localizableString, provider));
		}

		void insert(const StringRef& key, const StringRef& value){
			ParamNodePair& pair = tree.getOrInsert(&tempPool, key);
			ParamNode* newNode = (ParamNode*)tempPool.allocate(sizeof(ParamNode));
			newNode->next = nullptr;
			newNode->string = value;
			if ( pair.last ){
				pair.last->next = newNode;
				pair.last = newNode;
			}else{
				pair.last = pair.first = newNode;
			}
		}

		MemoryPoolSlice& tempPool;
		LocalizationDictionary* dictionary;
		container::SearchTree<StringRef, ParamNodePair, StringRef::Compare> tree;
	};

	StringRef LocalizationDictionary::makeLocalizedString(MemoryPoolSlice* hostPool, MemoryPoolSlice& tempPool, const StringRef& code, ILocalizationParamProvider& params){
		container::ArrayList<StringRef> parts(&tempPool);
		container::ArrayList<LocalizedStringNode*> nodeStack(&tempPool);

		LocalizedStringNode* node = getLocalizedString(code);
		if ( !node ){
			parts.push("{missing:");
			parts.push(code);
			parts.push("}");
		}
		ParamVisitor visitor(this, tempPool);
		
		params.accept(visitor);

		while ( node ){
			match(node)
				rule(LocalizedStringPlain, node)
					parts.push(node->string);
				erule
				rule(LocalizedStringIf, if_node)
					ParamNode* param = visitor.tree.find(if_node->param).first;
					LocalizedStringNode* newNode = nullptr;					
					if ( param ){
						newNode = if_node->ifGiven;
					}else{
						newNode = if_node->ifNotGiven;
					}
					if ( newNode ){
						nodeStack.push(node->next);
						node = newNode;
						continue;
					}
				erule
				rule(LocalizedStringParam, node)
					ParamNode* param = visitor.tree.find(node->param).first;
					if ( param ){
						parts.push(param->string);
						param = param->next;
						while ( param ){
							parts.push(node->separator);
							parts.push(param->string);
							param = param->next;
						}
					}else{
						parts.push(node->alt);
					}
				erule
				nodefrule
			ematch
			node = node->next;
			if ( !node && nodeStack.getSize() > 0 ){
				node = nodeStack.get(nodeStack.getSize() - 1);
				nodeStack.pop();
			}
		}

		size_t totalLength = 0;
		for ( auto e = parts.enumerate(); e.hasNext(); e.advance() ){
			totalLength += e.get().getLength();
		}

		u8* buffer = (u8*)hostPool->allocate(totalLength);
		StringRef result(buffer, totalLength);
		for ( auto e = parts.enumerate(); e.hasNext(); e.advance() ){
			::memcpy(buffer, e.get().getData(), e.get().getLength());
			buffer += e.get().getLength();
		}
		return result;
	}

	LocalizedStringNode* LocalizationDictionary::getLocalizedString(const StringRef& code){
		return strings.find(code);
	}

	LocalizedStringNode* LocalizationDictionary::parseLocalizationString(const u8* data, size_t length, size_t& i, bool& wasError){
		LocalizedStringNode* first = nullptr;
		LocalizedStringNode** last = &first;
		size_t j = i;
		for ( ; i <= length; ){
			if ( i == length || data[i] == '}' || data[i] == '{' || data[i] == '|' ){
				if ( i - j > 0 ){
					LocalizedStringPlain* node = new (allocate(sizeof(LocalizedStringPlain))) LocalizedStringPlain(StringRef(data + j, i - j).slice(this));
					*last = node;
					last = &node->next;
				}
				if ( i == length || data[i] == '}' || data[i] == '|' ){
					break;
				}

				//{
				i++;
				j = i;
				StringRef key, alt, sep;
				for ( ; i <= length; i++ ){
					if ( i == length || data[i] == '@' || data[i] == '|' || data[i] == '}' || data[i] == '?' ){
						key = StringRef(data + j, i - j).slice(this);
						break;
					}else if ( data[i] == '\\' ){
						if ( i < length - 1 ){
							i++;
						}
					}
				}
				if ( i < length && data[i] == '?' ){
					i++;
					j = i;
					LocalizedStringNode* ifNode = parseLocalizationString(data, length, i, wasError);
					if ( data[i] != '|' ){
						if ( !wasError ){
							wasError = true;
							error = StringRef(data + i, length - i);
						}
					}else{
						i++;
					}
					LocalizedStringNode* elseNode = parseLocalizationString(data, length, i, wasError);
					if ( data[i] != '}' ){
						if ( !wasError ){
							wasError = true;
							error = StringRef(data + i, length - i);
						}
					}else{
						i++;
					}
					LocalizedStringIf* node = new (allocate(sizeof(LocalizedStringIf))) LocalizedStringIf(key, ifNode, elseNode);
					*last = node;
					last = &node->next;
					j = i;
					continue;
				}
				if ( i < length && data[i] == '@' ){
					i++;
					j = i;
					for ( ; i <= length; i++ ){
						if ( i == length || data[i] == '|' || data[i] == '}' ){
							sep = StringRef(data + j, i - j).slice(this);
							break;
						}else if ( data[i] == '\\' ){
							if ( i < length - 1 ){
								i++;
							}
						}
					}
				}
				if ( i < length && data[i] == '|' ){
					i++;
					j = i;
					for ( ; i <= length; i++ ){
						if ( i == length || data[i] == '}' ){
							alt = StringRef(data + j, i - j).slice(this);
							break;
						}else if ( data[i] == '\\' ){
							if ( i < length - 1 ){
								i++;
							}
						}
					}
				}
				if ( i < length && data[i] == '}' ){
					i++;
				}else if ( !wasError ){
					wasError = true;
					error = StringRef(data, length);
				}
				j = i;
				LocalizedStringParam* node = new (allocate(sizeof(LocalizedStringParam))) LocalizedStringParam(key, sep, alt);
				*last = node;
				last = &node->next;
			}else if ( data[i] == '\\' ){
				i++;
				if ( i < length - 1 ){
					i++;
				}
			}else{
				i++;
			}
		}
		if ( i > length ){
			i = length;
		}
		return first;
	}


	LocalizationParseError* LocalizationDictionary::addLocalization(const StringRef& key, const StringRef& value){
		bool wasError = false;
		const u8* data = value.getData();
		size_t length = value.getLength();
		size_t i = 0;
		LocalizedStringNode* node = parseLocalizationString(data, length, i, wasError);
		if ( !wasError && i != length ){
			wasError = true;
			error = StringRef(data + i, length - i);
		}
		strings.getOrInsert(this, key) = node;
		return wasError ? &error : nullptr;
	}
}