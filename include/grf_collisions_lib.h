#ifndef GRF_COLLISIONS_LIB
#	define GRF_COLLISIONS_LIB

#include <stdbool.h>

#include "grf_snake_lib.h"
#include "map.h"
#include "level.h"

bool snake_wall_collision(snake_t* snake, map_t* map);

bool snake_rock_collision(snake_t* snake, map_t* map);

bool snake_snake_collision(snake_t* snake);

bool snake_mouse_collision(snake_t* snake, mouse_list_t* mouse_list);

bool snake_apple_collision(snake_t* snake, apple_t* apple);

position_t get_random_free_position(level_t* level);

#endif
