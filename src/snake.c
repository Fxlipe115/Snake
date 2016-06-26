#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>

#include "grf_control_lib.h"

int main(){
	printf("Snake started.\n\n");

	//seed for rand function
	srand(time(NULL));

	//start ncurses
	initscr();

	//ncurses options
	nodelay(stdscr,TRUE);
	keypad(stdscr,TRUE);
	noecho();

	//start menu
	menuControl();

	//once game is over, finish ncurses
	endwin();
	
	printf("Snake ended.\n\n");
	
	return 0;
}
