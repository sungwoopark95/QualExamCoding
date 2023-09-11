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


// Bellman-Ford 알고리즘 구현
void BellmanFord(Graph* G, Vertex* start) {
    // 시작점에서 모든 정점까지의 거리를 초기화
    for (Vertex* vertex : G->GetVertices()) {
        vertex->SetKey(INT_MAX);         // 초기 거리 값을 무한대로 설정
        vertex->SetPrevious(nullptr);    // 이전 정점을 nullptr로 초기화
    }
    start->SetKey(0);                    // 시작 정점의 거리를 0으로 설정

    // Relaxation 과정
    for (int i=1;i<G->GetNumVertices();i++) {
        for (Vertex* from : G->GetVertices()) {
            for (auto& item : from->GetAdjacencyList()) {
                Vertex* to = item.first;          // 목적지 정점
                int weight = item.second;         // 해당 엣지의 가중치
                // Relaxation 조건 검사 및 적용
                if (from->GetKey() != INT_MAX && to->GetKey() > from->GetKey() + weight) {
                    to->SetKey(from->GetKey() + weight);   // 거리 업데이트
                    to->SetPrevious(from);                // 이전 정점 업데이트
                }
            }
        }
    }
}

// 최단 경로를 구축하는 함수
vector<Vertex*> ConstructPath(Vertex* from, Vertex* to) {
    vector<Vertex*> path;
    while (from != nullptr && from != to) {
        path.insert(path.begin(), to);   // 경로에 정점을 앞쪽부터 추가
        to = to->GetPrevious();          // 이전 정점으로 이동
    }
    if (from == to) {
        path.insert(path.begin(), from); // 시작 정점 추가
    }
    return path;
}

// 그래프에서 모든 정점까지의 최단 경로를 검색하는 함수
unordered_map<Vertex*, vector<Vertex*>> RetrieveShortestPath(Graph* G, Vertex* start) {
    BellmanFord(G, start);  // Bellman-Ford 알고리즘 실행

    unordered_map<Vertex*, vector<Vertex*>> shortest_paths;
    for (Vertex* v : G->GetVertices()) {
        shortest_paths[v] = ConstructPath(start, v); // 각 정점까지의 경로 구축
    }
    return shortest_paths;
}

// 최단 경로를 화면에 출력하는 함수
void PrintShortestPath(Graph* G, Vertex* start, int threshold) {
    // 모든 정점까지의 최단 경로를 검색하여 shortest_paths에 저장
    // RetrieveShortestPath 함수는 Bellman-Ford 알고리즘을 사용하여 최단 경로를 계산
    unordered_map<Vertex*, vector<Vertex*>> shortest_paths = RetrieveShortestPath(G, start);
    
    // shortest_paths에서 각 정점까지의 경로 정보를 추출하여 출력
    for (auto& item : shortest_paths) {
        Vertex* to = item.first;              // 목적지 정점
        vector<Vertex*> path = item.second;   // 시작 정점에서 목적지 정점까지의 경로

        // 시작 정점과 동일한 경우 출력하지 않고 스킵
        if (start == to) { continue; }

        // 정점까지의 거리가 threshold보다 큰 경우 출력하지 않고 스킵
        // threshold가 필요 없는 경우 이 조건문을 제거하면 됨
        if (to->GetKey() > threshold) { continue; }

        // 시작 정점과 목적지 정점 ID를 출력
        cout << "(" << start->GetId() << ", " << to->GetId() << ") : ";
        bool is_start = true;
        cout << "[";
        
        // 경로에 포함된 각 정점을 순서대로 출력
        for (Vertex* intermediate : path) {
            if (!is_start) {
                cout << ", "; // 첫 번째 정점이 아닌 경우에만 콤마를 출력
            }
            cout << intermediate->GetId(); // 경로의 중간 정점 ID 출력
            is_start = false;  // 첫 번째 정점을 출력한 후에는 false로 설정
        }
        cout << "]" << endl;  // 경로 출력을 마치고 줄바꿈
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
