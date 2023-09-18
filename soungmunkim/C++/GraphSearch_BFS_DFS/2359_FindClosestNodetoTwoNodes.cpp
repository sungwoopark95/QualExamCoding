/*
[두 노드에서 출발해서 도달하는 smallest path 중 max dist를 뽑아
    해당 max dist중 가장 smallest한 max dist를 가지고 있는 
    노드 반환 (여러개일 경우 가장 Index가 작은)]
You are given a directed graph of n nodes numbered from 0 to n - 1, 
    where each node has at most one outgoing edge.

The graph is represented with a given 0-indexed array edges of size n, 
    indicating that there is a directed edge from node i to node edges[i]. 

If there is no outgoing edge from i, then edges[i] == -1.

You are also given two integers node1 and node2.

Return the index of the node that can be reached 
    from both node1 and node2, such that 
    the maximum between the distance from node1 to that node, 
    and from node2 to that node is minimized. 

If there are multiple answers, 
    return the node with the smallest index, 
    and if no possible answer exists, return -1.

Note that edges may contain cycles.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <limits>

using namespace std;

// 순환 경로를 탐지하는 함수
vector<vector<int>> detect_cycles(unordered_map<int, vector<pair<int, int>>> &graph) {
    // 방문한 노드들을 저장하는 집합
    set<int> visited;
    // 현재 경로를 저장하는 스택
    vector<int> stack;
    // 탐지된 순환 경로들을 저장하는 리스트
    vector<vector<int>> cycles;

    // DFS(깊이 우선 탐색)를 실행하는 함수
    function<void(int, int)> dfs = [&](int node, int parent) {
        // 현재 노드가 스택에 이미 있다면 순환 경로 발견
        auto it = find(stack.begin(), stack.end(), node);
        if(it != stack.end()) {
            cycles.push_back(vector<int>(it, stack.end()));
            return;
        }
        // 이미 방문한 노드면 DFS 중지
        if(visited.find(node) != visited.end()) return;

        visited.insert(node);  // 현재 노드를 방문한 것으로 표시
        stack.push_back(node);  // 현재 노드를 스택에 추가

        // 인접 노드를 방문
        for(auto &neighbor : graph[node]) {
            if(neighbor.first != parent) dfs(neighbor.first, node);
        }

        stack.pop_back();  // 현재 노드를 스택에서 제거
    };

    // 그래프의 모든 노드에 대해 DFS 실행
    for(auto &pair : graph) {
        if(visited.find(pair.first) == visited.end()) dfs(pair.first, -1);
    }

    // 탐지된 순환 경로들 반환
    return cycles;
}

// Bellman-Ford 알고리즘을 이용하여 최단 경로를 찾는 함수
pair<unordered_map<int, int>, unordered_map<int, int>> bellman_ford(unordered_map<int, vector<pair<int, int>>> &graph, int s) {
    // 각 노드까지의 최단 거리를 저장하는 맵
    unordered_map<int, int> distances;
    // 각 노드의 전임자를 저장하는 맵
    unordered_map<int, int> predecessor;
    for(auto &pair : graph) {
        // 초기 거리는 무한대로 설정
        distances[pair.first] = numeric_limits<int>::max();
    }
    // 시작 노드의 거리는 0으로 설정
    distances[s] = 0;

    // Relaxation 작업 (최단 거리 갱신)
    for(int i = 0; i < graph.size() - 1; i++) {
        for(auto &pair : graph) {
            for(auto &neighbor : pair.second) {
                // 더 짧은 경로 발견시 거리 및 전임자 갱신
                if(distances[pair.first] + neighbor.second < distances[neighbor.first]) {
                    distances[neighbor.first] = distances[pair.first] + neighbor.second;
                    predecessor[neighbor.first] = pair.first;
                }
            }
        }
    }

    // 음의 가중치 순환 경로가 있는지 확인
    for(auto &pair : graph) {
        for(auto &neighbor : pair.second) {
            if(distances[pair.first] + neighbor.second < distances[neighbor.first]) {
                // 음의 가중치 순환 경로 발견시 빈 맵 반환
                return {{}, {}};
            }
        }
    }

    // 최단 거리 및 전임자 맵 반환
    return {distances, predecessor};
}


// 두 노드에서 가장 가까운 만날 수 있는 노드를 찾는 함수
int closestMeetingNodes(vector<int> &edges, int node1, int node2) {
    // 그래프를 나타내는 해시 맵
    unordered_map<int, vector<pair<int, int>>> graph;

    // 엣지 리스트로부터 그래프 구성
    for(int i = 0; i < edges.size(); i++) {
        if(edges[i] != -1) graph[i].push_back({edges[i], 1});  // 가중치는 1로 고정
    }

    // 순환 경로를 탐지
    vector<vector<int>> cycles = detect_cycles(graph);
    // 순환에 포함된 노드들을 저장할 집합
    set<int> ignore_nodes;
    for(auto &cycle : cycles) {
        for(auto &node : cycle) ignore_nodes.insert(node);
    }

    // 각 노드까지의 최대 거리를 저장할 맵
    unordered_map<int, vector<int>> max_dist;
    for(auto &pair : graph) {
        if(pair.first == node1 || pair.first == node2) {  // node1과 node2에 대해서만 실행
            auto [distances, _] = bellman_ford(graph, pair.first);
            for(auto &dist_pair : distances) {
                max_dist[dist_pair.first].push_back(dist_pair.second); // 거리 저장
            }
        }
    }

    // 최대 거리 계산
    for(auto &pair : max_dist) {
        int dist = max(pair.second[0], pair.second[1]);
        if(dist != numeric_limits<int>::max()) pair.second[0] = dist;  // 무한대가 아니면 거리 저장
        else pair.second.clear();  // 무한대면 리스트 비우기
    }

    // 최소 최대 거리를 찾기
    int smallest = numeric_limits<int>::max();
    for(auto &pair : max_dist) {
        if(!pair.second.empty() && smallest > pair.second[0]) {
            smallest = pair.second[0];  // 최소 거리 갱신
        }
    }

    // 최소 거리와 일치하는 노드 반환
    for(auto &pair : max_dist) {
        if(pair.second[0] == smallest) return pair.first;
    }

    return -1; // 에러의 경우 반환값
}


int main() {
    vector<int> edges = {1, 2, 3, 4, -1};
    int node1 = 1, node2 = 4;

    cout << closestMeetingNodes(edges, node1, node2) << endl; 

    return 0;
}
