#include <curses.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "grf_snake_lib.h"
#include "hsb_mouse_lib.h"
#include "grf_control_lib.h"
#include "grf_draw_lib.h"
#include "grf_scores_lib.h"

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
	char mapfile[13];
	sprintf(mapfile,"maps/%d.txt",lvl);

	char **map = loadMap(mapfile,&mapWidth,&mapHeight);

	//Create snake
	Snake *snake = newSnake(SNAKE_SIZE,mapWidth/2,mapHeight/2);

	//Create mouse list
	Mouse *mouse = NULL;

	//MOVIMENTAÇÃO
	do{
		int hasEaten = 0;

		//Controle da velocidade do jogo
		iteraction++;
		if(iteraction % mapHeight == 0){
			wait.tv_nsec = ((wait.tv_nsec - 70000000) * .95) + 70000000;
			mouse = newMouse(mouse,map,mapHeight,mapWidth,mapHeight*4,snake);
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

		mouse = eatMouse(mouse,&hasEaten,snake->x,snake->y);
		destroyLastMouse(mouse);

		if(hasEaten){
			increaseSnake(snake,1);
			score += (lvl+1);
		}
			
		//DESENHA A TELA
		refreshScreen(gamescr,snake,mouse,map,mapWidth,mapHeight,score);
		
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
	
}

void menuControl(){
	WINDOW *menuscr = newwin(0,0,0,0);
	int option = 0;
	int exit = 0;

	nodelay(menuscr,FALSE);
	keypad(menuscr,TRUE);
	noecho();

	do{
		drawMenu(menuscr,option);

		int key = getch();

		switch(toupper(key)){
			case 'W':
			case KEY_UP:
				option--;
				if(option < 0){
					option++;
				}
				drawMenu(menuscr,option);
				break;
			case 'S':
			case KEY_DOWN:
				option++;
				if(option > 3){
					option--;
				}
				drawMenu(menuscr,option);
				break;
			case '\n':
				switch(option){
					//New Game
					case 0:
						startLevel(0);
						break;
					//Select Level
					case 1:
						startLevel(1);
						break;
					//Highscores
					case 2:
						scoreScreen();
						break;
					//Quit
					case 3:
						exit = 1;
						break;
				}
				break;
		}
	}while(!exit);

	delwin(menuscr);
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
