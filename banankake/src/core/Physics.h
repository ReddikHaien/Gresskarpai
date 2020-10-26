/*
 * Physics.h
 *
 *  Created on: 24. okt. 2020
 *      Author: Fredrik Fluge
 */

#ifndef CORE_PHYSICS_H_
#define CORE_PHYSICS_H_

namespace System{
	namespace Physics{
		struct Data{
			float x;
			float y;
			float r;
			float mass;
			float radius;
			float ax;
			float ay;
			float vx;
			float vy;
		};

		struct PhysicsBody{
			Data cur;
			Data future;
		};

		void init();

		void run();

		void addNewBody(float x, float y, float r);

		void print();
	}
}



#endif /* CORE_PHYSICS_H_ */
