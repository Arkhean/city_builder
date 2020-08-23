#include "menu.hpp"

Menu::Menu(Screen *s) : overlay(s, 1600, 900), s(s){
    position_indicator = new Texture("(0,0)", s);
}

void Menu::blit(){
    overlay.clear(s, true);
    SDL_Rect position_indicator_rect = {0,0, position_indicator->get_width(), position_indicator->get_height()};
    overlay.blit(s, position_indicator, &position_indicator_rect);
    s->blit_screen(&overlay, NULL);
}

void Menu::update_position_indicator(int i, int j){
    delete position_indicator;
    position_indicator = new Texture("("+std::to_string(i)+","+std::to_string(j)+")", s);
}
