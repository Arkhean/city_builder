#include <unistd.h>
#include <SDL2/SDL.h>

#include "sprite.hpp"
#include "map.hpp"
#include "screen.hpp"

bool interactions(SDL_Event event, bool &attendre, Map *m, Screen *s){
    const Uint8 *state;
    int d = 50;
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
            if (state[SDL_SCANCODE_C]){
                s->clear();
            }
            if (state[SDL_SCANCODE_R]){
                m->randomize();
            }
            return true;
            break;
        case SDL_MOUSEMOTION :
            //la souris a bougé (event.button.x)
            break;
        case SDL_MOUSEBUTTONDOWN :
            //on a cliqué
            int i, j;
            localiser(event.button.x+m->get_dx(), event.button.y+m->get_dy(), &i, &j);
            std::cout << "i = " << i << " j = " << j << " n = " << std::endl;
            break;
    }
    return false;
}

int main(int argc, char * argv[]){
    /* initialisation */
    init_SDL_TTF();
    Screen s(1600, 900);
    load_all_textures(&s);

    Map m(&s);
    m.randomize();
    m.blit();
    s.update();

    SDL_Event event;
    bool attendre = true;
    bool draw = false;

    while(attendre){
        SDL_Delay(50);

        while(SDL_PollEvent(&event)){
            draw = interactions(event, attendre, &m, &s) || draw;
        }
        if (draw){
            m.blit();
            s.update();
            draw = false;
        }
    }

    /* libération */
    free_all_textures();
    quit_SDL_TTF();
    return 0;
}
