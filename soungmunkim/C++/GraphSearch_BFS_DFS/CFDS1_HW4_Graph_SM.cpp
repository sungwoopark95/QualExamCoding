/*
[Class 사용하여 Graph 표현하기]
1. Vertex class
(1) member data
    std::string name_ 
        Vertex의 이름
    std::vertex<Vertex*> adjacency_list_ 
        Vertex의 adjacency list
(2) member function
    Vertex(std::string name) 
        Vertex의 constructor; vertex의 이름 입력 받아 저장
    std::string GetName()   
        Vertex의 이름 반환
    std::vector<Vertex*> GetAdjacencyList() 
        Vertex의 adjacency list를 반환
    void AddToAdjacentList(Vertex* vertex)
        Vertex의 adjacency list에 입력받은 input 추가 
2. Graph class
(1) member class
    std::vector<Vertex*> vertices_
        Graph 내의 모든 vertex instance를 저장해두는 list
(2) member function
    Vertex* GenVertex(std::string name)
        Vertex instance 생성, verticies_member data에 생성한 instance 저장
    void GenEdge(Vertex* start, Vertex* end)
        start vertex의 adjacency list에 end vertex를 추가
    std::vector<Vertex*> GetVertices()
        Graph 내의 모든 vertex instance를 담고 있는 list 반환
    size_t GetNumVertices()
        Graph 내의 모든 vertex 개수 반환
    void PrintGraph()
        Graph 내의 모든 vertex 이름과 각각의 adjacencey list 출력

<Output>
============== Defined Graph ==============
Vertexu, Adjacency List: Vertex v, Vertex x
Vertexv, Adjacency List: Vertex y
Vertexw, Adjacency List: Vertex y, Vertex z
Vertexx, Adjacency List: Vertex v
Vertexy, Adjacency List: Vertex x
Vertexz, Adjacency List: Vertex z 
*/
#include <iostream>
#include "CFDS1_HW4_Graph.h"

using namespace std;
// 인접한 node list에 입력받은 input node를 추가하는 method
void Vertex::AddToAdjacentList(Vertex* vertex){
    adjacency_list_.push_back(vertex); // 입력받은 vertex append하기
}

// Graph deconstructor
/*
Graph::~Graph() { // !auto 가 지원 안 되면 사용할 코드!
    for (std::vector<Vertex*>::iterator it = vertices_.begin(); it != vertices_.end(); ++it) {
        delete *it;
    }
    vertices_.clear();
}
*/
Graph::~Graph() {
    for (auto vertex : vertices_) { // vertices list 돌면서 vertex element 지우기
        delete vertex;
    }
    vertices_.clear();
}

// Vertex instance 생성
// vertices_member data에 생성한 인스턴스 저장
Vertex* Graph::GenVertex(string name){
    Vertex* vertex = new Vertex(name); // vertex class에서 새로운 이름 가진 vetex 생성
    vertices_.push_back(vertex); // 해당 vertex를 vertex list에 append하기
    return vertex; // vertex* 함수이므로 vertex 반환
}

// vertex edge 만들기 
// start vertex의 adj list에 end vertex 추가
void Graph::GenEdge(Vertex* start, Vertex* end) {
    start -> AddToAdjacentList(end); // start vertex -> end vertex (연결)
}

void Graph::PrintGraph() {
    cout << "============== Defined Graph ==============" << endl;
    for (auto vertex : vertices_) { // vertex 노드마다 돌기
        // vertex의 이름 가져와서 print
        cout << "Vertex" << vertex->GetName() << ", Adjacency List: ";

        // 첫번째 print하는 노드인지 체크
        bool is_first = true;
        // adjacency list의 key(adjacent)마다 돌기
        for (auto adjacent : vertex->GetAdjacencyList()){
            if (is_first == false) // 
                cout << ", ";
            // 해당 노드 이름 가져오기 (adjacent 마다 도니까 그 pointer 이용)
            cout << "Vertex " << adjacent->GetName();
            is_first = false;
        }
        cout << endl;
    }
}