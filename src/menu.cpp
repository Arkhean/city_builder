#include <iostream>

#include "menu.hpp"


#define PANEL_NUMBER 163

Texture *panelings[PANEL_NUMBER];

Menu::Menu(Screen *s) : overlay(s, 1600, 900), s(s){
    position_indicator = new Texture(s, "(0,0)");
    SDL_Color gray = {100, 100, 100, 100};
    right_bar = new Texture(s, 60, 900);

    /* charger toutes les textures des boutons */
    char path[] = "data/paneling/paneling_001.png";
    for(int i = 0; i < PANEL_NUMBER; i++){
        // changer le numéro de fin, padding...
        int n = i + 1;
        if (n < 10){
            path[25] = '0' + n;
        }
        else if (n < 10){
            path[24] = '0' + (n / 10);
            path[25] = '0' + (n % 10);
        }
        else {
            path[23] = '0' + (n / 100);
            path[24] = '0' + ((n / 10) % 10);
            path[25] = '0' + (n % 10);
        }
        panelings[i] = new Texture(s, path);
        if (panelings[i] == NULL){
            std::cout << "error texture paneling load\n";
            exit(1);
        }
    }

    /* création des boutons */
    // 4 lignes de 3 éléments
    for(int i = 0; i < 12; i++){
        buttons[i] = new Button_menu(10, 100+i*50, 27+4*i);
    }
}

void Menu::blit(){
    overlay.clear(true);
    SDL_Rect position_indicator_rect = {0,0, position_indicator->get_width(), position_indicator->get_height()};
    SDL_Rect right_bar_rect = {1540, 0, 60, 900};
    overlay.blit(position_indicator, &position_indicator_rect);
    overlay.blit(right_bar, &right_bar_rect);
    for(int i = 0; i < 12; i++){
        buttons[i]->blit(right_bar);
    }
    s->blit_screen(&overlay, NULL);
}

void Menu::update_position_indicator(int i, int j, int num_type){
    delete position_indicator;
    position_indicator = new Texture(s, "("+std::to_string(i)+","+std::to_string(j)+","+std::to_string(num_type)+")");
}

Menu::~Menu(){
    delete position_indicator;
    delete right_bar;
    for(int i = 0; i < 12; i++){
        delete buttons[i];
    }
}

/******************************************************************************/

Button_menu::Button_menu(int x, int y, int texture_num)
    : cadre({x, y, panelings[texture_num]->get_width(), panelings[texture_num]->get_height()}),
    texture_num(texture_num), state(NORMAL) {}

bool Button_menu::is_inside(int x, int y){
    return x >= cadre.x && x < cadre.x+cadre.w
            && y >= cadre.y && y < cadre.y+cadre.h;
}

void Button_menu::blit(Texture *target){
    target->blit(panelings[texture_num+state], &cadre);
}
