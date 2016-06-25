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
#include "grf_collisions_lib.h"

int startLevel(int lvl, int score, int snakeSize, int* lives, int* isGameOver){
	//Game window
	WINDOW *gamescr = newwin(0,0,0,0);
	nodelay(gamescr,TRUE);
	keypad(gamescr,TRUE);
	noecho();

	//Initial direction of snake
	int dir = _RIGHT_;

	//Pause between iteractions
	struct timespec wait;
	wait.tv_sec = 0;
	wait.tv_nsec = 999999999L;

	//Number of iteraction for mouse creation control
	unsigned int iteraction = 0;

	//Map loading
	int mapHeight, mapWidth;
	char mapfile[13];
	sprintf(mapfile,"maps/%d.txt",lvl);

	char **map = loadMap(mapfile,&mapWidth,&mapHeight);

	//Create snake
	int xpos = 0,ypos = 0;
	getInitPos(map,mapWidth,mapHeight,&xpos,&ypos);
	Snake *snake = newSnake(snakeSize,xpos,ypos);

	//Create mouse list
	Mouse *mouse = NULL;

	int isDead = 0;

	int isPaused = 0;
	
	//MOVIMENTAÇÃO
	do{
		int hasEaten = 0;

		//Game speed control
		iteraction++;
		if(iteraction % mapHeight == 0){
			wait.tv_nsec = ((wait.tv_nsec - 70000000) * .95) + 70000000;
			mouse = newMouse(mouse,map,mapHeight,mapWidth,mapHeight*4,snake);
		}

		dir = gameControl(dir,&isPaused);

		//Pause
		if(isPaused){
			int key;
			do{
				key = getch();
			}while(key == ERR);
			isPaused = 0;
			continue;
		}

		//Update snake position
		moveSnake(snake,dir,mapWidth,mapHeight);

		//Tries to eat mouse and changes hasEaten status on success
		mouse = eatMouse(mouse,&hasEaten,snake->x,snake->y);
		//Destroy one mouse when its time is 0
		destroyLastMouse(mouse);

		//Increase snake size and update status
		if(hasEaten){
			increaseSnake(snake,1);
			score += (lvl+1);
		}

		//Checks collision with rock
		if(rockCollision(map,snake->x,snake->y)){
			decreaseSnake(snake);
			if(score > 0){
				score--;
			}
		}

		//Checks collision with wall, itself or insufficient size
		if(wallCollision(map,snake->x,snake->y) || snakeCollision(snake) || (getSnakeSize(snake) < 2)){
			isDead = 1;
			--*lives;
			if(*lives == 0){
				*isGameOver = 1;
			}
		}

		if(dir == 'Q'){
			isDead = 1;
			*isGameOver = 1;
		}
			
		//DESENHA A TELA
		refreshScreen(gamescr,snake,mouse,map,mapWidth,mapHeight,score,*lives);
		
		//Espera para próxima iteração
		nanosleep(&wait,NULL);
		
	}while(!isDead);

	destroyMap(map,mapHeight);

	//Encerra a tela
	delwin(gamescr);

	//Destroy a cobra	
	destroySnake(snake);
	
	return score;
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
						levelControl();
						break;
					//Select Level
					case 1:
						//startLevel(1);
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

int gameControl(int dir,int* isPaused){
	int key = getch();
	
	if(key != ERR){
		switch(toupper(key)){
			case 'W':
			case KEY_UP:
				if(dir == _LEFT_ || dir == _RIGHT_){
					dir = _UP_;
				}
				break;
			case 'A':
			case KEY_LEFT:
				if(dir == _UP_ || dir == _DOWN_){
					dir = _LEFT_;
				}
				break;
			case 'S':
			case KEY_DOWN:
				if(dir == _LEFT_ || dir == _RIGHT_){
					dir = _DOWN_;
				}
				break;
			case 'D':
			case KEY_RIGHT:
				if(dir == _UP_ || dir == _DOWN_){
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
				*isPaused = 1;
				break;
			case 'Q':
			case KEY_ESC:
				dir = 'Q';
				break;
		}
	}
	return dir;
}

void levelControl(){
	int isGameOver = 0;
	int lives = 3;
	int score = 0;

	while(!isGameOver){
		score = startLevel(0,score,5,&lives,&isGameOver);
	}
}

void getInitPos(char** map,int width,int height,int* xpos,int* ypos){
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			if(map[y][x] == 'o'){
				*xpos = x;
				*ypos = y;
			}
		}
	}
}
