#include <stdio.h>
//#include <conio.h>

#include "grf_snake_lib.h"

//Carrega o mapa do arquivo "filename" e o retorna como uma string junto com a altura e largura do mesmo
char* loadMap(char* filename,int *width,int *height){
	//TODO
	return NULL;
}

//Imprime a tela com todos os elementos nela
void refreshScreen(Snake *snake,int matrixSize){
	//DESENHA A TELA
	//gotoxy(0,0);
	printf("TAMANHO DA COBRA: %d\n",getSnakeSize(snake));

	for(int i = 0, size = matrixSize+2; i<size; i++){
		printf("#");
	}
	printf("\n");
	
	for(int y = 0; y<matrixSize; y++){
		printf("#");
		for(int x = 0; x<matrixSize; x++){
			if(snake->y == y && snake->x == x){
				printf("@");
			}else if(hasFood(snake,x,y)){
				printf("O");
			}else if(isSnake(snake,x,y)){
				printf("*");
			}else{
				printf(" ");
			}
		}
		printf("#\n");
	}
		
	for(int i = 0, size = matrixSize+2; i<size; i++){
		printf("#");
	}
	printf("\n");
	//FIM DESENHA A TELA
}
