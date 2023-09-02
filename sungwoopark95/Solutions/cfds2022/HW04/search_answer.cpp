#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include "search.h"
using namespace std;

void BFS(Vertex* start, map<Vertex*, unsigned int> &distance) {
    unsigned int curr;
    Vertex* vertex;
	queue<pair<Vertex*, unsigned int>> q;

    // boolean value is true when vertex is visited
    map<Vertex*, bool> visited;

    // root node has distance of zero
    curr = 0;
    
    // TODO: mark root node as visited
    visited[start] = true;

    // push (root node, distance 0) pair to the queue
	q.push(make_pair(start, curr));

	// loop utill the queue is empty
	while (q.empty() == false) {
        // lookup front of the queue
	    vertex = q.front().first;
        curr = q.front().second;

        // TODO: pop out front of the queue
        q.pop();

        for (auto adjacent : vertex->GetAdjacencyList()) {
            // when adjacent vertex is not yet visited
            if (visited[adjacent] == false) {
                // TODO: mark adjacent vertex as visited
                visited[adjacent] = true;

                // TODO: push (adjacent vertex, distance) pair to the queue
                int dist = curr + 1;
                q.push(make_pair(adjacent, dist));
            }
        }

        // write distance of the vertex to the map
        distance[vertex] = curr;
	}
}

void DFS(Vertex* vertex, unsigned int &timestamp, // DFS_VISIT에 해당
  map<Vertex*, unsigned int> &discovery_time,
  map<Vertex*, unsigned int> &finishing_time) {
  // TODO: increase timestamp for discovery time
  timestamp++;

  // TODO: store discovery time of current vertex
  discovery_time[vertex] = timestamp;

  // TODO: recursively call DFS for vertices in the adjancency list
  for (auto adjacent : vertex->GetAdjacencyList()) {
    // if the vertex is not included in the discovery time <-> not visited yet
    if (discovery_time.find(adjacent) == discovery_time.end()) { 
      DFS(adjacent, timestamp, discovery_time, finishing_time);
    }
  }

  // increase timestamp for finishing time
  timestamp += 1;

  // store finishing time of current vertex
  finishing_time[vertex] = timestamp;
}
