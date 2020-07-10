#ifndef GRF_DRAW_LIB
#	define GRF_DRAW_LIB

#include "grf_snake_lib.h"
#include "hsb_mouse_lib.h"
#include "hsb_apple_lib.h"
#include "grf_scores_lib.h"

void refreshScreen(Snake *snake,Mouse *mouse,Apple *apple,char **map,int matrixSize,int matrixySize,int lvl,int score,int lives,int miceEaten);

void drawMenu(int option);

void drawPlayerData(Score* player);

void instructionsScreen();

void level_selection_screen(int level, int levels_quantity);

#endif
