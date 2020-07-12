#include "map.h"

#include <stdio.h>
#include <stdlib.h>

char** allocate_map_memory(map_size_t size);

//Loads map from file "filename" and returns it as a matrix of chars and returns by reference its width and height
map_t loadMap(char* filename){
    FILE *mapfile = fopen(filename, "r");
    map_t map;

    if(mapfile != NULL){
        fscanf(mapfile, "%d", &map.size.height);
        fscanf(mapfile, "%d", &map.size.width);
        fseek(mapfile, 1, SEEK_CUR);

        //Aloca a matriz que armazena o mapa
        map.layout = allocate_map_memory(map.size);

        for(int i = 0; i < map.size.height; i++){
            fgets(map.layout[i], map.size.width+2, mapfile);
        }

        fclose(mapfile);
    }

    return map;
}

char** allocate_map_memory(map_size_t size){
    size_t column_memory_size = size.height * sizeof(char*);
    size_t row_memory_size = (size.width+2) * sizeof(char);

    char** map = (char**)malloc(column_memory_size);
    for(int i = 0; i < size.height; i++){
        map[i] = malloc(row_memory_size);
    }

    return map;
}

//Frees the memory associated with the map matrix
void destroyMap(map_t map){
    for(int i = 0; i < map.size.height; i++){
        free(map.layout[i]);
    }
    free(map.layout);
}

position_t map_initial_position(map_t map){
	position_t position;
	for(int y = 0; y < map.size.height; y++){
		for(int x = 0; x < map.size.width; x++){
			if(map.layout[y][x] == 'o'){
				position.x = x;
				position.y = y;
			}
		}
	}
	return position;
}