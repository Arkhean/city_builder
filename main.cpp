#include <unistd.h>
#include <SDL2/SDL.h>

#include "src/sprite.hpp"
#include "src/map.hpp"
#include "src/screen.hpp"

bool interactions(SDL_Event event, bool &attendre, Map *m){
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
            return true;
            break;
        case SDL_MOUSEMOTION :
            //la souris a bougé (event.button.x)
            break;
        case SDL_MOUSEBUTTONDOWN :
            //on a cliqué
            //int n = m->get_n(event.button.x+m->get_dx(), event.button.y+m->get_dy());
            //int id = m->get_region(event.button.x+m->get_dx(), event.button.y+m->get_dy());
            //std::cout << "x = " << event.button.x+m->get_dx() << " y = " << event.button.y+m->get_dy() << " id = " << id << std::endl;
            break;
    }
    return false;
}

char tiles[MAP_SIZE][MAP_SIZE] = {0};

int main(int argc, char * argv[]){
    /* initialisation */
    init_SDL_TTF();
    Screen s(1600, 900);
    load_all_textures(&s);

    Map m(&s);
    m.load_tiles(&s, tiles);
    m.blit();
    s.update();

    SDL_Event event;
    bool attendre = true;
    bool draw = false;

    while(attendre){
        SDL_Delay(50);

        while(SDL_PollEvent(&event)){
            draw = interactions(event, attendre, &m) || draw;
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
