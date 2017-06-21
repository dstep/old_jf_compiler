#pragma once
#include "StringRef.h"
#include "SourceLoc.h"
#include "MemoryPool.h"
#include "Localization.h"

namespace jf{
	namespace DiagnosticType{
		enum Value{
			Trace,
			Info,
			Warning,
			Error
		};
	}

	class IDiagnosticContext{
	public:
		virtual DiagnosticType::Value getType() = 0;
		virtual StringRef getSubsystem() = 0;
		virtual StringRef getFile() = 0;
		virtual SrcSpan getSourceLocation() = 0;
		virtual StringRef getDiagnosticCode() = 0;
		virtual ILocalizationParamProvider& getParameters() = 0;
	};

	class DiagnosticDelegate: public IDiagnosticContext{
	public:
		DiagnosticDelegate(IDiagnosticContext& context)
			: context(context){
		}

		DiagnosticType::Value getType(){
			return context.getType();
		}

		StringRef getSubsystem(){
			return context.getSubsystem();
		}

		StringRef getFile(){
			return context.getFile();
		}

		SrcSpan getSourceLocation(){
			return context.getSourceLocation();
		}

		StringRef getDiagnosticCode(){
			return context.getDiagnosticCode();
		}

		ILocalizationParamProvider& getParameters(){
			return context.getParameters();
		}
	private:
		IDiagnosticContext& context;
	};

	class DiagnosticAt;
	class DiagnosticCode;
	class DiagnosticSetType;
	class DiagnosticParameters;
	class DiagnosticFile;

	template<class Value>
	class DiagnosticParameterValue;

	template<class T>
	class DiagnosticChain{
	public:
		DiagnosticFile file(const StringRef& where);
		DiagnosticAt at(const SrcSpan& where);
		DiagnosticCode code(const StringRef& code);
		DiagnosticSetType type(DiagnosticType::Value type);
		DiagnosticParameters parameters(ILocalizationParamProvider& provider);
	
		template<class Value>
		DiagnosticParameterValue<Value> parameter(const StringRef& key, const Value& value);
		template<class Value>
		DiagnosticParameterValue<Value> parameter_if(bool condition, const StringRef& key, const Value& value);
	};
	
	class DiagnosticAt: public DiagnosticDelegate, public DiagnosticChain<DiagnosticAt>{
	public:
		DiagnosticAt(IDiagnosticContext& context, const SrcSpan& where)
			: DiagnosticDelegate(context)
			, where(where){
		}

		SrcSpan getSourceLocation(){
			return where;
		}
	private:
		SrcSpan where;
	};

	class DiagnosticFile: public DiagnosticDelegate, public DiagnosticChain<DiagnosticFile>{
	public:
		DiagnosticFile(IDiagnosticContext& context, const StringRef& file)
			: DiagnosticDelegate(context)
			, file(file){
		}

		StringRef getFile(){
			return file;
		}
	private:
		StringRef file;
	};

	class DiagnosticCode: public DiagnosticDelegate, public DiagnosticChain<DiagnosticCode>{
	public:
		DiagnosticCode(IDiagnosticContext& context, const StringRef& code)
			: DiagnosticDelegate(context)
			, code(code){
		}

		StringRef getDiagnosticCode(){
			return code;
		}
	private:
		StringRef code;
	};

	class DiagnosticSetType: public DiagnosticDelegate, public DiagnosticChain<DiagnosticSetType>{
	public:
		DiagnosticSetType(IDiagnosticContext& context, DiagnosticType::Value type)
			: DiagnosticDelegate(context)
			, type(type){
		}

		DiagnosticType::Value getType(){
			return type;
		}
	private:
		DiagnosticType::Value type;
	};

	class DiagnosticParameters: public DiagnosticDelegate, public DiagnosticChain<DiagnosticParameters>, private ILocalizationParamProvider{
	public:
		DiagnosticParameters(IDiagnosticContext& context, ILocalizationParamProvider& provider)
			: DiagnosticDelegate(context)
			, provider(provider){
		}

		ILocalizationParamProvider& getParameters(){
			return *this;
		}
	private:
		void accept(ILocalizationParamVisitor& visitor){
			provider.accept(visitor);
			DiagnosticDelegate::getParameters().accept(visitor);
		}

		ILocalizationParamProvider& provider;
	};

	template<class Value>
	class DiagnosticParameterValue: public DiagnosticDelegate, public DiagnosticChain< DiagnosticParameterValue<Value> >, private ILocalizationParamProvider{
	public:
		DiagnosticParameterValue(IDiagnosticContext& context, bool condition, const StringRef& key, const Value& value)
			: DiagnosticDelegate(context)
			, condition(condition)
			, key(key)
			, value(value){
		}

		ILocalizationParamProvider& getParameters(){
			return *this;
		}
	private:
		void accept(ILocalizationParamVisitor& visitor){
			if ( condition ){
				visitor.visitValue(key, value);
			}
			DiagnosticDelegate::getParameters().accept(visitor);
		}

		StringRef key;
		const Value& value;
		bool condition;
	};

	class Subsystem: public IDiagnosticContext, private ILocalizationParamProvider, public DiagnosticChain<Subsystem>{
	public:
		Subsystem(const StringRef& subsystem)
			: subsystem(subsystem){
		}

		DiagnosticType::Value getType(){
			return DiagnosticType::Trace;
		}

		StringRef getSubsystem(){
			return subsystem;
		}

		StringRef getFile(){
			return "";
		}

		SrcSpan getSourceLocation(){
			return SrcSpan::Undefined();
		}

		StringRef getDiagnosticCode(){
			return "";
		}

		ILocalizationParamProvider& getParameters(){
			return *this;
		}
	private:
		void accept(ILocalizationParamVisitor&){
		}

		StringRef subsystem;
	};

	template<class T>
	DiagnosticAt DiagnosticChain<T>::at(const SrcSpan& where){
		return DiagnosticAt(*(T*)this, where);
	}

	template<class T>
	DiagnosticCode DiagnosticChain<T>::code(const StringRef& code){
		return DiagnosticCode(*(T*)this, code);
	}

	template<class T>
	DiagnosticFile DiagnosticChain<T>::file(const StringRef& file){
		return DiagnosticFile(*(T*)this, file);
	}

	template<class T>
	DiagnosticSetType DiagnosticChain<T>::type(DiagnosticType::Value type){
		return DiagnosticSetType(*(T*)this, type);
	}

	template<class T>
	template<class Value>
	DiagnosticParameterValue<Value> DiagnosticChain<T>::parameter(const StringRef& key, const Value& value){
		return DiagnosticParameterValue<Value>(*(T*)this, true, key, value);
	}

	template<class T>
	template<class Value>
	DiagnosticParameterValue<Value> DiagnosticChain<T>::parameter_if(bool condition, const StringRef& key, const Value& value){
		return DiagnosticParameterValue<Value>(*(T*)this, condition, key, value);
	}

	template<class T>
	DiagnosticParameters DiagnosticChain<T>::parameters(ILocalizationParamProvider& provider){
		return DiagnosticParameters(*(T*)this, provider);
	}
		
	class IDiagnosticStream{
	public:
		virtual void report(IDiagnosticContext& context) = 0;
	};
}