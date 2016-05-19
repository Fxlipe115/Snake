#include <stdio.h>
#include <ctype.h>
//#include <conio.h>

//#include "../include/grf_snake_lib.h"
#include "grf_snake_lib.h"
#include "grf_draw_lib.h"

#define SNAKE_SIZE 5
#define MATRIX_SIZE 10

int main(){
	Snake *snake = newSnake(SNAKE_SIZE,MATRIX_SIZE/2,MATRIX_SIZE/2);
	char key;
	
	printf("TAMANHO DO MAPA: %dX%d\n\n",MATRIX_SIZE,MATRIX_SIZE);
		
	//DESENHA A TELA
	refreshScreen(snake,MATRIX_SIZE);
	
	//MOVIMENTAÇÃO
	printf("ENTRADA DE COMANDOS: (DIGITE 'X' PARA SAIR)\n");
	do{
		//INPUT DE COMANDOS
		scanf(" %c",&key);
		//key = getch();
		key = toupper(key);
		
		//ATUALIZA POSIÇÃO DA CABEÇA DA COBRA
		int dir;
		switch(key){
			case 'W':
				//snake[0].y--;
				dir = _UP_;
				break;
			case 'A':
				//snake[0].x--;
				dir = _LEFT_;
				break;
			case 'S':
				//snake[0].y++;
				dir = _DOWN_;
				break;
			case 'D':
				//snake[0].x++;
				dir = _RIGHT_;
				break;
			case '+':
				increaseSnake(snake);
				break;
			case '-':
				if(getSnakeSize(snake) > 2)
					decreaseSnake(snake);
				break;
			case 'X':
				break;
		}
		if(key == 'W' || key == 'A' || key == 'S' || key == 'D'){
			//ATUALIZA POSIÇÃO DO CORPO DA COBRA
			moveSnake(snake,dir,MATRIX_SIZE,MATRIX_SIZE);
		}
		
		if(key != 'X'){
			
			//clrscr();
			//DESENHA A TELA
			refreshScreen(snake,MATRIX_SIZE);

		}
		
		
	}while(key != 'X');
	
	destroySnake(snake);
	
	return 0;
}
