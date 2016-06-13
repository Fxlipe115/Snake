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

	menuControl();

	endwin();
	
	printf("Snake ended.\n\n");
	
	return 0;
}
