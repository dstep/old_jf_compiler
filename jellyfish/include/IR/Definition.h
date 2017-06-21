#pragma once
#include <Parser/AST/AST.h>

namespace jf{
	namespace ir{
		namespace instr{
			class FunctionFrame;
		}

		class Initializer{
		public:
			Initializer(parser::ast::Expr* ast)
				: ast(ast){
			}

			parser::ast::Expr* getAST(){
				return ast;
			}
		private:
			parser::ast::Expr* ast;
		};

		enum FunctionBodyTag{
			FunctionBodyCodeTag,
			FunctionBodyFFITag
		};

		class FunctionBody{
		public:
			FunctionBodyTag tag;

			FunctionBody(FunctionBodyTag tag, const SrcSpan& where)
				: tag(tag)
				, where(where){
			}

			const SrcSpan& getSrcLoc(){
				return where;
			}
		private:
			SrcSpan where;
		};

		class FunctionBodyFFI: public FunctionBody{
		public:
			FunctionBodyFFI(const SrcSpan& where, const StringRef& string)
				: FunctionBody(FunctionBodyFFITag, where)
				, string(string){
			}

			const StringRef& getString(){
				return string;
			}
		private:
			StringRef string;
		};

		class FunctionBodyCode: public FunctionBody{
		public:
			FunctionBodyCode(const SrcSpan& where, parser::ast::Stmt* ast)
				: FunctionBody(FunctionBodyCodeTag, where)
				, ast(ast)
				, frame(nullptr){
			}

			parser::ast::Stmt* getAST(){
				return ast;
			}

			instr::FunctionFrame* getFrame(){
				return frame;
			}

			void setFrame(instr::FunctionFrame* frame){
				this->frame = frame;
			}
		private:
			instr::FunctionFrame* frame;
			parser::ast::Stmt* ast;
		};
	}
}