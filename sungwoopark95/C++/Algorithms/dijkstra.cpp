#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <limits>

using namespace std;

struct Vertex {
    int id;
    double d = numeric_limits<double>::infinity();
    Vertex* pi = nullptr;
};

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

void INITIALIZE_SINGLE_SOURCE(vector<Vertex*>& G, Vertex* s) {
    for (Vertex* v : G) {
        v->d = numeric_limits<double>::infinity();
        v->pi = nullptr;
    }
    s->d = 0;
}

void RELAX(Vertex* u, Vertex* v, unordered_map<pair<Vertex*, Vertex*>, double, pair_hash>& weights) {
    auto it = weights.find({u, v});
    if (it != weights.end() && v->d > u->d + it->second) {
        v->d = u->d + it->second;
        v->pi = u;
    }
}

void DIJKSTRA(vector<Vertex*>& G, unordered_map<pair<Vertex*, Vertex*>, double, pair_hash>& weights, Vertex* s, unordered_map<Vertex*, vector<Vertex*>>& Adj) {
    INITIALIZE_SINGLE_SOURCE(G, s);
    vector<Vertex*> S;
    auto compare = [](Vertex* left, Vertex* right) { return left->d > right->d; };
    priority_queue<Vertex*, vector<Vertex*>, decltype(compare)> Q(compare);

    for (Vertex* u : G) {
        Q.push(u);
    }

    while (!Q.empty()) {
        Vertex* u = Q.top();
        Q.pop();
        S.push_back(u);
        for (Vertex* v : Adj[u]) {
            double old_distance = v->d;
            RELAX(u, v, weights);
            if (v->d < old_distance) {
                Q.push(v);
            }
        }
    }
}

int main() {
    // Sample usage
    Vertex v1, v2, v3, v4;
    v1.id = 1;
    v2.id = 2;
    v3.id = 3;
    v4.id = 4;

    vector<Vertex*> G = {&v1, &v2, &v3, &v4};
    unordered_map<pair<Vertex*, Vertex*>, double, pair_hash> weights = {
        {{&v1, &v2}, 5},
        {{&v1, &v3}, 3},
        {{&v2, &v4}, 2},
        {{&v3, &v4}, 1}
    };

    unordered_map<Vertex*, vector<Vertex*>> Adj = {
        {&v1, {&v2, &v3}},
        {&v2, {&v4}},
        {&v3, {&v4}},
        {&v4, {}}
    };

    DIJKSTRA(G, weights, &v1, Adj);

    for (Vertex* v : G) {
        cout << "Distance from v1 to v" << v->id << ": " << v->d << endl;
    }

    return 0;
}
