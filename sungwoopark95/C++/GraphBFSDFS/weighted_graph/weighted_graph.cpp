#include <iostream>
#include <string>
#include <vector>
#include "weighted_graph.h"
using namespace std;

WeightedEdge::WeightedEdge(Vertex* end, int weight) {
    this->end_ = end;
    this->weight_ = weight;
}

Vertex* WeightedEdge::GetEndVertex() {
    return this->end_; 
}

int WeightedEdge::GetWeight() {
    return this->weight_;
}

Vertex::Vertex(string name) {
    this->name_ = name;
}

string Vertex::GetName() {
    return this->name_;
}

vector<WeightedEdge*> Vertex::GetAdjacencyList() {
    return this->adjacency_list_;
}

void Vertex::AddToAdjacentList(Vertex* vertex, int weight) {
    WeightedEdge* edge = new WeightedEdge(vertex, weight);
    this->adjacency_list_.push_back(edge);
}

Graph::~Graph() {
    // GenVertex에서 동적으로 할당된 각각의 vertex를 해제
    size_t size = this->GetNumVertices();
    for (int i=0;i<size;i++) {
        delete this->vertices_[i];
    }
    // vertices를 비움
    this->vertices_.clear();
}

Vertex* Graph::GenVertex(string name) {
    Vertex* newNode = new Vertex(name);
    this->vertices_.push_back(newNode);
    return newNode;
}

void Graph::GenEdge(Vertex* start, Vertex* end, int weight) {
    start->AddToAdjacentList(end, weight);
}

vector<Vertex*> Graph::GetVertices() {
    return this->vertices_;
}

size_t Graph::GetNumVertices() {
    return this->vertices_.size();
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
            cout << "(Vertex " << adjacent->GetEndVertex()->GetName() << " Weight " << adjacent->GetWeight() << ")";
            is_first = false;
        }
        cout << endl;
    }
}