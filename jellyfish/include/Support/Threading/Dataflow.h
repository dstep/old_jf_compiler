#pragma once

#include "Atomic.h"

namespace jf{
	namespace threading{		
		class DataflowJob;
		class DataflowManager;
		
		class Dependency{
		public:
			Dependency* next;
			DataflowJob* job;
			bool satisfied;			
		};

		class JobCompletionCallback{
		public:
			JobCompletionCallback(DataflowManager* manager, DataflowJob* job)
				: manager(manager)
				, job(job){
			}

			void run();
		private:
			DataflowManager* manager;
			DataflowJob* job;
		};

		class IJob{
		public:
			virtual void run(bool deadlocked, JobCompletionCallback callback) = 0;
		};

		class DataflowJob{
		public:
			DataflowJob();

			void addDependency(DataflowJob* dependsOn, Dependency* dependency);
		private:
			AtomicPointer<Dependency> blocks;
			AtomicInt blockers;
			DataflowJob* next;
			IJob* job;

			friend class DataflowManager;
		};

		class DataflowManager{
		public:
			DataflowManager();

			void addJob(DataflowJob* job, IJob* jobRunner);
			void completeJob(DataflowJob* job);

			bool join();
		private:
			AtomicPointer<DataflowJob> sheduledJobs;
			AtomicInt runningJobs;
		};
	}
}