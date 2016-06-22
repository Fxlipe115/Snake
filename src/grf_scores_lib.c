#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

#include "grf_scores_lib.h"

void getScores(Score* scores){
	FILE *fp = fopen("highscores.bin","rb");

	if(fp != NULL){
		fread(scores,sizeof(Score),10,fp);

		fclose(fp);
	}
}

int updateScore(Score score){
	int isHighscore = 0;

	FILE *fp = fopen("highscores.bin","wb");

	Score *scores = malloc(10 * sizeof(Score));
	getScores(scores);

	if(fp != NULL){
		int index = 0;

		for(int i = 0; i < 10; i++){
			if(score.score > scores[i].score){
				index = i;
				isHighscore = 1;
			}
		}

		if(isHighscore){
			for(int i = 9; i > index; i--){
				scores[i] = scores[i-1];
			}
			
			scores[index] = score;
		}

		fwrite(scores,sizeof(Score),10,fp);

		fclose(fp);
	}
	
	free(scores);

	return isHighscore;
}

void scoreScreen(){
	WINDOW* scorescr = newwin(0,0,0,0);

	start_color();
	init_pair(1,COLOR_BLACK,COLOR_GREEN);//bkgd
	init_pair(2,COLOR_WHITE,COLOR_BLACK);//text
	wbkgd(scorescr,COLOR_PAIR(1));

	wmove(scorescr,0,0);

	Score *scores = malloc(10 * sizeof(Score));
	getScores(scores);

	for(int i = 0; i < 10; i++){
		wattron(scorescr,COLOR_PAIR(2));
		mvwprintw(scorescr,i+1,1,"%s",scores[i].name);
		mvwprintw(scorescr,i+1,22,"|%03d",scores[i].score);
		wattroff(scorescr,COLOR_PAIR(2));
	}

	mvwprintw(scorescr,22,0,"Pressione qualquer tecla para sair.");
	
	wrefresh(scorescr);

	int k;
	do{
		k = getch();
	}while(k == ERR);

	free(scores);
}
