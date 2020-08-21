#include "map.hpp"

Map::Map(Screen *s): s(s){
    std::cout << "generating map\n";
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            this->tiles[i][j] = new Sprite(0, s);
            this->tiles[i][j]->move(0, 0); // TODO
        }
    }
}

void Map::blit(){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            this->tiles[i][j]->blit();
        }
    }
}
