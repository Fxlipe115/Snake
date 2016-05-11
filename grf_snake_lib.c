#include <stdlib.h>

#define SNAKE_SIZE 5

typedef struct snake{
	int x;
	int y;
	struct snake *next;
} Snake;

Snake* newSnake(){
	Snake *node = malloc(sizeof(Snake));
	for(int i = 0; i<SNAKE_SIZE; i++){
		
	}
	return node;
}
