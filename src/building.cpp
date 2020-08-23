#include "building.hpp"

int building_size(int type){
    switch (type) {
        case WELL:
        case FOUNTAIN:
        case DOCTOR:
        case BARBER:
        case PREFET:
            return 1;
        case UNIVERSITY:
        case CASERN:
        case HOSPITAL:
        case WAREHOUSE:
            return 3;
        case COLISEUM:
        case SENATE:
            return 4;
        default:
            return 2;
    }
}

Building::Building(int type, int i, int j)
                    : type(type), i(i), j(j) {
    this->sprite = new Sprite(LAND_TEXTURES+type);
    int x, y;
    convertir(i, j, &x, &y);
    this->sprite->move(x, y);
}

void Building::blit(Map *m){
    m->blit_on_map(sprite);
}
