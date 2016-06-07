#ifndef HSB_RATS_LIB
#define HSB_RATS_LIB 

typedef struct rats{

int time;
int x;
int y;
struct rats *next;

} Rats;

int isRat (Rats* rats, int x, int y);

void DestroyRat (Rats* rat);

void newRat (Rats* ratlist, char** map, int height, int width, int time, Snake* snake);

#endif
