#ifndef MAP_H
#define MAP_H

#include "screen.hpp"
#include "sprite.hpp"
#include "building.hpp"

#define MAP_SIZE 32
#define TILE_WIDTH 58
#define TILE_HEIGHT 30

class Map {
    private:
        Sprite *tile_sprites[MAP_SIZE][MAP_SIZE];
        int tile_types[MAP_SIZE][MAP_SIZE];
        // position dans la liste des bâtiments (pour sauvegarde et gestion au clic)
        int building_index[MAP_SIZE][MAP_SIZE];
        Texture *big_map;
        Screen *s;
        SDL_Rect visible_area;
        int get_water_tile(int i, int j);
        int determine_sprite(int i, int j);
        int get_road_tile(int i, int j);
        void set_type(int i, int j, int type);
        void update_sprite(int i, int j);
        void update_sprites(int start_i, int end_i, int start_j, int end_j);
    public:
        Map(Screen *s); // require load_all_textures
        Map(Map const &) = delete;
        Map& operator=(Map const &) = delete;
        void update_all_sprites();
        void blit_to_screen();
        void add_to_map(Building *building, int index);
        ~Map();
        int get_dx(){return this->visible_area.x;}
        int get_dy(){return this->visible_area.y;}
        void translate(int dx, int dy);
        void set_all_types(int new_tile_types[MAP_SIZE][MAP_SIZE]);
        int save(std::string path);
        int load(std::string path);
        void randomize();
        int get_building_index(int i, int j){ return this->building_index[i][j]; }
        void add_road(int i, int j);
};

void localiser(int x, int y, int *i, int *j);
void convertir(int i, int j, int *x, int *y);

#endif
