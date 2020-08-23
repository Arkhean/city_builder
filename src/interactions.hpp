#ifndef INTERACTIONS_HPP
#define INTERACTIONS_HPP

#include "sprite.hpp"
#include "map.hpp"
#include "screen.hpp"
#include "menu.hpp"

bool interactions(SDL_Event event, bool &attendre, Map *m, Menu *menu);

#endif
