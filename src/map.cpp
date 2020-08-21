#include "map.hpp"

void convertir2(int i, int j, int *x, int *y, int w){	// de matrice vers écran
	w=w/2-29;
    *x = w-(i-j)*29+10;
    *y = (i+j)*15-5;
}

void convertir(int i, int j, int *x, int *y, int w){
	w = w/2-29;
    *x = w-(i-j)*29;
    *y = (i+j)*15;
}

void localiser(int x, int y, int *i, int *j, int w){	// écran vers matrice
	w = w/2;
    *i = (29*y-15*x+15*w)/870;
    *j = (29*y+15*x-15*w)/870;
}

/******************************************************************************/

Map::Map(Screen *s): s(s){
    this->big_map = new Texture(s, MAP_SIZE*TILE_WIDTH, MAP_SIZE*TILE_HEIGHT);
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            int r = (rand() % 109) + 10;
            this->tiles[i][j] = new Sprite(r, s);
            int x,y;
            convertir(i, j, &x, &y, MAP_SIZE*TILE_WIDTH);
            this->tiles[i][j]->move(x, y);
        }
    }
}

Map::~Map(){
    delete this->big_map;
}

void Map::blit(){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            this->tiles[i][j]->blit();
        }
    }
}
