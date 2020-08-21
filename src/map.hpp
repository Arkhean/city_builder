#ifndef MAP_H
#define MAP_H

#include "screen.hpp"
#include "sprite.hpp"

#define MAP_SIZE 128

class Map {
    private:
        Sprite *tiles[MAP_SIZE][MAP_SIZE];
        Screen *s;
    public:
        Map(Screen *s); // require load_all_textures
        void blit();
};

#endif
