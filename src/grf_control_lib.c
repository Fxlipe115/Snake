#include <ctype.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "grf_snake_lib.h"
#include "hsb_mouse_lib.h"
#include "grf_control_lib.h"
#include "grf_draw_lib.h"
#include "grf_scores_lib.h"
#include "grf_collisions_lib.h"
#include "control.h"
#include "map.h"

#define LEVELS_NUMBER 7

int startLevel(int lvl, int score, int snakeSize, int* lives, int* isGameOver, int* levelFinished){
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

	//Apple for the end of the level
	Apple *apple = NULL;

	//Number of mice eaten
	int miceEaten = 0;

	//Flags
	int isDead = 0;
	int isPaused = 0;
	
	//Game loop
	do{
		int hasEaten = 0;

		iteraction++;
		if(iteraction % mapHeight == 0){
			//Game speed control
			wait.tv_nsec = ((wait.tv_nsec - 70000000) * .95) + 70000000;

			//Food creation control
			if(miceEaten < 10){
				mouse = newMouse(mouse,map,mapHeight,mapWidth,mapHeight*4,snake);
			}
		}

		if(miceEaten >= 10 && apple == NULL && !isDead){
			mouse = destroyAllMice(mouse);
			apple = newApple(map,mapHeight,mapWidth,snake);
		}


		dir = gameControl(dir,&isPaused);

		//Pause
		if(isPaused){
            wait_for_key_press();
			isPaused = 0;
			continue;
		}

		//Update snake position
		moveSnake(snake,dir,mapWidth,mapHeight);

		//Tries to eat mouse and changes hasEaten status on success
		mouse = eatMouse(mouse,&hasEaten,snake->x,snake->y);
		//Destroy one mouse when its time is 0
		mouse = destroyLastMouse(mouse);

		//Increase snake size and update status
		if(hasEaten){
			increaseSnake(snake,1);
			score += (lvl+1);
			miceEaten++;
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

		//If snake ate the apple
		if(eatApple(apple,snake->x,snake->y)){
			//End level
			score += 10;
			isDead = 1;
			*levelFinished = 1;
		}
			
		//Draws screen
		refreshScreen(snake,mouse,apple,map,mapWidth,mapHeight,lvl,score,*lives,miceEaten);
		
		//Wait for next iteration
		nanosleep(&wait,NULL);
		
	}while(!isDead);

	destroyMap(map,mapHeight);

	//Destroy snake
	destroySnake(snake);
	
	return score;
}

//Receives input, changes the current option and sends it to drawMenu function
void menuControl(){
	int option = 0;
	int exit = 0;

	do{
		drawMenu(option);

		control_key_t key = get_key();

		switch(key){
			case K_UP:
				option--;
				if(option < 0){
					option++;
				}
				drawMenu(option);
				break;
			case K_DOWN:
				option++;
				if(option > 4){
					option--;
				}
				drawMenu(option);
				break;
			case K_ENTER:
				//Selects current option
				switch(option){
					//New Game
					case 0:
						levelControl();
						break;
					//Select Level
					case 1:
						chooseLevel();
						break;
					//Highscores
					case 2:
						scoreScreen(-1);
						break;
					//Instructions
					case 3:
                        instructions();
						break;
					//Quit
					case 4:
						exit = 1;
						break;
				}
				break;
            default:
                break;
		}
	}while(!exit);
}

int gameControl(int dir,int* isPaused){
	int key = get_key_non_blocking();
	
	//Case it's a direction key, evaluates if diretion is valid
	//case it's 'p' changes isPaused to true
	//case q or esc returns q for quiting the level
	if(key != K_ERR){
		switch(key){
			case K_UP:
				if(dir == _LEFT_ || dir == _RIGHT_){
					dir = _UP_;
				}
				break;
			case K_LEFT:
				if(dir == _UP_ || dir == _DOWN_){
					dir = _LEFT_;
				}
				break;
			case K_DOWN:
				if(dir == _LEFT_ || dir == _RIGHT_){
					dir = _DOWN_;
				}
				break;
			case K_RIGHT:
				if(dir == _UP_ || dir == _DOWN_){
					dir = _RIGHT_;
				}
				break;
			case K_PAUSE:
				*isPaused = 1;
				break;
			case K_QUIT:
			case K_ESC:
				dir = 'Q';
				break;
		}
	}
	return dir;
}

void levelControl(){
	int curlevel = 0;
	int isGameOver = 0;
	int lives = 3;
	int score = 0;

	//This while makes the player advance one level case he beat the last one
	while(curlevel < LEVELS_NUMBER && !isGameOver){
		int levelFinished = 0;

		//This one returns to the same level until game over if the player dies
		while(!isGameOver && !levelFinished){
			score = startLevel(curlevel,score,5,&lives,&isGameOver,&levelFinished);
		}
	
		curlevel++;
	}
	getPlayerData(score);
}

//Gets player name and score and send it to update score function, then calls the highscores screen
void getPlayerData(int score){
	Score player;

	player.score = score;
	drawPlayerData(&player);
	

	int isHighscore = updateScore(player);

	scoreScreen(isHighscore);
}

//Gets initial x, y position given in the map
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

//Draws choose level menu and calls the level selected
void chooseLevel(){
	int level = 0;
	int exit = 0;
	int lives = 1;
	int isGameOver = 0;
	int levelFinished = 0;

	do{
		level_selection_screen(level, LEVELS_NUMBER);

		//Take care of user input
		control_key_t key = get_key();

		switch(key){
			case K_UP:
				level--;
				if(level < 0){
					level++;
				}
				break;
			case K_DOWN:
				level++;
				if(level > LEVELS_NUMBER - 1){
					level--;
				}
				break;
			case K_ENTER:
				lives = 1;
				startLevel(level,0,5,&lives,&isGameOver,&levelFinished);
				break;
			case K_ESC:
				exit = 1;
				break;
            default:
                break;
		}
	}while(!exit);
}

void instructions(){
    instructionsScreen();
    wait_for_key_press();
}
