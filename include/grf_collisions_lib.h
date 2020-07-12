#ifndef GRF_COLLISIONS_LIB
#	define GRF_COLLISIONS_LIB

#include "grf_snake_lib.h"
#include "map.h"

int wallCollision(map_t map, snake_t* snake);

int rockCollision(map_t map, snake_t* snake);

int snakeCollision(snake_t* snake);

#endif
