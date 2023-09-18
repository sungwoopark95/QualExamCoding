/*  
GNode class, DFS를 이용하여 undirected graph의 cycle과 cycle path, redundant edge까치 찾는 코드
print하는 코드 있음 
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

// 그래프의 노드를 표현하는 클래스
class GNode {
public:
    int id;            // 노드의 ID
    string color = "W"; // 방문 상태 (W: 미방문, G: 방문 중, B: 완전 방문)
    int parent = -1;   // 이 노드의 부모 노드 ID

    GNode(int id) : id(id) {}
};

// 주어진 노드에서 순환을 찾는 함수
bool hasCycle(int node, unordered_map<int, vector<int>>& graph, unordered_map<int, GNode>& nodes, vector<int>& path) {
    nodes[node].color = "G";       // 현재 노드를 방문 중 상태로 설정
    path.push_back(node);         // 현재 노드를 경로에 추가

    // 이웃 노드들을 순회
    for (int neighbor : graph[node]) {
        if (nodes[neighbor].color == "W") {  // 미방문 상태의 이웃 노드에 대해서
            nodes[neighbor].parent = node;  // 부모 노드를 현재 노드로 설정
            if (hasCycle(neighbor, graph, nodes, path)) {
                return true;
            }
        } else if (nodes[neighbor].color == "G" && nodes[node].parent != neighbor) {  // 순환이 발견된 경우
            return true;
        }
    }

    path.pop_back();              // 현재 노드를 경로에서 제거
    nodes[node].color = "B";      // 현재 노드를 완전 방문 상태로 설정
    return false;
}

// 그래프에서 순환 경로를 찾는 함수
vector<int> findCycle(vector<vector<int>>& edges) {
    int n = edges.size();
    unordered_map<int, vector<int>> graph;   // 그래프 구조
    unordered_map<int, GNode> nodes;         // 노드 정보

    // 그래프 초기화 및 노드 정보 설정
    for (int i = 1; i <= n; ++i) {
        graph[i] = {};
        nodes[i] = GNode(i);
    }

    // 간선 정보를 그래프에 추가
    for (auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }

    vector<int> path;            // 순환 경로 저장
    for (int i = 1; i <= n; ++i) {
        if (nodes[i].color == "W" && hasCycle(i, graph, nodes, path)) {  // 미방문 상태의 노드에서 순환 찾기
            return path;
        }
    }
    return {};   // 순환 경로가 없는 경우
}

// 경로를 출력하는 함수
void printPath(const vector<int>& path) {
    cout << "[";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

// 순환 경로에 포함된 간선 중 불필요한 연결 찾기
vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    vector<int> paths = findCycle(edges);   // 순환 경로 찾기
    if (paths.empty()) {                    // 순환 경로가 없는 경우
        return {};
    }

    set<int> pathSet(paths.begin(), paths.end());
    // 순환 경로에 포함된 간선을 거꾸로 검사
    for (auto it = edges.rbegin(); it != edges.rend(); ++it) {
        if (pathSet.find((*it)[0]) != pathSet.end() && pathSet.find((*it)[1]) != pathSet.end()) {
            return *it;
        }
    }
    return {};
}

int main() {
    vector<vector<int>> edges = {{1,2},{2,3},{3,4},{1,4},{1,5}};

    // findCycle 결과 출력
    vector<int> cyclePath = findCycle(edges);
    cout << "Cycle Path: ";
    printPath(cyclePath);

    // findRedundantConnection 결과 출력
    vector<int> result = findRedundantConnection(edges);
    cout << "Redundant Connection: [" << result[0] << ", " << result[1] << "]" << endl;
}
