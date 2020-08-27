#include <iostream>
#include <fstream>
#include "map.hpp"

static Sprite *tile_sprites[MAP_SIZE][MAP_SIZE];
static Sprite *building_tile;
static int tile_types[MAP_SIZE][MAP_SIZE];
// position dans la liste des bâtiments (pour sauvegarde et gestion au clic)
static Building* building_links[MAP_SIZE][MAP_SIZE];
static Texture *big_map;
static Texture *map_overlay;
static Screen *s;
static SDL_Rect visible_area = {0, 0, 1600, 900};
static int build_mode = NO_BUILDING;

/******************************************************************************/
/* private functions */

int rand_between(int a, int b){
    return (rand() % (b-a)) + a;
}

int map__grassland_rand_number(){
    int r = rand_between(61, 118 + (288-229));
    if (r > 118){
        r = 229 - 119 + r;
    }
    return r;
}

int map__water_rand_number(){
    return rand_between(119, 126);
}

int map__tree_rand_number(){
    int r = rand_between(9, 16 + (60-29));
    if (r > 16){
        r = 29 - 17 + r;
    }
    return r;
}

int map__rock_rand_number(){
    return rand_between(289, 296);
}

int map__get_water_tile(int i, int j){
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
            r += (d * (tile_types[i+di[k]][j+dj[k]] == WATER));
        }
        else{
            // les bords comptent comme de l'eau
            r += d;
        }
        d *= 2;
    }
    return res[r]-1;
}

int map__get_road_tile(int i, int j){
    int di[] = {0, -1, 0, 1};
    int dj[] = {-1, 0, 1, 0};
    int r = 0, d = 1;
    int res[] = {396, 407, 404, 403, 405, 397, 400, 412,
                406, 402, 398, 411, 401, 410, 409, 413};
    for(int k = 0; k < 4; k++){
        if (i+di[k] < MAP_SIZE && i+di[k] >= 0 && j+dj[k] < MAP_SIZE && j+dj[k] >= 0){
            r += (d * (tile_types[i+di[k]][j+dj[k]] == ROAD));
        }
        d *= 2;
    }
    return res[r]-1;
}

int map__get_empty_tile(int i, int j){
    int di[] = {0, -1, 0, 1};
    int dj[] = {-1, 0, 1, 0};
    int r = 0, d = 1;
    int res[] = {308, 310, 309, 310, 308, 310, 308, 311,
                308, 310, 309, 311, 308, 310, 309, 311};
    for(int k = 0; k < 4; k++){
        if (i+di[k] < MAP_SIZE && i+di[k] >= 0 && j+dj[k] < MAP_SIZE && j+dj[k] >= 0){
            r += (d * (tile_types[i+di[k]][j+dj[k]] == EMPTY));
        }
        d *= 2;
    }
    return res[r]-1;
}

int map__determine_sprite(int i, int j){
    int r;
    switch (tile_types[i][j]) {
        case GRASS:
            return map__grassland_rand_number();
        case TREE:
            return map__tree_rand_number();
        case WATER:
            r = map__get_water_tile(i, j);
            if (r < 0){
                return map__water_rand_number();
            }
            return r;
        case ROCK:
            return map__rock_rand_number();
        case ROAD:
            return map__get_road_tile(i, j);
        case EMPTY:
            return map__get_empty_tile(i, j);
        default:
            return tile_types[i][j]; // le type du bâtiments;
    }
}

void map__set_type(int i, int j, int type){
    tile_types[i][j] = type;
}

// attention : les types des cases adjacentes doivent être à jour !
void map__update_sprite(int i, int j){
    if (tile_sprites[i][j] != NULL){
        delete tile_sprites[i][j];
    }
    int x,y;
    map__convertir(i, j, &x, &y);
    tile_sprites[i][j] = new Sprite(map__determine_sprite(i, j), x, y, tile_size(tile_types[i][j]));
}

void map__set_all_types(int new_tile_types[MAP_SIZE][MAP_SIZE]){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            tile_types[i][j] = new_tile_types[i][j];
        }
    }
}

void map__update_sprites(int start_i, int end_i, int start_j, int end_j){
    for(int i = start_i; i <= end_i; i++){
        for(int j = start_j; j <= end_j; j++){
            map__update_sprite(i, j);
        }
    }
}

void map__update_all_sprites(){
    map__update_sprites(0,  MAP_SIZE-1, 0, MAP_SIZE-1);
}

/******************************************************************************/
/* public functions */
int map__get_width(){
    return (MAP_SIZE*TILE_WIDTH+(2*MAP_SIZE-1));
}

void map__convertir(int i, int j, int *x, int *y){  // de matrice vers écran
    int w = map__get_width()/2 - HALF_TILE_WIDTH;
    *x = w-(i-j)*HALF_TILE_WIDTH;
    *y = (i+j)*HALF_TILE_HEIGHT;
}

void map__localiser(int x, int y, int *i, int *j){	// écran vers matrice
    int w = map__get_width()/2;
    *i = (2*y - x + w) / 60;
    *j = (2*y - w + x) / 60;
}

void map__init_map(Screen *screen){
    s = screen;
    /* initialize random seed: */
    srand (time(NULL));
    /* initialize map texture */
    big_map = new Texture(s, map__get_width(), MAP_SIZE*TILE_HEIGHT);
    map_overlay = new Texture(s, map__get_width(), MAP_SIZE*TILE_HEIGHT);
    map_overlay->clear(true);
    building_tile = new Sprite(343, 0, 0);
    /* fill the map */
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            tile_sprites[i][j] = NULL;
            tile_types[i][j] = GRASS;
            building_links[i][j] = NULL;
        }
    }
    map__update_all_sprites();
}

void map__free_map(){
    delete big_map;
    delete map_overlay;
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            delete tile_sprites[i][j];
        }
    }
    delete building_tile;
}

void map__translate(int dx, int dy){
    visible_area.x += dx;
    visible_area.y += dy;
    int w = big_map->get_width();
    int h = big_map->get_height();
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

bool map__is_visible(int i, int j){
    int x, y;
    map__convertir(i, j, &x, &y);
    return x+TILE_WIDTH >= visible_area.x && x < visible_area.x+visible_area.w
        && y+TILE_HEIGHT >= visible_area.y && y < visible_area.y+visible_area.h;
}

int map__get_dx(){
    return visible_area.x;
}

int map__get_dy(){
    return visible_area.y;
}

bool map__is_accessible(int i, int j){
    return tile_types[i][j] == GRASS;
}

bool map__is_road(int i, int j) {
    return tile_types[i][j] == ROAD;
};

int map__save(std::string path){
    std::cout << "saving to " << path << std::endl;
    std::ofstream myfile (path);
    if (myfile.is_open()){
        for(int i = 0; i < MAP_SIZE; i++){
            for(int j = 0; j < MAP_SIZE; j++){
                myfile << tile_types[i][j] << "-";
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

int map__load(std::string path){
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
        map__set_all_types(new_tile_types);
        map__update_all_sprites();
    }
    else{
        std::cout << "Unable to open file\n";
        return 1;
    }
    return 0;
}

void map__randomize(){
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
    map__set_all_types(tiles);
    map__update_all_sprites();
}

/* redessine tous les sprites sur big_map puis blit le tout sur l'écran */
void map__blit_to_screen(){
    big_map->clear();
    // optimisation : trouver imin/imax/jmin/jmax avant ??
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            if (tile_sprites[i][j] != NULL){
                if (map__is_visible(i, j)){
                    tile_sprites[i][j]->blit(big_map);
                }
            }
        }
    }
    s->blit_screen(big_map, NULL, &visible_area);
    s->blit_screen(map_overlay, NULL, &visible_area);
}

void map__handle_mouse_motion(int i, int j){
    if (i < MAP_SIZE && i >= 0 && j < MAP_SIZE && j >= 0){
        if (build_mode != NO_BUILDING){
            // cas spéciaux
            if (build_mode == EMPTY){
                return;
            }
            if (build_mode == FISH1){
                return;
            }
            // TODO case road
            map_overlay->clear(true);
            // taille du bâtiment
            int size = tile_size(build_mode);
            // vérifier construction possible (toutes tuiles herbes)
            for(int n_i = i; n_i > i-size; n_i--){
                for(int n_j = j; n_j > j-size; n_j--){
                    if (tile_types[n_i][n_j] != GRASS){
                        //cannot build here
                        return;
                    }
                }
            }
            // les colorier en vert (par dessus)
            int x, y;
            for(int n_i = i-size+1; n_i <= i; n_i++){
                for(int n_j = j-size+1; n_j <= j; n_j++){
                    map__convertir(n_i, n_j, &x, &y);
                    building_tile->move(x, y);
                    building_tile->blit(map_overlay);
                }
            }
        }
    }
}

/* méthode pour construire sur la map */

void map__set_build_mode(int mode) {
    if (build_mode == EMPTY){
        // si on était en mode clean, on remet la flèche
        system_set_cursor(CURSOR_ARROW);
    }
    build_mode=mode;
    map_overlay->clear(true);
    if (mode == EMPTY){
        // si on passe en mode clean, on met la pelle
        system_set_cursor(CURSOR_SHOVEL);
    }
 }

void map__add_building(int i, int j){
    // taille du batiment
    int size = tile_size(build_mode);
    // vérifier construction possible
    for(int n_i = i; n_i > i-size; n_i--){
        for(int n_j = j; n_j > j-size; n_j--){
            if (tile_types[n_i][n_j] != GRASS){
                std::cout << "cannot build here\n";
                return;
            }
        }
    }
    /* second step : clear the area */
    Building *building = create_new_building(build_mode, i, j);
    for(int n_i = i; n_i > i-size; n_i--){
        for(int n_j = j; n_j > j-size; n_j--){
            tile_types[n_i][n_j] = EMPTY;
            delete tile_sprites[n_i][n_j];
            tile_sprites[n_i][n_j] = NULL;
            building_links[n_i][n_j] = building;
        }
    }
    /* then : add the new sprite and fix its position */
    tile_types[i][j] = building->type;
    map__update_sprite(i, j);
    building->has_been_built();
}

void map__clean(int i, int j){
    if (tile_types[i][j] == TREE){
        map__set_type(i, j, GRASS);
        map__update_sprite(i, j);
    }
    else if (building_links[i][j] != NULL){
        Building * b = building_links[i][j];
        int size = tile_size(b->type);
        for(int n_i = b->i; n_i > b->i-size; n_i--){
            for(int n_j = b->j; n_j > b->j-size; n_j--){
                map__set_type(n_i, n_j, GRASS);
                building_links[n_i][n_j] = NULL;
                map__update_sprite(n_i, n_j);
            }
        }
        remove_building(b);
    }
}

void map__add_road(int i, int j){
    if (tile_types[i][j] == GRASS){
        map__set_type(i, j, ROAD);
        map__update_sprite(i, j);
        int di[] = {0, -1, 0, 1};
        int dj[] = {-1, 0, 1, 0};
        for(int k = 0; k < 4; k++){
            if (i+di[k] < MAP_SIZE && i+di[k] >= 0 && j+dj[k] < MAP_SIZE && j+dj[k] >= 0){
                if (tile_types[i+di[k]][j+dj[k]] == ROAD){
                    map__update_sprite(i+di[k], j+dj[k]);
                }
            }
        }
    }
    else{ // TODO : gérer l'erreur
        std::cout << "cannot build road here (no grass) " << tile_types[i][j] << std::endl;;
    }
}

void map__add_fishery(int i, int j){
    // TODO
}

void map__add_warehouse(int i, int j){
    // TODO
}

void map__handle_mouse_click(int i, int j){
    if (i < MAP_SIZE && i >= 0 && j < MAP_SIZE && j >= 0){
        map_overlay->clear(true);
        switch (build_mode) {
            case NO_BUILDING:
                return;
            case EMPTY:
                // supprimer des arbres
                map__clean(i, j);
                break;
            case ROAD:
                map__add_road(i, j);
                break;
            case FISH1:
                // cas compliqué (position côte...)
                map__add_fishery(i, j);
                break;
            case WAREHOUSE:
                // cas compliqué
                map__add_warehouse(i, j);
                break;
            default:
                // cas simple
                map__add_building(i, j);
                break;
        }
    }
}

Building* map__get_building_link(int i, int j){
    if (i < MAP_SIZE && i >= 0 && j < MAP_SIZE && j >= 0){
        return building_links[i][j];
    }
    return NULL;
}
