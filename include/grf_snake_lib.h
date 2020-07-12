#ifndef GRF_SNAKE_LIB_H
# define GRF_SNAKE_LIB_H

#include "map.h"
#include "position.h"

//Direction macros for funtion moveSnake()
#define _RIGHT_ 0
#define _UP_ 90
#define _LEFT_ 180
#define _DOWN_ 270

typedef struct snake_body {
	position_t position;
	int food;
	struct snake_body *next;
} snake_body_t;

typedef struct snake {
	snake_body_t* head;
	int size;
	int direction;
} snake_t;



snake_t* newSnake(int size, position_t position);

void destroySnake(snake_t* snake);

void increaseSnake(snake_t* snake, int food);

void decreaseSnake(snake_t* snake);

int getSnakeSize(snake_t* snake);

void moveSnake(snake_t* snake, int dir, map_t map);

int isSnake(snake_t* snake, position_t position);

int is_snake_head(snake_t* snake, position_t position);

int hasFood(snake_t* snake, position_t position);

#endif
