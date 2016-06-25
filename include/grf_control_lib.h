#ifndef GRF_CONTROL_LIB
#	define GRF_CONTROL_LIB

#define KEY_ESC 27

int startLevel(int lvl, int lives, int* isGameOver);

void startMenu();

void menuControl();

int gameControl(int dir,int* isPaused);

#endif
