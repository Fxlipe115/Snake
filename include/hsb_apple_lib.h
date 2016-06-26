#ifndef HSB_APPLE_LIB
#	define HSB_APPLE_LIB

#include "grf_snake_lib.h"

typedef struct apple{
	int x;
	int y;
}Apple;

Apple* newApple(char** map, int height, int width, Snake* snake);

int eatApple(Apple* apple, int x, int y);

int isApple(Apple* apple, int x, int y);

#endif
