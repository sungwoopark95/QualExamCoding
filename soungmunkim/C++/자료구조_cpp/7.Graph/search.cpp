#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include "search.h"

void BFS(Vertex* start, std::map<Vertex*, unsigned int> &distance) {
  unsigned int dist; // root로부터 거리 기록
  Vertex* vertex;
  // 노드와 방문 distance 기록할 q
	std::queue<std::pair<Vertex*, unsigned int> > q;

  // 노드 방문 표시
  std::map<Vertex*, bool> visited;

  // root node has distance of zero
  dist = 0;
  
  // TODO: mark root node as visited
  visited[start] = true;

  // push (root node, distance 0) pair to the queue
	q.push(std::make_pair(start, dist));

	// loop until the queue is empty
	while (q.empty() == false) {
    // lookup front of the queue
		vertex = q.front().first;
    dist = q.front().second;

    // TODO: pop out front of the queue
    q.pop();

    for (auto adjacent : vertex->GetAdjacencyList()) {
      // when adjacent vertex is not yet visited
      if (visited[adjacent] == false) {
        // TODO: mark adjacent vertex as visited
        visited[adjacent] = true;

        // TODO: push (adjacent vertex, distance) pair to the queue
        q.push(std::make_pair(adjacent, dist+1));
      }
    }

    // write distance of the vertex to the map
    distance[vertex] = dist;
	}
}

void DFS(Vertex* vertex, unsigned int &timestamp,
    std::map<Vertex*, unsigned int> &discovery_time,
    std::map<Vertex*, unsigned int> &finishing_time) {
  // TODO: increase timestamp for discovery time
  timestamp++;

  // TODO: store discovery time of current vertex
  discovery_time[vertex] = timestamp;

  // TODO: recursively call DFS for vertices in the adjancency list
  for (auto adjacent : vertex->GetAdjacencyList()) {
    if (discovery_time[adjacent] == NULL){
      DFS(adjacent, timestamp, discovery_time, finishing_time);
    }
  }

  // increase timestamp for finishing time
  timestamp ++;

  // store finishing time of current vertex
  finishing_time[vertex] = timestamp;
}
