#include "game.h"

#include <stdlib.h>

game_t* new_game(void){
    game_t* game = malloc(sizeof(game_t));
    game->score = 0;
    game->lives = 3;
    game->paused = false;
    game->game_over = false;
    game->current_level = NULL;
    return game;
}

void update_game_state(game_t* game){
    if(!game->paused){
        update_level_state(game->current_level);
    }

    if(!game->current_level->snake->alive){
        game->lives--;
        reset_snake(game->current_level);
    }
    
    if(game->lives < 1){
        game->game_over = true;
        game->score += game->current_level->score;
    }
}