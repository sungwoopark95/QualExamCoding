/*
[Single Source Shortest Paths - Bellman Ford Algorithm]
그래프의 최단 경로 (minimum weight)를 찾는 알고리즘
negative weights 포함 가능하며 negative cycle 찾을 수 있음

g++ -std=c++17 SingleShortestPath_BellmanFord.cpp -o Bellman

True/False 로 반환하는 코드지만 path 또는 path & distance 반환 코드도 넣어놓음
*/

#include <iostream>
#include <vector>
#include <climits> // INT_MAX를 위해 사용 (like infinity)

using namespace std;

struct Edge {
    int u, v;
    int weight;
};

class Graph {
public:
    int V, E;
    vector<Edge> edges;

    // 그래프 생성자
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
        edges.reserve(E);  // 에지의 수만큼 예약
    }

    // 그래프에 에지 추가
    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }
};

vector<int> shortestDistance;      // 각 정점까지의 최단 거리를 저장
vector<int> predecessor;   // 최단 경로 트리에 사용되는 선행 정점을 저장

// 시작 정점으로부터의 거리와 선행 정점을 초기화하는 함수
void Initialize_Single_Source(Graph& g, int source) {
    shortestDistance.assign(g.V, INT_MAX);  // 모든 거리를 무한대로 초기화
    predecessor.assign(g.V, -1);    // 선행 정점을 없음으로 초기화
    shortestDistance[source] = 0;           // 시작 정점의 거리는 0
}

// 에지 (u, v)에 대한 Relax 연산을 수행하는 함수
void Relax(int u, int v, int weight) {
    // 새로운 경로가 더 짧으면 거리와 선행 정점을 업데이트
    if (shortestDistance[v] > shortestDistance[u] + weight) {
        shortestDistance[v] = shortestDistance[u] + weight;
        predecessor[v] = u;
    }
}

// Bellman-Ford 알고리즘을 수행하는 함수
bool Bellman_Ford(Graph& g, int source) {
    Initialize_Single_Source(g, source);

    // V-1번 반복하여 각 에지에 대해 Relax 연산 수행
    for (int i = 1; i <= g.V - 1; i++) {
        for (Edge& edge : g.edges) {
            Relax(edge.u, edge.v, edge.weight);
        }
    }

    // 음수 가중치의 사이클 검사
    for (Edge& edge : g.edges) {
        if (shortestDistance[edge.v] > shortestDistance[edge.u] + edge.weight) {
            return false; // 음수 가중치의 사이클이 존재
        }
    }

    return true; // 성공적으로 최단 경로 계산
}

//  [최단 경로를 리턴하고 싶을 때 추가해야할 코드]
// vector<vector<int>> GetShortestPaths(int source) {
//     vector<vector<int>> paths;
//     for (int i = 0; i < shortestDistance.size(); i++) {
//         vector<int> path;
//         for (int v = i; v != -1; v = predecessor[v]) {
//             path.push_back(v);
//         }
//         reverse(path.begin(), path.end());
//         paths.push_back(path);
//     }
//     return paths;
// }

/*-------- Or ----------------*/

//  [최단 경로와 distance를 반환하고 싶을 때 추가해야할 코드]
// pair<vector<int>, int> GetShortestPath(int source, int destination) {
//     vector<int> path;
//     int distance = shortestDistance[destination];
//     for (int v = destination; v != -1; v = predecessor[v]) {
//         path.push_back(v);
//     }
//     reverse(path.begin(), path.end());
//     return {path, distance};
// }


int main() {
    int V = 5;
    int E = 8;
    Graph g(V, E);

    // 그래프에 에지 추가
    g.addEdge(0, 1, -1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 2);
    g.addEdge(3, 2, 5);
    g.addEdge(3, 1, 1);
    g.addEdge(4, 3, -3);

    // Bellman-Ford 알고리즘 수행
    if (Bellman_Ford(g, 0)) {
        cout << "최단 경로가 성공적으로 계산되었습니다!" << endl;

        // [최단 경로를 리턴하고 싶을 때 추가해야할 코드]
        // vector<vector<int>> paths = GetShortestPaths(0);
        // for (int i = 0; i < paths.size(); i++) {
        //     cout << "0 -> " << i << ": ";
        //     for (int j = 0; j < paths[i].size(); j++) {
        //         cout << paths[i][j];
        //         if (j != paths[i].size() - 1) {
        //             cout << " -> ";
        //         }
        //     }
        //     cout << endl;
        // }
    
    /*-------- Or ----------------*/

    //    [최단 경로와 distance를 반환하고 싶을 때 추가해야할 코드]
    //    for (int i = 0; i < g.V; i++) {
    //         pair<vector<int>, int> result = GetShortestPath(0, i);
    //         cout << "0 -> " << i << " (distance: " << result.second << "): ";
    //         for (int j = 0; j < result.first.size(); j++) {
    //             cout << result.first[j];
    //             if (j != result.first.size() - 1) {
    //                 cout << " -> ";
    //             }
    //         }
    //         cout << endl;
    //     }
       
    } else {
        cout << "그래프에 음수 가중치의 사이클이 존재합니다!" << endl;
    }

    return 0;
}
