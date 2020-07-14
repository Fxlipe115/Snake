#include "grf_collisions_lib.h"

#include <stdlib.h>

bool snake_can_colide_with_itself(snake_t* snake);
snake_body_t* ignore_beginning_of_body(snake_t* snake);
position_t get_random_position(map_size_t bounds);
bool is_free_position(position_t position, level_t* level);

bool snake_wall_collision(snake_t* snake, map_t* map){
	return is_wall_at(snake->head->position, map);
}

bool snake_rock_collision(snake_t* snake, map_t* map){
	return is_rock_at(snake->head->position, map);
}

bool snake_snake_collision(snake_t* snake){
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

bool snake_can_colide_with_itself(snake_t* snake){
	return snake->size > 4;
}

snake_body_t* ignore_beginning_of_body(snake_t* snake){
	// if the body part after the head is not skipped,
	// there's a false positive when the snake
	// grows in size
	return snake->head->next->next;
}

bool snake_mouse_collision(snake_t* snake, mouse_list_t* mouse_list){
	return is_mouse_at(snake->head->position, mouse_list);
}

bool snake_apple_collision(snake_t* snake, apple_t* apple){
	return false;
}

position_t get_random_free_position(level_t* level){
    position_t position;
	do{
		position = get_random_position(level->map->size);
	}while(!is_free_position(position, level));
	return position;
}

position_t get_random_position(map_size_t bounds){
	position_t position;
	position.x = rand() % bounds.width;
	position.y = rand() % bounds.height;
	return position;
}

bool is_free_position(position_t position, level_t* level){
    // return (map.layout[apple->y][apple->x] == '#') ||
	//        (map.layout[apple->y][apple->x] == '*') ||           
	//	      isSnake(snake, apple_position);
	return true;
}