/*
 * Screen.cpp
 *
 *  Created on: 22. okt. 2020
 *      Author: Eier
 */


#include <iostream>
#include "Screen.h"

#define CHAR_INDEX 0
#define FG_INDEX 1
#define BG_INDEX 2

namespace Screen{
	namespace{
		unsigned char prev_buffer[HEIGHT][WIDTH+1][3];
		unsigned char imm_buffer[HEIGHT][WIDTH+1][3];

		const char colors[3][10] = {
			"\033[97m",
			"\033[31m",
			"\033[40m"
		};

	}

	void init(){
		for (uint32_t i = 0; i < HEIGHT; i++){
			imm_buffer[i][WIDTH][CHAR_INDEX] = 0;
		}
		for (uint32_t y = 0; y < HEIGHT; y++){
			for (uint32_t x = 0; x < WIDTH; x++){
				imm_buffer[y][x][CHAR_INDEX] = '#';
				imm_buffer[y][x][FG_INDEX] = FG_WHITE;
				imm_buffer[y][x][BG_INDEX] = BG_BLACK;
			}
		}

	}

	void setChar(uint32_t x, uint32_t y, unsigned char chr, unsigned char chr_col, unsigned char bg_col){
		if (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0){
			imm_buffer[y][x][CHAR_INDEX] = chr;
			imm_buffer[y][x][FG_INDEX] = chr_col;
			imm_buffer[y][x][BG_INDEX] = bg_col;

		}
	}

	void update(){

		for (uint32_t y = 0; y < HEIGHT; y++){
			for (uint32_t x = 0; x < WIDTH; x++){
				std::cout << colors[imm_buffer[y][x][FG_INDEX]] << colors[imm_buffer[y][x][BG_INDEX]] << imm_buffer[y][x][CHAR_INDEX];
			}
			std::cout  << std::endl;
		}

	}

}



