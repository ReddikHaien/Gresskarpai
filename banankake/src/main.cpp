/*
 * main.cpp
 *
 *  Created on: 22. okt. 2020
 *      Author: Fredrik Fluge
 */
#include <iostream>
#include <mutex>
#include "util/Jobsystem.h"
#include "util/Logging.h"
#include "core/Physics.h"
int main(){
	JobSystem::init();
	JobSystem::execute([](){System::Physics::init();});

	JobSystem::wait();

	System::Physics::addNewBody(0,0,1);
	System::Physics::addNewBody(2,0,1);
	System::Physics::addNewBody(0,2,1);
	System::Physics::addNewBody(2,2,1);
	while(true){
		System::Physics::run();
		System::Physics::print();
	}
	return 0;
}


