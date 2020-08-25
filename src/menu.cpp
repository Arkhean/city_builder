#include <iostream>

#include "menu.hpp"


#define PANEL_NUMBER 163

Texture *panelings[PANEL_NUMBER+2];

void load_all_panel_textures(Screen *s){
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

    /* les 2 dernières sont un assemblage */
    panelings[PANEL_NUMBER] = new Texture(s, 16*20, 20);
    panelings[PANEL_NUMBER+1] = new Texture(s, 16*20, 20);
    SDL_Rect rect = {0,0, 16, 20};
    panelings[PANEL_NUMBER]->blit(panelings[0], &rect);
    panelings[PANEL_NUMBER+1]->blit(panelings[3], &rect);
    for(int i = 1; i < 19; i++){
        rect.x += 16;
        panelings[PANEL_NUMBER]->blit(panelings[1], &rect);
        panelings[PANEL_NUMBER+1]->blit(panelings[4], &rect);
    }
    rect.x += 16;
    panelings[PANEL_NUMBER]->blit(panelings[2], &rect);
    panelings[PANEL_NUMBER+1]->blit(panelings[5], &rect);
}

Menu::Menu(Screen *s) : overlay(s, 1600, 900), s(s){
    position_indicator = new Texture(s, "(0,0)");
    fps_indicator = new Texture(s, "0 fps");
    //SDL_Color gray = {100, 100, 100, 100};
    right_bar = new Texture(s, 60, 900);

    test = new Button_text(500, 20, "Coucou !!", s);
    load_all_panel_textures(s);

    /* création des boutons */
    // 4 lignes de 3 éléments
    for(int i = 0; i < NB_BUTTONS; i++){
        buttons[i] = new Button_menu(10, 100+i*50, 26+4*i);
    }
}

void Menu::blit() {
    overlay.clear(true);
    SDL_Rect position_indicator_rect = {0,0, position_indicator->get_width(), position_indicator->get_height()};
    SDL_Rect right_bar_rect = {SHIFT_MENU, 0, 60, 900};
    SDL_Rect fps_indicator_rect = {150, 0, fps_indicator->get_width(), fps_indicator->get_height()};
    overlay.blit(position_indicator, &position_indicator_rect);
    overlay.blit(fps_indicator, &fps_indicator_rect);
    overlay.blit(right_bar, &right_bar_rect);
    for(int i = 0; i < NB_BUTTONS; i++){
        buttons[i]->blit(right_bar);
    }
    test->blit(&overlay);
    s->blit_screen(&overlay, NULL);
}

void Menu::update_position_indicator(int i, int j, int num_type){
    delete position_indicator;
    position_indicator = new Texture(s, "("+std::to_string(i)+","+std::to_string(j)+","+std::to_string(num_type)+")");
}

Menu::~Menu(){
    delete position_indicator;
    delete right_bar;
    for(int i = 0; i < NB_BUTTONS; i++){
        delete buttons[i];
    }
    for(int i = 0; i < PANEL_NUMBER; i++){
        delete panelings[i];
    }
}

void Menu::mouse_motion(int x, int y){
    x = x - SHIFT_MENU;
    for(int i = 0; i < NB_BUTTONS; i++){
        if (buttons[i]->is_inside(x, y)){
            buttons[i]->set_state(OVER);
        }
        else{
            buttons[i]->set_state(NORMAL);
        }
    }
}

void Menu::mouse_click(int x, int y){
    x = x - SHIFT_MENU;
    for(int i = 0; i < NB_BUTTONS; i++){
        if (buttons[i]->is_inside(x, y)){
            buttons[i]->set_state(CLICKED);
        }
        else{
            buttons[i]->set_state(NORMAL);
        }
    }
}

void Menu::set_fps(float avgFPS){
    delete fps_indicator;
    std::string text = "" + std::to_string(avgFPS) + " fps";
    fps_indicator = new Texture(s, text);
}

/******************************************************************************/

Button_menu::Button_menu(int x, int y, int texture_num)
    : cadre({x, y, panelings[texture_num]->get_width(), panelings[texture_num]->get_height()}),
    texture_num(texture_num) {}

bool Button_menu::is_inside(int x, int y) const{
    return x >= cadre.x && x < cadre.x+cadre.w
            && y >= cadre.y && y < cadre.y+cadre.h;
}

void Button_menu::blit(Texture *target) const{
    target->blit(panelings[texture_num+state], &cadre);
}

/******************************************************************************/

Button_text::Button_text(int x, int y, std::string text, Screen *s)
    : cadre({x, y, 16*20, 20}) {
    SDL_Color color = { 30, 30, 30, 255 };
    texture_text = new Texture(s, text, color);
    int w = texture_text->get_width();
    int h = texture_text->get_height();
    cadre_text.x = x + 16*10 - w/2;
    cadre_text.y = y + 10 - h/2;
    cadre_text.w = w;
    cadre_text.h = h;
}

bool Button_text::is_inside(int x, int y) const{
    return x >= cadre.x && x < cadre.x+cadre.w
            && y >= cadre.y && y < cadre.y+cadre.h;
}

void Button_text::blit(Texture *target) const{
    target->blit(panelings[PANEL_NUMBER+state], &cadre);
    target->blit(texture_text, &cadre_text);

}
