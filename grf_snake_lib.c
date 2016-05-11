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

void destroySnake(Snake *head){
        while(head != NULL){
            Snake *tmp = head;
            head = head->next;
            free(tmp);
        }
}

void increaseSnake(Snake *head){
	//TODO
}

void decreaseSnake(Snake *head){
	//TODO
}

int getSnakeSize(Snake *head){
	//TODO
}
