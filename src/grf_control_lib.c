#include "grf_control_lib.h"

#include <ctype.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "grf_snake_lib.h"
#include "hsb_mouse_lib.h"
#include "grf_draw_lib.h"
#include "grf_scores_lib.h"
#include "grf_collisions_lib.h"
#include "control.h"
#include "map.h"
#include "position.h"
#include "game.h"

#define LEVELS_NUMBER 7

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
						gameControl();
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

int levelControl(int dir){
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
			case K_QUIT:
			case K_ESC:
				dir = 'Q';
				break;
		}
	}
	return dir;
}

void gameControl(){
	struct timespec wait;
	wait.tv_sec = 0;
	wait.tv_nsec = 999999999L;
	int curlevel = 0;

	game_t* game = new_game();

	game->current_level = new_level(curlevel);

		//This while makes the player advance one level case he beat the last one
	while(!game->game_over && !game->current_level->win){
		game->current_level->snake->direction = levelControl(game->current_level->snake->direction);

		update_game_state(game);

		if(game->paused){
			wait_for_key_press();
			game->paused = false;
		}

		refreshScreen(game);
		nanosleep(&wait,NULL);
	}
	getPlayerData(game->score);
}

//Gets player name and score and send it to update score function, then calls the highscores screen
void getPlayerData(int score){
	Score player;

	player.score = score;
	drawPlayerData(&player);
	

	int isHighscore = updateScore(player);

	scoreScreen(isHighscore);
}

//Draws choose level menu and calls the level selected
void chooseLevel(){
	int level = 0;
	int exit = 0;

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
				//startLevel(new_level(level));
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
