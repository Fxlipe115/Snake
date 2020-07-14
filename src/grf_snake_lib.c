#include "grf_snake_lib.h"

#include <stdlib.h>

void increase_snake(snake_t* snake, bool has_eaten);
void move_snake_body(snake_t* snake);
void move_snake_head(snake_t* snake, map_size_t map_size);

snake_t* new_snake(int size, position_t position){
	snake_t* snake = malloc(sizeof(snake_t));
	snake->size = 0;
	snake->direction = _RIGHT_;
	snake->mice_eaten = 0;
	snake->alive = true;

	snake_body_t* head = malloc(sizeof(snake_body_t));
	head->position.x = position.x;
	head->position.y = position.y;
	head->has_food = false;
	snake->size++;

	snake_body_t* tail = malloc(sizeof(snake_body_t));
	tail->position.x = position.x;
	tail->position.y = position.y;
	tail->has_food = false;
	snake->size++;

	snake->head = head;
	head->next = tail;
	tail->next = NULL;
	size -= 2;

	for(int i = 0; i<size; i++){
		increase_snake(snake, false);
	}

	return snake;
}

void snake_eat(snake_t* snake){
	increase_snake(snake, true);
}

void increase_snake(snake_t* snake, bool has_eaten){
	snake_body_t* head = snake->head;
	snake_body_t* newbody = malloc(sizeof(snake_body_t));
	
	newbody->position.x = head->position.x;
	newbody->position.y = head->position.y;
	newbody->has_food = has_eaten;
	
	newbody->next = head->next;
	head->next = newbody;

	snake->size++;
}

void decrease_snake(snake_t *snake){
	if(snake->size > 1){
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

void destroy_snake(snake_t* snake){
	snake_body_t* head = snake->head;
	while(head != NULL){
		snake_body_t* tmp = head;
		head = head->next;
		free(tmp);
	}
	snake->size = 0;
}

void move_snake(snake_t* snake, map_size_t map_size){
	move_snake_body(snake);
	move_snake_head(snake, map_size);
	
}

void move_snake_body(snake_t* snake){
	int dir = snake->direction;
	if(dir == _RIGHT_ ||\
	   dir == _LEFT_ ||\
	   dir == _UP_ ||\
	   dir == _DOWN_){
		decrease_snake(snake);
		increase_snake(snake, false);
	}
}

void move_snake_head(snake_t* snake, map_size_t map_size){
	int dir = snake->direction;
	switch(dir){
		case _RIGHT_:
			snake->head->position.x = (snake->head->position.x + 1) % map_size.width;
			break;
		case _UP_:
			snake->head->position.y--;
			if(snake->head->position.y < 0){
				snake->head->position.y = map_size.height-1;
			}
			break;
		case _LEFT_:
			snake->head->position.x--;
			if(snake->head->position.x < 0){
				snake->head->position.x = map_size.width-1;
			}
			break;
		case _DOWN_:
			snake->head->position.y = (snake->head->position.y + 1) % map_size.height;
			break;
	}
}

//Returns true if position x,y coincides with any snake part
bool is_snake_at(snake_t* snake, position_t position){
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

bool is_snake_head_at(snake_t* snake, position_t position){
	position_t head_position = snake->head->position;
	return is_same_position(head_position, position);
}

//Returns true if snake part located on x,y has attribute food = 1
bool has_food_at(snake_t* snake, position_t position){
	snake_body_t* body = snake->head;
	int hasFood = 0;

	while(body != NULL){
		if(is_same_position(body->position, position) && body->has_food){
			hasFood = 1;
		}
		body = body->next;
	}
	return hasFood;
}
