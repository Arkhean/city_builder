#include <unistd.h>
#include <SDL2/SDL.h>

#include "interactions.hpp"

void interactions(SDL_Event event, bool &attendre, Menu *menu){
    const Uint8 *state;
    int d = 50;
    int i, j, x, y;
    int num_type;
    Building *b;
    switch (event.type){
        case SDL_QUIT :
            attendre = false;
            break;
        case SDL_KEYDOWN :
            state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_ESCAPE]){
                attendre = false;
            }
            if (state[SDL_SCANCODE_UP]){
                map__translate(0, -d);
            }
            if (state[SDL_SCANCODE_RIGHT]){
                map__translate(d, 0);
            }
            if (state[SDL_SCANCODE_LEFT]){
                map__translate(-d, 0);
            }
            if (state[SDL_SCANCODE_DOWN]){
                map__translate(0, d);
            }
            if (state[SDL_SCANCODE_S]){
                map__save("saves/save1.map");
            }
            if (state[SDL_SCANCODE_L]){
                map__load("saves/save1.map");
            }
            if (state[SDL_SCANCODE_R]){
                map__randomize();
            }
            break;
        case SDL_MOUSEMOTION :
            //la souris a bougé
            x = event.button.x;
            y = event.button.y;
            if (!menu->mouse_motion(x, y)){
                map__localiser(x+map__get_dx(), y+map__get_dy(), &i, &j);
                b = map__get_building_link(i, j);
                if (b == NULL){
                    num_type = -1;
                }
                else{
                    num_type = b->type;
                }
                menu->update_position_indicator(i, j, num_type);
                map__handle_mouse_motion(i, j);
            }
            break;
        case SDL_MOUSEBUTTONDOWN :
            //on a cliqué
            if (event.button.button == SDL_BUTTON_RIGHT){
                map__set_build_mode(NO_BUILDING);
                menu->set_menu_state(NONE);
            }
            else{
                x = event.button.x;
                y = event.button.y;
                if (!menu->mouse_click(x, y)){
                    // click on the map
                    map__localiser(x+map__get_dx(), y+map__get_dy(), &i, &j);
                    map__handle_mouse_click(i, j);
                }
            }
            break;
    }
}
