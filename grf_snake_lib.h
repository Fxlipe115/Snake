#ifndef GRF_SNAKE_LIB_H
# define GRF_SNAKE_LIB_H

//Macros de direção para a função moveSnake()
#define RIGHT 0
#define UP 90
#define LEFT 180
#define DOWN 270

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
