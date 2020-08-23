#include <unistd.h>
#include <list>
#include <SDL2/SDL.h>

#include "sprite.hpp"
#include "map.hpp"
#include "building.hpp"
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
    //m.randomize();
    m.update();

    /* buildings */
    std::list<Building*> buildings;
    Building * b = new Building(MARKET, 0, 0);
    buildings.push_back(b);
    for(Building *b : buildings){ b->blit(&m); }

    /* menu */
    Menu menu(&s);
    menu.blit();

    /* all on screen */
    m.blit_to_screen();
    s.update();

    SDL_Event event;
    bool attendre = true;
    bool draw = false;

    while(attendre){
        SDL_Delay(50);

        while(SDL_PollEvent(&event)){
            draw = interactions(event, attendre, &m, &menu) || draw;
        }
        if (draw){
            m.blit_to_screen();
            for(Building *b : buildings){ b->blit(&m); }
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
