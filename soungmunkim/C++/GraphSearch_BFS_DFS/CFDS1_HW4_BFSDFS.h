
#pragma once

#include "CFDS1_HW4_Graph.h"
#include <map>
using namespace std;

// BFS 함수 (노드와 distance 저장한 dict)
void BFS(Vertex* start,
    std::map<Vertex*, unsigned int> &distance);

// DFS 함수 (노드와, visit start/end time 저장한 dict)
void DFS(Vertex* vertex, unsigned int &timestamp,
    std::map<Vertex*, unsigned int> &discovery_time,
    std::map<Vertex*, unsigned int> &finishing_time);
