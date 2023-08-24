#include "CFDS1_HW4_Graph.h"
#include "CFDS1_HW4_BFSDFS.h"
#include <cstdlib>
#include <iostream>

void ShowcaseGraph() {
  // 기본 그래프 생성 및 출력 that manages vertices and edges
  Graph graph;

  // generate vertices (노드들 만들기)
  Vertex* vertex_u = graph.GenVertex("u");
  Vertex* vertex_v = graph.GenVertex("v");
  Vertex* vertex_w = graph.GenVertex("w");
  Vertex* vertex_x = graph.GenVertex("x");
  Vertex* vertex_y = graph.GenVertex("y");
  Vertex* vertex_z = graph.GenVertex("z");

  // generate edges (노드 edges 만들기)
  graph.GenEdge(vertex_u, vertex_v);
  graph.GenEdge(vertex_u, vertex_x);
  graph.GenEdge(vertex_v, vertex_y);
  graph.GenEdge(vertex_w, vertex_y);
  graph.GenEdge(vertex_w, vertex_z);
  graph.GenEdge(vertex_x, vertex_v);
  graph.GenEdge(vertex_y, vertex_x);
  graph.GenEdge(vertex_z, vertex_z);

  // print all vertices and its their adjacency lists
  // 그래프 출력하기 (모든 노드들과 연결된 정보들 프린트)
  graph.PrintGraph();
}

/*--------------------------- BFS 보여주는 함수 --------------------------*/
void ShowcaseBFS() {
  // generate graph instance that manages vertices and edges
  Graph graph;

  // generate vertices
  Vertex* vertex_r = graph.GenVertex("r");
  Vertex* vertex_s = graph.GenVertex("s");
  Vertex* vertex_t = graph.GenVertex("t");
  Vertex* vertex_u = graph.GenVertex("u");
  Vertex* vertex_v = graph.GenVertex("v");
  Vertex* vertex_w = graph.GenVertex("w");
  Vertex* vertex_x = graph.GenVertex("x");
  Vertex* vertex_y = graph.GenVertex("y");

  // generate edges
  graph.GenEdge(vertex_r, vertex_s); graph.GenEdge(vertex_s, vertex_r);
  graph.GenEdge(vertex_r, vertex_v); graph.GenEdge(vertex_v, vertex_r);
  graph.GenEdge(vertex_s, vertex_w); graph.GenEdge(vertex_w, vertex_s);
  graph.GenEdge(vertex_t, vertex_w); graph.GenEdge(vertex_w, vertex_t);
  graph.GenEdge(vertex_t, vertex_x); graph.GenEdge(vertex_x, vertex_t);
  graph.GenEdge(vertex_t, vertex_u); graph.GenEdge(vertex_u, vertex_t);
  graph.GenEdge(vertex_u, vertex_x); graph.GenEdge(vertex_x, vertex_u);
  graph.GenEdge(vertex_u, vertex_y); graph.GenEdge(vertex_y, vertex_u);
  graph.GenEdge(vertex_w, vertex_x); graph.GenEdge(vertex_x, vertex_w);
  graph.GenEdge(vertex_x, vertex_y); graph.GenEdge(vertex_y, vertex_x);

  // print all vertices and its their adjacency lists
  graph.PrintGraph();

  // do breadth-first search [BFS 시작]
  {
    // container that stores distance for each vertex
    // 각 노드의 거리 저장하는 dict 
    std::map<Vertex*, unsigned int> distance;

    // compute distance from vertex_s (노드간 거리 계산)
    BFS(vertex_s, distance);

    // print computed distance (계산된 거리 출력)
    std::cout << "=============== BFS Result ===============" << std::endl;
    for (auto vertex : graph.GetVertices()) {
      std::cout << "Vertex " << vertex->GetName() << ", ";
      std::cout << "Distance: " << distance[vertex] << std::endl;
    }
  }
}

/*--------------------------- DFS 보여주는 함수 --------------------------*/
void ShowcaseDFS() {
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
  graph.GenEdge(vertex_u, vertex_v);
  graph.GenEdge(vertex_u, vertex_x);
  graph.GenEdge(vertex_v, vertex_y);
  graph.GenEdge(vertex_w, vertex_y);
  graph.GenEdge(vertex_w, vertex_z);
  graph.GenEdge(vertex_x, vertex_v);
  graph.GenEdge(vertex_y, vertex_x);
  graph.GenEdge(vertex_z, vertex_z);

  // print all vertices and its their adjacency lists
  graph.PrintGraph();

  // do depth-first search [DFS 함수 시작]
  {
    // initial timestamp starts from zero
    unsigned int timestamp = 0;

    // container that stores discovery time of each vertex
    // 노드 visit된 시간 저장하는 dict
    std::map<Vertex*, unsigned int> discovery_time;

    // container that stores finishing time of each vertex
    // 노드 visit 끝난 시간 기록하는 dict
    std::map<Vertex*, unsigned int> finishing_time;

    // do DFS for all vertices in the graph
    for (auto vertex : graph.GetVertices()) {
      // call DFS only when the vertex is not discovered once
      if (discovery_time.find(vertex) == discovery_time.end()) {
        DFS(vertex, timestamp, discovery_time, finishing_time);
      }
    }

    // print discovery time and finishing time of vertices
    std::cout << "=============== DFS Result ===============" << std::endl;
    for (auto vertex : graph.GetVertices()) {
      std::cout << "Vertex " << vertex->GetName() << ", ";
      std::cout << "Discovery time: " << discovery_time[vertex] << ", ";
      std::cout << "Finishing time: " << finishing_time[vertex] << std::endl;
    }
  }
}
/*--------------------------- main 함수 시작 --------------------------*/
int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " [selector]" << std::endl;
    std::cout << "Selector 0: Showcase graph" << std::endl;
    std::cout << "Selector 1: Showcase Breadth-First Search" << std::endl;
    std::cout << "Selector 2: Showcase Depth-First Search" << std::endl;
    return EXIT_FAILURE;
  }

// selector에 사용자 입력 받기 
  int selector = atoi(argv[1]);
  switch (selector) { // 사용자 입력에 따라 적절한 함수 실행
  case 0: ShowcaseGraph(); break;
  case 1: ShowcaseBFS(); break;
  case 2: ShowcaseDFS(); break;
  }

  return EXIT_SUCCESS;
}
