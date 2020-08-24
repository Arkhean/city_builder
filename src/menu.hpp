#ifndef MENU_HPP
#define MENU_HPP

#include "screen.hpp"

enum states { NORMAL, OVER, CLICKED, DISABLED };

// use texture from paneling

class Button_menu {
    private:
        SDL_Rect cadre; // position du bouton
        // numero des textures à utiliser (+1 pour survolé, +2 pour cliqué)
        int texture_num;
        int state; // normal, survolé, cliqué
    public:
        Button_menu(int x, int y, int texture_num);
        bool is_inside(int x, int y);
        void blit(Texture *target);
};


// ne doit être instancié qu'une seule fois
class Menu{
    private:
        Texture overlay;
        Texture * position_indicator;
        Texture * right_bar;
        Screen *s;
        Button_menu *buttons[12];
    public:
        Menu(Screen *s);
        ~Menu();
        void blit();
        void update_position_indicator(int i, int j, int num_type);

};

#endif
