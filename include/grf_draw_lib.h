#ifndef GRF_DRAW_LIB
#	define GRF_DRAW_LIB

#include <curses.h>

#include "grf_snake_lib"
#include "hsb_mouse_lib.h"

char** loadMap(char* filename,int *width,int *height);

void destroyMap(char** map,int height);

void refreshScreen(WINDOW *window,Snake *snake,Mouse *mouse,char **map,int matrixSize,int matrixySize,int score);

void drawMenu(WINDOW* menu,int option);

#endif
