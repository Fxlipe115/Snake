#ifndef GRF_SNAKE_LIB_H
# define GRF_SNAKE_LIB_H

//Macros de direção para a função moveSnake()
#define _RIGHT_ 0
#define _UP_ 90
#define _LEFT_ 180
#define _DOWN_ 270

typedef struct snake{
	int x;
	int y;
	struct snake *next;
} Snake;

Snake* newSnake(int size);

void destroySnake(Snake *head);

void increaseSnake(Snake *head);

void decreaseSnake(Snake *head);

int getSnakeSize(Snake *head);

void moveSnake(Snake *head,int dir);

int isSnake(Snake *head,int x,int y);

#endif