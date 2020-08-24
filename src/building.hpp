#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "screen.hpp"
#include "sprite.hpp"

int building_size(int type);

/* affichage du sprite */
class Building {
    public:
        const int type;
        const int i, j;
        Building(int type, int i, int j);
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
