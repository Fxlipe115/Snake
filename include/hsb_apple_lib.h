#ifndef HSB_APPLE_LIB
#	define HSB_APPLE_LIB

#include <stdbool.h>

#include "position.h"

typedef struct apple {
	position_t position;
} apple_t;

apple_t* new_apple(position_t position);

void destroy_apple(apple_t* apple);

bool is_apple_at(apple_t* apple, position_t position);

#endif
