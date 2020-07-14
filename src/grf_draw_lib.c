#include "grf_draw_lib.h"

#include <stdlib.h>

#include "draw.h"

//Prints screen with all elements given in it
void refreshScreen(game_t* game){
    level_t* current_level = game->current_level;
    map_t* map = current_level->map;
    snake_t* snake = current_level->snake;
    mouse_list_t* mouse_list = current_level->mouse_list;
    Apple* apple = current_level->apple;
    int level_number = current_level->number;
    int total_score = game->score + current_level->score;
    int lives = game->lives;
    int mice_eaten = current_level->snake->mice_eaten;

    draw_initialize();
    move_cursor(0,0);

    set_background_color(COLOR_BACKGROUND);

    draw(COLOR_SCORE, "Level: %d | Score: %03d | Lives: %d | \
            ~>: %0d/10\n", level_number+1, total_score, lives, mice_eaten);

    for(int y = 0; y < map->size.height; y++){
        for(int x = 0; x < map->size.width; x++){
            position_t current_position = {x, y};
            if(is_wall_at(current_position, map)){
                draw(COLOR_WALL, "  ");
            }else if(is_snake_head_at(snake, current_position)){
                draw(COLOR_HEAD, "00");
            }else if(has_food_at(snake, current_position)){
                draw(COLOR_FOOD_EATEN, "()");
            }else if(is_snake_at(snake, current_position)){
                draw(COLOR_BODY, "  ");
            }else if(is_mouse_at(current_position, mouse_list)){
                draw(COLOR_MOUSE, "~>");
            }else if(isApple(apple,x,y)){
                draw(COLOR_LEAF, "~");
                draw(COLOR_APPLE, "@");
            }else if(is_rock_at(current_position, map)){
                draw(COLOR_ROCK, "{}");
            }else{
                draw(COLOR_MAP, "  ");
            }
        }
        draw(COLOR_BACKGROUND, "\n");
    }


    refresh_screen();
}

void drawMenu(int option){
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
void drawPlayerData(Score* player){
    draw_initialize();
    set_background_color(COLOR_PLAYER_DATA);

    draw_at(2,8, COLOR_PLAYER_DATA, "Game Over!");
    draw_at(5,5, COLOR_PLAYER_DATA, "Your score: %03d", player->score);
    draw_at(7,5, COLOR_PLAYER_DATA, "Your name:  ");
    refresh_screen();

    get_formatted("%s", player->name);
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
}

void level_selection_screen(int level, int levels_quantity){
    set_background_color(COLOR_MENU);
    move_cursor(0, 0);
    for(int i = 0; i < levels_quantity; i++){
        if(level == i){
            draw(COLOR_SELECTED_OPTION, "-LEVEL %d\n", i+1);
        }else{
            draw(COLOR_MENU, " LEVEL %d\n", i+1);
        }
    }
    draw(COLOR_MENU, "\nPress ESC to exit");
    
    refresh_screen();
}