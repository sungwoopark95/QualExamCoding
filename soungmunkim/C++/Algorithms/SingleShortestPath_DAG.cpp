/*
[최단 경로 찾기 DAG]
cycle이 없음 (directed graph)

(base) soungmunkim@gimseongmun-ui-MacBookPro Algorithms % g++ -std=c++17 SingleShortestPath_DAG.cpp -o DAG
(base) soungmunkim@gimseongmun-ui-MacBookPro Algorithms % ./DAG 
Distance from 0 to 0 is: 0
Distance from 0 to 1 is: 5
Distance from 0 to 2 is: 3
*/

#include <iostream>
#include <vector>
#include <stack>
#include <limits>

using namespace std;

// INF는 '무한대'를 나타내는 값으로 설정합니다.
const int INF = numeric_limits<int>::max();

// 간선 클래스: 그래프의 간선을 나타냅니다.
class Edge {
public:
    int u, v, weight;  // u: 시작 정점, v: 종료 정점, weight: 가중치
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}  // 생성자
};

// 그래프 클래스: 정점과 간선을 저장합니다.
class Graph {
public:
    int V, E;  // V: 정점의 수, E: 간선의 수
    vector<Edge> edges;  // 간선 정보를 저장하는 벡터

    Graph(int V, int E) : V(V), E(E) {}  // 생성자

    // 간선을 그래프에 추가하는 함수
    void addEdge(int u, int v, int weight) {
        edges.push_back(Edge(u, v, weight));
    }
};

vector<int> shortestDistance;  // 시작 정점에서 다른 모든 정점까지의 최단 거리를 저장하는 전역 변수

// 시작 정점에서의 최단 거리를 초기화하는 함수
void Initialize_Single_Source(Graph& g, int source) {
    shortestDistance.assign(g.V, INF);  // 모든 거리를 '무한대'로 초기화
    shortestDistance[source] = 0;  // 시작 정점의 거리는 0
}

// relax 함수: 시작 정점에서의 거리와 간선의 가중치를 고려하여 목적지 정점의 거리를 업데이트
void relax(int u, int v, int weight) {
    if (shortestDistance[u] != INF && shortestDistance[u] + weight < shortestDistance[v]) {
        shortestDistance[v] = shortestDistance[u] + weight;
    }
}

// 그래프의 정점을 위상 정렬하는 함수
vector<int> topological_sort(Graph& g) {
    vector<bool> visited(g.V, false);  // 방문 여부를 저장하는 벡터
    stack<int> s;  // DFS 수행 결과를 저장하는 스택
    vector<int> order;  // 위상 정렬된 결과를 저장하는 벡터

    // 깊이 우선 탐색 (DFS) 함수
    auto dfs = [&](auto&& self, int v) -> void {
        visited[v] = true;
        for (const auto& edge : g.edges) {
            if (edge.u == v && !visited[edge.v]) {
                self(self, edge.v);
            }
        }
        s.push(v);
    };

    // 모든 정점에 대해 DFS 수행
    for (int i = 0; i < g.V; i++) {
        if (!visited[i]) {
            dfs(dfs, i);
        }
    }

    // 스택의 내용을 order 벡터에 저장
    while (!s.empty()) {
        order.push_back(s.top());
        s.pop();
    }

    return order;
}

// DAG에서의 최단 경로를 계산하는 함수
void DAG_shortest_path(Graph& g, int source) {
    vector<int> order = topological_sort(g);
    for (int u : order) {
        for (const auto& edge : g.edges) {
            if (edge.u == u) {
                relax(edge.u, edge.v, edge.weight);
            }
        }
    }
}

int main() {
    int V = 3, E = 2;  // 예제: 정점 3개, 간선 2개의 그래프
    Graph g(V, E);

    // 예제 그래프에 간선 추가
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);

    int source = 0;  // 시작 정점 설정
    Initialize_Single_Source(g, source);

    DAG_shortest_path(g, source);

    // 결과 출력
    for (int i = 0; i < V; i++) {
        cout << "Distance from " << source << " to " << i << " is: " << shortestDistance[i] << endl;
    }

    return 0;
}


