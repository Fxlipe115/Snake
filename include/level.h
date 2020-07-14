#ifndef LEVEL_H
#define LEVEL_H

#include <stdbool.h>

#include "map.h"
#include "grf_snake_lib.h"
#include "hsb_apple_lib.h"
#include "hsb_mouse_lib.h"

typedef struct level {
    int number;
    int score;
    int lives;
    bool win;
    map_t* map;
    snake_t* snake;
    mouse_list_t* mouse_list;
    apple_t* apple;
} level_t;

level_t* new_level(int number);

void end_level(level_t* level);

void update_level_state(level_t* level);

void reset_snake(level_t* level);

#endif