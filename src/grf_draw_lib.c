#include <stdio.h>
#include <curses.h>

#include "grf_snake_lib.h"

//Carrega o mapa do arquivo "filename" e o retorna como uma string junto com a altura e largura do mesmo
char* loadMap(char* filename,int *width,int *height){
	//TODO
	return NULL;
}

//Imprime a tela com todos os elementos nela
void refreshScreen(Snake *snake,int matrixSize){
	//DESENHA A TELA
	//initscr();
	start_color();

	init_pair(1,COLOR_MAGENTA,COLOR_MAGENTA);//fundo
	init_pair(2,COLOR_WHITE,COLOR_BLACK);//score
	init_pair(3,COLOR_WHITE,COLOR_WHITE);//mapa
	init_pair(4,COLOR_BLACK,COLOR_BLACK);//cabeça
	init_pair(5,COLOR_RED,COLOR_RED);//comida
	init_pair(6,COLOR_BLUE,COLOR_BLUE);//corpo
	move(0,0);

	bkgd(COLOR_PAIR(1));	

	attron(COLOR_PAIR(2));
	printw("Tamanho: %d\n",getSnakeSize(snake));
	attroff(COLOR_PAIR(2));

	for(int y = 0; y<matrixSize; y++){
		for(int x = 0; x<matrixSize; x++){
			if(snake->y == y && snake->x == x){
				attron(COLOR_PAIR(4));
				printw("  ");
				attroff(COLOR_PAIR(4));
				//printf("@");
			}else if(hasFood(snake,x,y)){
				attron(COLOR_PAIR(5));
				printw("  ");
				attroff(COLOR_PAIR(5));
				//printf("O");
			}else if(isSnake(snake,x,y)){
				attron(COLOR_PAIR(6));
				printw("  ");
				attroff(COLOR_PAIR(6));
				//printf("*");
			}else{
				attron(COLOR_PAIR(3));
				printw("  ");
				attroff(COLOR_PAIR(3));
				//printf(" ");
			}
		}
		printw("\n");
	}
		
	/*for(int i = 0, size = matrixSize+2; i<size; i++){
		printf("#");
	}
	printf("\n");*/
	
	refresh();
	//FIM DESENHA A TELA
}
