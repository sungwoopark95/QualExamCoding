#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include "search.h"
using namespace std;

void BFS(Vertex* start, map<Vertex*, unsigned int> &distance) {
    vector<Vertex*> visited;
    queue<pair<Vertex*, unsigned int>> Q;
    distance[start] = 0;
    Q.push({start, 0});
    
    // mark root node as visited
    visited.push_back(start);

    while (!Q.empty()) { // while Q is not empty
        // TODO: pop out front of the queue
        pair<Vertex*, int> curr = Q.front();
        Vertex* curr_node = curr.first;
        unsigned int curr_distance = curr.second;
        Q.pop();

        for (auto adj : curr_node->GetAdjacencyList()) {
            // vertex: Vertex*
            // python의 if vertex not in visited에 해당하는 코드
            if (find(visited.begin(), visited.end(), adj) == visited.end()) {
                // mark adjacent vertex as visited
                visited.push_back(adj);
                // push (adjacent vertex, distance) pair to the queue
                distance[adj] = curr_distance + 1;
                Q.push({adj, distance[adj]});
            }
        }
    }
}

void map_BFS(Vertex* start, map<Vertex*, unsigned int> &distance) {
    map<Vertex*, bool> visited;
    queue<pair<Vertex*, unsigned int>> Q;
    distance[start] = 0;
    Q.push(make_pair(start, 0));

    // mark root node as visited
    visited[start] = true;

    while (!Q.empty()) {
        // pop out the front of the queue
        pair<Vertex*, unsigned int> curr = Q.front();
        Vertex* curr_node = curr.first;
        unsigned int curr_distance = curr.second;
        Q.pop();

        for (auto adj : curr_node->GetAdjacencyList()) {
            // if adj is not visited
            if (!visited[adj]) {
                // mark adj as visited
                visited[adj] = true;
                distance[adj] = curr_distance + 1;
                Q.push(make_pair(adj, distance[adj]));
            }
        }
    }
}

void DFS_prob1_stack(Vertex* start, map<Vertex*, unsigned int> &distance) {
    map<Vertex*, bool> visited;
    stack<pair<Vertex*, unsigned int>> S;
    distance[start] = 0;
    S.push({start, 0});

    visited[start] = true;

    // DFS
    while (!S.empty()) {
        pair<Vertex*, unsigned int> curr = S.top();
        Vertex* curr_node = curr.first;
        unsigned int curr_distance = curr.second;
        S.pop();

        vector<Vertex*> adj_list = curr_node->GetAdjacencyList();
        for (auto it = adj_list.rbegin(); it != adj_list.rend(); ++it) {
            Vertex* adj = *it;
            if (!visited[adj]) {
                visited[adj] = true;
                distance[adj] = curr_distance + 1;
                S.push({adj, distance[adj]});
            }
        }
    }
}

void DFS_prob1_recursion(Vertex* start, map<Vertex*, bool> &visited, 
                        map<Vertex*, unsigned int> &distance, unsigned int &curr_dist) {
    if (visited[start]) {
        return;
    }
    visited[start] = true;
    distance[start] = curr_dist;
    for (auto adj : start->GetAdjacencyList()) {
        unsigned int new_dist = curr_dist + 1;
        DFS_prob1_recursion(adj, visited, distance, new_dist);
    }
    return;
}

void DFS(Vertex* vertex, unsigned int &timestamp, map<Vertex*, unsigned int> &discovery_time,
    map<Vertex*, unsigned int> &finishing_time) {
    // TODO: increase timestamp for discovery time
    timestamp++;

    // TODO: store discovery time of current vertex
    discovery_time[vertex] = timestamp;

    // TODO: recursively call DFS for vertices in the adjancency list
    for (auto adj : vertex->GetAdjacencyList()) {
        // if adj is not visited
        if (discovery_time.find(adj) == discovery_time.end()) {
            DFS(adj, timestamp, discovery_time, finishing_time);
        }
    }
    // search가 끝날 때마다 timestamp하나씩 올림
    timestamp++;
    finishing_time[vertex] = timestamp;
}

void DFS_prob2_recursion_map(Vertex* vertex, unsigned int &timestamp, map<Vertex*, unsigned int> &discovery_time,
        map<Vertex*, unsigned int> &finishing_time, map<Vertex*, bool> &visited) {
    // main 함수에 visited 추가해야
    timestamp++;
    discovery_time[vertex] = timestamp;
    visited[vertex] = true;

    // TODO: recursively call DFS for vertices in the adjancency list
    for (auto adj : vertex->GetAdjacencyList()) {
        // if adj is not visited
        if (!visited[adj]) {
            DFS_prob2_recursion_map(adj, timestamp, discovery_time, finishing_time, visited);
        }
    }
    // search가 끝날 때마다 timestamp하나씩 올림
    timestamp++;
    finishing_time[vertex] = timestamp;    
}

void DFS_prob2_stack(Vertex* start, unsigned int &timestamp, map<Vertex*, unsigned int> &discovery_time, 
                map<Vertex*, unsigned int> &finishing_time, map<Vertex*, bool> &visited) {
    stack<Vertex*> S;
    S.push(start);

    while (!S.empty()) {
        Vertex* curr_node = S.top();
        
        if (!visited[curr_node]) {
            visited[curr_node] = true;
            timestamp++;
            discovery_time[curr_node] = timestamp;

            vector<Vertex*> adj_list = curr_node->GetAdjacencyList();
            for (auto it = adj_list.rbegin(); it != adj_list.rend(); ++it) { // 역순으로 반복
                /*
                재귀적 DFS: 현재 노드의 인접 목록에서 첫 번째 노드부터 방문을 시작합니다.
                스택 기반 DFS: 인접 목록의 노드를 스택에 넣을 때, 
                             스택의 특성 상 마지막에 넣은 노드를 먼저 처리하므로 인접 목록을 역순으로 처리할 필요가 있을 수 있습니다.
                */
                Vertex* adj = *it;
                if (!visited[adj]) {
                    S.push(adj);
                }
            }
        } else {
            S.pop();
            if (finishing_time.find(curr_node) == finishing_time.end()) {
                /*
                처음으로 재방문을 했을 때 finishing time을 update하는데, 
                stack의 특성상 finishing time을 update하더라도 해당 노드를 다시 방문하는 것이 가능하기 때문에, 
                이미 방문과 재방문이 모두 완료되어 discovery, finishing time을 업데이트할 필요가 없다는 것을 indicate하기 위함
                */
                timestamp++;
                finishing_time[curr_node] = timestamp;
            }
        }
    }
}
