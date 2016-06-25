#ifndef GRF_COLLISIONS_LIB
#	define GRF_COLLISIONS_LIB

#include "grf_snake_lib.h"

int wallCollision(char** map, int x, int y);

int rockCollision(char** map, int x, int y);

int snakeCollision(Snake* snake);

#endif
