#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include "screen.hpp"

class Sprite {
    private:
        int texture_number;
        SDL_Rect pos;
        Screen *s;
    public:
        int get_num(){ return texture_number; }
        Sprite(int texture_number, Screen *s);
        void move(int x, int y);
        void blit(Texture *target);
};

void load_all_textures(Screen *s);
void free_all_textures();

#endif
