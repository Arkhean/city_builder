#ifndef MAP_H
#define MAP_H

#include "screen.hpp"
#include "sprite.hpp"

#define MAP_SIZE 16
#define TILE_WIDTH 58
#define TILE_HEIGHT 30

class Map {
    private:
        Sprite *tiles[MAP_SIZE][MAP_SIZE];
        Texture *big_map;
        Screen *s;
        SDL_Rect visible_area;
    public:
        Map(Screen *s); // require load_all_textures
        Map(Map const &) = delete;
        Map& operator=(Map const &) = delete;
        void blit();
        ~Map();
        void translate(int dx, int dy);
        void load_tiles(Screen *s, char num[MAP_SIZE][MAP_SIZE]);
        int save(std::string path);
        int load(std::string path);
};

#endif
