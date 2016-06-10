#include <curses.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "grf_snake_lib.h"
#include "grf_draw_lib.h"
#include "grf_control_lib.h"

#define SNAKE_SIZE 5

int startLevel(int lvl){
	//Game window
	WINDOW *gamescr = newwin(0,0,0,0);
	nodelay(gamescr,TRUE);
	keypad(gamescr,TRUE);
	noecho();

	//Score
	int score = 0;

	//Initial direction of snake
	int dir = _RIGHT_;

	//Pause between iteractions
	struct timespec wait;
	wait.tv_sec = 0;
	wait.tv_nsec = 999999999L;

	//Number of iteraction for mouse creation/destruction control
	unsigned int iteraction = 0;

	//Map loading
	int mapHeight, mapWidth;
	char mapfile[13] = "maps/", lvlstr[3];
	sprintf(lvlstr,"%d",lvl);
	strcat(mapfile,lvlstr);
	strcat(mapfile,".txt");

	char **map = loadMap(mapfile,&mapWidth,&mapHeight);

	//Create snake
	Snake *snake = newSnake(SNAKE_SIZE,mapWidth/2,mapHeight/2);

	//MOVIMENTAÇÃO
	do{
		//Controle da velocidade do jogo
		iteraction++;
		if(iteraction % 4 == 0){
			wait.tv_nsec = ((wait.tv_nsec - 50000000) * .95) + 50000000;
		}

		dir = gameControl(dir);
		
		//Pausa
		//TODO passar pra uma função
		if(dir == 'P'){
			do{
				dir = getch();
			}while(dir == ERR);
			ungetch(dir);
}

		//ATUALIZA POSIÇÃO DO CORPO DA COBRA
		moveSnake(snake,dir,mapWidth,mapHeight);
			
		//DESENHA A TELA
		refreshScreen(gamescr,snake,map,mapWidth,mapHeight);
		
		//Espera para próxima iteração
		nanosleep(&wait,NULL);
		
	}while(dir != 'Q');

	destroyMap(map,mapHeight);

	//Encerra a tela
	delwin(gamescr);

	//Destroy a cobra	
	destroySnake(snake);
	
	return score;
}

void startMenu(){
	//TODO
}

int gameControl(int dir){
	int key = getch();
	
	if(key != ERR){
		switch(toupper(key)){
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
//			case '+':
//				increaseSnake(snake,1);
//				break;
//			case '-':
//				if(getSnakeSize(snake) > 2)
//					decreaseSnake(snake);
//				break;
			case 'P':
				dir = 'P';
				break;
			case 'Q':
			case KEY_ESC:
				dir = 'Q';
				break;
		}
	}
	return dir;
}
