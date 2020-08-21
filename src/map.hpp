#ifndef MAP_H
#define MAP_H

#include "screen.hpp"
#include "sprite.hpp"

#define MAP_SIZE 32
#define TILE_WIDTH 58
#define TILE_HEIGHT 30

class Map {
    private:
        Sprite *tiles[MAP_SIZE][MAP_SIZE];
        Texture *big_map;
        Screen *s;
    public:
        Map(Screen *s); // require load_all_textures
        void blit();
        ~Map();
};

#endif
