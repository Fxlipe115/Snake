#ifndef HSB_RATS_LIB
#define HSB_RATS_LIB

#include <stdbool.h>

#include "grf_snake_lib.h"
#include "map.h"
#include "position.h"

typedef struct mouse {
    position_t position;
    int time;
    struct mouse *next;
} mouse_t;

typedef struct mouse_list {
    mouse_t* first;
    int size;
} mouse_list_t;


mouse_list_t* new_mouse_list(void);

void destroy_mouse_list(mouse_list_t* mouse_list);

void newMouse(mouse_list_t* mouse_list, map_t map, int time, snake_t* snake);

void destroy_last_mouse(mouse_list_t* mouse_list);

void clear_mouse_list(mouse_list_t* mouse_list);

int destroy_mouse_at(mouse_list_t* mouse_list, position_t position);

bool is_mouse_at(position_t position, mouse_list_t* mouse_list);

bool is_mouse_list_empty(mouse_list_t* mouse_list);

#endif
