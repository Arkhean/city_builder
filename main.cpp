#include <unistd.h>

#include "src/sprite.hpp"
#include "src/map.hpp"
#include "src/screen.hpp"

int main(int argc, char * argv[]){
    /* initialisation */
    init_SDL_TTF();
    Screen s(800, 600);
    load_all_textures(&s);

    Map m(&s);
    m.blit();

    usleep(1000000);

    /* libération */
    free_all_textures();
    quit_SDL_TTF();
    return 0;
}
