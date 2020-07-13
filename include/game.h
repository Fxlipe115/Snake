#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "level.h"

typedef struct game {
    int score;
    int lives;
    bool paused;
    bool game_over;
    level_t* current_level;
} game_t;

game_t* new_game(void);

void update_game_state(game_t* game);

#endif