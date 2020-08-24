#include <unistd.h>
#include <SDL2/SDL.h>

#include "interactions.hpp"

bool interactions(SDL_Event event, bool &attendre, Map *m, Menu *menu){
    const Uint8 *state;
    int d = 50;
    int i, j;
    int num_type;
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
                m->translate(0, -d);
            }
            if (state[SDL_SCANCODE_RIGHT]){
                m->translate(d, 0);
            }
            if (state[SDL_SCANCODE_LEFT]){
                m->translate(-d, 0);
            }
            if (state[SDL_SCANCODE_DOWN]){
                m->translate(0, d);
            }
            if (state[SDL_SCANCODE_S]){
                m->save("saves/save1.map");
            }
            if (state[SDL_SCANCODE_L]){
                m->load("saves/save1.map");
            }
            if (state[SDL_SCANCODE_R]){
                m->randomize();
            }
            return true;
            break;
        case SDL_MOUSEMOTION :
            //la souris a bougé (event.button.x)
            localiser(event.button.x+m->get_dx(), event.button.y+m->get_dy(), &i, &j);
            num_type = m->get_building_index(i, j);
            menu->update_position_indicator(i, j, num_type);
            return true;
            break;
        case SDL_MOUSEBUTTONDOWN :
            //on a cliqué
            localiser(event.button.x+m->get_dx(), event.button.y+m->get_dy(), &i, &j);
            std::cout << "i = " << i << " j = " << j << " n = " << std::endl;
            break;
    }
    return false;
}
