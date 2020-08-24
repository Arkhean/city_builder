#include <unistd.h>
#include <vector>
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
    m.randomize();

    /* buildings */
    std::vector<Building*> buildings;

    buildings.push_back(new Building(MARKET, 1, 5));
    buildings.push_back(new Building(PREFET, 1, 1));
    for(size_t i = 0; i < buildings.size(); i++){
        m.add_to_map(buildings[i], i);
    }

    m.add_road(1, 2);
    m.add_road(2, 2);
    m.add_road(2, 3);
    m.add_road(3, 2);
    m.add_road(9, 10);

    /* menu */
    Menu menu(&s);
    menu.blit();

    /* all on screen */
    m.update_all_sprites();
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
            menu.blit();
            s.update();
            draw = false;
        }
    }

    /* libération */
    for(Building *b : buildings){
        delete b;
    }
    free_all_textures();
    quit_SDL_TTF();
    return 0;
}
