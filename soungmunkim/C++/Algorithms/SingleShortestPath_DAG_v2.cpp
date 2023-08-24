/*
[최단 경로 찾기 DAG]
cycle이 없음 (directed graph)

(base) soungmunkim@gimseongmun-ui-MacBookPro Algorithms % g++ -std=c++17 SingleShortestPath_DAG_v2.cpp -o DAGv2
(base) soungmunkim@gimseongmun-ui-MacBookPro Algorithms % ./DAGv2 
Distance from 0 to 0 is: 0
Distance from 0 to 1 is: 5
Distance from 0 to 2 is: 3
*/


#include <iostream>
#include <vector>
#include <stack>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

class Edge {
public:
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

class Graph {
public:
    int V, E;
    vector<Edge> edges;

    Graph(int V, int E) : V(V), E(E) {}

    void addEdge(int u, int v, int weight) {
        edges.push_back(Edge(u, v, weight));
    }
};

// 시작 정점에서의 거리를 초기화하는 함수
vector<int> Initialize_Single_Source(Graph& g, int source) {
    vector<int> distance(g.V, INF);
    distance[source] = 0;
    return distance;
}

// 간선의 끝 정점의 거리를 업데이트하려고 시도하는 함수
void relax(vector<int>& distance, int u, int v, int weight) {
    if (distance[u] != INF && distance[u] + weight < distance[v]) {
        distance[v] = distance[u] + weight;
    }
}

vector<int> topological_sort(Graph& g) {
    vector<bool> visited(g.V, false);
    stack<int> s;
    vector<int> order;

    auto dfs = [&](auto&& self, int v) -> void {
        visited[v] = true;
        for (const auto& edge : g.edges) {
            if (edge.u == v && !visited[edge.v]) {
                self(self, edge.v);
            }
        }
        s.push(v);
    };

    for (int i = 0; i < g.V; i++) {
        if (!visited[i]) {
            dfs(dfs, i);
        }
    }

    while (!s.empty()) {
        order.push_back(s.top());
        s.pop();
    }

    return order;
}

vector<int> DAG_shortest_path(Graph& g, int source) {
    vector<int> distance = Initialize_Single_Source(g, source);
    vector<int> order = topological_sort(g);
    for (int u : order) {
        for (const auto& edge : g.edges) {
            if (edge.u == u) {
                relax(distance, edge.u, edge.v, edge.weight);
            }
        }
    }
    return distance;
}

int main() {
    int V = 3, E = 2; 
    Graph g(V, E);

    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);

    int source = 0;
    vector<int> distances = DAG_shortest_path(g, source);

    for (int i = 0; i < V; i++) {
        cout << "Distance from " << source << " to " << i << " is: " << distances[i] << endl;
    }

    return 0;
}
