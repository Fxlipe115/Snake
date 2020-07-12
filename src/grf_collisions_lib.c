#include "grf_collisions_lib.h"

#include <stdlib.h>

int snake_can_colide_with_itself(snake_t* snake);
snake_body_t* ignore_beginning_of_body(snake_t* snake);

int wallCollision(map_t map, snake_t* snake){
	int status = 0;
	int x = snake->head->position.x;
	int y = snake->head->position.y;

	if(map.layout[y][x] == '#'){
		status = 1;
	}
	return status;
}

int rockCollision(map_t map, snake_t* snake){
	int status = 0;
	int x = snake->head->position.x;
	int y = snake->head->position.y;

	if(map.layout[y][x] == '*'){
		status = 1;
	}
	return status;
}

int snakeCollision(snake_t* snake){
	int status = 0;
	snake_body_t* head = snake->head;
	if(snake_can_colide_with_itself(snake)){
		snake_body_t* body = ignore_beginning_of_body(snake);
		while(body != NULL && status == 0){
			if(is_same_position(head->position, body->position)){
				status = 1;
			}
			body = body->next;
		}
	}
	return status;
}

int snake_can_colide_with_itself(snake_t* snake){
	return getSnakeSize(snake) > 4;
}

snake_body_t* ignore_beginning_of_body(snake_t* snake){
	// if the body part after the head is not skipped,
	// there's a false positive when the snake
	// grows in size
	return snake->head->next->next;
}