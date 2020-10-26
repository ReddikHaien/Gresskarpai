/*
 * Jobsystem.cpp
 *
 *  Created on: 22. okt. 2020
 *      Author: Fredrik Fluge
 */


#include <iostream>
#include <thread>
#include <functional>
#include <atomic>
#include <condition_variable>
#include <algorithm>

#include "Buffers.h"
#include "Logging.h"
#include "Jobsystem.h"


namespace JobSystem{



	namespace{
		uint32_t numThreads = 0;
		Buffers::CirkularBuffer<std::function<void()>,256> pool;
		std::condition_variable wakeCondition;
		std::mutex wakeMutex;
		uint64_t currentLabel = 0;
		std::atomic<uint64_t> finishedLabel;
	}
	void init(){
		finishedLabel.store(0);
		auto numCores = std::thread::hardware_concurrency() - 1;
		numThreads = std::max(1u,numCores);
		for (uint32_t id = 0; id < numThreads; ++id){
			std::thread worker([]{
					std::function<void()> job;

					while(true){
						if (pool.pop(job)){
							if (job){
								job();
							}
							finishedLabel.fetch_add(1);
						}
						else{
							std::unique_lock<std::mutex> lock(wakeMutex);
							wakeCondition.wait(lock);
						}

						//Logger::print(std::to_string(id));

					}
			});

			worker.detach();
		}
	}

	static inline void poll(){
		std::this_thread::yield();
	}

	void execute(std::function<void()> func){
		currentLabel+= 1;
		while(!pool.push(func)){
			poll();
		}
;
		wakeCondition.notify_one();

	}

	void dipatch(uint32_t jobCount, uint32_t groupSize, std::function<void(Dispatch)> job){
		if (jobCount == 0 || groupSize == 0) return;

		const uint32_t groupCount = (jobCount + groupSize - 1) / groupSize;

		currentLabel+=groupCount;
		for (uint32_t groupIndex = 0; groupIndex < groupCount; ++groupIndex){
			auto group = [jobCount,groupSize,job,groupIndex](){
				const uint32_t offset = groupIndex*groupSize;
				const uint32_t end = std::min(offset+groupSize,jobCount);

				Dispatch args;
				args.groupID = groupIndex;

				for (uint32_t jobIndex = offset; jobIndex < end; ++jobIndex){
					args.jobID = jobIndex;
					job(args);
				}
			};

			while(!pool.push(group)){
				poll();
			}

			wakeCondition.notify_one();

		}
	}

	bool isBusy(){
		return finishedLabel.load() < currentLabel;
	}

	void wait(){
		while(isBusy()){
			poll();
		}
	}
}


