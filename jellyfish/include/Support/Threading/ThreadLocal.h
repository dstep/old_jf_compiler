#pragma once

namespace jf{
	namespace threading{
		class ThreadLocalBase{
		public:
			ThreadLocalBase();
			~ThreadLocalBase();

			void* get();
			void set(void* ptr);
		private:
			void* impl;
		};

		template<class T>
		class ThreadLocal: private ThreadLocalBase{
		public:
			T* get(){
				return (T*)ThreadLocalBase::get();
			}

			void set(T* value){
				ThreadLocalBase::set(value); 
			}
		};
	}
}