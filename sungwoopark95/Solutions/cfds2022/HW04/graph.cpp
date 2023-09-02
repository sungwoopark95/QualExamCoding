#include <iostream>
#include "graph.h"
using namespace std;

void Vertex::AddToAdjacentList(Vertex* vertex) {
    // TODO: Add 'vertex' to adjacency list (class member)
    this->adjacency_list_.push_back(vertex);
}

Graph::~Graph() {
    // GenVertex에서 동적으로 할당된 각각의 vertex를 해제
    size_t size = this->GetNumVertices();
    for (int i=0;i<size;i++) {
        cout << "Delete vertex " << this->vertices_[i]->GetName() << endl;
        delete this->vertices_[i];
    }

    // or for advanced c++ version
    // for (auto vertex : vertices_) {
    //     delete vertex;
    // }

    // vertices를 비움
    this->vertices_.clear();
}

Vertex* Graph::GenVertex(string name) { 
    // vertex class를 활용해 동적할당
    Vertex* vertex = new Vertex(name);
    // vertex 목록에 추가
    this->vertices_.push_back(vertex);
    
    return vertex;
}

void Graph::GenEdge(Vertex* start, Vertex* end) {
    // TODO: Add 'end' vertex to adjacency list of 'start' vertex
    // Vertex의 adjacency_list_ 활용
    start->AddToAdjacentList(end); // start가 pointer이므로 start.가 아니라 start->여야 함
}

void Graph::PrintGraph() {
    cout << "============== Defined Graph ==============" << endl;
    for (auto vertex : vertices_) {
        cout << "Vertex " << vertex->GetName() << ", Adjacency List: ";

        bool is_first = true;
        for (auto adjacent : vertex->GetAdjacencyList()) {
            if (is_first == false) {
                cout << ", ";
            }
            cout << "Vertex " << adjacent->GetName();
            is_first = false;
        }
        cout << endl;
    }
}
