#ifndef GRF_COLLISIONS_LIB
#	define GRF_COLLISIONS_LIB

#include "grf_snake_lib.h"
#include "map.h"

int wallCollision(map_t map, int x, int y);

int rockCollision(map_t map, int x, int y);

int snakeCollision(Snake* snake);

#endif
