#include <stdlib.h>

#include "grf_snake_lib.h"


//Returns size of snake
int getSnakeSize(Snake *head){
	int size = 0;
	while(head != NULL){
		size++;
		head = head->next;
	}
	return size;
}

//Increase snake by 1, putting 0 or 1 on food attribute
void increaseSnake(Snake *head,int food){
	Snake *newbody = malloc(sizeof(Snake));
	
	newbody->x = head->x;
	newbody->y = head->y;
	newbody->food = food;
	
	newbody->next = head->next;
	head->next = newbody;
}

//Removes the last element from snake
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

//Creates snake of size "size" on position x,y
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

//Frees all memory associated with snake
void destroySnake(Snake *head){
	while(head != NULL){
		Snake *tmp = head;
		head = head->next;
		free(tmp);
	}
}

//Removes last element, puts new one in place of head and moves head in direction dir
void moveSnake(Snake *head, int dir, map_t map){
	
	if(dir == _RIGHT_ ||\
	   dir == _LEFT_ ||\
	   dir == _UP_ ||\
	   dir == _DOWN_){
		decreaseSnake(head);
		increaseSnake(head,0);
	}
	
	switch(dir){
		case _RIGHT_:
			head->x = (head->x + 1) % map.size.width;
			break;
		case _UP_:
			head->y--;
			if(head->y < 0){
				head->y = map.size.height-1;
			}
			break;
		case _LEFT_:
			head->x--;
			if(head->x < 0){
				head->x = map.size.width-1;
			}
			break;
		case _DOWN_:
			head->y = (head->y + 1) % map.size.height;
			break;
	}
}

//Returns true if position x,y coincides with any snake part
int isSnake(Snake *head,int x,int y){
	int isSnake = 0;

	while(head != NULL && isSnake == 0){

		int position = ((head->x == x) && (head->y == y));

		if(position){
			isSnake = 1;
		}
		head = head->next;
	}
	return isSnake;
}

//Returns true if snake part located on x,y has attribute food = 1
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
