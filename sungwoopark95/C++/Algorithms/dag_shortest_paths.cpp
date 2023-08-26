#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
using namespace std;

class Vertex {
public:
    double d = numeric_limits<double>::infinity(); // v와 s 사이의 거리를 나타냅니다.
    Vertex* pi = nullptr; // v의 부모 노드를 나타냅니다.
};

class Graph {
public:
    vector<Vertex*> V; // 정점의 집합
    vector<pair<Vertex*, Vertex*>> E; // 간선의 집합
    unordered_map<Vertex*, vector<Vertex*>> Adj; // 인접 리스트
};

void INITIALIZE_SINGLE_SOURCE(Graph& G, Vertex* s) {
    for (Vertex* v : G.V) {
        v->d = numeric_limits<double>::infinity();
        v->pi = nullptr;
    }
    s->d = 0;
}

void RELAX(Vertex* u, Vertex* v, unordered_map<pair<Vertex*, Vertex*>, double>& weights) {
    if (weights.find({u, v}) != weights.end() && v->d > u->d + weights[{u, v}]) {
        v->d = u->d + weights[{u, v}];
        v->pi = u;
    }
}

vector<Vertex*> topological_sort(Graph& G) {
    unordered_map<Vertex*, string> color;
    for (Vertex* v : G.V) {
        color[v] = "white";
    }
    unordered_map<Vertex*, int> finish_time;
    int time = 0;
    vector<Vertex*> order;

    function<void(Vertex*)> dfs_visit = [&](Vertex* u) {
        time++;
        color[u] = "gray";
        for (Vertex* v : G.Adj[u]) {
            if (color[v] == "white") {
                dfs_visit(v);
            }
        }
        color[u] = "black";
        time++;
        finish_time[u] = time;
        order.insert(order.begin(), u);
    };

    for (Vertex* u : G.V) {
        if (color[u] == "white") {
            dfs_visit(u);
        }
    }

    return order;
}

void DAG_SHORTEST_PATHS(Graph& G, unordered_map<pair<Vertex*, Vertex*>, double>& weights, Vertex* s) {
    vector<Vertex*> sorted_vertices = topological_sort(G);
    INITIALIZE_SINGLE_SOURCE(G, s);
    for (Vertex* u : sorted_vertices) {
        for (Vertex* v : G.Adj[u]) {
            RELAX(u, v, weights);
        }
    }
}

int main() {
    // 그래프 초기화
    Vertex v1, v2, v3, v4;
    Graph G;
    G.V = {&v1, &v2, &v3, &v4};
    G.E = {{&v1, &v2}, {&v1, &v3}, {&v2, &v4}, {&v3, &v4}};
    G.Adj[&v1] = {&v2, &v3};
    G.Adj[&v2] = {&v4};
    G.Adj[&v3] = {&v4};
    G.Adj[&v4] = {};

    unordered_map<pair<Vertex*, Vertex*>, double> weights;
    weights[make_pair(&v1, &v2)] = 5;
    weights[make_pair(&v1, &v3)] = 3;
    weights[make_pair(&v2, &v4)] = 2;
    weights[make_pair(&v3, &v4)] = 1;

    // 위상 정렬 실행
    vector<Vertex*> sorted_vertices = topological_sort(G);
    cout << "Topologically sorted vertices: ";
    for (Vertex* v : sorted_vertices) {
        cout << v << " ";
    }
    cout << endl;

    // DAG_SHORTEST_PATHS 실행
    DAG_SHORTEST_PATHS(G, weights, &v1);

    // 결과 출력
    for (Vertex* vertex : G.V) {
        cout << "Distance from " << &v1 << " to " << vertex << ": " << vertex->d << endl;
    }

    return 0;
}
