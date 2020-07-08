#include "draw.h"

#include <curses.h>
#include <stdarg.h>

void draw_initialize(void){
    if(stdscr == NULL){
        initscr();
    }
    start_color();
    init_pair(COLOR_BACKGROUND, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(COLOR_SCORE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_MAP, COLOR_WHITE, COLOR_WHITE);
    init_pair(COLOR_WALL, COLOR_BLACK, COLOR_BLACK);
    init_pair(COLOR_FOOD_EATEN, COLOR_BLACK, COLOR_GREEN);
    init_pair(COLOR_BODY, COLOR_GREEN, COLOR_GREEN);
    init_pair(COLOR_HEAD, COLOR_BLACK, COLOR_GREEN);
    init_pair(COLOR_MOUSE, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_ROCK, COLOR_RED, COLOR_WHITE);
    init_pair(COLOR_APPLE, COLOR_RED, COLOR_WHITE);
    init_pair(COLOR_LEAF, COLOR_GREEN, COLOR_WHITE);
    init_pair(COLOR_LOGO, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_MENU, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_SELECTED_OPTION, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_PLAYER_DATA, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(COLOR_TEXT, COLOR_WHITE, COLOR_BLACK);
}

void end_draw(void){
    endwin();
}

void draw(colors_t color, const char* text, ...){
    va_list args;
    va_start(args, text);
    attron(COLOR_PAIR(color));
    vw_printw(stdscr, text, args);
    attroff(COLOR_PAIR(color));
    va_end(args);
}

void draw_at(int x, int y, colors_t color, const char* text, ...){
    va_list args;
    va_start(args, text);
    attron(COLOR_PAIR(color));
    move(x, y);
    vw_printw(stdscr, text, args);
    attroff(COLOR_PAIR(color));
    va_end(args);
}

void set_background_color(colors_t color){
    bkgd(COLOR_PAIR(color));
}

void move_cursor(int x, int y){
    move(x, y);
}

void refresh_screen(void){
    refresh();
}

void clear_screen(void){
    clear();
}
