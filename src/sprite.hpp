#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include "screen.hpp"

#define LAND_NUMBER 420
#define BUILDING_NUMBER 142
#define HOUSE_NUMBER 12

enum types { MARKET=LAND_NUMBER,
            FARM, MINE, CLAY, WOOD, SCHOOL,
            UNIVERSITY, WINE, OIL, WEAPON,
            FURNITURE, THEATRE, COLISEUM, SENATE,
            PREFET, FORT, CASERN, BARBER,
            DOCTOR, THERME, HOSPITAL,
            TEMPLE_CERES, TEMPLE_NEPTUNE,
            TEMPLE_MERCURE, TEMPLE_MARS, TEMPLE_VENUS,
            ORACLE, FISH1, FISH2,
            FISH3, FISH4, WELL, FOUNTAIN, POTERY,
            WHEAT_FIELD,
            VEGETABLE_FIELD=WHEAT_FIELD+5,
            ORCHARD=VEGETABLE_FIELD+5,
            OLIVE_GROVE=ORCHARD+5,
            VINE=OLIVE_GROVE+5,
            CATTLE_PEN=VINE+5,
            HOUSE=CATTLE_PEN+5,
            WAREHOUSE,
            GRASS, TREE, WATER, ROCK, ROAD, EMPTY,
};

extern std::string names[72];

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
