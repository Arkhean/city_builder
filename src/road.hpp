#ifndef ROAD_HPP
#define ROAD_HPP

#include <vector>
#include "map.hpp"

std::vector<int> path_between(int i_start, int j_start, int i_end, int j_end);
int get_access_value(int i, int j, int access_type);
void update_road_network(int i, int j, int access_type, Map *m, int value);
void init_road_network();

#endif
