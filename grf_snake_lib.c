#include <stdlib.h>

#define SNAKE_SIZE 5

typedef struct snake{
	int x;
	int y;
	struct snake *next;
} Snake;

Snake* newSnake(){
	Snake *head = NULL;
	Snake *node = head;
	
	for(int i = 0; i<SNAKE_SIZE; i++){
		node = malloc(sizeof(Snake));
		node->next = NULL;
		node = node->next;
	}
	
	return head;
}
