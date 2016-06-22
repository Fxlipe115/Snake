#ifndef GRF_SCORES_LIB
#	define GRF_SCORES_LIB

typedef struct score{
	char name[20];
	int score;
}Score;

void getScores(Score* scores);

int updateScore(Score score);

void scoreScreen();

#endif
