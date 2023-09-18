/* ============ vector<vector<int>> 형태로 edge가 주어지는 경우 ============ */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

using Graph = unordered_map<int, vector<int>>;

Graph list_to_gnode_graph(const vector<vector<int>>& edges) {
    Graph graph;
    for (const auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
    }
    return graph;
}

void printGraph(const Graph& G) {
    for (const auto& pair : G) {
        cout << pair.first << " : ";
        for (int node : pair.second) {
            cout << node << " ";
        }
        cout << endl;
    }
}

bool dfs_cycle(int node, Graph& graph, set<int>& visited, set<int>& rec_stack) {
    visited.insert(node);
    rec_stack.insert(node);

    if (graph.find(node) != graph.end()) { // Check if node has neighbors
        for (int neighbor : graph[node]) {
            if (visited.find(neighbor) == visited.end()) {
                if (dfs_cycle(neighbor, graph, visited, rec_stack)) {
                    return true;
                }
            } else if (rec_stack.find(neighbor) != rec_stack.end()) {
                return true;
            }
        }
    }

    rec_stack.erase(node);
    return false;
}

bool detect_directed_cycle(Graph& graph) {
    set<int> visited;
    set<int> rec_stack;

    for (const auto& pair : graph) {
        int node = pair.first;
        if (visited.find(node) == visited.end()) {
            if (dfs_cycle(node, graph, visited, rec_stack)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    vector<vector<int>> edges = {{1,2}, {2,3}, {3,4}, {4,2}}; // this has a cycle
    Graph graph = list_to_gnode_graph(edges);
    printGraph(graph);
    
    cout << (detect_directed_cycle(graph) ? "True" : "False") << endl; // True
}


/* ============ GNode 형태의 그래프를 이용하는 경우 ============ */
// #include <iostream>
// #include <vector>
// #include <map>
// #include <set>
// #include <algorithm>
// using namespace std;

// class GNode {
// public:
//     int id;
//     GNode* parent;
//     int distance;

//     GNode(int id) : id(id), parent(nullptr), distance(0) {}

//     string to_string() {
//         return std::to_string(id);
//     }
// };

// using Graph = map<GNode*, vector<GNode*>>;

// Graph list_to_gnode_graph(const vector<vector<int>>& edges) {
//     vector<int> nodes;
//     for (const auto& edge : edges) {
//         if (find(nodes.begin(), nodes.end(), edge[0]) == nodes.end()) {
//             nodes.push_back(edge[0]);
//         }
//         if (find(nodes.begin(), nodes.end(), edge[1]) == nodes.end()) {
//             nodes.push_back(edge[1]);
//         }
//     }

//     map<int, GNode*> node_dict;
//     for (int node : nodes) {
//         node_dict[node] = new GNode(node);
//     }

//     Graph graph;
//     for (const auto& edge : edges) {
//         GNode* from_node = node_dict[edge[0]];
//         GNode* to_node = node_dict[edge[1]];

//         graph[from_node].push_back(to_node);
//     }
//     return graph;
// }

// void printGraph(const Graph& G) {
//     for (const auto& pair : G) {
//         cout << pair.first->id << " : ";
//         for (GNode* node : pair.second) {
//             cout << node->id << " ";
//         }
//         cout << endl;
//     }
// }

// bool dfs_cycle(GNode* node, Graph& graph, set<GNode*>& visited, set<GNode*>& rec_stack) {
//     visited.insert(node);
//     rec_stack.insert(node);

//     for (GNode* neighbor : graph[node]) {
//         if (visited.find(neighbor) == visited.end()) {
//             if (dfs_cycle(neighbor, graph, visited, rec_stack)) {
//                 return true;
//             }
//         } else if (rec_stack.find(neighbor) != rec_stack.end()) {
//             return true;
//         }
//     }

//     rec_stack.erase(node);
//     return false;
// }

// bool detect_directed_cycle(Graph& graph) {
//     set<GNode*> visited;
//     set<GNode*> rec_stack;

//     for (const auto& pair : graph) {
//         GNode* node = pair.first;
//         if (visited.find(node) == visited.end()) {
//             if (dfs_cycle(node, graph, visited, rec_stack)) {
//                 return true;
//             }
//         }
//     }
//     return false;
// }

// int main() {
//     vector<vector<int>> edges = {{1,2}, {2,3}, {3,4}, {4,2}}; // this has a cycle
//     Graph graph = list_to_gnode_graph(edges);
//     printGraph(graph);
    
//     cout << (detect_directed_cycle(graph) ? "True" : "False") << endl; // True

//     // Clean up
//     for (const auto& pair : graph) {
//         delete pair.first;
//     }
// }
