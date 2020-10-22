/*
 * Screen.h
 *
 *  Created on: 22. okt. 2020
 *      Author: Eier
 */

#ifndef SCREEN_SCREEN_H_
#define SCREEN_SCREEN_H_

#define WIDTH 32
#define HEIGHT 16

#define FG_WHITE 0
#define FG_RED 1
#define BG_BLACK 2

#include <inttypes.h>
namespace Screen{

	void init();

	void setChar(uint32_t x, uint32_t y, unsigned char chr, unsigned char chr_col, unsigned char bg_col);

	void update();
}



#endif /* SCREEN_SCREEN_H_ */
