#include <iostream>
#include <fstream>

#include "map.hpp"

void convertir(int i, int j, int *x, int *y){  // de matrice vers écran
    int w = MAP_SIZE*TILE_WIDTH/2 - 29;
    *x = w-(i-j)*29;
    *y = (i+j)*15;
}

void localiser(int x, int y, int *i, int *j){	// écran vers matrice
    int w = MAP_SIZE*TILE_WIDTH/2;
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
            convertir(i, j, &x, &y);
            this->tiles[i][j]->move(x, y);
        }
    }
}

Map::~Map(){
    delete this->big_map;
}

void Map::blit(){
    big_map->clear(this->s);
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

int Map::get_water_tile(int i, int j){
    int res[] = {199, 199, 167, 167, 199, 199, 167, 167, 164, 164,				//0
				198, 198, 164, 164, 156, 156, 199, 199, 167, 167,				//1
				199, 199, 167, 167, 164, 164, 198, 198, 164, 164,					//2
				156+(rand()%4), 156+(rand()%4), 165, 165, 160+(rand()%2), 160+(rand()%2), 165, 165, 160+(rand()%2), 160+(rand()%2),		//3
				195, 195, 185, 185, 195, 195, 184, 184, 165, 165,					//4
				160+(rand()%2), 160+(rand()%2), 165, 160+(rand()%2), 160+(rand()%2), 160+(rand()%2), 144+(rand()%4), 144+(rand()%4), 183, 183,		//5
				144+(rand()%4), 144+(rand()%4), 128+(rand()%4), 128+(rand()%4), 199, 199, 167, 167, 199, 199,		//6
				167, 167, 164, 164, 198, -1, 164, 164, 156+(rand()%4), -1,					//7
				199, 199, 167, 167, 199, 199, 167, 167, 164, 164,					//8
				198, -1, 164, -1, -1, -1, 165, 165, 160+(rand()%2), 160+(rand()%2),		//9
				165, 165, 160+(rand()%2), -1, 195, 195, -1, 185, 195, 195,				//10
				-1, -1, 165, 165, 160+(rand()%2), 160+(rand()%2), -1, -1, 160+(rand()%2), 160+(rand()%2),				//11
				144+(rand()%4), 144+(rand()%4), 165, -1, 144+(rand()%4), 128+(rand()%4), 128+(rand()%4), 128+(rand()%4), 166, 166,	//12
				197, 152+(rand()%4), 166, 166, 197, 152+(rand()%4), 162+(rand()%2), 162+(rand()%2), 194, 193,			//13
				162+(rand()%2), 162+(rand()%2), 192, 140+(rand()%4), 166, 166, 197, 152+(rand()%4), 166, 166,			//14
				197, -1, 162+(rand()%2), 162+(rand()%2), 194, -1, 162+(rand()%2), 162+(rand()%2), 192, 140+(rand()%4),	//15
				196, 196, 191, 189, 196, 196, 191, 189, 188, 188,			//16
				182, -1, 188, -1, 180, 176, 196, 196, 191, -1,			// 17
				-1, -1, -1, -1, 187, -1, -1, 169, 187, -1,			//18
				177, 173, 166, 166, 197, 152+(rand()%4), 166, 166, 197, 152+(rand()%4),	//19
				162+(rand()%2), 162+(rand()%2), 194, 193, 162+(rand()%2), 162+(rand()%2), -1, 140+(rand()%4), 166, 166,		//20
				197, 162+(rand()%2), 166, -1, 197, 197, 162+(rand()%2), 162+(rand()%2), 148+(rand()%4), -1,				//21
				162+(rand()%2), -1, 168, 140+(rand()%4), 148+(rand()%4), 148+(rand()%4), 190, 136+(rand()%4), 148+(rand()%4), -1,	//22
				190, 136+(rand()%4), 186, 175, 178, 175, 132+(rand()%4), -1, -1, 172,
				148+(rand()%4), 148+(rand()%4), 190, 136+(rand()%4), 148+(rand()%4), 185, -1, 136+(rand()%4), 132+(rand()%4), 132+(rand()%4),
				-1, 171, 132+(rand()%4), 132+(rand()%4), 170, 120+(rand()%8)};
    int r = 0, d = 1;
    int di[] = {1,0,-1,-1,-1,0,1,1};
    int dj[] = {-1,-1,-1,0,1,1,1,0};
	for(int k = 0; k < 8; k++){
        if (i+di[k] < MAP_SIZE && i+di[k] >= 0 && j+dj[k] < MAP_SIZE && j+dj[k] >= 0){
            r += (d * (this->num[i+di[k]][j+dj[k]] == WATER));
        }
        d *= 2;
    }
    return res[r]-1;
}

int Map::determine_sprite(int n, int i, int j){
    int r;
    switch (n) {
        case GRASS:
            return grassland_rand_number();
        case TREE:
            return tree_rand_number();
        case WATER:
            r = this->get_water_tile(i, j);
            if (r < 0){
                return water_rand_number();
            }
            return r;
        case ROCK:
            return rock_rand_number();
        default:
            return grassland_rand_number();
    }
}

void Map::load_tiles(int new_num[MAP_SIZE][MAP_SIZE]){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            this->num[i][j] = new_num[i][j];
        }
    }
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            int r = this->determine_sprite(this->num[i][j], i, j);
            delete this->tiles[i][j];
            this->tiles[i][j] = new Sprite(r, s);
            int x,y;
            convertir(i, j, &x, &y);
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
                myfile << this->num[i][j];
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
    std::string line;
    std::ifstream myfile (path);
    int new_num[MAP_SIZE][MAP_SIZE] = {0};
    if (myfile.is_open()){
        for(int i = 0; i < MAP_SIZE; i++){
            if ( getline (myfile, line) ){
                for(int j = 0; j < MAP_SIZE; j++){
                    new_num[i][j] = line[j] - '0';
                }
            }
            else{
                std::cout << "Error in file\n";
                return 1;
            }
        }
        myfile.close();
        this->load_tiles(new_num);
    }
    else{
        std::cout << "Unable to open file\n";
        return 1;
    }
    return 0;
}

void Map::randomize(){
    int tiles[MAP_SIZE][MAP_SIZE] = { GRASS };
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            int r = rand() % (MAP_SIZE*10);
            if (r < 1){
                tiles[i][j] = WATER;
            }
            else if (r < 2){
                tiles[i][j] = ROCK;
            }
            else if (r < (MAP_SIZE)){
                tiles[i][j] = TREE;
            }
        }
    }
    int proba[] = {0, 15, 4, 6};
    int di[] = {1,0,-1,0};
    int dj[] = {0,-1,0,1};
    for(int n = 0; n < 10; n++){
        for(int i = 1; i < MAP_SIZE-1; i++){
            for(int j = 1; j < MAP_SIZE-1; j++){
                if (tiles[i][j] != GRASS){
                    for(int k = 0; k < 4; k++){
                        if (i+di[k] < MAP_SIZE && i+di[k] >= 0
                            && j+dj[k] < MAP_SIZE && j+dj[k] >= 0){
                            if ((rand()%proba[tiles[i][j]]) == 0){
                                tiles[i+di[k]][j+dj[k]] = tiles[i][j];
                            }
                        }
                    }
                }
            }
        }
    }
    this->load_tiles(tiles);
}
