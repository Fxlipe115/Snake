#include <stdlib.h>

#include "grf_snake_lib.h"


int getSnakeSize(Snake *head){
	int size = 0;
	while(head != NULL){
		size++;
		head = head->next;
	}
	return size;
}

void increaseSnake(Snake *head,int food){
	Snake *newbody = malloc(sizeof(Snake));
	
	newbody->x = head->x;
	newbody->y = head->y;
	newbody->food = food;
	
	newbody->next = head->next;
	head->next = newbody;
}

void decreaseSnake(Snake *head){
	if(getSnakeSize(head) > 1){
		Snake* snake = head->next;
;
		while(snake->next != NULL){
			head = head->next;
			snake = head->next;
		}
		free(snake);
		head->next = NULL;
	}   
}

Snake* newSnake(int size,int x,int y){
	Snake *head = malloc(sizeof(Snake));
	head->x = x;
	head->y = y;
	head->food = 0;

	Snake *tail = malloc(sizeof(Snake));
	tail->x = x;
	tail->y = y;
	tail->food = 0;

	head->next = tail;
	tail->next = NULL;
	size -= 2;

	for(int i = 0; i<size; i++){
		increaseSnake(head,0);
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

void moveSnake(Snake *head,int dir,int xSize,int ySize){
	
	if(dir == _RIGHT_ ||\
	   dir == _LEFT_ ||\
	   dir == _UP_ ||\
	   dir == _DOWN_){
		decreaseSnake(head);
		increaseSnake(head,0);
	}
	
	switch(dir){
		case _RIGHT_:
			head->x = (head->x + 1) % xSize;
			break;
		case _UP_:
			head->y--;
			if(head->y < 0){
				head->y = ySize-1;
			}
			break;
		case _LEFT_:
			head->x--;
			if(head->x < 0){
				head->x = xSize-1;
			}
			break;
		case _DOWN_:
			head->y = (head->y + 1) % ySize;
			break;
	}
}

	
int isSnake(Snake *head,int x,int y){
	int isSnake = 0;

	head = head->next;

	while(head != NULL && isSnake == 0){

		int position = ((head->x == x) && (head->y == y));

		if(position){
			isSnake = 1;
		}
		head = head->next;
	}
	return isSnake;
}

int hasFood(Snake *head,int x,int y){
	int hasFood = 0;

	while(head != NULL){

		int position = ((head->x == x) && (head->y == y));

		if(position && head->food){
			hasFood = 1;
		}
		head = head->next;
	}
	return hasFood;
}
