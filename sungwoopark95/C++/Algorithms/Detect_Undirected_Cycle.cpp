// /* ============ vector<vector<int>> 형태의 edge가 주어지는 경우 ============ */
// #include <iostream>
// #include <vector>
// #include <set>
// using namespace std;

// // `find` 함수는 노드 x의 대표 노드(루트 노드)를 찾습니다.
// int find(vector<int>& parent, int x) {
//     // x의 부모가 자기 자신이 아니라면, 대표 노드를 찾기 위한 재귀 호출을 합니다.
//     if (parent[x] != x) {
//         parent[x] = find(parent, parent[x]);
//     }
//     return parent[x];
// }

// // `union` 함수는 두 노드 x, y를 같은 집합에 속하도록 합치는 역할을 합니다.
// bool unionSet(vector<int>& parent, int x, int y) {
//     int rootX = find(parent, x);
//     int rootY = find(parent, y);
    
//     if (rootX == rootY) {
//         return false;  // x와 y는 이미 연결되어 있습니다.
//     }

//     parent[rootX] = rootY;
//     return true;
// }

// // 이 함수는 주어진 그래프에서 불필요한 간선(이미 연결된 노드들을 연결하는 간선)을 찾습니다.
// bool findRedundantConnection(const vector<vector<int>>& edges) {
//     set<int> nodes;
//     for (const auto& edge : edges) {
//         nodes.insert(edge[0]);
//         nodes.insert(edge[1]);
//     }
//     int n = nodes.size();
    
//     vector<int> parent(n + 1);
//     for (int i = 0; i <= n; ++i) {
//         parent[i] = i;
//     }
    
//     for (const auto& edge : edges) {
//         if (!unionSet(parent, edge[0], edge[1])) {
//             // 만약 edge[0]과 edge[1]이 이미 연결되어 있다면, 해당 간선이 불필요한 간선임을 의미합니다.
//             cout << "Cycle detected at " << edge[0] << " - " << edge[1] << endl;
//             return true;
//         }
//     }
//     cout << "No cycle" << endl;
//     return false;
// }

// int main() {
//     vector<vector<int>> edges1 = {{1,2},{1,3}};
//     findRedundantConnection(edges1);

//     // vector<vector<int>> edges2 = {{1,2},{2,3},{3,4},{1,4},{1,5}};
//     // findRedundantConnection(edges2);
    
//     return 0;
// }

/* ============ GNode 형태의 그래프를 이용하는 경우 ============ */
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

class GNode {
public:
    int id;
    GNode* parent;
    int distance;

    GNode(int id) : id(id), parent(nullptr), distance(0) {}

    string to_string() {
        return std::to_string(id);
    }
};

using Graph = map<GNode*, vector<GNode*>>;

Graph list_to_gnode_graph(const vector<vector<int>>& edges) {
    set<int> nodes;
    for (const auto& edge : edges) {
        nodes.insert(edge[0]);
        nodes.insert(edge[1]);
    }

    map<int, GNode*> node_dict;
    for (int node : nodes) {
        node_dict[node] = new GNode(node);
    }

    Graph graph;
    for (const auto& edge : edges) {
        GNode* from_node = node_dict[edge[0]];
        GNode* to_node = node_dict[edge[1]];

        graph[from_node].push_back(to_node);
        graph[to_node].push_back(from_node);
    }
    return graph;
}

void printGraph(const Graph& G) {
    for (const auto& pair : G) {
        cout << pair.first->id << " : ";
        for (GNode* node : pair.second) {
            cout << node->id << " ";
        }
        cout << endl;
    }
}

GNode* find(GNode* x) {
    if (x->parent != x) {
        x->parent = find(x->parent);
    }
    return x->parent;
}

bool unionSet(GNode* x, GNode* y) {
    GNode* rootX = find(x);
    GNode* rootY = find(y);

    if (rootX == rootY) {
        return false; // already connected - cycle
    }
    rootX->parent = rootY;
    return true; // not connected - can be connected
}

bool detect_undirected_cycle(Graph& G) {
    for (const auto& pair : G) {
        pair.first->parent = pair.first;
    }

    set<pair<int, int>> visited_edges;
    for (const auto& item : G) {
        for (GNode* adj : item.second) {
            pair<int, int> edge(min(item.first->id, adj->id), max(item.first->id, adj->id));
            if (visited_edges.find(edge) != visited_edges.end()) {
                continue;
            }
            visited_edges.insert(edge);
            if (!unionSet(item.first, adj)) {
                cout << "Cycle detected!" << endl;
                return true;
            }
        }
    }
    cout << "No cycle." << endl;
    return false;
}

int main() {
    vector<vector<int>> edges = {{1,2}, {1,3}, {2,3}};
    Graph graph = list_to_gnode_graph(edges);
    printGraph(graph);
    cout << (detect_undirected_cycle(graph) ? "Cycle detected" : "No cycle") << endl;

    // Clean up
    for (const auto& pair : graph) {
        delete pair.first;
    }
}
