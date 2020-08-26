#include <iostream>
#include <fstream>

#include "map.hpp"

void convertir(int i, int j, int *x, int *y){  // de matrice vers écran
    int w = MAP_SIZE*TILE_WIDTH/2 - 29;
    *x = w-(i-j)*29 - i + MAP_SIZE;
    *y = (i+j)*15;
}

void localiser(int x, int y, int *i, int *j){	// écran vers matrice
    int w = MAP_SIZE*TILE_WIDTH/2;
    x = x - MAP_SIZE;
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


Map::Map(Screen *s): s(s), visible_area({0,0,1600,900}), build_mode(NO_BUILDING) {
    /* initialize random seed: */
    srand (time(NULL));
    /* initialize map texture */
    this->big_map = new Texture(s, MAP_SIZE*TILE_WIDTH+MAP_SIZE, MAP_SIZE*TILE_HEIGHT);
    this->map_overlay = new Texture(s, MAP_SIZE*TILE_WIDTH+MAP_SIZE, MAP_SIZE*TILE_HEIGHT);
    this->map_overlay->clear(true);
    this->building_tile = new Sprite(343, 0, 0);
    /* fill the map */
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            this->tile_sprites[i][j] = NULL;
            this->tile_types[i][j] = GRASS;
            this->building_links[i][j] = NULL;
        }
    }
    this->update_all_sprites();
}

Map::~Map(){
    delete this->big_map;
    delete this->map_overlay;
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            delete this->tile_sprites[i][j];
        }
    }
    delete building_tile;
}

void Map::add_to_map(Building *building){
    /* first step : check the area */
    int size = tile_size(building->type);
    for(int i = building->i; i > building->i-size; i--){
        for(int j = building->j; j > building->j-size; j--){
            if (this->tile_types[i][j] != GRASS){
                std::cout << "cannot build here\n";
                return;
            }
        }
    }
    /* second step : clear the area */
    for(int i = building->i; i > building->i-size; i--){
        for(int j = building->j; j > building->j-size; j--){
            this->tile_types[i][j] = EMPTY;
            delete this->tile_sprites[i][j];
            this->tile_sprites[i][j] = NULL;
            this->building_links[i][j] = building;
        }
    }
    /* then : add the new sprite and fix its position */
    this->tile_types[building->i][building->j] = building->type;
    int x, y;
    convertir(building->i, building->j, &x, &y);
    this->tile_sprites[building->i][building->j] = new Sprite(building->type,
                                                x, y, tile_size(building->type));
}

void Map::translate(int dx, int dy){
    visible_area.x += dx;
    visible_area.y += dy;
    int w = this->big_map->get_width();
    int h = this->big_map->get_height();
    if (visible_area.x > w - s->get_width()){
        visible_area.x = w - s->get_width();
    }
    if (visible_area.y > h - s->get_height()){
        visible_area.y = h - s->get_height();
    }
    if (visible_area.x < 0){
        visible_area.x = 0;
    }
    if (visible_area.y < 0){
        visible_area.y = 0;
    }
}

int Map::get_water_tile(int i, int j){
    int res[] = { 199, 199, 167, 167, 199, 199, 167, 167, 164, 164,				//0
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
			197, 162+(rand()%2), 166, -1, 197, 152+(rand()%4), 162+(rand()%2), 162+(rand()%2), 148+(rand()%4), -1,				//21
			162+(rand()%2), -1, 168, 140+(rand()%4), 148+(rand()%4), 148+(rand()%4), 190, 136+(rand()%4), 148+(rand()%4), -1,	//22
			190, 136+(rand()%4), 186, 175, 178, 175, 132+(rand()%4), -1, -1, 172,
			148+(rand()%4), 148+(rand()%4), 190, 136+(rand()%4), 148+(rand()%4), 185, -1, 136+(rand()%4), 132+(rand()%4), 132+(rand()%4),
			-1, 171, 132+(rand()%4), 132+(rand()%4), 170, 120+(rand()%8) };
    int r = 0, d = 1;
    int di[] = {1,0,-1,-1,-1,0,1,1};
    int dj[] = {-1,-1,-1,0,1,1,1,0};
	for(int k = 0; k < 8; k++){
        if (i+di[k] < MAP_SIZE && i+di[k] >= 0 && j+dj[k] < MAP_SIZE && j+dj[k] >= 0){
            r += (d * (this->tile_types[i+di[k]][j+dj[k]] == WATER));
        }
        else{
            // les bords comptent comme de l'eau
            r += d;
        }
        d *= 2;
    }
    return res[r]-1;
}

int Map::get_road_tile(int i, int j){
    int di[] = {0, -1, 0, 1};
    int dj[] = {-1, 0, 1, 0};
    int r = 0, d = 1;
    int res[] = {396, 407, 404, 403, 405, 397, 400, 412,
                406, 402, 398, 411, 401, 410, 409, 413};
    for(int k = 0; k < 4; k++){
        if (i+di[k] < MAP_SIZE && i+di[k] >= 0 && j+dj[k] < MAP_SIZE && j+dj[k] >= 0){
            r += (d * (this->tile_types[i+di[k]][j+dj[k]] == ROAD));
        }
        d *= 2;
    }
    return res[r]-1;
}

int Map::determine_sprite(int i, int j){
    int r;
    switch (this->tile_types[i][j]) {
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
        case ROAD:
            return this->get_road_tile(i, j);
        case EMPTY:
            return 0;
        default:
            return this->tile_types[i][j]; // le type du bâtiments;
    }
}

int Map::save(std::string path){
    std::cout << "saving to " << path << std::endl;
    std::ofstream myfile (path);
    if (myfile.is_open()){
        for(int i = 0; i < MAP_SIZE; i++){
            for(int j = 0; j < MAP_SIZE; j++){
                myfile << this->tile_types[i][j] << "-";
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
    int new_tile_types[MAP_SIZE][MAP_SIZE] = {0};
    if (myfile.is_open()){
        for(int i = 0; i < MAP_SIZE; i++){
            if ( getline (myfile, line) ){
                std::string delimiter = "-";
                size_t pos = 0;
                int j = 0;
                std::string token;
                while ((pos = line.find(delimiter)) != std::string::npos) {
                    token = line.substr(0, pos);
                    new_tile_types[i][j] = atoi(token.c_str());
                    line.erase(0, pos + delimiter.length());
                    j++;
                }
            }
            else{
                std::cout << "Error in file\n";
                return 1;
            }
        }
        myfile.close();
        this->set_all_types(new_tile_types);
        this->update_all_sprites();
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
            else{
                tiles[i][j] = GRASS;
            }
        }
    }
    int di[] = {1,0,-1,0};
    int dj[] = {0,-1,0,1};
    for(int n = 0; n < 10; n++){
        for(int i = 1; i < MAP_SIZE-1; i++){
            for(int j = 1; j < MAP_SIZE-1; j++){
                if (tiles[i][j] != GRASS){
                    for(int k = 0; k < 4; k++){
                        if (i+di[k] < MAP_SIZE && i+di[k] >= 0
                            && j+dj[k] < MAP_SIZE && j+dj[k] >= 0){
                                switch (tiles[i][j]) {
                                    case WATER:
                                        if ((rand()%4) == 0){
                                            tiles[i+di[k]][j+dj[k]] = tiles[i][j];
                                        }
                                        break;
                                    case TREE:
                                        if ((rand()%15) == 0){
                                            tiles[i+di[k]][j+dj[k]] = tiles[i][j];
                                        }
                                        break;
                                    case ROCK:
                                        if ((rand()%6) == 0){
                                            tiles[i+di[k]][j+dj[k]] = tiles[i][j];
                                        }
                                        break;
                                }

                        }
                    }
                }
            }
        }
    }
    this->set_all_types(tiles);
    this->update_all_sprites();
}

/******************************************************************************/

void Map::set_type(int i, int j, int type){
    this->tile_types[i][j] = type;
}

void Map::set_all_types(int new_tile_types[MAP_SIZE][MAP_SIZE]){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            this->tile_types[i][j] = new_tile_types[i][j];
        }
    }
}

// attention : les types des cases adjacentes doivent être à jour !
void Map::update_sprite(int i, int j){
    if (this->tile_sprites[i][j] != NULL){
        delete this->tile_sprites[i][j];
    }
    int x,y;
    convertir(i, j, &x, &y);
    this->tile_sprites[i][j] = new Sprite(determine_sprite(i, j), x, y, tile_size(this->tile_types[i][j]));
}

void Map::update_sprites(int start_i, int end_i, int start_j, int end_j){
    for(int i = start_i; i <= end_i; i++){
        for(int j = start_j; j <= end_j; j++){
            this->update_sprite(i, j);
        }
    }
}

void Map::update_all_sprites(){
    update_sprites(0,  MAP_SIZE-1, 0, MAP_SIZE-1);
}

/* redessine tous les sprites sur big_map puis blit le tout sur l'écran */
void Map::blit_to_screen(){
    big_map->clear();
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            if (this->tile_sprites[i][j] != NULL){
                this->tile_sprites[i][j]->blit(big_map);
            }
        }
    }
    s->blit_screen(big_map, NULL, &visible_area);
    s->blit_screen(map_overlay, NULL, &visible_area);
}


void Map::handle_mouse_motion(int i, int j){
    if (i < MAP_SIZE && i >= 0 && j < MAP_SIZE && j >= 0){
        if (this->build_mode != NO_BUILDING){
            // cas spéciaux
            if (this->build_mode == EMPTY){
                return;
            }
            if (this->build_mode == FISH1){
                return;
            }
            map_overlay->clear(true);
            // taille du bâtiment
            int size = tile_size(this->build_mode);
            // vérifier construction possible (toutes tuiles herbes)
            for(int n_i = i; n_i > i-size; n_i--){
                for(int n_j = j; n_j > j-size; n_j--){
                    if (this->tile_types[n_i][n_j] != GRASS){
                        //cannot build here
                        return;
                    }
                }
            }
            // les colorier en vert (par dessus)
            int x, y;
            for(int n_i = i-size+1; n_i <= i; n_i++){
                for(int n_j = j-size+1; n_j <= j; n_j++){
                    convertir(n_i, n_j, &x, &y);
                    this->building_tile->move(x, y);
                    this->building_tile->blit(map_overlay);
                }
            }
        }
    }
}

void Map::handle_mouse_click(int i, int j){
    if (i < MAP_SIZE && i >= 0 && j < MAP_SIZE && j >= 0){
        if (this->build_mode != NO_BUILDING){
            // cas spéciaux
            if (this->build_mode == EMPTY){
                return;
            }
            if (this->build_mode == ROAD){
                if (this->tile_types[i][j] == GRASS){
                    this->tile_types[i][j] = ROAD;
                    //this->update_sprites(i-1, i+1, j-1, j+1);
                    // TODO: update road
                }
                else{ // TODO : gérer l'erreur
                    std::cout << "cannot build road here (no grass) " << this->tile_types[i][j] << std::endl;;
                }
            }
            if (this->build_mode == FISH1){
                return;
            }
            map_overlay->clear(true);
            // taille du batiment
            int size = tile_size(this->build_mode);
            // vérifier construction possible
            for(int n_i = i; n_i > i-size; n_i--){
                for(int n_j = j; n_j > j-size; n_j--){
                    if (this->tile_types[n_i][n_j] != GRASS){
                        std::cout << "cannot build here\n";
                        return;
                    }
                }
            }
            // si oui :
                Building *b = create_new_building(this->build_mode, i, j);
                this->add_to_map(b);
                this->build_mode = NO_BUILDING;
            // si non :
                // message erreur
        }
    }
}

Building* Map::get_building_link(int i, int j){
    if (i < MAP_SIZE && i >= 0 && j < MAP_SIZE && j >= 0){
        return this->building_links[i][j];
    }
    return NULL;
}
