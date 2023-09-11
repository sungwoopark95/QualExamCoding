#pragma once

#include <string>
#include <vector>
using namespace std;

class Vertex {
public:
    Vertex(string name);
    string GetName();
    vector<WeightedEdge*> GetAdjacencyList();
    void AddToAdjacentList(Vertex* vertex, int weight);

private:
    string name_;
    vector<WeightedEdge*> adjacency_list_;
};

class WeightedEdge {
public:
    WeightedEdge(Vertex* end, int weight);
    Vertex* GetEndVertex();
    int GetWeight();

private:
    Vertex* end_;
    int weight_;
};

class Graph {
public:
    Graph() {}
    ~Graph();

    Vertex* GenVertex(string name);
    void GenEdge(Vertex* start, Vertex* end, int weight);
    vector<Vertex*> GetVertices();
    size_t GetNumVertices();
    void PrintGraph();

private:
    vector<Vertex*> vertices_;
};
