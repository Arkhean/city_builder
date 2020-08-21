#include "map.hpp"

Map::Map(){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            this->map[i][j] = 0;
        }
    }
}
