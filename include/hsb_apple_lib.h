#ifndef HSB_APPLE_LIB
#	define HSB_APPLE_LIB

#include "grf_snake_lib.h"
#include "map.h"

struct apple {
	int x;
	int y;
} ;
typedef struct apple Apple;

Apple* newApple(map_t map, snake_t* snake);

int eatApple(Apple* apple, snake_t* snake);

int isApple(Apple* apple, int x, int y);

#endif
