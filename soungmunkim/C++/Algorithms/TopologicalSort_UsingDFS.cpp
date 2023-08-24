/*
[DFS 사용해서 topological order로 나타내기]

(base) soungmunkim@gimseongmun-ui-MacBookPro Algorithms % g++ -std=c++17 TopologicalSort_UsingDFS.cpp -o Sort
(base) soungmunkim@gimseongmun-ui-MacBookPro Algorithms % ./Sort 
해당 그래프의 위상 정렬 결과:
5 4 2 3 1 0 %                                            
*/

#include <iostream>
#include <list>
#include <stack>
using namespace std;

class Graph {
    int V;    // 정점의 개수
    list<int> *adj;    // 인접 리스트

    // DFS를 위한 도우미 함수
    void DFSUtil(int v, bool visited[], stack<int> &Stack);

public:
    Graph(int V);   // 생성자
    void addEdge(int v, int w);    // 간선 추가

    // 위상 정렬 함수
    void topologicalSort();
};

// 생성자: 정점의 개수를 입력으로 받아 그래프 초기화
Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

// 간선 추가 함수: v에서 w로의 간선을 그래프에 추가
void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // 정점 v에서 w로 가는 간선 추가
}

// DFS 도우미 함수
void Graph::DFSUtil(int v, bool visited[], stack<int> &Stack) {
    // 현재 노드를 방문 표시
    visited[v] = true;  

    // v와 인접한 모든 정점들에 대해서
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited, Stack);  // 인접한 정점에 대해 DFS 재귀 호출

    Stack.push(v);   // 정점 v를 스택에 푸시
}

// 위상 정렬 함수
void Graph::topologicalSort() {
    stack<int> Stack;  // 위상 정렬을 저장할 스택
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;  // 모든 정점들을 방문하지 않은 상태로 초기화

    // 모든 정점에 대해서 DFS 수행
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            DFSUtil(i, visited, Stack);

    // 스택의 위에서부터 요소를 하나씩 꺼내서 출력
    while (Stack.empty() == false) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}

int main() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout << "해당 그래프의 위상 정렬 결과:\n";
    g.topologicalSort();

    return 0;
}
