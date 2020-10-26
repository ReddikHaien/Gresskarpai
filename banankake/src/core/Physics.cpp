/*
 * Physics.cpp
 *
 *  Created on: 24. okt. 2020
 *      Author: Fredrik Fluge
 */
#include <iostream>
#include <mutex>
#include <vector>
#include <math.h>
#include <inttypes.h>
#include "Physics.h"
#include "../util/Jobsystem.h"

#define GAMMA 6.674*0.0000000001

namespace System{
	namespace Physics{
		namespace{
			std::mutex bodyLock; //lås for bodies og bodyCount
			uint32_t bodyCount = 0;
			std::vector<PhysicsBody> bodies;
		}

		void init(){

		}
		void run(){
			std::lock_guard<std::mutex> lock(bodyLock);
			JobSystem::dipatch(bodyCount,100,[](JobSystem::Dispatch args){
				uint32_t index = args.jobID;
				const Data& t = bodies[index].cur;
				float fx = t.ax/t.mass, fy = t.ay/t.mass;

				fy -= 9.81;

				if (t.y < 0){
					f.
				}

			});
			JobSystem::wait(); //venter på at beregningene skal bli ferdig

			JobSystem::dipatch(bodyCount,1000,[](JobSystem::Dispatch arg){
				bodies[arg.jobID].cur = bodies[arg.jobID].future;
			});

			JobSystem::wait();
		}

		void addNewBody(float x, float y, float r){
			std::lock_guard<std::mutex> lock(bodyLock);
			PhysicsBody body;
			body.cur = {
					x, 		//x
					y,		//y
					0.0f,	//r
					1.0f,	//m
					r,		//radius
					0.0f,	//ax
					0.0f,	//ay
					0.0f, 	//vx
					0.0f	//vy
				};
			body.future ={
					0.0f,
					0.0f,
					0.0f,
					0.0f,
					0.0f,
					0.0f,
					0.0f,
					0.0f,
					0.0f,
				};
			bodies.push_back(body);
			bodyCount = bodies.size();
		}

		void print(){
			std::lock_guard<std::mutex> lock(bodyLock);
			for (uint32_t i = 0; i < bodyCount; i++){
				std::cout << "kropp["<<i<<"]: pos:("<<bodies[i].cur.x<<","<<bodies[i].cur.y<<") rot::"<<bodies[i].cur.r << "vel:("<<bodies[i].cur.vx<<","<<bodies[i].cur.vy<<")" << std::endl;
			}
		}
	}
}

