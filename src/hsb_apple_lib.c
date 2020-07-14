#include "hsb_apple_lib.h"

#include <stdlib.h>

apple_t* new_apple(position_t position){
	apple_t* apple = malloc(sizeof(apple_t));
	apple->position = position;
	return apple;
}

void destroy_apple(apple_t* apple){
	if(apple != NULL){
		free(apple);
	}
}

bool is_apple_at(apple_t* apple, position_t position){
	if(apple != NULL){
		return is_same_position(apple->position, position);
	}else{
		return false;
	}
}
