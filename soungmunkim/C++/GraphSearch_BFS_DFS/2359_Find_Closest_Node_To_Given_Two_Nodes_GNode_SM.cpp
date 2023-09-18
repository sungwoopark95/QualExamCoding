#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <list>
#include <algorithm>
#include <set>

using namespace std;

// 노드 클래스 정의
class GNode {
public:
    int id;
    char color;
    int distance;
    GNode* parent;

    GNode(int id, char color = 'W', int distance = 0, GNode* parent = nullptr)
        : id(id), color(color), distance(distance), parent(parent) {}

    friend ostream& operator<<(ostream& os, const GNode& node) {
        os << node.id;
        return os;
    }
};

using Edge = pair<GNode*, int>;
using Graph = map<int, vector<Edge>>;

vector<vector<GNode*>> detect_cycles(const Graph& graph) {
    vector<vector<GNode*>> cycles;
    vector<GNode*> stack;

    function<void(GNode*)> dfs = [&](GNode* node) {
        if (node->color == 'G') {
            auto it = find(stack.begin(), stack.end(), node);
            cycles.push_back(vector<GNode*>(it, stack.end()));
            return;
        }

        if (node->color == 'B') {
            return;
        }

        stack.push_back(node);
        node->color = 'G';

        for (const auto& [neighbor, _] : graph.at(node->id)) {
            dfs(neighbor);
        }

        node->color = 'B';
        stack.pop_back();
    };

    for (const auto& [_, node_list] : graph) {
        if (node_list[0].first->color == 'W') {
            dfs(node_list[0].first);
        }
    }

    return cycles;
}

pair<map<GNode*, int>, map<GNode*, GNode*>> bellman_ford(const Graph& graph, GNode* s) {
    map<GNode*, int> distances;
    map<GNode*, GNode*> predecessor;

    for (const auto& pair : graph) {
        distances[pair.second[0].first] = numeric_limits<int>::max();
    }
    distances[s] = 0;

    for (size_t i = 0; i < graph.size() - 1; ++i) {
        for (const auto& pair : graph) {
            GNode* u = pair.second[0].first;
            for (const auto& edge : pair.second) {
                GNode* v = edge.first;
                int w = edge.second;
                if (distances[u] + w < distances[v]) {
                    distances[v] = distances[u] + w;
                    predecessor[v] = u;
                }
            }
        }
    }

    for (const auto& pair : graph) {
        GNode* u = pair.second[0].first;
        for (const auto& edge : pair.second) {
            GNode* v = edge.first;
            int w = edge.second;
            if (distances[u] + w < distances[v]) {
                return {{}, {}};
            }
        }
    }

    return {distances, predecessor};
}

// detect_cycles와 bellman_ford 함수도 이미 정의되었다고 가정합니다.

int closestMeetingNodes(const vector<int>& edges, int node1, int node2) {
    Graph G;
    for (int i = 0; i < edges.size(); i++) {
        G[i].push_back(make_pair(new GNode(i), 0));  // distance is initially set as 0
    }

    // 그래프 구성
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i] != -1) {
            G[i].push_back(make_pair(G[edges[i]][0].first, 1));
        }
    }

    // 순환 경로 탐지
    auto cycles = detect_cycles(G);

    // 순환 경로에 포함된 모든 노드들을 집합에 추가
    set<int> cycle_nodes;
    for (const auto& cycle : cycles) {
        for (const auto& node : cycle) {
            cycle_nodes.insert(node->id);
        }
    }

    // Bellman-Ford 알고리즘을 위한 초기 설정
    map<GNode*, int> max_distances;
    for (const auto& [_, node_list] : G) {
        max_distances[node_list[0].first] = 0;
    }

    // 두 개의 노드에 대해 각각 Bellman-Ford 알고리즘 수행
    for (const auto& source : {node1, node2}) {
        auto [distances, _] = bellman_ford(G, G[source][0].first);
        for (const auto& [node, distance] : distances) {
            max_distances[node] = max(max_distances[node], distance);
        }
    }

    // 최대 거리 중에서 가장 작은 값을 가진 노드 찾기
    int min_max_distance = numeric_limits<int>::max();
    for (const auto& [_, distance] : max_distances) {
        min_max_distance = min(min_max_distance, distance);
    }

    for (const auto& [node, distance] : max_distances) {
        if (distance == min_max_distance) {
            return node->id;
        }
    }

    return -1;  // This is added for safety. Ideally, the code shouldn't reach here.
}

int main() {
    // Sample graph: a tree-like structure for simplicity
    //  0
    //  |
    //  1
    //  |
    //  2
    vector<int> edges = {-1, 0, 1};
    Graph G;
    for (int i = 0; i < edges.size(); i++) {
        G[i].push_back(make_pair(new GNode(i), 0));
        if (edges[i] != -1) {
            G[i].push_back(make_pair(G[edges[i]][0].first, 1));
        }
    }

    int result = closestMeetingNodes(edges, 0, 2);
    cout << "Closest meeting node: " << result << endl;  // Expected output: 1

    // Bellman-Ford Test
    GNode* s = G[0][0].first;
    auto [distances, _] = bellman_ford(G, s);
    for (const auto& [node, distance] : distances) {
        cout << "Distance from node 0 to node " << node->id << ": " << distance << endl;
    }

    // Clean up the allocated memory for GNodes
    for (auto& [_, node_list] : G) {
        delete node_list[0].first;
    }

    return 0;
}
