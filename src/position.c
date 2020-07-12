#include "position.h"

int is_same_position(position_t p1, position_t p2){
    int is_same_x = p1.x == p2.x;
    int is_same_y = p1.y == p2.y;
    return is_same_x && is_same_y;
}