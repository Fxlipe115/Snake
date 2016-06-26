#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "grf_control_lib.h"
#include "grf_scores_lib.h"

int main(int argc, char* argv[]){
	if(argc > 1){
		if(strcmp(argv[1],"-c") == 0 || strcmp(argv[1],"--clear") == 0){
			clearScores();
		}
	}

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
