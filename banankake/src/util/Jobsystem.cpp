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
		auto numCores = std::thread::hardware_concurrency();
		numThreads = std::max(1u,numCores);
		for (uint32_t id = 0; id < numThreads; ++id){
			std::thread worker([]{
					std::function<void()> job;

					while(true){
						if (!pool.empty()){
							job = pool.pop();
							job();
							finishedLabel.fetch_add(1);
						}
						else{
							std::unique_lock<std::mutex> lock(wakeMutex);
							wakeCondition.wait(lock);
						}
					}
			});

			worker.detach();
		}
	}

	static inline void poll(){
		wakeCondition.notify_one();
		std::this_thread::yield();
	}

	void execute(std::function<void()> func){
		currentLabel+= 1;
		while(!pool.push(func)){
			poll();
		}
		wakeCondition.notify_one();
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


