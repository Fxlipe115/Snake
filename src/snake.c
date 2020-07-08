#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "grf_control_lib.h"
#include "grf_scores_lib.h"
#include "draw.h"
#include "control.h"

int main(int argc, char* argv[]){
	if(argc > 1){
		if(strcmp(argv[1],"-c") == 0 || strcmp(argv[1],"--clear") == 0){
			clearScores();
		}
	}

	printf("Snake started.\n\n");

	//seed for rand function
	srand(time(NULL));

    draw_initialize();
    initialize_controls();

	//start menu
	menuControl();

    end_draw();
    end_controls();
	
	printf("Snake ended.\n\n");
	
	return 0;
}
