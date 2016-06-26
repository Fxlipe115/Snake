#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

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
	start_color();

	init_pair(1,COLOR_MAGENTA,COLOR_MAGENTA);//background
	init_pair(2,COLOR_WHITE,COLOR_BLACK);//score

	if(matrixySize==27){
		init_pair(3,COLOR_BLACK,COLOR_BLACK);
		init_pair(4,COLOR_BLUE,COLOR_BLUE);
		init_pair(5,COLOR_BLACK,COLOR_BLACK);
		init_pair(6,COLOR_BLACK,COLOR_BLACK);
		init_pair(7,COLOR_BLACK,COLOR_YELLOW);
		init_pair(8,COLOR_YELLOW,COLOR_BLACK);
		init_pair(9,COLOR_RED,COLOR_BLACK);
		init_pair(10,COLOR_GREEN,COLOR_BLACK);
	}else{
		init_pair(3,COLOR_WHITE,COLOR_WHITE);//map
		init_pair(4,COLOR_BLACK,COLOR_BLACK);//wall
		init_pair(5,COLOR_BLACK,COLOR_GREEN);//food eaten
		init_pair(6,COLOR_GREEN,COLOR_GREEN);//body
		init_pair(7,COLOR_BLACK,COLOR_GREEN);//head
		init_pair(8,COLOR_BLACK,COLOR_WHITE);//mouse
		init_pair(9,COLOR_RED,COLOR_WHITE);//rock/apple
		init_pair(10,COLOR_GREEN,COLOR_WHITE);//apple leaf
	}

	wmove(window,0,0);

	wbkgd(window,COLOR_PAIR(1));	

	wattron(window,COLOR_PAIR(2));
	wprintw(window,"Level: %d | Score: %03d | Lives: %d | ~>: %0d/10\n",lvl+1,score,lives,miceEaten);
	wattroff(window,COLOR_PAIR(2));

	for(int y = 0; y<matrixySize; y++){
		for(int x = 0; x<matrixSize; x++){
			if(map[y][x] == '#'){
				//wall
				wattron(window,COLOR_PAIR(4));
				wprintw(window,"  ");
				wattroff(window,COLOR_PAIR(4));
			}else if(snake->y == y && snake->x == x){
				//head
				wattron(window,COLOR_PAIR(7)|A_BOLD);
				wprintw(window,"00");
				wattroff(window,COLOR_PAIR(7)|A_BOLD);
			}else if(hasFood(snake,x,y)){
				//food eaten
				wattron(window,COLOR_PAIR(5));
				wprintw(window,"()");
				wattroff(window,COLOR_PAIR(5));
			}else if(isSnake(snake,x,y)){
				//body
				wattron(window,COLOR_PAIR(6));
				wprintw(window,"  ");
				wattroff(window,COLOR_PAIR(6));
			}else if(isMouse(mouse,x,y)){
				//mouse
				wattron(window,COLOR_PAIR(8)|A_BOLD);
				wprintw(window,"~>");
				wattroff(window,COLOR_PAIR(8)|A_BOLD);
			}else if(isApple(apple,x,y)){
				//apple
				wattron(window,COLOR_PAIR(10));
				wprintw(window,"~");
				wattroff(window,COLOR_PAIR(10));
				wattron(window,COLOR_PAIR(9));
				wprintw(window,"@");
				wattroff(window,COLOR_PAIR(9));
			}else if(map[y][x] == '*'){
				//rocks
				wattron(window,COLOR_PAIR(9));
				wprintw(window,"{}");
				wattroff(window,COLOR_PAIR(9));
			}else{
				//map background
				wattron(window,COLOR_PAIR(3));
				wprintw(window,"  ");
				wattroff(window,COLOR_PAIR(3));
			}
		}
		wprintw(window,"\n");
	}
	
	
	wrefresh(window);
}

void drawMenu(WINDOW* menu,int option){
	char* options[] = {"Start Game","Select Level","Highscores","Instructions","Quit"};

	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_GREEN,COLOR_BLACK);
	wbkgd(menu,COLOR_PAIR(1));
	
	wmove(menu,0,0);

	wattron(menu,COLOR_PAIR(2));

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

	mvwprintw(menu,1,0,"         ---_ ...... _/_ -      ");
	mvwprintw(menu,2,0,"        /  .      ./ .\'*\\ \\     ");
	mvwprintw(menu,3,0,"        : \'         /__-\'   \\.  ");
	mvwprintw(menu,4,0,"       /                      ) ");
	mvwprintw(menu,5,0,"     _/                  >   .\' ");
	mvwprintw(menu,6,0,"   /   .   .       _.-\" /  .\'   ");
	mvwprintw(menu,7,0,"   \\           __/\"     /.\'/|   ");
	mvwprintw(menu,8,0,"     \\ \'--  .-\" /     //\' |\\|   ");
	mvwprintw(menu,9,0,"      \\|  \\ | /     //_ _ |/|   ");
	mvwprintw(menu,10,0,"       `.  \\:     //|_ _ _|\\|   ");
	mvwprintw(menu,11,0,"       | \\/.    //  | _ _ |/|   ");
	mvwprintw(menu,12,0,"        \\_ | \\/ /    \\ _ _ \\\\\\  ");
	mvwprintw(menu,13,0,"            \\__/      \\ _ _ \\|\\ ");

	wattroff(menu,COLOR_PAIR(2));

	//Prints the menu options with the current one highlighted
	for(int i = 0; i < 5; i++){
		if(option == i){
			wattron(menu,A_REVERSE);
			mvwprintw(menu,i+3,36,"-%s",options[i]);
			wattroff(menu,A_REVERSE);
		}else{
			mvwprintw(menu,i+3,36," %s\n",options[i]);
		}
	}

	wmove(menu,14,0);
	
	wrefresh(menu);
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
