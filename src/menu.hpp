#ifndef MENU_HPP
#define MENU_HPP

#include "screen.hpp"

class Menu{
    private:
        Texture overlay;
        Texture * position_indicator;
        Screen *s;
    public:
        Menu(Screen *s);
        void blit();
        void update_position_indicator(int i, int j, int num_type);

};

#endif
