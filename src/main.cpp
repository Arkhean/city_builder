#include <unistd.h>
#include <vector>
#include <SDL2/SDL.h>

#include "sprite.hpp"
#include "map.hpp"
#include "building.hpp"
#include "screen.hpp"
#include "menu.hpp"
#include "interactions.hpp"
#include "timer.hpp"

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

    /* menu */
    Menu menu(&s);
    menu.blit();

    /* all on screen */
    m.update_all_sprites();
    m.blit_to_screen();
    s.update();

    SDL_Event event;
    bool attendre = true;

    LTimer fpsTimer; //The frames per second timer
    int countedFrames = 0;
    fpsTimer.start();

    while(attendre){
        SDL_Delay(20);
        //Calculate and correct fps
        float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
        if( avgFPS > 2000000 ) {
            avgFPS = 0;
        }
        menu.set_fps(avgFPS);

        /* handle events */
        while(SDL_PollEvent(&event)){
            interactions(event, attendre, &m, &menu);
        }
        /* update screen */
        m.blit_to_screen();
        menu.blit();
        s.update();
        ++countedFrames;
    }

    /* libération */
    clear_all_buildings();
    free_all_textures();
    quit_SDL_TTF();
    return 0;
}
