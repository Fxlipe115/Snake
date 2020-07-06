#ifndef DRAW_H
#define DRAW_H

typedef enum {
    COLOR_BACKGROUND=1, COLOR_SCORE, COLOR_MAP, COLOR_WALL, 
    COLOR_FOOD_EATEN, COLOR_BODY, COLOR_HEAD, COLOR_MOUSE, 
    COLOR_ROCK, COLOR_APPLE, COLOR_LEAF, COLOR_LOGO, COLOR_MENU,
    COLOR_SELECTED_OPTION, COLOR_PLAYER_DATA, COLOR_TEXT
} colors_t;

void draw_initialize(void);

void draw(colors_t color, const char* text, ...);

void draw_at(int x, int y, colors_t color, const char* text, ...);

void set_background_color(colors_t color);

void move_cursor(int x, int y);

void refresh_screen(void);

void clear_screen(void);

#endif
