#ifndef GRF_SNAKE_LIB_H
# define GRF_SNAKE_LIB_H

typedef struct snake Snake;

Snake* newSnake();

void destroySnake(Snake *head);

void increaseSnake(Snake *head);

void decreaseSnake(Snake *head);

int getSnakeSize(Snake *head);

#endif
