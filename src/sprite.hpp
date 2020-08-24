#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include "screen.hpp"

#define LAND_TEXTURES 420
#define BUILDING_NUMBER 33

enum types { MARKET=LAND_TEXTURES, FARM, MINE, CLAY, WOOD, SCHOOL, UNIVERSITY, WINE,
                    OIL, WEAPON, FURNITURE, THEATRE, COLISEUM, SENATE, PREFET,
                    FORT, CASERN, BARBER, DOCTOR, THERME, HOSPITAL, TEMPLE1,
                    TEMPLE2, TEMPLE3, TEMPLE4, TEMPLE5, ORACLE, FISH1, FISH2,
                    FISH3, FISH4, WELL, FOUNTAIN, WAREHOUSE, GRASS, TREE, WATER,
                    ROCK, ROAD, EMPTY  };

class Sprite {
    private:
        int texture_number;
        SDL_Rect pos;
    public:
        int get_num(){ return texture_number; }
        Sprite(int texture_number, int x, int y, int size=1);
        void move(int x, int y, int size=1);
        void blit(Texture *target);
};

void load_all_textures(Screen *s);
void free_all_textures();

#endif
