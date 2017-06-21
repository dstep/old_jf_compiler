#include <IR/Instr/Builtin.h>

namespace jf{
	namespace ir{		
		namespace instr{
			namespace BuiltinFunction{
				static TypeTemplateVar v0(0, TypeTemplateVar::Unconstrainted, "");
				static TypeTemplateVar v1(1, TypeTemplateVar::Unconstrainted, "");
				static TypeTemplateVar v2(2, TypeTemplateVar::Unconstrainted, "");

				static TypeTemplateVar* v0tvar[] = {&v0};
				
				static TypeTemplateVar n0(0, TypeTemplateVar::Numeric, "number");

				static TypeTemplateVar r0(0, TypeTemplateVar::Real, "real");
				
				static TypeTemplateVar* n0tvar[] = {&n0};
				static Type* n0n0[] = {&n0, &n0};
				static Type* n0p[] = {&n0};
				static Type* strstr[] = {instr::TypeString::Get(), instr::TypeString::Get()};
				
				static TypeTemplateVar* r0tvar[] = {&r0};
				static Type* r0p[] = {&r0};

				static ArrayRef<TypeTemplateVar*> emptytvar;
				static ArrayRef<Type*> emptyt;

				static TypeArray arrayv0(&v0);
				static Type* v0p[] = {&v0};

				Template Not(ID::Not, emptytvar, instr::TypeBool::Get(), nullptr, instr::TypeBool::Get());
				Template Negate(ID::Negate, n0tvar, &n0, nullptr, n0p);
				Template Plus(ID::Plus, n0tvar, &n0, nullptr, n0n0);
				Template Minus(ID::Minus, n0tvar, &n0, nullptr, n0n0);
				Template Multiply(ID::Multiply, n0tvar, &n0, nullptr, n0n0);
				Template Divide(ID::Divide, n0tvar, &n0, nullptr, n0n0);
				Template Remainder(ID::Remainder, n0tvar, &n0, nullptr, n0n0);

				Template Concat(ID::Concat, emptytvar, instr::TypeString::Get(), nullptr, strstr);

				Template NearbyInt(ID::NearbyInt, n0tvar, instr::TypeInt::Get(), nullptr, n0p); 
				Template NearbyFloat(ID::NearbyFloat, n0tvar, instr::TypeFloat::Get(), nullptr, n0p); 

				Template Round(ID::Round, r0tvar, &r0, nullptr, r0p);  
				Template Ceil(ID::Ceil, r0tvar, &r0, nullptr, r0p); 
				Template Floor(ID::Floor, r0tvar, &r0, nullptr, r0p);  
				Template Trunc(ID::Trunc, r0tvar, &r0, nullptr, r0p);  

				Template Sqrt(ID::Sqrt, r0tvar, &r0, nullptr, r0p);  

				Template EmptyArray(ID::EmptyArray, v0tvar, &arrayv0, nullptr, emptyt);  

				Template ArrayPush(ID::ArrayPush, v0tvar, instr::TypeUnit::Get(), &arrayv0, v0p);
				Template ArrayPop(ID::ArrayPop, v0tvar, instr::TypeUnit::Get(), &arrayv0, emptyt);
				Template ArrayClear(ID::ArrayClear, v0tvar, instr::TypeUnit::Get(), &arrayv0, emptyt);

				static Type* iv0p[] = {instr::TypeInt::Get(), &v0};
				Template ArraySet(ID::ArraySet, v0tvar, instr::TypeUnit::Get(), &arrayv0, iv0p);

				static Type* ip[] = {instr::TypeInt::Get()};
				Template ArrayGet(ID::ArrayGet, v0tvar, &v0, &arrayv0, ip);

				Template ArraySize(ID::ArraySize, v0tvar, instr::TypeInt::Get(), &arrayv0, emptyt);

				static Type* ifp[] = {instr::TypeInt::Get(), instr::TypeFloat::Get()};
				static Type* iip[] = {instr::TypeInt::Get(), instr::TypeInt::Get()};
				Template AllocateBytes(ID::AllocateBytes, emptytvar, instr::TypeBytes::Get(), nullptr, ip);
				Template BytesWriteFloat(ID::BytesWriteFloat, emptytvar, instr::TypeUnit::Get(), instr::TypeBytes::Get(), ifp);
				Template BytesWriteU16(ID::BytesWriteU16, emptytvar, instr::TypeUnit::Get(), instr::TypeBytes::Get(), iip);
			}

			#define ch(i) name.getData()[i]
			#define cmp(i, n, s) ::memcmp(name.getData() + i, s, n)

			BuiltinFunction::Template* FindPropertyArray(const StringRef& name){
				switch ( name.getLength() ){
				case 3:{
					switch ( ch(0) ){
					case 'p':{
						if ( !cmp(1, 2, "op") ) return &BuiltinFunction::ArrayPop;
					}break;
					case 'g':{
						if ( !cmp(1, 2, "et") ) return &BuiltinFunction::ArrayGet;
					}break;
					case 's':{
						if ( !cmp(1, 2, "et") ) return &BuiltinFunction::ArraySet;
					}break;
					}
				}break;
				case 4:{
					switch ( ch(0) ){
					case 'p':{
						if ( !cmp(1, 3, "ush") ) return &BuiltinFunction::ArrayPush;
					}break;
					case 's':{
						if ( !cmp(1, 3, "ize") ) return &BuiltinFunction::ArraySize;
					}break;
					}
				}break;
				case 5:{
					switch ( ch(0) ){
					case 'c':{
						if ( !cmp(1, 4, "lear") ) return &BuiltinFunction::ArrayClear;
					}break;
					}
				}break;
				}
				return nullptr;
			}

			BuiltinFunction::Template* FindPropertyBytes(const StringRef& name){
				switch ( name.getLength() ){
				case 10:{
					switch ( ch(0) ){
					case 'w':{
						if ( !cmp(1, 9, "riteFloat") ) return &BuiltinFunction::BytesWriteFloat;
					}break;
					}
				}break;
				case 8:{
					switch ( ch(0) ){
					case 'w':{
						if ( !cmp(1, 6, "riteU16") ) return &BuiltinFunction::BytesWriteU16;
					}break;
					}
				}break;
				}
				return nullptr;
			}

			BuiltinFunction::Template* FindBuiltinFunction(const StringRef& name){
				switch ( name.getLength() ){
				case 4:{
					switch ( ch(0) ){
					case 's':{
						if ( !cmp(1, 3, "qrt") ) return &BuiltinFunction::Sqrt;
					}break;
					case 'c':{
						if ( !cmp(1, 3, "eil") ) return &BuiltinFunction::Ceil;
					}break;
					}
				}break;
				case 5:{
					switch ( ch(0) ){
					case 'f':{
						if ( !cmp(1, 4, "loor") ) return &BuiltinFunction::Floor;
					}break;
					case 'r':{
						if ( !cmp(1, 4, "ound") ) return &BuiltinFunction::Round;
					}break;
					}
				}break;				
				case 9:{
					switch ( ch(0) ){
					case 'n':{
						if ( !cmp(1, 8, "earbyInt") ) return &BuiltinFunction::NearbyInt;
					}break;
					}
				}break;
				case 10:{
					switch ( ch(0) ){
					case 'e':{
						if ( !cmp(1, 9, "mptyArray") ) return &BuiltinFunction::EmptyArray;
					}break;
					}
				}break;
				case 11:{
					switch ( ch(0) ){
					case 'n':{
						if ( !cmp(1, 10, "earbyFloat") ) return &BuiltinFunction::NearbyFloat;
					}break;
					}
				}break;
				case 13:{
					switch ( ch(0) ){
					case 'a':{
						if ( !cmp(1, 12, "llocateBytes") ) return &BuiltinFunction::AllocateBytes;
					}break;
					}
				}break;
				}
				return nullptr;
			}
		}
	}
}