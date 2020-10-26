/*
 * Buffers.h
 *
 *  Created on: 22. okt. 2020
 *      Author: Fredrik Fluge
 */

#ifndef UTIL_BUFFERS_H_
#define UTIL_BUFFERS_H_


#include "Logging.h"
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
			bool result = false;
			lock.lock();
			//Logger::print(std::string("skubb[ start: ") + std::to_string(start) + " slutt " + std::to_string(end) + " ]");
			if ((end+1)%size != start){

				elements[end] = value;
				end = (end+1)%size;
				result = true;
			}
			lock.unlock();
			return result;
		}

		bool pop(std::function<void()>& out){
			bool result = false;
			lock.lock();
			//Logger::print(std::string("pop[ start: ") + std::to_string(start) + " slutt " + std::to_string(end) + " ]");
			if (start != end){
				out = elements[start];
				start = (start + 1)%size;
				result = true;
			}

			else{
			}
			lock.unlock();
			return result;
		}

		bool empty(){
			bool result = false;
			lock.lock();
			result = start == empty;
			lock.unlock();
			return result;
		}

		~CirkularBuffer(){

		}

	};

}



#endif /* UTIL_BUFFERS_H_ */
