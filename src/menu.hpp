#ifndef MENU_HPP
#define MENU_HPP

#include "screen.hpp"

enum states { NORMAL, OVER, CLICKED, DISABLED };
#define NB_BUTTONS 12
#define SHIFT_MENU 1540

// use texture from paneling

class Button {
    protected:
        int state; // normal, survolé, cliqué
    public:
        Button() : state(NORMAL){};
        virtual ~Button() {}
        void set_state(int state){ this->state = state; }
        virtual bool is_inside(int x, int y) const =0;
        virtual void blit(Texture *target) const =0;
};


class Button_menu : public Button {
    private:
        SDL_Rect cadre; // position du bouton
        // numero des textures à utiliser (+1 pour survolé, +2 pour cliqué)
        int texture_num;
    public:
        Button_menu(int x, int y, int texture_num);
        virtual ~Button_menu() {}
        bool is_inside(int x, int y) const;
        void blit(Texture *target) const;
};

class Button_text : public Button {
    private:
        SDL_Rect cadre; // position du bouton
        SDL_Rect cadre_text;
        Texture * texture_text;
    public:
        Button_text(int x, int y, std::string text, Screen *s);
        virtual ~Button_text() {}
        bool is_inside(int x, int y) const;
        void blit(Texture *target) const;
};

/******************************************************************************/

// ne doit être instancié qu'une seule fois
class Menu{
    private:
        Texture overlay;
        Texture * position_indicator;
        Texture * right_bar;
        Screen *s;
        Button_menu *buttons[NB_BUTTONS];
        Texture * fps_indicator;
        Button_text *test;
    public:
        Menu(Screen *s);
        ~Menu();
        void blit();
        void set_fps(float avgFPS);
        void update_position_indicator(int i, int j, int num_type);
        void mouse_motion(int x, int y);
        void mouse_click(int x, int y);
};

#endif
