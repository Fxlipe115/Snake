#include <stdlib.h>
#include <math.h>

#include "hsb_apple_lib.h"
#include "grf_snake_lib.h"


//Creates apple and randomically gives it a x,y position until it does not collide with anything on the map
Apple* newApple(char** map, int height, int width, Snake* snake){
	Apple* apple = malloc(sizeof(Apple));

	int isValid = 1;

	do{
		isValid = 1;

		apple->x = rand() % width;
		apple->y = rand() % height;

		if ((map[apple->y][apple->x] == '#') ||\
			(map[apple->y][apple->x] == '*') ||\
		      	isSnake(snake, apple->x, apple->y)){
			
			isValid = 0;
		}

	}while(!isValid);

	return apple;
}

//Returns true if position x,y has apple and destroy apple
int eatApple(Apple* apple, int x, int y){
	int eaten = 0;

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
