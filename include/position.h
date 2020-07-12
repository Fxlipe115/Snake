#ifndef POSITION_H
#define POSITION_H

typedef struct position
{
    int x;
    int y;
} position_t;

int is_same_position(position_t p1, position_t p2);

#endif