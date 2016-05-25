#include <stdio.h>
#include <ctype.h>
#include <curses.h>
#include <time.h>

#include "grf_snake_lib.h"
#include "grf_draw_lib.h"

#define SNAKE_SIZE 5
#define MATRIX_SIZE 25

int main(){
	//Inicia ncurses
	initscr();
	nodelay(stdscr,TRUE);

	//Cria a cobra
	Snake *snake = newSnake(SNAKE_SIZE,MATRIX_SIZE/2,MATRIX_SIZE/2);
	
	//Input do usuário
	char key;

	//Direção inicial da cobra
	int dir = _RIGHT_;

	//Pausa entre as iterações
	struct timespec espera;
	espera.tv_sec = 0;
	espera.tv_nsec = 100000000L;
	
	printf("Snake started.\n\n");

	//MOVIMENTAÇÃO
	do{
		//INPUT DE COMANDOS
		//scanf(" %c",&key);
		key = getch();

		if(key != ERR){
			key = toupper(key);
		}

		//ATUALIZA POSIÇÃO DA CABEÇA DA COBRA
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
				increaseSnake(snake,1);
				break;
			case '-':
				if(getSnakeSize(snake) > 2)
					decreaseSnake(snake);
				break;
			case 'X':
				endwin();
				break;
		}
		//if(key == 'W' || key == 'A' || key == 'S' || key == 'D'){
			//ATUALIZA POSIÇÃO DO CORPO DA COBRA
			moveSnake(snake,dir,MATRIX_SIZE,MATRIX_SIZE);
		//}
		
		if(key != 'X'){
			
			//clrscr();
			//DESENHA A TELA
			refreshScreen(snake,MATRIX_SIZE);

		}

		nanosleep(&espera,NULL);
		
	}while(key != 'X');
	
	destroySnake(snake);

	printf("Snake ended.\n\n");
	
	return 0;
}
