#include "hsb_apple_lib.h"

#include <stdlib.h>
#include <math.h>

#include "grf_snake_lib.h"


//Creates apple and randomically gives it a x,y position until it does not collide with anything on the map
Apple* newApple(map_t map, snake_t* snake){
	Apple* apple = malloc(sizeof(Apple));

	int isValid = 1;

	do{
		isValid = 1;

		apple->x = rand() % map.size.width;
		apple->y = rand() % map.size.height;

		position_t apple_position = {apple->x, apple->y};
		if ((map.layout[apple->y][apple->x] == '#') ||\
			(map.layout[apple->y][apple->x] == '*') ||\
		      	isSnake(snake, apple_position)){
			
			isValid = 0;
		}

	}while(!isValid);

	return apple;
}

//Returns true if position x,y has apple and destroy apple
int eatApple(Apple* apple, snake_t* snake){
	int eaten = 0;
	int x = snake->head->position.x;
	int y = snake->head->position.y;

	if(apple != NULL){
		if(apple->x == x && apple->y == y){
			free(apple);
			eaten = 1;
		}
	}

	return eaten;
}

//Returns true if position x,y has apple
int isApple(Apple* apple, int x, int y){
	int isApple = 0;

	if(apple != NULL){
		if(apple->x == x && apple->y == y){
			isApple = 1;
		}
	}

	return isApple;
}
