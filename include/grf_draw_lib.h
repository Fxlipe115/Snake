#ifndef GRF_DRAW_LIB
#	define GRF_DRAW_LIB

#include "grf_snake_lib.h"
#include "hsb_mouse_lib.h"
#include "hsb_apple_lib.h"
#include "grf_scores_lib.h"
#include "map.h"

void refreshScreen(snake_t *snake,Mouse *mouse,Apple *apple,map_t map,int lvl,int score,int lives,int miceEaten);

void drawMenu(int option);

void drawPlayerData(Score* player);

void instructionsScreen();

void level_selection_screen(int level, int levels_quantity);

#endif
