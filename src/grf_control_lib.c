#include <stdio.h>
#include <curses.h>
#include <ctype.h>

#include "grf_snake_lib.h"

void startLevel(){
	//TODO
	//trecho do snake.c
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
			case 'X':
				dir = 'X';
				break;
		}
	}
	return dir;
}
