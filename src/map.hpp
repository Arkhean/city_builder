#ifndef MAP_H
#define MAP_H

#include "screen.hpp"
#include "sprite.hpp"

#define MAP_SIZE 64
#define TILE_WIDTH 58
#define TILE_HEIGHT 30
enum land_types { GRASS, TREE, WATER, ROCK };

class Map {
    private:
        Sprite *tiles[MAP_SIZE][MAP_SIZE];
        int num[MAP_SIZE][MAP_SIZE];
        Texture *big_map;
        Screen *s;
        SDL_Rect visible_area;
        int get_water_tile(int i, int j);
        int determine_sprite(int n, int i, int j);
    public:
        Map(Screen *s); // require load_all_textures
        Map(Map const &) = delete;
        Map& operator=(Map const &) = delete;
        void blit();
        void blit_on_map(Sprite *sprite);
        ~Map();
        int get_dx(){return this->visible_area.x;}
        int get_dy(){return this->visible_area.y;}
        void translate(int dx, int dy);
        void load_tiles(int new_num[MAP_SIZE][MAP_SIZE]);
        int save(std::string path);
        int load(std::string path);
        void randomize();
};

void localiser(int x, int y, int *i, int *j);
void convertir(int i, int j, int *x, int *y);

#endif
