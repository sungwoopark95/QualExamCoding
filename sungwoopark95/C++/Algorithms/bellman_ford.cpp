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
};

struct pair_hash {
    template <class T1, class T2>
    size_t operator () (const pair<T1,T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

void INITIALIZE_SINGLE_SOURCE(Graph& G, Vertex* s) {
    for (Vertex* v : G.V) {
        v->d = numeric_limits<double>::infinity();
        v->pi = nullptr;
    }
    s->d = 0;
}

void RELAX(Vertex* u, Vertex* v, unordered_map<pair<Vertex*, Vertex*>, double, pair_hash>& weights) {
    if (weights.find({u, v}) != weights.end() && v->d > u->d + weights[{u, v}]) {
        v->d = u->d + weights[{u, v}];
        v->pi = u;
    }
}

vector<Vertex*> construct_path(Vertex* s, Vertex* v) {
    vector<Vertex*> path;
    while (v != s && v != nullptr) {
        path.insert(path.begin(), v);
        v = v->pi;
    }
    if (v == s) {
        path.insert(path.begin(), s);
    }
    return path;
}

unordered_map<Vertex*, vector<Vertex*>> BELLMAN_FORD(Graph& G, unordered_map<pair<Vertex*, Vertex*>, double, pair_hash>& weights, Vertex* s) {
    INITIALIZE_SINGLE_SOURCE(G, s);
    
    for (int i = 0; i < G.V.size() - 1; ++i) {
        for (auto edge : G.E) {
            RELAX(edge.first, edge.second, weights);
        }
    }
    
    for (auto edge : G.E) {
        if (edge.second->d > edge.first->d + weights[edge]) {
            return {}; // 음의 순환이 있으면 빈 맵을 반환합니다.
        }
    }
    
    unordered_map<Vertex*, vector<Vertex*>> shortest_paths;
    for (Vertex* v : G.V) {
        shortest_paths[v] = construct_path(s, v);
    }
    
    return shortest_paths;
}

int main() {
    // 그래프 초기화
    Vertex v1, v2, v3;
    Graph G;
    G.V.push_back(&v1);
    G.V.push_back(&v2);
    G.V.push_back(&v3);
    G.E.push_back({&v1, &v2});
    G.E.push_back({&v2, &v3});
    
    unordered_map<pair<Vertex*, Vertex*>, double, pair_hash> weights;
    weights[make_pair(&v1, &v2)] = 5;
    weights[make_pair(&v2, &v3)] = 3;

    // 알고리즘 실행
    auto paths = BELLMAN_FORD(G, weights, &v1);

    // 결과 출력
    for (auto& [vertex, path] : paths) {
        cout << "Path to vertex " << vertex << ": ";
        for (Vertex* v : path) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}

// negative cycle이 있는지를 확인하는 코드
// bool BELLMAN_FORD(Graph& G, unordered_map<pair<Vertex*, Vertex*>, double, pair_hash>& weights, Vertex* s) {
//     INITIALIZE_SINGLE_SOURCE(G, s);
    
//     for (int i = 0; i < G.V.size() - 1; ++i) {
//         for (auto edge : G.E) {
//             RELAX(edge.first, edge.second, weights);
//         }
//     }
    
//     for (auto edge : G.E) {
//         if (edge.second->d > edge.first->d + weights[edge]) {
//             return false; // 음의 순환이 있으면 false를 반환합니다.
//         }
//     }
    
//     return true; // 그렇지 않으면 true를 반환합니다.
// }

// int main() {
//     // 그래프 초기화
//     Vertex v1, v2, v3;
//     Graph G;
//     G.V.push_back(&v1);
//     G.V.push_back(&v2);
//     G.V.push_back(&v3);
//     G.E.push_back({&v1, &v2});
//     G.E.push_back({&v2, &v3});
    
//     unordered_map<pair<Vertex*, Vertex*>, double, pair_hash> weights;
//     weights[make_pair(&v1, &v2)] = 5;
//     weights[make_pair(&v2, &v3)] = 3;

//     // 알고리즘 실행
//     bool result = BELLMAN_FORD(G, weights, &v1);

//     // 결과 출력
//     if (result) {
//         cout << "No negative cycles detected." << endl;
//     } else {
//         cout << "Negative cycle detected!" << endl;
//     }

//     return 0;
// }
