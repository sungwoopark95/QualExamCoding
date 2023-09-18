/*
BFS 활용하여 주어진 그래프를 deepcopy하는 함수
print하는 코드 있음
*/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node(int _val) {
        val = _val;
    }
};

// 리스트를 그래프 형식으로 변환하는 함수
Node* list_to_graph(const vector<vector<int>>& adj_list) {
    if (adj_list.empty()) return nullptr; // 입력 리스트가 비어있다면 nullptr 반환

    unordered_map<int, Node*> node_dict; // 노드 값을 키로 하고, 노드 객체를 값으로 하는 해시맵 생성
    for (int val = 1; val <= adj_list.size(); ++val) { // 각 노드 값에 대하여
        node_dict[val] = new Node(val); // 새 노드 객체를 생성하고 해시맵에 저장
    }

    for (int idx = 0; idx < adj_list.size(); ++idx) { // 주어진 인접 리스트를 순회
        for (int neighbor_val : adj_list[idx]) { // 각 노드의 이웃들을 순회
            node_dict[idx + 1]->neighbors.push_back(node_dict[neighbor_val]); // 이웃 노드를 현재 노드의 이웃으로 추가
        }
    }

    return node_dict[1]; // 변환된 그래프의 시작 노드를 반환
}

// Node 객체로 이루어진 그래프를 출력하는 함수
void printGraph(Node* node) {
    unordered_set<Node*> visited; // 방문한 노드들을 저장할 집합
    queue<Node*> q; // BFS를 위한 큐
    q.push(node); // 시작 노드를 큐에 추가

    cout << "["; // 최상위 리스트 시작

    bool first_outer = true; // 첫 번째 외부 리스트 항목 여부를 확인하는 플래그
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (visited.find(current) != visited.end()) continue; // 이미 방문한 노드라면 스킵
        visited.insert(current); // 현재 노드를 방문한 것으로 표시

        vector<int> neighbors_vals; // 현재 노드의 이웃들의 값을 저장할 벡터
        for (Node* neighbor : current->neighbors) {
            neighbors_vals.push_back(neighbor->val); // 이웃 노드의 값을 벡터에 추가
            if (visited.find(neighbor) == visited.end()) {
                q.push(neighbor); // 아직 방문하지 않은 이웃 노드를 큐에 추가
            }
        }

        if (!first_outer) cout << ", ";
        cout << "[";
        bool first_inner = true; // 첫 번째 내부 리스트 항목 여부를 확인하는 플래그
        for (int val : neighbors_vals) {
            if (!first_inner) cout << ", ";
            cout << val;
            first_inner = false;
        }
        cout << "]";
        first_outer = false;
    }
    cout << "]" << endl; // 최상위 리스트 종료
}

// 그래프를 복제하는 함수
Node* cloneGraph(Node* node) {
    if (!node) return nullptr; // 입력 노드가 nullptr이라면 nullptr 반환

    unordered_map<Node*, Node*> mapping; // 원래 노드와 복제된 노드를 매핑할 해시맵
    queue<Node*> q; // BFS를 위한 큐
    mapping[node] = new Node(node->val); // 시작 노드를 복제하고 해시맵에 저장
    q.push(node); // 시작 노드를 큐에 추가

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        for (Node* neighbor : current->neighbors) { // 현재 노드의 이웃들을 순회
            if (mapping.find(neighbor) == mapping.end()) { // 이웃 노드가 아직 복제되지 않았다면
                mapping[neighbor] = new Node(neighbor->val); // 이웃 노드를 복제하고 해시맵에 저장
                q.push(neighbor); // 복제된 이웃 노드를 큐에 추가
            }
            mapping[current]->neighbors.push_back(mapping[neighbor]); // 복제된 현재 노드의 이웃 리스트에 복제된 이웃 노드 추가
        }
    }

    printGraph(mapping[node]); // 복제된 그래프 출력
    return mapping[node]; // 복제된 그래프의 시작 노드 반환
}

int main() {
    vector<vector<int>> adjList = {{2,4},{1,3},{2,4},{1,3}};
    Node* graph = list_to_graph(adjList); // 주어진 인접 리스트로 그래프 생성
    Node* cloned_graph = cloneGraph(graph); // 그래프 복제

    // 메모리 해제는 이 예제에서는 제외되어 있습니다.
    return 0;
}
