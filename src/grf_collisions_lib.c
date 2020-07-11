#include "grf_collisions_lib.h"

#include <stdlib.h>

int wallCollision(map_t map, int x, int y){
	int status = 0;

	if(map.layout[y][x] == '#'){
		status = 1;
	}
	return status;
}

int rockCollision(map_t map, int x, int y){
	int status = 0;

	if(map.layout[y][x] == '*'){
		status = 1;
	}
	return status;
}

int snakeCollision(Snake* snake){
	int status = 0;

	if(getSnakeSize(snake) > 4){
		Snake* head = snake;
		snake = snake->next->next->next->next;

		while(snake != NULL && status == 0){

			int position = ((snake->x == head->x) && (snake->y == head->y));

			if(position){
				status = 1;
			}
			snake = snake->next;
		}
	}
	return status;
}
