#ifndef GRF_DRAW_LIB
#	define GRF_DRAW_LIB

char** loadMap(char* filename,int *width,int *height);

void destroyMap(char** map,int height);

void refreshScreen(WINDOW *window,Snake *snake,char **map,int matrixSize,int matrixySize);

#endif
