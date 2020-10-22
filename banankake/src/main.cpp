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
#include "screen/Screen.h"
int main(){
	JobSystem::init();
	Screen::init();

	Screen::setChar(10, 10, '@', FG_RED, BG_BLACK);

	Screen::update();

	return 0;
}


