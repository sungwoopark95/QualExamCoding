/*
Graph를 만들기 위해선 vertex(node)와 edge가 필요함
(node1, node2) -> graph 안에 있는 edge
*/

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
*/
#pragma once

#include <string>
#include <vector>
/*---------------------------------- Vertex(Node) ---------------------------------*/
class Vertex {
public:
  // 이름을 받아 Vertex 객체를 생성하는 constructor (node 존재를 만듦)
  Vertex(std::string name) {
    name_ = name;
  }

  // 정점(node)의 이름을 반환하는 메소드 (구현됨)
  std::string GetName() { return name_; }
  
  // 인접한 정점(node)들의 목록을 반환하는 메소드 (구현됨)
  std::vector<Vertex*> GetAdjacencyList() { return adjacency_list_; }
  // Vertex*로 구성된 vector임 (*사용함으로 virtual이나 객체 연결이 쉬움)

  // 인접한 정점(node) 목록에 정점을 추가하는 메소드 (append nodes)
  void AddToAdjacentList(Vertex* vertex);

private:
  std::string name_;  // 정점(node)의 이름
  std::vector<Vertex*> adjacency_list_;  // 인접한 정점(node)들의 목록
};

/*---------------------------------- Graph (make edges) ---------------------------------*/

// 그래프를 나타내는 클래스
class Graph {
public:
  // 기본 생성자
  Graph() {}
  
  // 소멸자 (deconstructor는 구현해야함!)
  ~Graph();

  // 이름을 받아 새로운 node을 생성하는 메소드 (create node)
  Vertex* GenVertex(std::string name);
  
  // 시작node와 끝 node를 받아 그 사이에 edge를 생성하는 메소드 (create edge)
  void GenEdge(Vertex* start, Vertex* end);

  // 그래프의 모든 nodes의 목록을 반환하는 메소드 (구현됨)
  std::vector<Vertex*> GetVertices() { return vertices_; }
  
  // 그래프의 nodes의 수를 반환하는 메소드 (구현됨)
  size_t GetNumVertices() { return vertices_.size(); }

  // 그래프의 정보를 출력하는 메소드
  void PrintGraph();

private:
  std::vector<Vertex*> vertices_;  // 그래프 내의 모든 edges의 목록
};
