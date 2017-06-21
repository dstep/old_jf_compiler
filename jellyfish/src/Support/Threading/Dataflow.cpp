#pragma once
#include <Support/Threading/Dataflow.h>
#include <cassert>

namespace jf{
	namespace threading{
		DataflowJob::DataflowJob()
			: next(nullptr)
			, blocks(nullptr)
			, blockers(1) //<<1 is for dataflow manager
			{
		}

		static Dependency DependencyPoisonValue;

		void DataflowJob::addDependency(DataflowJob* dependsOn, Dependency* dependency){			
			Dependency* next = dependsOn->blocks.read();
			if ( next == &DependencyPoisonValue ){
				dependency->satisfied = true;
				return;
			}
			blockers.increment();
			dependency->next = next;
			dependency->job = this;
			dependency->satisfied = false;
			while( next != dependsOn->blocks.compareAndSwap(next, dependency) ){
				next = dependsOn->blocks.read();
				if ( next == &DependencyPoisonValue ){
					blockers.decrement();
					dependency->satisfied = true;
					return;
				}
				dependency->next = next;
			};
		}

		DataflowManager::DataflowManager()
			: runningJobs(0)
			, sheduledJobs(nullptr){
		}

		void DataflowManager::addJob(DataflowJob* job, IJob* jobRunner){
			if ( job->blockers.decrement() == 0 ){
				runningJobs.increment();
				jobRunner->run(false, JobCompletionCallback(this, job));
			}else{
				job->job = jobRunner;
				DataflowJob* nextJob;
				do{
					nextJob = sheduledJobs.read();
					job->next = nextJob;
				}while ( nextJob != sheduledJobs.compareAndSwap(nextJob, job) );
			}
		}

		void DataflowManager::completeJob(DataflowJob* job){
			Dependency* dependency;
			do{
				dependency = job->blocks.read();
			}while ( dependency != job->blocks.compareAndSwap(dependency, &DependencyPoisonValue) );
			while ( dependency ){
				dependency->satisfied = true;
				Dependency* nextDependency = dependency->next;
				DataflowJob* job = dependency->job;
				if ( job->blockers.decrement() == 0 ){
					runningJobs.increment();
					job->job->run(false, JobCompletionCallback(this, job));
				}
				dependency = nextDependency;
			}
			runningJobs.decrement();
		}

		bool DataflowManager::join(){
			assert(runningJobs.read() == 0);
			DataflowJob* job = sheduledJobs.read();
			sheduledJobs.write(nullptr);
			bool hasJobs = false;
			while ( job ){
				DataflowJob* nextJob = job->next;
				if ( job->blocks.read() != &DependencyPoisonValue ){
					//This job is not yet completed, so run as deadlocked
					job->blockers.increment(); //block it forever
					runningJobs.increment();
					job->job->run(true, JobCompletionCallback(this, job));
					hasJobs = true;
				}
				job = nextJob;
			}
			return hasJobs;
		}

		void JobCompletionCallback::run(){
			if ( job ){
				manager->completeJob(job);
			}
		}
	}
}