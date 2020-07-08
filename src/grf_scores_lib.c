#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grf_scores_lib.h"
#include "draw.h"
#include "control.h"

#define SCORES_NUMBER 15

//reds all scores on highscores.bin
void getScores(Score* scores){
	FILE *fp = fopen("highscores.bin","rb");

	if(fp != NULL){
		fread(scores,sizeof(Score),SCORES_NUMBER,fp);

		fclose(fp);
	}
}

//receives a score and if it's a highscore puts it on the list of highscores and saves back to the file 
int updateScore(Score score){
	int isHighscore = 0;

	//get the scores currently on the file as an array
	Score *scores = malloc(SCORES_NUMBER * sizeof(Score));
	getScores(scores);

	FILE *fp = fopen("highscores.bin","wb");

	
	if(fp != NULL){
		int index = 0;
		
		//evaluates if score received is highscore
		for(int i = 0; i < SCORES_NUMBER && isHighscore == 0; i++){
			if(score.score >= scores[i].score){
				index = i;
				isHighscore = 1;
			}
		}

		//case positive, sorts it in the list
		if(isHighscore){
			for(int i = SCORES_NUMBER - 1; i > index; i--){
				scores[i] = scores[i-1];
			}
			
			scores[index] = score;
		}

		fwrite(scores,sizeof(Score),SCORES_NUMBER,fp);

		fclose(fp);
	}
	
	free(scores);

	return isHighscore;
}

//shows highscores
//if called after puting a score on the list can show a message saying if it was or not a highscore
void scoreScreen(int isHighscore){
    draw_initialize();
	set_background_color(COLOR_MENU);

	move_cursor(0, 0);

	Score *scores = malloc(SCORES_NUMBER * sizeof(Score));
	getScores(scores);

	for(int i = 0; i < SCORES_NUMBER; i++){
		draw_at(i+1, 1, COLOR_MENU, "%2d. %s", i+1,scores[i].name);
		draw_at(i+1, 22, COLOR_MENU, "|%03d", scores[i].score);
	}

	switch(isHighscore){
		case 0:
			draw_at(18, 2, COLOR_SELECTED_OPTION, "You did not make it to the top 15. :'\(");
			break;
		case 1:
			draw_at(18, 2, COLOR_SELECTED_OPTION, "HIGHSCORE!!!");
			break;
	}

	draw_at(20, 0, COLOR_MENU, "Press any key to exit.");
	
	refresh_screen();

    wait_for_key_press();

	free(scores);
}

void clearScores(){
	FILE* fp = fopen("highscores.bin","wb");

	if(fp != NULL){
		Score score[SCORES_NUMBER];

		for(int i = 0; i < SCORES_NUMBER; i++){
			strcpy(score[i].name,"-----");
			score[i].score = 0;
		}
		
		fwrite(score,sizeof(Score),15,fp);

		fclose(fp);
	}
}
