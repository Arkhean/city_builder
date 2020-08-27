#include <vector>

#include "road.hpp"
#include "building.hpp"

// distance minimal vers chaque types de batiments (de services)
int road_network_access[MAP_SIZE][MAP_SIZE][SERVICE_NUMBER];

void init_road_network(){
    for(int i =0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            for(int k = 0; k < SERVICE_NUMBER; k++){
                road_network_access[i][j][k] = 0;
            }
        }
    }
}

int di[] = {0, -1, 0, 1};
int dj[] = {-1, 0, 1, 0};

void update_road_network(int i, int j, int access_type, Map *m, int value){
    if (road_network_access[i][j][access_type] > value){
        road_network_access[i][j][access_type] = value;
        for(int k = 0; k < 4; k++){
            if (i+di[k] < MAP_SIZE && i+di[k] >= 0 && j+dj[k] < MAP_SIZE && j+dj[k] >= 0){
                if (m->is_road(i, j)){
                    update_road_network(i+di[k], j+dj[k], access_type, m, value-1);
                }
            }
        }
    }
}

int get_access_value(int i, int j, int access_type){
    return road_network_access[i][j][access_type];
}


std::vector<int> path_between(int i_start, int j_start, int i_end, int j_end){
    std::vector<int> path;
    return path;
}
