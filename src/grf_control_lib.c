#include <stdio.h>
#include <curses.h>

#include "grf_snake_lib.h"

void startLevel(){
	//TODO
	//trecho do snake.c
}

void startMenu(){
	//TODO
}

int gameControl(Snake *snake){
	int key = getch();
	
	if(key != ERR){
		switch(key){
			case 'W':
			case KEY_UP:
				if(snake->dir != _DOWN_){
					snake->dir = _UP_;
				}
				break;
			case 'A':
			case KEY_LEFT:
				if(snake->dir != _RIGHT_){
					snake->dir = _LEFT_;
				}
				break;
			case 'S':
			case KEY_DOWN:
				if(snake->dir != _UP_){
					snake->dir = _DOWN_;
				}
				break;
			case 'D':
			case KEY_RIGHT:
				if(snake->dir != _LEFT_){
					snake->dir = _RIGHT_;
				}
				break;
//			case '+':
//				increaseSnake(snake,1);
//				break;
//			case '-':
//				if(getSnakeSize(snake) > 2)
//					decreaseSnake(snake);
//				break;
//			case 'X':
//				endwin();
//				break;
		}
	}
	return 0;
}
