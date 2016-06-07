#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

#include "grf_snake_lib.h"

//Carrega o mapa do arquivo "filename" e o retorna como um array de strings e informa por referência a altura e largura do mesmo
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
	}
	fclose(mapfile);

	return mapa;
}

void destroyMap(char** map,int height){
	for(int i = 0; i<height; i++){
		free(map[i]);
	}
	free(map);
}

//Imprime a tela com todos os elementos nela
void refreshScreen(WINDOW *window,Snake *snake,char **map,int matrixSize,int matrixySize){
	//DESENHA A TELA
	//initscr();
	start_color();

	init_pair(1,COLOR_MAGENTA,COLOR_MAGENTA);//fundo
	init_pair(2,COLOR_WHITE,COLOR_BLACK);//score
	init_pair(3,COLOR_WHITE,COLOR_WHITE);//mapa
	init_pair(4,COLOR_BLACK,COLOR_BLACK);//cabeça
	init_pair(5,COLOR_RED,COLOR_RED);//comida
	init_pair(6,COLOR_BLUE,COLOR_BLUE);//corpo
	wmove(window,0,0);

	wbkgd(window,COLOR_PAIR(1));	

	wattron(window,COLOR_PAIR(2));
	wprintw(window,"Tamanho: %d\n",getSnakeSize(snake));
	wattroff(window,COLOR_PAIR(2));

	for(int y = 0; y<matrixySize; y++){
		for(int x = 0; x<matrixSize; x++){
			if(snake->y == y && snake->x == x){
				wattron(window,COLOR_PAIR(4));
				wprintw(window,"  ");
				wattroff(window,COLOR_PAIR(4));
				//printf("@");
			}else if(hasFood(snake,x,y)){
				wattron(window,COLOR_PAIR(5));
				wprintw(window,"  ");
				wattroff(window,COLOR_PAIR(5));
				//printf("O");
			}else if(isSnake(snake,x,y)){
				wattron(window,COLOR_PAIR(6));
				wprintw(window,"  ");
				wattroff(window,COLOR_PAIR(6));
				//printf("*");
			}else if(map[y][x] == '#'){
				wattron(window,COLOR_PAIR(4));
				wprintw(window,"  ");
				wattroff(window,COLOR_PAIR(4));
				//printf(" ");
			}else{
				wattron(window,COLOR_PAIR(3));
				wprintw(window,"  ");
				wattroff(window,COLOR_PAIR(3));
			}
		}
		wprintw(window,"\n");
	}
	
	
	wrefresh(window);
	//FIM DESENHA A TELA
}
