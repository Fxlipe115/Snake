#ifndef GRF_CONTROL_LIB
#	define GRF_CONTROL_LIB

#define KEY_ESC 27

int startLevel(int lvl,int score,int snakeSize,int* lives,int* isGameOver,int* levelFinished);

void startMenu();

void menuControl();

int gameControl(int dir,int* isPaused);

void levelControl();

void getPlayerData(int score);

void getInitPos(char** map,int width,int height,int* xpos,int* ypos);

void chooseLevel();

void instructions();

#endif
