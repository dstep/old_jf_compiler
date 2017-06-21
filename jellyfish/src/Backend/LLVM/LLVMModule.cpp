#include <Backend/LLVM/LLVMModule.h>
#include <Backend/LLVM/Common.h>
#include <Support/Container/ArrayList.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/raw_ostream.h>

namespace jf{
	namespace backend{
		namespace llvm{
			LLVMModule::LLVMModule(MemoryPoolSlice* tempPool, const StringRef& moduleId, LLVMContext* context)
				: tempPool(tempPool)
				, context(context)
				, globalFunctions(tempPool)
				, classConstructors(tempPool)
				, classMethods(tempPool)
				, classTables(tempPool)
				, classImplements(tempPool){

				module = new ::llvm::Module(toLLVM(moduleId), context->getContext());

				for ( size_t i = 0; i < Intrinsic::Count; i++ ){
					intrinsics[i] = nullptr;
				}
			}

			LLVMModule::~LLVMModule(){
				if ( module ){
					delete module;
				}
			}

			ModuleArchive* LLVMModule::archiveModule(MemoryPoolSlice& tempPool, MemoryPoolSlice* hostPool){
				::llvm::SmallVector<char, 1 * 1024 * 1024>* out = new(tempPool.allocate(sizeof(::llvm::SmallVector<char, 1 * 1024 * 1024>)))::llvm::SmallVector<char, 1 * 1024 * 1024>();
				
				{
					::llvm::raw_svector_ostream stream(*out);
					::llvm::WriteBitcodeToFile(module, stream);
				}

				return new(hostPool->allocate(sizeof(ModuleArchive)))ModuleArchive(MakeArrayRef((u8*)out->data(), out->size()).copy(hostPool));
			}

			::llvm::Constant* LLVMModule::getIntrinsic(Intrinsic::ID intrinsic){
				if ( intrinsics[intrinsic] ){
					return intrinsics[intrinsic];
				}
				return intrinsics[intrinsic] = createIntrinsic(intrinsic);
			}

			::llvm::GlobalVariable* LLVMModule::getClassImplementsTable(ir::Class* class_){
				ClassLayout* layout = context->getClassLayout(class_);
				::llvm::GlobalVariable*& implementsTable = classImplements.getOrInsert(layout);
				if ( !implementsTable ){
					implementsTable = layout->createImplementsTable(this);
				}
				return implementsTable;
			}

			::llvm::Constant* LLVMModule::getInterfaceImplement(ClassLayout* class_, ir::Interface* interface){
				::llvm::GlobalVariable*& implementsTable = classImplements.getOrInsert(class_);
				if ( !implementsTable ){
					implementsTable = class_->createImplementsTable(this);
				}
				return class_->getInterfaceFromImplementsTable(implementsTable, interface);
			}

			::llvm::Constant* LLVMModule::createIntrinsic(Intrinsic::ID intrinsic){
				switch ( intrinsic ){
				case Intrinsic::UnwindConstructorCallback:{
					::llvm::Type* ptrType = ::llvm::Type::getInt8PtrTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_unwind_constructor_stack", ::llvm::Type::getVoidTy(context->getContext()), ptrType, ptrType, nullptr);
				}break;
				case Intrinsic::AllocateObject:{
					::llvm::Type* intType = ::llvm::Type::getInt32Ty(context->getContext());
					::llvm::Type* ptrType = ::llvm::Type::getInt8PtrTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_allocate_object", ptrType, intType, nullptr);
				}break;
				case Intrinsic::MakeString:{
					::llvm::Type* params[] = {::llvm::Type::getInt8PtrTy(context->getContext()), ::llvm::Type::getInt32Ty(context->getContext())};
					return getModule()->getOrInsertFunction("__jf_make_string", ::llvm::Type::getInt8PtrTy(context->getContext()), params[0], params[1], nullptr);
				}break;
				case Intrinsic::StringEqual:{
					return getModule()->getOrInsertFunction("__jf_string_equal", context->getI1Type(), context->getSmallStringType()->getPointerTo(), context->getSmallStringType()->getPointerTo(), nullptr);
				}break;
				case Intrinsic::StringCompare:{
					return getModule()->getOrInsertFunction("__jf_string_compare", context->getI32Type(), context->getSmallStringType()->getPointerTo(), context->getSmallStringType()->getPointerTo(), nullptr);
				}break;
				case Intrinsic::StringConcat:{
					return getModule()->getOrInsertFunction("__jf_string_concat", context->getVoidType(), context->getSmallStringType()->getPointerTo(), context->getSmallStringType()->getPointerTo(), context->getSmallStringType()->getPointerTo(), nullptr);
				}break;	

				case Intrinsic::FloatCeil:{
					::llvm::Type* floatType = ::llvm::Type::getFloatTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_float_ceil", floatType, floatType, nullptr);
				}break;		
				case Intrinsic::DoubleCeil:{
					::llvm::Type* doubleType = ::llvm::Type::getDoubleTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_double_ceil", doubleType, doubleType, nullptr);
				}break;	

				case Intrinsic::FloatSqrt:{
					::llvm::Type* floatType = ::llvm::Type::getFloatTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_float_sqrt", floatType, floatType, nullptr);
				}break;		
				case Intrinsic::DoubleSqrt:{
					::llvm::Type* doubleType = ::llvm::Type::getDoubleTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_double_sqrt", doubleType, doubleType, nullptr);
				}break;	

				case Intrinsic::FloatFloor:{
					::llvm::Type* floatType = ::llvm::Type::getFloatTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_float_ceil", floatType, floatType, nullptr);
				}break;		
				case Intrinsic::DoubleFloor:{
					::llvm::Type* doubleType = ::llvm::Type::getDoubleTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_double_ceil", doubleType, doubleType, nullptr);
				}break;	
				
				case Intrinsic::FloatRound:{
					::llvm::Type* floatType = ::llvm::Type::getFloatTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_float_round", floatType, floatType, nullptr);
				}break;		
				case Intrinsic::DoubleRound:{
					::llvm::Type* doubleType = ::llvm::Type::getDoubleTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_double_round", doubleType, doubleType, nullptr);
				}break;	
				
				case Intrinsic::IntNearbyFloat:{
					::llvm::Type* intType = ::llvm::Type::getInt32Ty(context->getContext());
					::llvm::Type* floatType = ::llvm::Type::getFloatTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_int_nearby_float", floatType, intType, nullptr);
				}break;		
				case Intrinsic::DoubleNearbyFloat:{
					::llvm::Type* floatType = ::llvm::Type::getFloatTy(context->getContext());
					::llvm::Type* doubleType = ::llvm::Type::getDoubleTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_double_nearby_float", floatType, doubleType, nullptr);
				}break;	

				case Intrinsic::FloatNearbyInt:{
					::llvm::Type* intType = ::llvm::Type::getInt32Ty(context->getContext());
					::llvm::Type* floatType = ::llvm::Type::getFloatTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_float_nearby_int", intType, floatType, nullptr);
				}break;		
				case Intrinsic::DoubleNearbyInt:{
					::llvm::Type* intType = ::llvm::Type::getInt32Ty(context->getContext());
					::llvm::Type* doubleType = ::llvm::Type::getDoubleTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_double_nearby_int", intType, doubleType, nullptr);
				}break;	

				case Intrinsic::EmptyArray:{
					::llvm::Type* intType = ::llvm::Type::getInt32Ty(context->getContext());
					::llvm::Type* ptrType = ::llvm::Type::getInt8PtrTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_empty_array", ptrType, intType, ptrType, nullptr);
				}break;

				case Intrinsic::ArrayPush:{
					::llvm::Type* ptrType = ::llvm::Type::getInt8PtrTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_array_push", ptrType, ptrType, nullptr);
				}break;
				case Intrinsic::ArrayPop:{
					::llvm::Type* ptrType = ::llvm::Type::getInt8PtrTy(context->getContext());
					::llvm::Type* voidType = ::llvm::Type::getVoidTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_array_pop", voidType, ptrType, nullptr);
				}break;
				case Intrinsic::ArrayClear:{
					::llvm::Type* ptrType = ::llvm::Type::getInt8PtrTy(context->getContext());
					::llvm::Type* voidType = ::llvm::Type::getVoidTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_array_clear", voidType, ptrType, nullptr);
				}break;
				case Intrinsic::ArrayRef:{
					::llvm::Type* ptrType = ::llvm::Type::getInt8PtrTy(context->getContext());
					::llvm::Type* intType = ::llvm::Type::getInt32Ty(context->getContext());
					return getModule()->getOrInsertFunction("__jf_array_ref", ptrType, ptrType, intType, nullptr);
				}break;
				case Intrinsic::ArraySize:{
					::llvm::Type* ptrType = ::llvm::Type::getInt8PtrTy(context->getContext());
					::llvm::Type* intType = ::llvm::Type::getInt32Ty(context->getContext());
					return getModule()->getOrInsertFunction("__jf_array_size", intType, ptrType, nullptr);
				}break;

				case Intrinsic::AllocateBytes:{
					::llvm::Type* ptrType = ::llvm::Type::getInt8PtrTy(context->getContext());
					::llvm::Type* intType = ::llvm::Type::getInt32Ty(context->getContext());
					return getModule()->getOrInsertFunction("__jf_allocate_bytes", ptrType, intType, nullptr);
				}break;
				case Intrinsic::BytesWriteFloat:{
					::llvm::Type* voidType = ::llvm::Type::getVoidTy(context->getContext());
					::llvm::Type* ptrType = ::llvm::Type::getInt8PtrTy(context->getContext());
					::llvm::Type* intType = ::llvm::Type::getInt32Ty(context->getContext());
					::llvm::Type* floatType = ::llvm::Type::getFloatTy(context->getContext());
					return getModule()->getOrInsertFunction("__jf_write_float", voidType, intType, ptrType, intType, floatType, nullptr);
				}break;
				case Intrinsic::BytesWriteU16:{
					::llvm::Type* voidType = ::llvm::Type::getVoidTy(context->getContext());
					::llvm::Type* ptrType = ::llvm::Type::getInt8PtrTy(context->getContext());
					::llvm::Type* intType = ::llvm::Type::getInt32Ty(context->getContext());
					return getModule()->getOrInsertFunction("__jf_write_u16", voidType, intType, ptrType, intType, intType, nullptr);
				}break;
				default: unreachable;
				}
			}

			::llvm::Function* LLVMModule::getDeclaration(ir::GlobalFunction* globalFunction){
				::llvm::Function*& function = globalFunctions.getOrInsert(globalFunction);
				if ( !function ){
					function = createDeclaration(globalFunction);
				}
				return function;
			}

			::llvm::Function* LLVMModule::getDeclaration(ir::ClassMethod* method){
				::llvm::Function*& function = classMethods.getOrInsert(method);
				if ( !function ){
					function = createDeclaration(method);
				}
				return function;
			}

			::llvm::Function* LLVMModule::getDeclaration(ir::ClassConstructor* constructor){
				auto& function = classConstructors.getOrInsert(constructor);
				if ( !function.first ){
					function.first = createDeclaration(constructor);
				}
				return function.first;
			}

			::llvm::Function* LLVMModule::getClosureDeclaration(ir::ClassConstructor* constructor){
				auto& function = classConstructors.getOrInsert(constructor);
				if ( !function.second ){
					function.second = createClosureDeclaration(constructor);
				}
				return function.second;
			}

			::llvm::GlobalVariable* LLVMModule::getClassTable(ir::Class* class_){
				::llvm::GlobalVariable*& variable = classTables.getOrInsert(class_);
				if ( !variable ){
					variable = createClassTable(class_);
				}
				return variable;
			}

			::llvm::GlobalVariable* LLVMModule::createClassTable(ir::Class* class_){
				ClassLayout* layout = context->getClassLayout(class_);
				::llvm::GlobalVariable* variable = new ::llvm::GlobalVariable
					(
						*module, 
						layout->getClassVTableType(),
						true,
						::llvm::GlobalValue::ExternalLinkage, 
						nullptr, 
						toLLVM(class_->getOwner()->qid->asString()) + ".C" + toLLVM(class_->getName()) + ".@vtable"
					); 
				return variable;
			}

			::llvm::Function* LLVMModule::createDeclaration(ir::ClassConstructor* constructor){
				ArrayList<::llvm::Type*> params(tempPool);
				::llvm::Type* result = ::llvm::Type::getVoidTy(context->getContext());
				ClassLayout* layout = context->getClassLayout(constructor->getOwner());
				params.push(::llvm::Type::getInt8PtrTy(context->getContext()));
				params.push(::llvm::Type::getInt8PtrTy(context->getContext()));
				params.push(layout->getObjectType());
				iterate_array(param, constructor->getSignature()->getParams()){
					context->fillParams(param.get().getType(), params);
				}
				if ( !result ){
					result = ::llvm::Type::getVoidTy(context->getContext());
				}

				::llvm::FunctionType* fTy = ::llvm::FunctionType::get(result, toLLVM(params.asFlatArray(tempPool)), false);
				::llvm::Function* function = 
					::llvm::Function::Create
						(
							fTy,
							::llvm::GlobalValue::ExternalLinkage,
							toLLVM
								(
									constructor->getOwner()->getOwner()->qid->asString()) 
										+ ".C" + toLLVM(constructor->getOwner()->getName())
										+ ".K" + toLLVM(constructor->getName()
								), 
							module
						);

				function->setCallingConv(::llvm::CallingConv::Fast);

				return function;
			}

			::llvm::Function* LLVMModule::createClosureDeclaration(ir::ClassConstructor* constructor){
				::llvm::Type* result = ::llvm::Type::getVoidTy(context->getContext());
				ClassLayout* layout = context->getClassLayout(constructor->getOwner());
				::llvm::Type* params[] =
					{
						::llvm::Type::getInt8PtrTy(context->getContext()),
						::llvm::Type::getInt8PtrTy(context->getContext()),
						layout->getObjectType()
					};

				::llvm::FunctionType* fTy = ::llvm::FunctionType::get(result, params, false);
				::llvm::Function* function = 
					::llvm::Function::Create
						(
							fTy,
							::llvm::GlobalValue::ExternalLinkage,
							toLLVM
								(
									constructor->getOwner()->getOwner()->qid->asString()) 
										+ ".C" + toLLVM(constructor->getOwner()->getName())
										+ ".K$" + toLLVM(constructor->getName()
								), 
							module
						);

				function->setCallingConv(::llvm::CallingConv::Fast);

				return function;
			}

			::llvm::Function* LLVMModule::createDeclaration(ir::ClassMethod* method){
				::llvm::FunctionType* fTy = context->getMethodType(method);
				::llvm::Function* function = 
					::llvm::Function::Create
						(
							fTy,
							::llvm::GlobalValue::ExternalLinkage,
							toLLVM
								(
									method->getOwner()->getOwner()->qid->asString()) 
										+ ".C" + toLLVM(method->getOwner()->getName())
										+ ".M" + toLLVM(method->getName()
								), 
							module
						);

				function->setCallingConv(::llvm::CallingConv::Fast);

				return function;
			}

			::llvm::Function* LLVMModule::createDeclaration(ir::GlobalFunction* globalFunction){
				ArrayList<::llvm::Type*> params(tempPool);
				::llvm::Type* result = nullptr;

				context->fillReturnValue(globalFunction->getSignature()->getReturnType(), result, params);
				iterate_array(param, globalFunction->getSignature()->getParams()){
					context->fillParams(param.get().getType(), params);
				}

				if ( !result ){
					result = ::llvm::Type::getVoidTy(context->getContext());
				}

				::llvm::FunctionType* fTy = ::llvm::FunctionType::get(result, toLLVM(params.asFlatArray(tempPool)), false);
				::llvm::Function* function = 
					::llvm::Function::Create
						(
							fTy,
							::llvm::GlobalValue::ExternalLinkage,
							toLLVM
								(
									globalFunction->getOwner()->qid->asString()) 
										+ ".F" 
										+ toLLVM(globalFunction->getName()
								), 
							module
						);

				function->setCallingConv(::llvm::CallingConv::Fast);

				return function;
			}
		}
	}
}