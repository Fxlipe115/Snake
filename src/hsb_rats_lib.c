#include <stdlib.h>

#include "hsb_rats_lib.h"
#include "grf_snake_lib.h" 

int isRat (Rats* rats, int x, int y){
int isRat = 0;

while( rats != NULL && isRat == 0 ){

	int position = ((rats->x == x) && (rats->y == y));
	
	if (position) {
		 isRat=1; }
	
	rats= rats->next;}

return isRat; 
}

void destroyRat (Rats* rat){

	if(rat != NULL){

		Rats *previous = NULL;

		while(rat->next != NULL){

			previous = rat;

			rat= rat->next;
		}

		if(rat->time == 0){
			free(rat);

			previous->next = NULL;
		}
	}
}


void newRat (Rats* ratlist, char** map, int height, int width, int time, Snake *snake){

	Rats* rat = malloc(sizeof(Rats));

	rat->next = ratlist;

	ratlist = rat;

	rat->time = time;

	do{
		int isValid = 0;

		rat->x = rand() % width;
		rat->y = rand() % height;
		
		if ((map[rat->y][rat->x] == '#') || (map[rat->y][rat->x] == '*') ||  isSnake(snake, rat->x, rat->y)){
			
			isValid = 1;}


	} while (isValid);

}







