#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

#include "position.h"

typedef struct map_size {
    int width;
    int height;
} map_size_t;

typedef struct map {
    char** layout;
    map_size_t size;
} map_t;

map_t* loadMap(char* filename);

void destroyMap(map_t* map);

position_t map_initial_position(map_t* map);

bool is_wall_at(position_t position, map_t* map);

bool is_rock_at(position_t position, map_t* map);

#endif