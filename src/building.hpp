#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "screen.hpp"
#include "sprite.hpp"
#include "map.hpp"

enum building_types { MARKET, FARM, MINE, CLAY, WOOD, SCHOOL, UNIVERSITY, WINE,
                    OIL, WEAPON, FURNITURE, THEATRE, COLISEUM, SENATE, PREFET,
                    FORT, CASERN, BARBER, DOCTOR, THERME, HOSPITAL, TEMPLE1,
                    TEMPLE2, TEMPLE3, TEMPLE4, TEMPLE5, ORACLE, FISH1, FISH2,
                    FISH3, FISH4, WELL, FOUNTAIN, WAREHOUSE };

int building_size(int type);

/* affichage du sprite */
class Building {
    private:
        int type;
        int i, j;
        Sprite *sprite;
    public:
        Building(int type, int i, int j);
        void blit(Map *m); // TODO: add to map
};

/* habitations */
// input: ressource + accès (rue)
// output: argent
class House : public Building {
    private:

    public:

};

/* bâtiments pourvoyant un service au rue alentour */
// input: argent (entretien)
// output: accès sur les rues
class Service : public Building {
    private:

    public:

};

/* bâtiments produisant des ressources */
// input: none ou autre ressource
// output: ressources
class Production : public Building {
    private:

    public:

};


#endif
