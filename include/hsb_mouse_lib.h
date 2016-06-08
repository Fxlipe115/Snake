#ifndef HSB_RATS_LIB
#define HSB_RATS_LIB 

typedef struct mouse{

int time;
int x;
int y;
struct mouse *next;

} Mouse;

int isMouse(Mouse* mouse, int x, int y);

void DestroyMouse(Mouse* mouse);

void newMouse(Mouse* mouselist, char** map, int height, int width, int time, Snake* snake);

#endif
