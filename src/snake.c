#include <stdio.h>
#include <ctype.h>
#include <curses.h>
#include <time.h>

#include "grf_snake_lib.h"
#include "grf_draw_lib.h"
#include "grf_control_lib.h"

#define SNAKE_SIZE 5
#define MATRIX_SIZE 25

int main(){
	printf("Snake started.\n\n");

	//Inicia ncurses
	initscr();
	nodelay(stdscr,TRUE);
	keypad(stdscr,TRUE);
	noecho();

	//Cria a cobra
	Snake *snake = newSnake(SNAKE_SIZE,MATRIX_SIZE/2,MATRIX_SIZE/2);

	//Direção inicial da cobra
	int dir = _RIGHT_;

	//Pausa entre as iterações
	struct timespec wait;
	wait.tv_sec = 0;
	wait.tv_nsec = 100000000L;
	
	//MOVIMENTAÇÃO
	do{
		dir = gameControl(dir);

/*		//INPUT DE COMANDOS
		key = getch();

		if(key != ERR){
			key = toupper(key);
		}

		//ATUALIZA POSIÇÃO DA CABEÇA DA COBRA
		switch(key){
			case 'W':
			case KEY_UP:
				if(dir != _DOWN_){
					dir = _UP_;
				}
				break;
			case 'A':
			case KEY_LEFT:
				if(dir != _RIGHT_){
					dir = _LEFT_;
				}
				break;
			case 'S':
			case KEY_DOWN:
				if(dir != _UP_){
					dir = _DOWN_;
				}
				break;
			case 'D':
			case KEY_RIGHT:
				if(dir != _LEFT_){
					dir = _RIGHT_;
				}
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
*/

			//ATUALIZA POSIÇÃO DO CORPO DA COBRA
			moveSnake(snake,dir,MATRIX_SIZE,MATRIX_SIZE);
		//}
			
		//DESENHA A TELA
		refreshScreen(snake,MATRIX_SIZE);


		if(dir == 'X'){
			endwin();
		}


		nanosleep(&wait,NULL);
		
	}while(dir != 'X');
	
	destroySnake(snake);

	printf("Snake ended.\n\n");
	
	return 0;
}
