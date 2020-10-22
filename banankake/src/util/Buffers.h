/*
 * Buffers.h
 *
 *  Created on: 22. okt. 2020
 *      Author: Fredrik Fluge
 */

#ifndef UTIL_BUFFERS_H_
#define UTIL_BUFFERS_H_

#include <mutex>
#include <array>
namespace Buffers{

	template <class T, int count>
	class CirkularBuffer{
	private:
		std::mutex lock;
		std::array<T,count> elements;
		uint32_t start;
		uint32_t end;
		uint32_t size;
	public:
		CirkularBuffer<T,count>(){
			start = 0;
			end = 0;
			size = count;
		}



		bool push(T value){
			std::lock_guard<std::mutex> guard(lock);

			if ((end+1)%size == start){
				//vi har fylt opp hele bufferen
				return false;
			}
			else{
				end = (end+1)%size;
				elements[end] = value;
				return true;
			}

		}

		T pop(){
			std::lock_guard<std::mutex> guard(lock);
			T v = elements[start];
			start = (start + 1)%size;
			return v;
		}

		bool empty(){
			std::lock_guard<std::mutex> guard(lock);
			return start == end;
		}

		~CirkularBuffer(){

		}

	};

}



#endif /* UTIL_BUFFERS_H_ */
