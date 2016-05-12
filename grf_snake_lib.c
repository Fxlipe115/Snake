#include <stdlib.h>

struct snake{
	int x;
	int y;
	struct snake *next;
};

struct snake* newSnake(int size){
	struct snake *head = malloc(sizeof(struct snake));
	struct snake *tail = malloc(sizeof(struct snake));

	head->next = tail;
	tail->next = NULL;
	size -= 2;

	for(int i = 0; i<size; i++){
		increaseSnake(head);
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
	int size = 0;
	while(head != NULL){
		head = head->next;
		size++;
	}
	return size;
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
