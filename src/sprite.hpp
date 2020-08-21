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
        Sprite(int texture_number, Screen * s);
        void move(int x, int y){
            this->pos.x = x;
            this->pos.y = y;
        }
        void blit();
};

void load_all_textures(Screen *s);
void free_all_textures();

#endif
