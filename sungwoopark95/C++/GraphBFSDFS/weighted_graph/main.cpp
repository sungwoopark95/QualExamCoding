#include "weighted_graph.h"
#include "search.h"
#include <cstdlib>
#include <iostream>
using namespace std;

void ShowcaseGraph() {
    // generate graph instance that manages vertices and edges
    Graph graph;

    // generate vertices
    Vertex* vertex_u = graph.GenVertex("u");
    Vertex* vertex_v = graph.GenVertex("v");
    Vertex* vertex_w = graph.GenVertex("w");
    Vertex* vertex_x = graph.GenVertex("x");
    Vertex* vertex_y = graph.GenVertex("y");
    Vertex* vertex_z = graph.GenVertex("z");

    // generate edges
    graph.GenEdge(vertex_u, vertex_v, 1);
    graph.GenEdge(vertex_u, vertex_x, 2);
    graph.GenEdge(vertex_v, vertex_y, 3);
    graph.GenEdge(vertex_w, vertex_y, 4);
    graph.GenEdge(vertex_w, vertex_z, 5);
    graph.GenEdge(vertex_x, vertex_v, 6);
    graph.GenEdge(vertex_y, vertex_x, 7);

    // print all vertices and its their adjacency lists
    graph.PrintGraph();
}

int main() {
    ShowcaseGraph();
    return 0;
}
