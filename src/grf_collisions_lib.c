#include <stdlib.h>

#include "grf_snake_lib.h"
#include "grf_collisions_lib.h"

int wallCollision(char** map, int x, int y){
	int status = 0;

	if(map[y][x] == '#'){
		status = 1;
	}
	return status;
}

int rockCollision(char** map, int x, int y){
	int status = 0;

	if(map[y][x] == '*'){
		status = 1;
	}
	return status;
}

int snakeCollision(Snake* snake){
	int status = 0;

	Snake* head = snake;
	snake = snake->next->next;

	while(snake != NULL && status == 0){

		int position = ((snake->x == head->x) && (snake->y == head->y));

		if(position){
			status = 1;
		}
		snake = snake->next;
	}
	return status;
}
