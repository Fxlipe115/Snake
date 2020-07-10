#include <stdio.h>
#include <stdlib.h>

//Loads map from file "filename" and returns it as a matrix of chars and returns by reference its width and height
char** loadMap(char* filename,int* width,int* height){

    FILE *mapfile = fopen(filename,"r");
    char **mapa;

    if(mapfile != NULL){
        fscanf(mapfile,"%d",height);
        fscanf(mapfile,"%d",width);
        fseek(mapfile,1,SEEK_CUR);

        //Aloca a matriz que armazena o mapa
        char **map = (char**)malloc(*height * sizeof(char*));
        for(int i = 0; i < *height; i++){
            map[i] = malloc((*width+2) * sizeof(char));
        }

        for(int i = 0;i<*height;i++){
            fgets(map[i],*width+2,mapfile);
        }

        mapa = map;
        fclose(mapfile);
    }

    return mapa;
}

//Frees the memory associated with the map matrix
void destroyMap(char** map,int height){
    for(int i = 0; i<height; i++){
        free(map[i]);
    }
    free(map);
}