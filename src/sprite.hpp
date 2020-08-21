#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include "screen.hpp"

class Sprite {
    private:
        int texture_number;
        SDL_Rect pos;
    public:
        Sprite(int texture_number);
        void move(int x, int y);
        void blit(Texture *target);
};

void load_all_textures(Screen *s);
void free_all_textures();

#endif
