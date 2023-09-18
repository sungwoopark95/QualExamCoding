#pragma once

#include "graph.h"
#include <map>
using namespace std;

void BFS(Vertex* start, map<Vertex*, unsigned int> &distance);

void map_BFS(Vertex* start, map<Vertex*, unsigned int> &distance);

void DFS_prob1_stack(Vertex* start, map<Vertex*, unsigned int> &distance);

void DFS_prob1_recursion(Vertex* start, map<Vertex*, bool> &visited, 
                        map<Vertex*, unsigned int> &distance, unsigned int &curr_dist);

void DFS(Vertex* vertex, unsigned int &timestamp, map<Vertex*, unsigned int> &discovery_time,
    map<Vertex*, unsigned int> &finishing_time); 

void DFS_prob2_recursion_map(Vertex* vertex, unsigned int &timestamp, map<Vertex*, unsigned int> &discovery_time,
        map<Vertex*, unsigned int> &finishing_time, map<Vertex*, bool> &visited);

void DFS_prob2_stack(Vertex* start, unsigned int &timestamp, map<Vertex*, unsigned int> &discovery_time, 
                map<Vertex*, unsigned int> &finishing_time, map<Vertex*, bool> &visited);