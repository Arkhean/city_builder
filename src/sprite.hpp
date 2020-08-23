#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include "screen.hpp"

#define LAND_TEXTURES 421
#define BUILDING_NUMBER 33

class Sprite {
    private:
        int texture_number;
        SDL_Rect pos;
    public:
        int get_num(){ return texture_number; }
        Sprite(int texture_number);
        void move(int x, int y, int size=1);
        void blit(Texture *target);
};

void load_all_textures(Screen *s);
void free_all_textures();

#endif
