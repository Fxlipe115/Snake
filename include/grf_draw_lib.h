#ifndef GRF_DRAW_LIB
#	define GRF_DRAW_LIB

#include "game.h"
#include "grf_scores_lib.h"

void refreshScreen(game_t* game);

void drawMenu(int option);

void drawPlayerData(Score* player);

void instructionsScreen();

void level_selection_screen(int level, int levels_quantity);

#endif
