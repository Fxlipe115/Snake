#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

#include "grf_snake_lib.h"
#include "hsb_mouse_lib.h"

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
void refreshScreen(WINDOW *window,Snake *snake,Mouse *mouse,char **map,int matrixSize,int matrixySize,int score){
	//DESENHA A TELA
	//initscr();
	start_color();

	init_pair(1,COLOR_MAGENTA,COLOR_MAGENTA);//background
	init_pair(2,COLOR_WHITE,COLOR_BLACK);//score
	init_pair(3,COLOR_WHITE,COLOR_WHITE);//map
	init_pair(4,COLOR_BLACK,COLOR_BLACK);//wall
	init_pair(5,COLOR_BLACK,COLOR_GREEN);//food eaten
	init_pair(6,COLOR_GREEN,COLOR_GREEN);//body
	init_pair(7,COLOR_BLACK,COLOR_GREEN);//head
	init_pair(8,COLOR_BLACK,COLOR_WHITE);//mouse
	init_pair(9,COLOR_RED,COLOR_WHITE);//rock
	wmove(window,0,0);

	wbkgd(window,COLOR_PAIR(1));	

	wattron(window,COLOR_PAIR(2));
	wprintw(window,"Score: %d\n",score);
	wattroff(window,COLOR_PAIR(2));

	for(int y = 0; y<matrixySize; y++){
		for(int x = 0; x<matrixSize; x++){
			if(snake->y == y && snake->x == x){
				//head
				wattron(window,COLOR_PAIR(7)|A_BOLD);
				wprintw(window,"00");
				wattroff(window,COLOR_PAIR(7)|A_BOLD);
			}else if(hasFood(snake,x,y)){
				//food eaten
				wattron(window,COLOR_PAIR(5)|A_BOLD);
				wprintw(window,"()");
				wattroff(window,COLOR_PAIR(5)|A_BOLD);
			}else if(isSnake(snake,x,y)){
				//body
				wattron(window,COLOR_PAIR(6));
				wprintw(window,"  ");
				wattroff(window,COLOR_PAIR(6));
			}else if(isMouse(mouse,x,y)){
				//mouse
				wattron(window,COLOR_PAIR(8)|A_BOLD);
				wprintw(window,"~>");
				wattroff(window,COLOR_PAIR(8)|A_BOLD);
			}else if(map[y][x] == '#'){
				//wall
				wattron(window,COLOR_PAIR(4));
				wprintw(window,"  ");
				wattroff(window,COLOR_PAIR(4));
			}else if(map[y][x] == '*'){
				//rocks
				wattron(window,COLOR_PAIR(9));
				wprintw(window,"@@");
				wattroff(window,COLOR_PAIR(9));
			}else{
				//map background
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

void drawMenu(WINDOW* menu,int option){
	char* options[] = {"Start Game","Select Level","Highscores","Quit"};

	start_color();
	init_pair(0,COLOR_WHITE,COLOR_BLACK);
	wbkgd(menu,COLOR_PAIR(0));
	
	wmove(menu,0,0);

	for(int i = 0; i < 4; i++){
		if(option == i){
			wattron(menu,A_REVERSE);
			wprintw(menu,"-%s\n",options[i]);
			wattroff(menu,A_REVERSE);
		}else{
			wprintw(menu," %s\n",options[i]);
		}
	}
	
	wrefresh(menu);
}
