
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
#include <limits>
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

// 주어진 그래프에서 시작 정점에서 다른 도시들까지의 거리가 threshold 이하인 도시의 수를 반환하는 함수
int NumCities(Graph* G, Vertex* start, int threshold) {
    BellmanFord(G, start);  // 시작 정점에서 다른 모든 정점까지의 최단 거리를 계산

    int cnt = 0;  // threshold 이하 거리에 있는 도시의 수를 저장할 변수 초기화

    // 모든 도시를 순회하면서 조건을 확인
    for (Vertex* v : G->GetVertices()) {
        // 시작 도시 자체이거나, 해당 도시까지의 거리가 threshold보다 크면 카운트에서 제외
        if (start == v || v->GetKey() > threshold) { 
            continue; 
        }
        cnt++;  // 위의 조건에 해당하지 않는 도시는 카운트에 포함
    }
    return cnt;  // 최종 계산된 도시의 수 반환
}

// threshold 이하의 거리에 있는 도시의 수가 가장 작은 도시를 찾고,
// 그러한 도시가 여러 개인 경우 ID가 가장 큰 도시의 ID를 반환하는 함수
int FindTheCity(Graph* G, int threshold) {
    int max = INT_MIN;  // 도시 ID의 최댓값을 저장할 변수 초기화
    int min = INT_MAX;  // 도시 간의 연결 수의 최솟값을 저장할 변수 초기화

    // 모든 도시를 순회하면서 각 도시를 시작점으로 했을 때의 조건을 확인
    for (Vertex* v : G->GetVertices()) {
        int num_cities = NumCities(G, v, threshold);  // 현재 도시를 시작점으로 했을 때 threshold 이하 거리에 있는 도시의 수 계산

        // 위에서 계산한 도시의 수가 이전 최솟값보다 작거나 같은 경우
        if (num_cities <= min) {
            min = num_cities;  // 최솟값 갱신

            // 동일한 수의 도시를 가진 다른 도시가 있을 경우, ID가 더 큰 도시를 선택하기 위해 조건 확인
            if (v->GetId() > max) {
                max = v->GetId();  // ID 최댓값 갱신
            }
        }
    }
    return max;  // 최종 계산된 도시의 ID 반환
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
    cout << FindTheCity(graph, threshold) << endl;
    return 0;
}
