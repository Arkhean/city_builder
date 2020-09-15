#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include "screen.hpp"

int init_soldier_textures();
int free_soldier_textures();


class Soldier {
    private:
        int i;
        int j;
        int pv;
        SDL_Rect position_on_screen;
        int current_image;
    public:
        Soldier(int i, int j, int type);
        void update();
        void set_orientation();
        void new_destination(int dest_i, int dest_j);

};


#endif
