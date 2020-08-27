#ifndef CURSOR_HPP
#define CURSOR_HPP

typedef enum {
    CURSOR_ARROW = 0,
    CURSOR_SHOVEL = 1,
    CURSOR_SWORD = 2,
    CURSOR_MAX,
} cursor_shape;

void init_cursors();
void system_set_cursor(int cursor_id);


#endif
