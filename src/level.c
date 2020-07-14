#include "level.h"

#include <stdlib.h>
#include <stdio.h>

#include "grf_control_lib.h"
#include "grf_collisions_lib.h"

level_t* allocate_game_memory();
void initialize_map(level_t* level);

level_t* new_level(int number){
    level_t* level = allocate_game_memory();
    level->number = number;
    level->score = 0;
    level->lives = 3;
    level->win = false;
    initialize_map(level);
    reset_snake(level);
    level->mouse_list = new_mouse_list();
    level->apple = NULL;

    return level;
}

level_t* allocate_game_memory(){
    return malloc(sizeof(level_t));
}

void initialize_map(level_t* level){
    char mapfile[13];
	sprintf(mapfile,"maps/%d.txt", level->number);
	level->map = loadMap(mapfile);
}

void reset_snake(level_t* level){
    if(level->snake != NULL){
        destroy_snake(level->snake);
    }
    const int initial_length = 5;
    position_t initial_position = map_initial_position(level->map);
    level->snake = new_snake(initial_length, initial_position);
}

void destruct_level(level_t* level){
    destroyMap(level->map);
	destroy_snake(level->snake);
}

void update_level_state(level_t* level){
    // TODO use timer
    // if(iteraction % level->map->size.height == 0){
    //     //Food creation control
    //     if(miceEaten < 10){
    //         level->mice = newMouse(level->mice, *level->map, level->map->size.height*4, level->snake);
    //     }
    // }

    if(level->snake->mice_eaten >= 10 && level->apple == NULL && level->snake->alive){
        clear_mouse_list(level->mouse_list);
        level->apple = newApple(*level->map, level->snake);
    }    

    //Update snake position
    move_snake(level->snake, level->map->size);

    if(snake_mouse_collision(level->snake, level->mouse_list)){
        snake_eat(level->snake);
        destroy_mouse_at(level->mouse_list, level->snake->head->position);
        level->score += (level->number+1);
        level->snake->mice_eaten++;
    }

    //Destroy one mouse when its time is 0
    //TODO: timer
    //level->mice = destroyLastMouse(level->mice);

    if(snake_rock_collision(level->snake, level->map)){
        decrease_snake(level->snake);
        if(level->snake->size < 2){
            level->snake->alive = false;
        }

        if(level->score > 0){
            level->score--;
        }
    }

    if(snake_wall_collision(level->snake, level->map)){
        level->snake->alive = false;
    }

    if(snake_snake_collision(level->snake)){
        level->snake->alive = false;
    }

    //If snake ate the apple
    if(eatApple(level->apple, level->snake)){
        //End level
        level->score += 10;
        level->win = true;
    }
}