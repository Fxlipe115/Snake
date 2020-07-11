#ifndef MAP_H
#define MAP_H

typedef struct map_size {
    int width;
    int height;
} map_size_t;

typedef struct map {
    char** layout;
    map_size_t size;
} map_t;

map_t loadMap(char* filename);

void destroyMap(map_t map);

#endif