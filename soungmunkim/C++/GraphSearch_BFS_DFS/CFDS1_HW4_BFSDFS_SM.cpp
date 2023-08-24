/*
[Graph class 사용해서 BFS 구현]
<C++ 11버전 이상으로 돌려야 auto warning 없이 돌아감>
g++ -std=c++17 CFDS1_HW4_1to3_main.cpp CFDS1_HW4_1_Graph_SM.cpp CFDS1_HW4_2to3_BFSDFS_SM.cpp -o Graph

void BFS(Vertex* start, std::map<Vertex*, unsigned int> &distance);
    첫번째 input으로 BFS를 시작할 vertex instance 받음
    두번째 input으로 search한 vertex들의 distance 저장하는 distance dict 만들기

< OUTPUT>
============== Defined Graph ==============
Vertexr, Adjacency List: Vertex s, Vertex v
Vertexs, Adjacency List: Vertex r, Vertex w
Vertext, Adjacency List: Vertex w, Vertex x, Vertex u
Vertexu, Adjacency List: Vertex t, Vertex x, Vertex y
Vertexv, Adjacency List: Vertex r
Vertexw, Adjacency List: Vertex s, Vertex t, Vertex x
Vertexx, Adjacency List: Vertex t, Vertex u, Vertex w, Vertex y
Vertexy, Adjacency List: Vertex u, Vertex x
=============== BFS Result ===============
Vertex r, Distance: 1
Vertex s, Distance: 0
Vertex t, Distance: 2
Vertex u, Distance: 3
Vertex v, Distance: 2
Vertex w, Distance: 1
Vertex x, Distance: 2
Vertex y, Distance: 3

[Graph class 사용해서 DFS 구현]
void DFS(Vertex* vertex, unsigned int &timestamp,
    std::map<Vertex*, unsigned int> &discovery_time, 
    std::map<Vertex*, unsigned int> &finishing_time);
        첫번째 input: DFS를 시작할 vertex instance 받음
        두번째 input: discovery time, finishing time 기록을 위한 시작 time 입력 받음
        세번째 input: search한 vertex들의 discovery time 저장
        네번째 intpu: search한 vertex들의 finishing time 저장

<OutPut>
============== Defined Graph ==============
Vertexu, Adjacency List: Vertex v, Vertex x
Vertexv, Adjacency List: Vertex y
Vertexw, Adjacency List: Vertex y, Vertex z
Vertexx, Adjacency List: Vertex v
Vertexy, Adjacency List: Vertex x
Vertexz, Adjacency List: Vertex z
=============== DFS Result ===============
Vertex u, Discovery time: 1, Finishing time: 8
Vertex v, Discovery time: 2, Finishing time: 7
Vertex w, Discovery time: 9, Finishing time: 12
Vertex x, Discovery time: 4, Finishing time: 5
Vertex y, Discovery time: 3, Finishing time: 6
Vertex z, Discovery time: 10, Finishing time: 11
*/

#include <iostream>
#include <stdbool.h>
#include <vector>
#include <queue>
#include <utility>
#include "CFDS1_HW4_BFSDFS.h"

using namespace std;
/*---------------------- BFS 함수 시작 --------------------*/
void BFS(Vertex* start, map<Vertex*, unsigned int> &distance){
    Vertex* vertex;

    // queue에 search한 vetex들과 distance 저장한 pair들 넣기
    queue<pair<Vertex*, unsigned int> > q;
    
    // 해당 node visit 했는지 체크하는 visited dict 만들기
    map<Vertex*, bool> visited;

    // root node는(첫 시작) distance가 0임
    unsigned int curr_dist = 0;

    /*  BFS로 Search 시작 */
    // root node를 visited 했다고 표시하기
    visited[start] = true;

    // queue에 (root node, distance 0) pair append하기;
    // make_pair 가 알아서 type에 맞게 pair로 만들어줌
    q.push(make_pair(start, curr_dist));

    // queue가 빌때까지 연결된 노드 다 접근하기
    while (q.empty() == false) {
        // queue니까 pop(0): 앞부분 노드부터 보기
        vertex = q.front().first; // dict의 key 접근
        curr_dist = q.front().second; // dict의 value 접근

        q.pop(); // queue의 앞부분 지우기 

        for (auto adjacent: vertex->GetAdjacencyList()){
            if (visited[adjacent] == false) {
                visited[adjacent] = true;
                q.push(make_pair(adjacent, curr_dist+1));
            }
        }
        // start node에서 해당 vertex까지 거리 distance dict에 저장하기 
        distance[vertex] = curr_dist;
    }
}   

/*---------------------- DFS 함수 시작 --------------------*/
/*
예를 들어, 정점 A가 정점 B와 C에 연결되어 있고, DFS(A)가 호출되면 다음과 같은 동작 순서가 됩니다:

A의 발견 시간 기록
A의 인접 정점 B에 대해 DFS(B) 호출
B에 대한 모든 작업이 끝나고, DFS(B)가 반환됨
A의 다음 인접 정점 C에 대해 DFS(C) 호출
C에 대한 모든 작업이 끝나고, DFS(C)가 반환됨
A의 종료 시간 기록
*/
void DFS(Vertex* vertex, unsigned int &timestamp, // DFS_VISIT에 해당
  map<Vertex*, unsigned int> &discovery_time,
  map<Vertex*, unsigned int> &finishing_time) {
    // discovery time을 위해 timestamp +1 하기 
    timestamp += 1;

    // 현재 노드의 discovery time 저장하기 (discovery_time dict에)
    discovery_time[vertex] = timestamp;

    // 연결된 노드들을 계속 방문하기 (recursively call DFS)
    // adjacency list에 있는 vertices 계속 타고 들어가는 방식
    for (auto adjacent: vertex->GetAdjacencyList()){
        // 만약 해당 adjacent(node)를 발견 dict에서 찾았는데 끝까지 안 나오면 방문 안 된 것! 타고 들가기
        if (discovery_time.find(adjacent) == discovery_time.end()) {
            DFS(adjacent, timestamp, discovery_time, finishing_time);
        }
    }
    /*
    해당 노드 주변 노드들 다 방문하고 더 이상 없을때 다음 time을 finish time으로 기록
    그 다음 노드 호출함 (방문했지만 아직 안 끝난 노드)
    */ 
    // finishing time을 위해 timestamp +1 하기
    timestamp += 1;

    finishing_time[vertex] = timestamp;
  }


