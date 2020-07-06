#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

#include "draw.h"
#include "grf_snake_lib.h"
#include "hsb_mouse_lib.h"
#include "hsb_apple_lib.h"

//Loads map from file "filename" and returns it as a matrix of chars and returns by reference its width and height
char** loadMap(char* filename,int* width,int* height){

	FILE *mapfile = fopen(filename,"r");
	char **mapa;

	if(mapfile != NULL){
		fscanf(mapfile,"%d",height);
		fscanf(mapfile,"%d",width);
		fseek(mapfile,1,SEEK_CUR);

		//Aloca a matriz que armazena o mapa
		char **map = (char**)malloc(*height * sizeof(char*));
		for(int i = 0; i < *height; i++){
			map[i] = malloc((*width+2) * sizeof(char));
		}

		for(int i = 0;i<*height;i++){
			fgets(map[i],*width+2,mapfile);
		}
		
		mapa = map;
		fclose(mapfile);
	}

	return mapa;
}

//Frees the memory associated with the map matrix
void destroyMap(char** map,int height){
	for(int i = 0; i<height; i++){
		free(map[i]);
	}
	free(map);
}

//Prints screen with all elements given in it
void refreshScreen(WINDOW *window,Snake *snake,Mouse *mouse,Apple *apple,char **map,int matrixSize,int matrixySize,int lvl,int score,int lives,int miceEaten){
    draw_initialize();
	move_cursor(0,0);
		
    set_background_color(COLOR_BACKGROUND);

    draw(COLOR_SCORE, "Level: %d | Score: %03d | Lives: %d | \
            ~>: %0d/10\n", lvl+1, score, lives, miceEaten);

	for(int y = 0; y<matrixySize; y++){
		for(int x = 0; x<matrixSize; x++){
			if(map[y][x] == '#'){
                draw(COLOR_WALL, "  ");
			}else if(snake->y == y && snake->x == x){
                draw(COLOR_HEAD, "00");
			}else if(hasFood(snake,x,y)){
                draw(COLOR_FOOD_EATEN, "()");
			}else if(isSnake(snake,x,y)){
                draw(COLOR_BODY, "  ");
			}else if(isMouse(mouse,x,y)){
                draw(COLOR_MOUSE, "~>");
			}else if(isApple(apple,x,y)){
                draw(COLOR_LEAF, "~");
                draw(COLOR_APPLE, "@");
			}else if(map[y][x] == '*'){
                draw(COLOR_ROCK, "{}");
			}else{
                draw(COLOR_MAP, "  ");
			}
		}
		draw(COLOR_BACKGROUND, "\n");
	}
	
	
	refresh_screen();
}

void drawMenu(WINDOW* menu,int option){
	char* options[] = {"Start Game","Select Level","Highscores","Instructions","Quit"};
    draw_initialize();
    set_background_color(COLOR_MENU);
	move_cursor(0,0);

	//Prints the following ascii art with all the escape sequences
	/*           ---_ ...... _/_ -    
	            /  .      ./ .'*\ \
	            : '         /__-'   \. 
	           /                      )
	         _/                  >   .' 
	       /   .   .       _.-" /  .'   
	       \           __/"     /.'/|   
	        \ '--  .-" /     //' |\|  
	          \|  \ | /     //_ _ |/|
	           `.  \:     //|_ _ _|\|
	           | \/.    //  | _ _ |/|
	            \_ | \/ /    \ _ _ \\\
	                \__/      \ _ _ \|\  */

    draw_at(COLOR_LOGO, 1, 0, "         ---_ ...... _/_ -      ");
	draw_at(COLOR_LOGO, 2, 0, "        /  .      ./ .\'*\\ \\     ");
	draw_at(COLOR_LOGO, 3, 0, "        : \'         /__-\'   \\.  ");
	draw_at(COLOR_LOGO, 4, 0, "       /                      ) ");
	draw_at(COLOR_LOGO, 5, 0, "     _/                  >   .\' ");
	draw_at(COLOR_LOGO, 6, 0, "   /   .   .       _.-\" /  .\'   ");
	draw_at(COLOR_LOGO, 7, 0, "   \\           __/\"     /.\'/|   ");
	draw_at(COLOR_LOGO, 8, 0, "     \\ \'--  .-\" /     //\' |\\|   ");
	draw_at(COLOR_LOGO, 9, 0, "      \\|  \\ | /     //_ _ |/|   ");
	draw_at(COLOR_LOGO, 10, 0, "       `.  \\:     //|_ _ _|\\|   ");
	draw_at(COLOR_LOGO, 11, 0, "       | \\/.    //  | _ _ |/|   ");
	draw_at(COLOR_LOGO, 12, 0, "        \\_ | \\/ /    \\ _ _ \\\\\\  ");
	draw_at(COLOR_LOGO, 13, 0, "            \\__/      \\ _ _ \\|\\ ");

	//Prints the menu options with the current one highlighted
	for(int i = 0; i < 5; i++){
		if(option == i){
			draw_at(COLOR_SELECTED_OPTION, i+3, 36, "-%s", options[i]);
		}else{
			draw_at(COLOR_MENU, i+3, 36, " %s\n", options[i]);
		}
	}

	move_cursor(14,0);
	
	refresh_screen();
}

//Screen for asking the player's name before evaluating his score
void drawPlayerData(WINDOW* window, int score){
	echo();
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_MAGENTA);
	wbkgd(window,COLOR_PAIR(1));

	mvwprintw(window,2,8,"Game Over!");
	mvwprintw(window,5,5,"Your score: %03d",score);
	mvwprintw(window,7,5,"Your name:  ");

	wrefresh(window);
}

//Instructions screen
void instructionsScreen(){
	WINDOW* window = newwin(0,0,0,0);

	start_color();
	init_pair(1,COLOR_BLACK,COLOR_BLUE);//bkgd
	init_pair(2,COLOR_WHITE,COLOR_BLACK);//text
	wbkgd(window,COLOR_PAIR(1));

	wmove(window,0,0);

	wattron(window,COLOR_PAIR(2));

	mvwprintw(window,0,0,"-----------INSTRUCTIONS-----------");
	mvwprintw(window,1,0,"**********************************");
	mvwprintw(window,2,0,"* W,A,S,D or arrow keys to move. *");
	mvwprintw(window,3,0,"*                                *");
	mvwprintw(window,4,0,"* P to pause.                    *");
	mvwprintw(window,5,0,"*                                *");
	mvwprintw(window,6,0,"* ESC or Q to quit game.         *");
	mvwprintw(window,7,0,"**********************************");

	mvwprintw(window,10,2,"Press any key to exit.");

	wattroff(window,COLOR_PAIR(2));

	wrefresh(window);

	int k;
	do{
		k = getch();
	}while(k == ERR);
}
