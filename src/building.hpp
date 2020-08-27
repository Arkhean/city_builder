#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "screen.hpp"
#include "sprite.hpp"

enum services {
    MARKET_ACCESS,
    SCHOOL_ACCESS,
    UNIVERSITY_ACCESS,
    THEATRE_ACCESS,
    COLISEUM_ACCESS,
    BARBER_ACCESS,
    DOCTOR_ACCESS,
    THERME_ACCESS,
    HOSPITAL_ACCESS,
    TEMPLE_CERES_ACCESS,
    TEMPLE_MARS_ACCESS,
    TEMPLE_VENUS_ACCESS,
    TEMPLE_MERCURE_ACCESS,
    TEMPLE_NEPTUNE_ACCESS,
    ORACLE_ACCESS,
    WELL_ACCESS,
    FOUNTAIN_ACCESS,
    WAREHOUSE_ACCESS,
    SERVICE_NUMBER };


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
        void has_been_built();
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
void remove_building(Building *b);
void clear_all_buildings();

#endif
