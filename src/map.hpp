#ifndef map__H
#define map__H

#include "screen.hpp"
#include "sprite.hpp"
#include "building.hpp"
#include "cursor.hpp"

#define MAP_SIZE 32
#define TILE_WIDTH 58
#define HALF_TILE_WIDTH 30
#define TILE_HEIGHT 30
#define HALF_TILE_HEIGHT 15

#define NO_BUILDING -1 // pas de constuction en cours


void map__localiser(int x, int y, int *i, int *j);
void map__convertir(int i, int j, int *x, int *y);
void map__init_map(Screen *s); // require load_all_textures
void map__update_all_sprites();
void map__blit_to_screen();
void map__free_map();
int map__get_dx();
int map__get_dy();
void map__translate(int dx, int dy);
int map__save(std::string path);
int map__load(std::string path);
void map__randomize();
Building* map__get_building_link(int i, int j);
void map__handle_mouse_motion(int i, int j);
void map__handle_mouse_click(int i, int j);
void map__set_build_mode(int mode);
bool map__is_accessible(int i, int j);
bool map__is_road(int i, int j);



#endif
