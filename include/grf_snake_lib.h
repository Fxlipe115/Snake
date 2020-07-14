#ifndef GRF_SNAKE_LIB_H
# define GRF_SNAKE_LIB_H

#include <stdbool.h>

#include "map.h"
#include "position.h"

//Direction macros for funtion moveSnake()
#define _RIGHT_ 0
#define _UP_ 90
#define _LEFT_ 180
#define _DOWN_ 270

typedef struct snake_body {
	position_t position;
	bool has_food;
	struct snake_body *next;
} snake_body_t;

typedef struct snake {
	snake_body_t* head;
	int size;
	int direction;
	int mice_eaten;
	bool alive;
} snake_t;

snake_t* new_snake(int size, position_t position);

void destroy_snake(snake_t* snake);

void snake_eat(snake_t* snake);

void decrease_snake(snake_t* snake);

void move_snake(snake_t* snake, map_size_t map_size);

bool is_snake_at(snake_t* snake, position_t position);

bool is_snake_head_at(snake_t* snake, position_t position);

bool has_food_at(snake_t* snake, position_t position);

#endif
