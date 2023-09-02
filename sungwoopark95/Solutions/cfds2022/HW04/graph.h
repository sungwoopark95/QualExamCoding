#pragma once

#include <string>
#include <vector>
using namespace std;

class Vertex {
public:
    Vertex(string name) {
        name_ = name;
    }

    string GetName() { 
        return name_; 
    }
    
    vector<Vertex*> GetAdjacencyList() {
        return adjacency_list_; 
    }

    void AddToAdjacentList(Vertex* vertex);

private:
    string name_;
    vector<Vertex*> adjacency_list_;
};

class Graph {
public:
    Graph() {}
    ~Graph();

    Vertex* GenVertex(string name);
    void GenEdge(Vertex* start, Vertex* end);

    vector<Vertex*> GetVertices() { 
        return vertices_; 
    }
    
    size_t GetNumVertices() { 
        return vertices_.size(); 
    }

    void PrintGraph();

private:
    vector<Vertex*> vertices_;
};
