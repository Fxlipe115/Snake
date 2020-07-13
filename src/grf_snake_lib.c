#include "grf_snake_lib.h"

#include <stdlib.h>

//Returns size of snake
int getSnakeSize(snake_t* snake){
	return snake->size;
}

//Creates snake of size "size" on position x,y
snake_t* newSnake(int size, position_t position){
	snake_t* snake = malloc(sizeof(snake_t));
	snake->size = 0;
	snake->direction = _RIGHT_;
	snake->mice_eaten = 0;
	snake->alive = true;

	snake_body_t* head = malloc(sizeof(snake_body_t));
	head->position.x = position.x;
	head->position.y = position.y;
	head->food = 0;
	snake->size++;

	snake_body_t* tail = malloc(sizeof(snake_body_t));
	tail->position.x = position.x;
	tail->position.y = position.y;
	tail->food = 0;
	snake->size++;

	snake->head = head;
	head->next = tail;
	tail->next = NULL;
	size -= 2;

	for(int i = 0; i<size; i++){
		increaseSnake(snake,0);
	}

	return snake;
}

//Increase snake by 1, putting 0 or 1 on food attribute
void increaseSnake(snake_t* snake, int food){
	snake_body_t* head = snake->head;
	snake_body_t* newbody = malloc(sizeof(snake_body_t));
	
	newbody->position.x = head->position.x;
	newbody->position.y = head->position.y;
	newbody->food = food;
	
	newbody->next = head->next;
	head->next = newbody;

	snake->size++;
}

//Removes the last element from snake
void decreaseSnake(snake_t *snake){
	if(getSnakeSize(snake) > 1){
		snake_body_t* body = snake->head;
		snake_body_t* tail = snake->head->next;

		while(tail->next != NULL){
			body = body->next;
			tail = tail->next;
		}
		free(tail);
		body->next = NULL;

		snake->size--;
	}
}

//Frees all memory associated with snake
void destroySnake(snake_t* snake){
	snake_body_t* head = snake->head;
	while(head != NULL){
		snake_body_t* tmp = head;
		head = head->next;
		free(tmp);
	}
	snake->size = 0;
}

//Removes last element, puts new one in place of head and moves head in direction dir
void moveSnake(snake_t* snake, int dir, map_t map){
	
	if(dir == _RIGHT_ ||\
	   dir == _LEFT_ ||\
	   dir == _UP_ ||\
	   dir == _DOWN_){
		decreaseSnake(snake);
		increaseSnake(snake, 0);
	}
	
	switch(dir){
		case _RIGHT_:
			snake->head->position.x = (snake->head->position.x + 1) % map.size.width;
			break;
		case _UP_:
			snake->head->position.y--;
			if(snake->head->position.y < 0){
				snake->head->position.y = map.size.height-1;
			}
			break;
		case _LEFT_:
			snake->head->position.x--;
			if(snake->head->position.x < 0){
				snake->head->position.x = map.size.width-1;
			}
			break;
		case _DOWN_:
			snake->head->position.y = (snake->head->position.y + 1) % map.size.height;
			break;
	}
}

//Returns true if position x,y coincides with any snake part
int isSnake(snake_t* snake, position_t position){
	int isSnake = 0;
	snake_body_t* body = snake->head;
	while(body != NULL && isSnake == 0){
		if(is_same_position(body->position, position)){
			isSnake = 1;
		}
		body = body->next;
	}
	return isSnake;
}

int is_snake_head(snake_t* snake, position_t position){
	position_t head_position = snake->head->position;
	return is_same_position(head_position, position);
}

//Returns true if snake part located on x,y has attribute food = 1
int hasFood(snake_t* snake, position_t position){
	snake_body_t* body = snake->head;
	int hasFood = 0;

	while(body != NULL){
		if(is_same_position(body->position, position) && body->food){
			hasFood = 1;
		}
		body = body->next;
	}
	return hasFood;
}
