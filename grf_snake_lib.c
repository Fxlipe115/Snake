#include <stdlib.h>

struct snake{
	int x;
	int y;
	struct snake *next;
};

struct snake* newSnake(int size){
	struct snake *head = malloc(sizeof(struct snake));
	
	//Para uso no laço for sem perder a referência para head
	struct snake *node = head;
	node->next = NULL;
	
	for(int i = 1; i<size; i++){
		struct snake *newnode = malloc(sizeof(struct snake));
		node->next = newnode;
		node = node->next;
		node->next = NULL;
	}
	
	return head;
}

void destroySnake(struct snake *head){
	while(head != NULL){
		struct snake *tmp = head;
		head = head->next;
		free(tmp);
	}
}

void increaseSnake(struct snake *head){
	struct snake *newbody = malloc(sizeof(struct snake));
	newbody->next = head->next;
	head->next = newbody;
}

void decreaseSnake(struct snake *head){
	while(head->next->next != NULL){
		head = head->next;
	}
	free(head->next);
	head->next = NULL;
}

int getSnakeSize(struct snake *head){
	//TODO
}

void moveSnake(struct snake *head,int dir){
	
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
