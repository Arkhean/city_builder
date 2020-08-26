#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "screen.hpp"
#include "sprite.hpp"

int tile_size(int type);

/* affichage du sprite */
class Building {
    private:
        int road_access_i;
        int road_access_j;
    public:
        const int type;
        const int i, j;
        const std::string name;
        const int maintenance_cost;
        Building(int type, int i, int j);
};

/* bâtiments pourvoyant un service au rue alentour */
// input: argent (entretien)
// output: accès sur les rues
class Service_building : public Building {
    private:
        const int range;
    public:
        Service_building(int type, int i, int j, int range);
};

/* bâtiments produisant des ressources */
// input: none ou autre ressource
// output: ressources
class Production_building : public Building {
    private:
        int reserve; // 0 - 4
        const int input_resource;
        const int output_resource;
        int progress; // 0 - 100
    public:
        Production_building(int type, int i, int j, int input_resource, int output_resource);

};

/* habitations */
// input: ressource + accès (rue)
// output: argent
class House : public Building {
    private:

    public:

};

/******************************************************************************/
// building management

#include <vector>

Building * create_new_building(int type, int i, int j);
void clear_all_buildings();


#endif
