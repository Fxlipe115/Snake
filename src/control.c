#include "control.h"

#include <curses.h>
#include <stdarg.h>
#include <ctype.h>

#define KEY_ESC 27

void set_blocking(void);
void set_non_blocking(void);
control_key_t to_key_t(int key_code);

void initialize_controls(void){
    if(stdscr == NULL){
        initscr();
    }
}

void end_controls(void){
    endwin();
}

void get_formatted(char* fmt, ...){
    echo();
    va_list args;
    va_start(args, fmt);
    vw_scanw(stdscr, fmt, args);
    va_end(args);
}

void get_formatted_silent(char* fmt, ...){
    noecho();
    va_list args;
    va_start(args, fmt);
    vw_scanw(stdscr, fmt, args);
    va_end(args);
}

void wait_for_key_press(void){
    int k;
    do{
        k = getch();
    }while(k == ERR);
}

control_key_t get_key(void){
    set_blocking();

    int pressed_key = getch();

    return to_key_t(pressed_key);
}

control_key_t get_key_non_blocking(void){
    set_non_blocking();
    
    int pressed_key = getch();

    return to_key_t(pressed_key);
}

void set_blocking(void){
    nodelay(stdscr, FALSE);
    keypad(stdscr, TRUE);
    noecho();
}

void set_non_blocking(void){
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    noecho();
}

control_key_t to_key_t(int key_code){
    control_key_t key;
    switch(toupper(key_code)){
        case 'W':
        case KEY_UP:
            key = K_UP;
            break;
        case 'S':
        case KEY_DOWN:
            key = K_DOWN;
            break;
        case 'A':
        case KEY_LEFT:
            key = K_LEFT;
            break;
        case 'D':
        case KEY_RIGHT:
            key = K_RIGHT;
            break;
        case 'P':
            key = K_PAUSE;
            break;
        case '\n':
            key = K_ENTER;
            break;
        case KEY_ESC:
            key = K_ESC;
            break;
        case 'Q':
            key = K_QUIT;
            break;
        case ERR:
            key = K_ERR;
            break;
    }
    return key;
}
