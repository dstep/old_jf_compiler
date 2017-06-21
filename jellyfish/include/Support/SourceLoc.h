#pragma once
#include "Types.h"

namespace jf{
	class SrcLoc{
	public:
		static const u32 ValueUndefined = 0xffffffffu;

		SrcLoc(u32 line, u32 col)
			: line(line)
			, col(col){
		}

		static SrcLoc Undefined(){
			return SrcLoc(ValueUndefined, ValueUndefined);
		}

		static SrcLoc Line(u32 line){
			return SrcLoc(line, ValueUndefined);
		}

		u32 getLine() const{
			return line;
		}

		u32 getCol() const{
			return col;
		}

		bool isUndefined() const{
			return line == ValueUndefined && col == ValueUndefined;
		}

		bool operator==(const SrcLoc& other) const{
			return line == other.line && col == other.col;
		}

		bool operator<(const SrcLoc& other) const{
			if ( line < other.line ){
				return true;
			}
			if ( line > other.line ){
				return false;
			}
			return col < other.col;
		}
	private:
		u32 line, col;
	};

	class SrcSpan{
	public:
		SrcSpan(u32 lineBegin, u32 colBegin, u32 lineEnd, u32 colEnd)
			: begin(lineBegin, colBegin)
			, end(lineEnd, colEnd){
		}

		SrcSpan(const SrcSpan& left, const SrcSpan& right)
			: begin(left.from() < right.from() ? left.from() : right.from())
			, end(left.to() < right.to() ? right.to() : left.to()){		
		}

		SrcSpan(const SrcLoc& begin, const SrcLoc& end)
			: begin(begin)
			, end(end){
		}

		static SrcSpan Undefined(){
			return SrcSpan(SrcLoc::Undefined(), SrcLoc::Undefined());
		}

		static SrcSpan Line(u32 line){
			return SrcSpan(SrcLoc::Line(line), SrcLoc::Line(line));
		}

		SrcLoc from() const{
			return begin;
		}

		SrcLoc to() const{
			return end;
		}

		bool isUndefined() const{
			return begin.isUndefined() && end.isUndefined();
		}
	private:
		SrcLoc begin, end;
	};
}