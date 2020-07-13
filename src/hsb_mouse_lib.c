#include "hsb_mouse_lib.h"

#include <stdlib.h>

#include "grf_snake_lib.h" 

mouse_list_t* new_mouse_list(void){
	mouse_list_t* mouse_list = malloc(sizeof(mouse_list_t));
	mouse_list->first = NULL;
	mouse_list->size = 0;
	return mouse_list;
}

void destroy_mouse_list(mouse_list_t* mouse_list){
	clear_mouse_list(mouse_list);
	free(mouse_list);
}

bool is_mouse_at(position_t position, mouse_list_t* mouse_list){
	mouse_t* mouse = mouse_list->first;
	while(mouse != NULL){
		if (is_same_position(position, mouse->position)){
			return true;
		}
		mouse = mouse->next;
	}
	return false;
}

void destroy_last_mouse(mouse_list_t* mouse_list){
	if (mouse_list->size == 1){
		free(mouse_list->first);
		mouse_list->first = NULL;
		mouse_list->size = 0;
	}else if(!is_mouse_list_empty(mouse_list)){
		mouse_t* previous = mouse_list->first;
		mouse_t* last = previous->next;
		while(last->next != NULL){
			previous = last;
			last = previous->next;
		}
		free(last);
		previous->next = NULL;
		mouse_list->size--;
	}
}

int destroy_mouse_at(mouse_list_t* mouse_list, position_t position){
	int destroyed_mice = 0;
	if (mouse_list->size == 1){
		if(is_same_position(mouse_list->first->position, position)){
			free(mouse_list->first);
			mouse_list->first = NULL;
			mouse_list->size = 0;
			destroyed_mice++;
		}
	}else if(!is_mouse_list_empty(mouse_list)){
		mouse_t* previous = mouse_list->first;
		mouse_t* to_remove = previous->next;
		while(to_remove != NULL){
			if(is_same_position(to_remove->position, position)){	
				previous->next = to_remove->next;
				free(to_remove);
				mouse_list->size--;
				destroyed_mice++;
			}
			previous = to_remove;
			to_remove = previous->next;
		}
	}
	return destroyed_mice;
}

void new_mouse(mouse_list_t* mouse_list, position_t position){
	mouse_t* mouse = malloc(sizeof(mouse_t));
	mouse->position = position;
	mouse->next = mouse_list->first;
	mouse_list->first = mouse;
	mouse_list->size++;
}

void clear_mouse_list(mouse_list_t* mouse_list){
	mouse_t* mouse = mouse_list->first;
	while(mouse != NULL){
		mouse_t* tmp = mouse;
		mouse = mouse->next;
		free(tmp);
	}
	mouse_list->first = NULL;
	mouse_list->size = 0;
}

bool is_mouse_list_empty(mouse_list_t* mouse_list){
	return mouse_list->first == NULL;
}