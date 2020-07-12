#include "hsb_mouse_lib.h"

#include <stdlib.h>

#include "grf_snake_lib.h" 

int isMouse(Mouse* mouse, int x, int y){
	int isMouse = 0;

	//verifies if there is a mouse of the given list at position (x,y)
	while(mouse != NULL && isMouse == 0){

		int position = ((mouse->x == x) && (mouse->y == y));
		
		if (position) {
			 isMouse=1;
		}
	
		mouse = mouse->next;
	}

	return isMouse;
}

Mouse* destroyLastMouse(Mouse* mouse){
	//destroys the last mouse of given list
	//sees if list is not empty
	if(mouse != NULL){
		//stores second to last mouse(aka new last mouse)
		Mouse *previous = mouse, *last = mouse;

		last->time--;

		//go last mouse in the list
		while(last->next != NULL){			
			previous = last;

			last = last->next;

			last->time--;
		}

		//if the mouse's life is over
		if(mouse->time == 0){
			free(last);
			mouse = NULL;

		}else if(last->time == 0){
			//brutally kill the mouse
			free(last);
			previous->next = NULL;
		}
	}
	return mouse;
}

Mouse* eatMouse(Mouse* mouse, int* hasEaten, snake_t* snake){
	Mouse *next = NULL, *returnValue = NULL;

	if(mouse == NULL){
		returnValue = NULL;
	}else if(mouse->x == snake->head->position.x &&
			mouse->y == snake->head->position.y){
		next = mouse->next;
		free(mouse);
		*hasEaten = 1;
		returnValue = next;
	}else{
		mouse->next = eatMouse(mouse->next, hasEaten, snake);
		returnValue = mouse;
	}

	return returnValue;
}

Mouse* newMouse(Mouse* mouselist, map_t map, int time, snake_t* snake){
	//create new node
	Mouse *mouse = malloc(sizeof(Mouse));
	//point to given list
	mouse->next = mouselist;
	//point 'mouselist' to new beggining of the list
	mouselist = mouse;
	//mouse lifespan to 'time'
	mouse->time = time;
	//flag
	int isValid = 1;
	do{
		//flag
		isValid = 1;
		//ramdomly set (x,y) position to mouse
		mouse->x = rand() % map.size.width;
		mouse->y = rand() % map.size.height;
		
		position_t mouse_position = {mouse->x, mouse->y};
		//if position doesn't match anything already on the map
		if ((map.layout[mouse->y][mouse->x] == '#') ||\
			(map.layout[mouse->y][mouse->x] == '*') ||\
		      	isSnake(snake, mouse_position)){
		//       	isMouse(mouselist, mouse->x, mouse->y)){
			
			isValid = 0;
		}


	} while (!isValid);
	
	return mouse;
}

//Frees all memory associated with mouse list given
Mouse* destroyAllMice(Mouse* mouse){
	while(mouse != NULL){
		Mouse *tmp = mouse;
		mouse = mouse->next;
		free(tmp);
	}
	return NULL;
}
