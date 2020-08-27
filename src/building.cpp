#include "building.hpp"

int tile_size(int type){
    switch (type) {
        case WELL:
        case FOUNTAIN:
        case DOCTOR:
        case BARBER:
        case PREFET:
        case GRASS:
        case WATER:
        case ROCK:
        case TREE:
        case ROAD:
        case WHEAT_FIELD:
        case VEGETABLE_FIELD:
        case OLIVE_GROVE:
        case ORCHARD:
        case VINE:
        case CATTLE_PEN:
            return 1;
        case UNIVERSITY:
        case CASERN:
        case HOSPITAL:
        case WAREHOUSE:
        case FORT:
            return 3;
        case COLISEUM:
        case SENATE:
            return 5;
        default:
            return 2;
    }
}

int maintenance_costs[] = { 100,100,100,100,100,100,100,100,100,100,100,100,100,
                100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
            100,100,100,100,100 };

Building::Building(int type, int i, int j)
        : type(type), i(i), j(j), name(names[type-LAND_NUMBER]),
        maintenance_cost(maintenance_costs[type-LAND_NUMBER]) {}

void Building::has_been_built(){
    // après la construction, il faut mettre à jour les routes
    int size = tile_size(this->type);

}

Service_building::Service_building(int type, int i, int j, int range)
        : Building(type, i, j), range(range) {}

/******************************************************************************/
// building management

std::vector<Building*> all_buildings;

Building * create_new_building(int type, int i, int j){
    Building * b = new Building(type, i, j);
    all_buildings.push_back(b);
    return b;
}

void remove_building(Building *b){
    size_t index = 0;
    for(size_t i = 0; i < all_buildings.size(); i++){
        if (all_buildings[i] == b){
            index = i;
            break;
        }
    }
    all_buildings.erase(all_buildings.begin()+index);
}

void clear_all_buildings(){
    for(Building *b : all_buildings){
        delete b;
    }
}
