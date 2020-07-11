#ifndef HSB_APPLE_LIB
#	define HSB_APPLE_LIB

#include "grf_snake_lib.h"
#include "map.h"

typedef struct apple{
	int x;
	int y;
}Apple;

Apple* newApple(map_t map, Snake* snake);

int eatApple(Apple* apple, int x, int y);

int isApple(Apple* apple, int x, int y);

#endif
