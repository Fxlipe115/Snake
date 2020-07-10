#ifndef MAP_H
#define MAP_H

char** loadMap(char* filename,int *width,int *height);

void destroyMap(char** map,int height);

#endif