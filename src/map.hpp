#ifndef MAP_H
#define MAP_H

#include "screen.hpp"
#include "sprite.hpp"
#include "building.hpp"

#define MAP_SIZE 32
#define TILE_WIDTH 58
#define TILE_HEIGHT 30

#define NO_BUILDING -1

class Map {
    private:
        Sprite *tile_sprites[MAP_SIZE][MAP_SIZE];
        Sprite *building_tile;
        int tile_types[MAP_SIZE][MAP_SIZE];
        // position dans la liste des bâtiments (pour sauvegarde et gestion au clic)
        Building* building_links[MAP_SIZE][MAP_SIZE];
        Texture *big_map;
        Texture *map_overlay;
        Screen *s;
        SDL_Rect visible_area;
        int build_mode;
        int get_water_tile(int i, int j);
        int determine_sprite(int i, int j);
        int get_road_tile(int i, int j);
        int get_empty_tile(int i, int j);
        void set_type(int i, int j, int type);
        void update_sprite(int i, int j);
        void update_sprites(int start_i, int end_i, int start_j, int end_j);
        void add_building(int i, int j);
        void clean(int i, int j);
        void add_road(int i, int j);
        void add_fishery(int i, int j);
    public:
        Map(Screen *s); // require load_all_textures
        Map(Map const &) = delete;
        Map& operator=(Map const &) = delete;
        void update_all_sprites();
        void blit_to_screen();
        ~Map();
        int get_dx(){return this->visible_area.x;}
        int get_dy(){return this->visible_area.y;}
        void translate(int dx, int dy);
        void set_all_types(int new_tile_types[MAP_SIZE][MAP_SIZE]);
        int save(std::string path);
        int load(std::string path);
        void randomize();
        Building* get_building_link(int i, int j);
        void handle_mouse_motion(int i, int j);
        void handle_mouse_click(int i, int j);
        void set_build_mode(int mode) { this->build_mode=mode; this->map_overlay->clear(true); }

};

void localiser(int x, int y, int *i, int *j);
void convertir(int i, int j, int *x, int *y);

#endif
