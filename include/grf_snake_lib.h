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
	int food;
	int dir;
	struct snake *next;
} Snake;

Snake* newSnake(int size,int x,int y);

void destroySnake(Snake *head);

void increaseSnake(Snake *head,int food);

void decreaseSnake(Snake *head);

int getSnakeSize(Snake *head);

void moveSnake(Snake *head,int dir,int xSize,int ySize);

int isSnake(Snake *head,int x,int y);

int hasFood(Snake *head,int x,int y);

#endif
