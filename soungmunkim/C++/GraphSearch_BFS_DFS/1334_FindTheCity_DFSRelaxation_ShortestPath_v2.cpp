
/*
[Bellman ford's algorithm 사용해서 모든 노드 shortest path 찾기]
1) threshold 이하인 shortest paths(노드들이 가장 적은 path중 source node가 가장큰 것 프린트)
2) threshold 이하인 shortest paths (from node, to node):[shortest path] 형식으로 프린트
    -> previous member variable 추가해서 프린트하기
    -> pred (previous node 정보) matrix 추가해서 프린트하기 

Bellman-Ford 알고리즘은 그래프 내의 모든 간선에 대해 여러 번의 반복을 필요로하므로, 
DFS보다 훨씬 느릴 수 있습니다. 

그러나 음의 가중치를 가진 간선이 있는 경우에도 사용할 수 있습니다. 
이 문제의 문맥에서는 음의 가중치를 갖는 간선이 없기 때문에 DFS가 더 효율적일 수 있음
int main 형식이 다른 버전!
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <stack>
#include <string>

using namespace std;

class Vertex {
private:
    int id_; // 정점의 ID
    int key_ = 0; // 키 (일반적으로 알고리즘에서 사용됨, 예: 프림 알고리즘)
    unordered_map<Vertex*, int> adjacency_list_; // 인접한 정점과 가중치를 담는 목록
    Vertex* previous_ = nullptr; // 알고리즘에서 사용될 이전 정점 참조

public:
    Vertex(int id) { // 생성자
        this->id_ = id;
    }

    // 정점에 엣지를 추가하는 함수
    void AddEdge(Vertex* vertex, int weight) {
        adjacency_list_[vertex] = weight;
    }

    // 정점의 ID를 반환하는 함수
    int GetId() { 
        return this->id_; 
    }

    // 키를 설정하는 함수
    void SetKey(int key) {
        this->key_ = key;
    }

    // 키를 반환하는 함수
    int GetKey() {
        return this->key_;
    }

    // 인접 리스트를 반환하는 함수
    unordered_map<Vertex*, int>& GetAdjacencyList() { 
        return this->adjacency_list_; 
    }

    // 이전 정점을 설정하는 함수
    void SetPrevious(Vertex* prev) { 
        this->previous_ = prev; 
    }

    // 이전 정점을 반환하는 함수
    Vertex* GetPrevious() { 
        return this->previous_; 
    }
};

class Graph {
private:
    vector<Vertex*> vertices_; // 그래프 내의 모든 정점들을 담는 벡터

public:
    Graph() {} // 기본 생성자

    // 소멸자: 동적으로 할당된 모든 정점들을 해제
    ~Graph() {
        for (Vertex* vertex : this->vertices_) {
            delete vertex;
        }
        this->vertices_.clear();
    }

    // 새로운 정점을 그래프에 추가하는 함수
    Vertex* addNode(int id) {
        Vertex* newVertex = new Vertex(id);
        this->vertices_.push_back(newVertex);
        return newVertex;
    }

    // 엣지를 그래프에 추가하는 함수
    void addEdge(Vertex* start, Vertex* end, int weight) {
        start->AddEdge(end, weight);
    }

    // 모든 정점들을 반환하는 함수
    vector<Vertex*>& GetVertices() { 
        return this->vertices_; 
    }

    // 그래프 내의 정점 개수를 반환하는 함수
    int GetNumVertices() {
        return this->vertices_.size();
    }
};

// 시작 정점에서 그래프 내의 다른 모든 정점까지의 최단 경로를 찾기 위한 DFS 기반 함수
void ShortestPathDFS(Graph* G, Vertex* start) {
    // 초기화: 모든 정점의 거리 값을 무한대로 설정하고 이전 정점을 null로 설정
    for (Vertex* vertex : G->GetVertices()) {
        vertex->SetKey(INT_MAX);
        vertex->SetPrevious(nullptr);
    }
    start->SetKey(0);  // 시작 정점의 거리 값을 0으로 설정
    
    // DFS 탐색을 위한 스택 초기화: 시작 정점을 스택에 넣는다.
    stack<Vertex*> s;
    s.push(start);

    // DFS 시작
    while (!s.empty()) {  // 스택이 비어있지 않는 동안 반복
        Vertex* curr = s.top();  // 스택의 맨 위 정점을 가져온다.
        s.pop();  // 스택에서 제거

        // 현재 정점과 연결된 모든 이웃 정점들을 확인
        for (auto& item : curr->GetAdjacencyList()) {
            Vertex* to = item.first;  // 이웃 정점
            int weight = item.second;  // 현재 정점에서 이웃 정점까지의 가중치

            // 경로가 더 짧은 경우 해당 경로로 갱신
            if (curr->GetKey() != INT_MAX && to->GetKey() > curr->GetKey() + weight) {
                to->SetKey(curr->GetKey() + weight);  // 거리 갱신
                to->SetPrevious(curr);  // 이전 정점 갱신
                s.push(to);  // 스택에 이웃 정점 추가
            }
        }
    }
}

// 두 정점 사이의 경로를 반환하는 함수
vector<Vertex*> ConstructPath(Vertex* from, Vertex* to) {
    vector<Vertex*> path;  // 경로를 저장할 벡터 초기화

    // 시작 정점에서 종료 정점까지의 경로를 역순으로 추적
    while (from != nullptr && from != to) {
        path.insert(path.begin(), to);  // 경로에 정점 추가
        to = to->GetPrevious();  // 이전 정점으로 이동
    }

    // 시작 정점과 종료 정점이 동일한 경우 시작 정점을 경로에 추가
    if (from == to) {
        path.insert(path.begin(), from);
    }
    
    return path;  // 경로 반환
}


// 주어진 그래프 내의 모든 정점들로부터 시작 정점까지의 최단 경로를 반환하는 함수
unordered_map<Vertex*, vector<Vertex*>> RetrieveShortestPath(Graph* G, Vertex* start) {
    // DFS 기반의 최단 경로 계산
    ShortestPathDFS(G, start);

    // 결과를 저장할 unordered_map 초기화
    unordered_map<Vertex*, vector<Vertex*>> shortest_paths;

    // 그래프의 모든 정점에 대해 최단 경로를 계산하고 저장
    for (Vertex* v : G->GetVertices()) {
        shortest_paths[v] = ConstructPath(start, v);
    }

    // 모든 최단 경로가 저장된 맵 반환
    return shortest_paths;
}

// 시작 정점으로부터 그래프 내의 모든 정점들까지의 최단 경로를 출력하는 함수
void PrintShortestPath(Graph* G, Vertex* start, int threshold) {
    // 주어진 시작 정점으로부터 모든 정점까지의 최단 경로를 가져옴
    unordered_map<Vertex*, vector<Vertex*>> shortest_paths = RetrieveShortestPath(G, start);

    // 가져온 경로를 반복하면서 출력
    for (auto& item : shortest_paths) {
        Vertex* to = item.first;  // 목적지 정점
        vector<Vertex*> path = item.second;  // 경로

        // 시작과 목적지가 동일한 경우 건너뜀
        if (start == to) { continue; }

        // threshold 값보다 큰 거리의 경로는 출력하지 않음
        if (to->GetKey() > threshold) { continue; }

        // 출력 형식 설정
        cout << "(" << start->GetId() << ", " << to->GetId() << ") : ";
        
        bool is_start = true;  // 경로의 첫 번째 정점인지를 확인하는 플래그
        cout << "[";
        for (Vertex* intermediate : path) {  // 경로 내의 각 정점을 반복하면서 출력
            if (!is_start) {  // 첫 번째 정점이 아니라면 콤마 출력
                cout << ", ";
            }
            cout << intermediate->GetId();
            is_start = false;  // 플래그 업데이트
        }
        cout << "]" << endl;
    }
}


int main() {
    Graph* graph = new Graph();

    Vertex* node0 = graph->addNode(0);
    Vertex* node1 = graph->addNode(1);
    Vertex* node2 = graph->addNode(2);
    Vertex* node3 = graph->addNode(3);

    graph->addEdge(node0, node1, 3);
    graph->addEdge(node1, node2, 1);
    graph->addEdge(node1, node3, 4);
    graph->addEdge(node1, node0, 3);
    graph->addEdge(node2, node1, 1);
    graph->addEdge(node2, node3, 1);
    graph->addEdge(node3, node1, 4);
    graph->addEdge(node3, node2, 1);

    int threshold = 4;
    // Print shortest paths for each pair of nodes
    for (Vertex* v : graph->GetVertices()) {
        cout << "Shortest path from " << v->GetId() << " : " << endl;
        PrintShortestPath(graph, v, threshold);
        cout << "=========================== DONE ===========================" << endl;
    }

    return 0;
}
