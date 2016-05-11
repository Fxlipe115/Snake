#include <stdlib.h>

typedef struct snake{
	int x;
	int y;
	struct snake *next;
} Snake;

Snake* newSnake(int size){
	Snake *head = NULL;
	Snake *node = head;
	
	for(int i = 0; i<size; i++){
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
	Snake *body = malloc(sizeof(Snake));
	
}

void decreaseSnake(Snake *head){
	while(head->next->next != NULL){
		head = head->next;
	}
	free(head->next);
	head->next = NULL;
}

int getSnakeSize(Snake *head){
	//TODO
}

void moveSnake(Snake *head,int dir){
	
	decreaseSnake(head);
	increaseSnake(head);
	
	switch(dir){
		case 0:
			head->x++;
			break;
		case 90:
			head->y--;
			break;
		case 180:
			head->x--;
			break;
		case 270:
			head->y++;
			break;
		default:
			
	}
}
