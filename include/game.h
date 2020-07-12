#ifndef GAME_H
#define GAME_H

#include "map.h"

typedef struct game {
    int score;
    map_t map;
} game_t;

game_t create_game(map_t map);

#endif