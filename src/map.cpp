#include <iostream>
#include <fstream>

#include "map.hpp"

void convertir(int i, int j, int *x, int *y, int w){  // de matrice vers écran
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

int rand_between(int a, int b){
    return (rand() % (b-a)) + a;
}

int grassland_rand_number(){
    int r = rand_between(61, 118 + (288-229));
    if (r > 118){
        r = 229 - 119 + r;
    }
    return r;
}

int water_rand_number(){
    return rand_between(119, 126);
}
// coastal : 127 - 199

int tree_rand_number(){
    int r = rand_between(9, 16 + (60-29));
    if (r > 16){
        r = 29 - 17 + r;
    }
    return r;
}

int fertil_rand_number(){
    return rand_between(17, 28);
}

int rock_rand_number(){
    return rand_between(289, 296);
}

/******************************************************************************/


Map::Map(Screen *s): s(s), visible_area({0,0,1600,900}){
    /* initialize random seed: */
    srand (time(NULL));
    /* initialize map texture */
    this->big_map = new Texture(s, MAP_SIZE*TILE_WIDTH, MAP_SIZE*TILE_HEIGHT);
    /* fill the map */
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            int r = grassland_rand_number();
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
            this->tiles[i][j]->blit(big_map);
        }
    }
    s->blit_screen(big_map, NULL, &visible_area);
}

void Map::translate(int dx, int dy){
    visible_area.x += dx;
    visible_area.y += dy;
    if (visible_area.x > MAP_SIZE*TILE_WIDTH - s->get_width()){
        visible_area.x = MAP_SIZE*TILE_WIDTH - s->get_width();
    }
    if (visible_area.y > MAP_SIZE*TILE_HEIGHT - s->get_height()){
        visible_area.y = MAP_SIZE*TILE_HEIGHT - s->get_height();
    }
    if (visible_area.x < 0){
        visible_area.x = 0;
    }
    if (visible_area.y < 0){
        visible_area.y = 0;
    }
}


// 0 -> grass
// 1 -> forest
// 2 -> water
// 3 -> rock
int determine_sprite(int n, int i, int j, Map *m){
    switch (n) {
        case 0:
            return grassland_rand_number();
        case 1:
            return tree_rand_number();
        case 2:
            // 46 possibilités
            return water_rand_number();
        case 3:
            return rock_rand_number();
        default:
            return grassland_rand_number();
    }

}

void Map::load_tiles(Screen *s, char num[MAP_SIZE][MAP_SIZE]){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            int r = determine_sprite(num[i][j], i, j, this);
            delete this->tiles[i][j];
            this->tiles[i][j] = new Sprite(r, s);
            int x,y;
            convertir(i, j, &x, &y, MAP_SIZE*TILE_WIDTH);
            this->tiles[i][j]->move(x, y);
        }
    }
}

int Map::save(std::string path){
    std::cout << "saving to " << path << std::endl;
    std::ofstream myfile (path);
    if (myfile.is_open()){
        for(int i = 0; i < MAP_SIZE; i++){
            for(int j = 0; j < MAP_SIZE; j++){
                myfile << this->tiles[i][j]->get_num();
            }
            myfile << "\n";
        }
        myfile.close();
    }
    else{
        std::cout << "Unable to open file\n";
        return 1;
    }
    return 0;
}

int Map::load(std::string path){
    std::cout << "loading from " << path << std::endl;
    big_map->clear(this->s);
    std::string line;
    std::ifstream myfile (path);
    if (myfile.is_open()){
        for(int i = 0; i < MAP_SIZE; i++){
            if ( getline (myfile, line) ){
                for(int j = 0; j < MAP_SIZE; j++){
                    int r = determine_sprite(line[j] - '0', i, j, this);
                    delete this->tiles[i][j];
                    this->tiles[i][j] = new Sprite(r, s);
                    int x,y;
                    convertir(i, j, &x, &y, MAP_SIZE*TILE_WIDTH);
                    this->tiles[i][j]->move(x, y);
                }
            }
            else{
                std::cout << "Error in file\n";
                return 1;
            }
        }
        myfile.close();
    }
    else{
        std::cout << "Unable to open file\n";
        return 1;
    }
    return 0;
}
