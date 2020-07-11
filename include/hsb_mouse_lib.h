#ifndef HSB_RATS_LIB
#define HSB_RATS_LIB 

#include "grf_snake_lib.h"
#include "map.h"

typedef struct mouse{

int time;
int x;
int y;
struct mouse *next;

} Mouse;

int isMouse(Mouse* mouse, int x, int y);

Mouse* destroyLastMouse(Mouse* mouse);

Mouse* eatMouse(Mouse* mouse,int *hasEaten,int x,int y);

Mouse* newMouse(Mouse* mouselist, map_t map, int time, Snake* snake);


Mouse* destroyAllMice(Mouse* mouse);

#endif
