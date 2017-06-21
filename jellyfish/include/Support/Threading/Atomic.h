#pragma once
#include "../Types.h"

namespace jf{
	namespace threading{
		namespace system{
			s32 CompareAndSwap(s32 volatile * pointer, s32 compare, s32 swap);
			s64 CompareAndSwap(s64 volatile * pointer, s64 compare, s64 swap);
			void* CompareAndSwap(void* volatile * pointer, void* compare, void* swap);
			s32 AtomicIncrement(s32 volatile* pointer);
			s32 AtomicDecrement(s32 volatile* pointer);
		}

		class AtomicInt{
		public:
			AtomicInt(s32 value)
				: value(value){
			}

			s32 increment(){
				return system::AtomicIncrement(&value);
			}

			s32 decrement(){
				return system::AtomicDecrement(&value);
			}

			s32 read(){
				return value;
			}

			void write(s32 value){
				this->value = value;
			}

			s32 compareAndSwap(s32 compare, s32 swap){
				return system::CompareAndSwap(&value, compare, swap);
			}
		private:
			volatile s32 value;
		};

		class AtomicPointerBase{
		public:
			AtomicPointerBase(void* value)
				: value(value){
			}

			void* read(){
				return value;
			}

			void write(void* value){
				this->value = value;
			}

			void* compareAndSwap(void* compare, void* swap){
				return system::CompareAndSwap(&value, compare, swap);
			}
		private:
			void* volatile value;
		};

		template<class T>
		class AtomicPointer: public AtomicPointerBase{
		public:
			AtomicPointer(T* value)
				: AtomicPointerBase(value){
			}

			T* read(){
				return (T*)AtomicPointerBase::read();
			}

			void write(T* value){
				AtomicPointerBase::write(value);
			}

			T* compareAndSwap(T* compare, T* swap){
				return (T*)AtomicPointerBase::compareAndSwap(compare, swap);
			}
		};
	}
}