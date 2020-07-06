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

    draw_at(1, 0, COLOR_LOGO, "         ---_ ...... _/_ -      ");
    draw_at(2, 0, COLOR_LOGO, "        /  .      ./ .\'*\\ \\     ");
    draw_at(3, 0, COLOR_LOGO, "        : \'         /__-\'   \\.  ");
    draw_at(4, 0, COLOR_LOGO, "       /                      ) ");
    draw_at(5, 0, COLOR_LOGO, "     _/                  >   .\' ");
    draw_at(6, 0, COLOR_LOGO, "   /   .   .       _.-\" /  .\'   ");
    draw_at(7, 0, COLOR_LOGO, "   \\           __/\"     /.\'/|   ");
    draw_at(8, 0, COLOR_LOGO, "     \\ \'--  .-\" /     //\' |\\|   ");
    draw_at(9, 0, COLOR_LOGO, "      \\|  \\ | /     //_ _ |/|   ");
    draw_at(10, 0, COLOR_LOGO, "       `.  \\:     //|_ _ _|\\|   ");
    draw_at(11, 0, COLOR_LOGO, "       | \\/.    //  | _ _ |/|   ");
    draw_at(12, 0, COLOR_LOGO, "        \\_ | \\/ /    \\ _ _ \\\\\\  ");
    draw_at(13, 0, COLOR_LOGO, "            \\__/      \\ _ _ \\|\\ ");

    //Prints the menu options with the current one highlighted
    for(int i = 0; i < 5; i++){
        if(option == i){
            draw_at(i+3, 36, COLOR_SELECTED_OPTION, "-%s", options[i]);
        }else{
            draw_at(i+3, 36, COLOR_TEXT, " %s\n", options[i]);
        }
    }

    move_cursor(14,0);

    refresh_screen();
}

//Screen for asking the player's name before evaluating his score
void drawPlayerData(WINDOW* window, int score){
    // TODO: wrap this in an input module
    echo();
    
    draw_initialize();
    set_background_color(COLOR_PLAYER_DATA);

    draw_at(2,8, COLOR_PLAYER_DATA, "Game Over!");
    draw_at(5,5, COLOR_PLAYER_DATA, "Your score: %03d",score);
    draw_at(7,5, COLOR_PLAYER_DATA, "Your name:  ");

    refresh_screen();
}

//Instructions screen
void instructionsScreen(){
    draw_initialize();
    set_background_color(COLOR_BACKGROUND);

    draw_at(0, 0, COLOR_TEXT, "-----------INSTRUCTIONS-----------");
    draw_at(1, 0, COLOR_TEXT, "**********************************");
    draw_at(2, 0, COLOR_TEXT, "* W,A,S,D or arrow keys to move. *");
    draw_at(3, 0, COLOR_TEXT, "*                                *");
    draw_at(4, 0, COLOR_TEXT, "* P to pause.                    *");
    draw_at(5, 0, COLOR_TEXT, "*                                *");
    draw_at(6, 0, COLOR_TEXT, "* ESC or Q to quit game.         *");
    draw_at(7, 0, COLOR_TEXT, "**********************************");

    draw_at(10, 2, COLOR_TEXT, "Press any key to exit.");

    refresh_screen();

    // TODO: wrap this in an input module
    int k;
    do{
        k = getch();
    }while(k == ERR);
}
