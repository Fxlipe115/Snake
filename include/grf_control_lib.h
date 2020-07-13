#ifndef GRF_CONTROL_LIB
#	define GRF_CONTROL_LIB

#include "level.h"

#define KEY_ESC 27

int startLevel(level_t* level);

void startMenu();

void menuControl();

int levelControl(int dir);

void gameControl();

void getPlayerData(int score);

void chooseLevel();

void instructions();

#endif
