#include <unistd.h>
#include <SDL2/SDL.h>

#include "sprite.hpp"
#include "map.hpp"
#include "screen.hpp"
#include "menu.hpp"
#include "interactions.hpp"

int main(int argc, char * argv[]){
    /* initialisation */
    init_SDL_TTF();
    /* window */
    Screen s(1600, 900);
    /* textures */
    load_all_textures(&s);

    /* map */
    Map m(&s);
    m.randomize();
    m.blit();

    /* menu */
    Menu menu(&s);
    menu.blit();

    /* all on screen */
    s.update();

    SDL_Event event;
    bool attendre = true;
    bool draw = false;

    while(attendre){
        SDL_Delay(50);

        while(SDL_PollEvent(&event)){
            draw = interactions(event, attendre, &m, &menu, &s) || draw;
        }
        if (draw){
            m.blit();
            menu.blit();
            s.update();
            draw = false;
        }
    }

    /* libération */
    free_all_textures();
    quit_SDL_TTF();
    return 0;
}
