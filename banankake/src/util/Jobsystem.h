/*
 * Jobsystem.h
 *
 *  Created on: 22. okt. 2020
 *      Author: Fredrik Fluge
 */

#ifndef UTIL_JOBSYSTEM_H_
#define UTIL_JOBSYSTEM_H_

#include <functional>

namespace JobSystem{

	struct Dispatch{
		uint32_t jobID;
	};

	void init();

	void execute(std::function<void()> func);

	bool isBusy();

	void wait();

}



#endif /* UTIL_JOBSYSTEM_H_ */
