#ifndef GRF_CONTROL_LIB
#	define GRF_CONTROL_LIB

#define KEY_ESC 27

int startLevel(int lvl,int score,int snakeSize, int* lives, int* isGameOver);

void startMenu();

void menuControl();

int gameControl(int dir,int* isPaused);

void levelControl();

void getInitPos(char** map,int width,int height,int* xpos,int* ypos);

#endif
