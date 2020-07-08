#ifndef GRF_DRAW_LIB
#	define GRF_DRAW_LIB

#include <curses.h>

#include "grf_snake_lib.h"
#include "hsb_mouse_lib.h"
#include "hsb_apple_lib.h"

char** loadMap(char* filename,int *width,int *height);

void destroyMap(char** map,int height);

void refreshScreen(Snake *snake,Mouse *mouse,Apple *apple,char **map,int matrixSize,int matrixySize,int lvl,int score,int lives,int miceEaten);

void drawMenu(int option);

void drawPlayerData(int score);

void instructionsScreen();

#endif
