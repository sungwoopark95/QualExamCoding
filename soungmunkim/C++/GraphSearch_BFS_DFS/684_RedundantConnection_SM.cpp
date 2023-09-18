/*
[Undirected graph에서 cycle 만드는 edge 찾는 것]
undirected graph (no cycle) 만들 수 있게 중복 edge 찾아서 없애기

중복된 edge return 하기 (여러개일 경우 맨 마지막 거 return)
해당 edge가 없어져도 모든 nodes이 다 연결되는 것

Cycle path: 1 -> 2 -> 3 -> 4 -> 1
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % g++ -std=c++17 684_RedundantConnection_SM.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test
[1, 4]
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// -------------------------- cycle이있는지 치크하는 함수 + path update ----------------------------//
bool hasCycle(int node, int parent, unordered_map<int, vector<int>>& graph, vector<bool>& visited, vector<int>& path) {
    visited[node] = true;  // 현재 노드 방문 표시
    path.push_back(node);  // 경로에 현재 노드 추가

    for (int neighbor : graph[node]) {
        if (neighbor != parent) {
            if (visited[neighbor]) {
                // 순환을 찾으면 path를 순환만 포함하도록 수정
                while(path[0] != neighbor) {
                    path.erase(path.begin());
                }
                return true;
            } else if (hasCycle(neighbor, node, graph, visited, path)) {
                return true;
            }
        }
    }

    path.pop_back();  // 경로에서 현재 노드 제거
    return false;  // 순환이 없다.
}

// -------------------------- 모든 edges 돌면서 cycle이 있는지 체크하고 있다면 해당 path 반환 ----------------------------//
vector<int> findCycle(vector<vector<int>>& edges) {
    int n = edges.size();
    unordered_map<int, vector<int>> graph;

    // 초기 그래프 생성
    for (int i = 1; i <= n; i++) {
        graph[i] = {}; //빈 벡터 (빈 리스트)
    }

    // 주어진 간선 정보로 그래프를 채움 (undirected graph 정보)
    for (auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }

    // 노드 방문 여부 및 경로 초기화
    vector<bool> visited(n + 1, false);
    vector<int> path;

    // 모든 노드를 순회하며 순환이 있는지 확인 (1 부터 n+1까지)
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && hasCycle(i, -1, graph, visited, path)) {
            return path;
        }
    }

    return {}; // 빈 벡터
}

// -------------------------- cycle이 있는 path = 주어진 edges 중 redundant edge 뽑기 ----------------------------//
vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    // 순환 경로 찾기
    vector<int> paths = findCycle(edges); 

    // 만약 순환 경로가 비어있다면 빈 벡터 반환
    if (paths.empty()) return {}; 

    // 순환을 형성하는 간선들을 저장할 벡터
    vector<vector<int>> redundant; 

    // 모든 간선에 대해 순회
    for (auto& edge : edges) {
        int true_cnt = 0; // 해당 간선의 노드가 순환 경로에 포함되는 횟수를 저장하는 변수

        // 순환 경로의 모든 노드에 대해 순회
        for (int node : paths) {
            // 만약 노드가 간선의 한쪽 끝에 있으면 true_cnt 증가
            if (node == edge[0] || node == edge[1]) {
                true_cnt++;
            }
        }

        // 만약 해당 간선의 두 노드가 모두 순환 경로에 포함되면 
        // 해당 간선은 순환을 형성하므로 redundant 벡터에 추가
        if (true_cnt == 2) {
            redundant.push_back(edge);
        }
    }

    // 순환을 형성하는 간선들 중 마지막 간선 반환
    return redundant.back(); 
}


int main() {
    vector<vector<int>> edges = {{1,2}, {2,3}, {3,4}, {1,4}, {1,5}};
    vector<int> result = findRedundantConnection(edges);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl;  // 출력: [1, 4]

    // Cycle path 출력
    vector<int> cyclePath = findCycle(edges);
    cout << "Cycle path: ";
    for (int node : cyclePath) {
        cout << node << " -> ";
    }
    cout << cyclePath[0] << endl;  // 순환 경로의 시작 노드로 마무리
}
