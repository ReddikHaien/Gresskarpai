/*
 * Logging.cpp
 *
 *  Created on: 22. okt. 2020
 *      Author: Eier
 */

#include <iostream>
#include <mutex>
#include "Logging.h"


namespace Logger{
	namespace {
		std::mutex lock;
		uint32_t flushCounter = 0;
	}
	void print(const std::string& message){
		lock.lock();
		flushCounter++;
		std::cout << message << std::endl;
		if (flushCounter > 10){
			flushCounter = 0;
			std::cout << std::flush;
		}
		lock.unlock();
	}
}

