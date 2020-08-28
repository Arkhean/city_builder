#ifndef ROAD_HPP
#define ROAD_HPP

#include <vector>
#include "map.hpp"

std::vector<int> path_between(int i_start, int j_start, int i_end, int j_end);
int road__get_access_value(int i, int j, int access_type);
void road__update_network(int i, int j, int access_type, int value);
void road__init_network();
void road__remove_road(int i, int j);

#endif
