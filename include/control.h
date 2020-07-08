#ifndef CONTROL_H
#define CONTROL_H

typedef enum {
    K_UP, K_DOWN, K_LEFT, K_RIGHT, K_ENTER, K_PAUSE, K_ESC, K_QUIT, 
    K_ERR = -1
} key_t;

void get_formatted(char* fmt, ...);

void get_formatted_silent(char* fmt, ...);

void wait_for_key_press(void);

key_t get_key(void);

key_t get_key_non_blocking(void);

#endif
