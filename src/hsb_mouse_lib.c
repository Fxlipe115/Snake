#include <stdlib.h>

#include "grf_snake_lib.h" 
#include "hsb_mouse_lib.h"

int isMouse(Mouse* mouse, int x, int y){
	int isMouse = 0;

	//verifies if there is a mouse of the given list at position (x,y)
	while(mouse != NULL && isMouse == 0){

		int position = ((mouse->x == x) && (mouse->y == y));
		
		if (position) {
			 isMouse=1;
		}
	
		mouse= mouse->next;
	}

	return isMouse;
}

void destroyLastMouse(Mouse* mouse){
	//destroys the last mouse of given list
	//sees if list is not empty
	if(mouse != NULL){
		//stores second to last mouse(aka new last mouse)
		Mouse *previous = NULL;

		//go last mouse in the list
		while(mouse->next != NULL){

			previous = mouse;

			mouse= mouse->next;
		}

		//if the mouse's life is over
		if(mouse->time == 0){
			//brutally kill the mouse
			free(mouse);

			previous->next = NULL;
		}
	}
}


void newMouse(Mouse* mouselist, char** map, int height, int width, int time, Snake* snake){
	//create new node
	Mouse *mouse = malloc(sizeof(Mouse));
	//point to given list
	mouse->next = mouselist;
	//point 'mouselist' to new beggining of the list
	mouselist = mouse;
	//mouse lifespan to 'time'
	mouse->time = time;
	//flag
	int isValid = 0;
	do{
		//flag
		isValid = 0;
		//ramdomly set (x,y) position to mouse
		mouse->x = rand() % width;
		mouse->y = rand() % height;
		
		//if position doesn't match anything already on the map
		if ((map[mouse->y][mouse->x] == '#') ||\
			(map[mouse->y][mouse->x] == '*') ||\
		      	isSnake(snake, mouse->x, mouse->y) ||\
		       	isMouse(mouselist, mouse->x, mouse->y)){
			
			isValid = 1;
		}


	} while (isValid);

}
