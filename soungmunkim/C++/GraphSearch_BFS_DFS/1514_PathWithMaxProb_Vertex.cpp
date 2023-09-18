/*
[undirected graph sorce -> target 까지의 max prob을 반환하기]
DFS + Relaxation 방법으로 품
!!  Vertex 버전 !!

Input: n = 3, edges = [[0,1],[1,2],[0,2]], 
succProb = [0.5,0.5,0.2], start = 0, end = 2
Output: 0.25000
Explanation: There are two paths from start to end, 
one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.

Input: n = 3, edges = [[0,1]], 
succProb = [0.5], start = 0, end = 2
Output: 0.00000
Explanation: There is no path between 0 and 2.

(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % g++ -std=c++17 1514_PathWithMaxProb.cpp -o test                                        
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test
Result for the first test case: 0.25
Result for the second test case: 0
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <limits>

using namespace std;

class Vertex {  // 'Vertex' 클래스 정의
public:
    int id;  // 정점의 ID
    string name;  // 정점의 이름
    double distance;  // 정점까지의 거리(확률 값)
    vector<pair<Vertex*, double>> edges;  // 연결된 간선들의 리스트
    vector<Vertex*> adjacency_list_;  // 인접한 정점들의 리스트

    Vertex(int _id, string _name) : id(_id), name(_name), distance(-std::numeric_limits<double>::infinity()) {}  // 생성자 정의
    
    void addEdge(Vertex* vertex, double weight) {  // 간선 추가 메서드
        edges.push_back({vertex, weight});
    }
    
    void AddToAdjacentList(Vertex* vertex) {  // 인접한 정점 추가 메서드
        adjacency_list_.push_back(vertex);
    }
};

class Graph {  // 'Graph' 클래스 정의
private:
    vector<Vertex*> vertices_;  // 정점들의 리스트

public:
    ~Graph() {  // 소멸자
        for (auto vertex : vertices_) {  // 각 정점에 대하여
            delete vertex;  // 메모리 해제
        }
        vertices_.clear();  // 정점 리스트 초기화
    }

    Vertex* GenVertex(string name) {  // 정점 생성 메서드
        Vertex* vertex = new Vertex(vertices_.size(), name);  // 새 정점 생성
        vertices_.push_back(vertex);  // 정점 리스트에 추가
        return vertex;  // 생성된 정점 반환
    }

    void GenEdge(Vertex* start, Vertex* end, double weight) {  // 간선 생성 메서드
        start->AddToAdjacentList(end);  // 시작 정점의 인접 리스트에 종료 정점 추가
        start->addEdge(end, weight);  // 시작 정점에서 종료 정점으로의 간선 추가
        end->addEdge(start, weight);  // 종료 정점에서 시작 정점으로의 간선 추가 (무방향 그래프 가정)
    }

    vector<Vertex*>& GetVertices() {  // 정점들의 리스트 반환 메서드
        return vertices_;
    }
};

void shortestPath(vector<Vertex*>& vertices, Vertex* s) {  // 최단 경로 (또는 최대 확률) 계산 함수
    s->distance = 1;  // 시작 정점의 거리(확률) 초기화
    stack<Vertex*> stk;  // 스택 생성
    stk.push(s);  // 시작 정점 스택에 푸시

    while (!stk.empty()) {  // 스택이 비어있지 않은 동안
        Vertex* cur = stk.top();  // 현재 정점 = 스택의 상단 요소
        stk.pop();  // 스택의 상단 요소 팝

        for (auto& [adj, weight] : cur->edges) {  // 각 인접 정점에 대하여
            if (adj->distance < cur->distance * weight) {  // 거리(확률) 업데이트 필요 시
                adj->distance = cur->distance * weight;  // 거리(확률) 업데이트
                stk.push(adj);  // 인접 정점 스택에 푸시
            }
        }
    }
}

double maxProb(Graph& graph, int start_node, int end_node) {  // 최대 확률 계산 함수
    vector<Vertex*> vertices = graph.GetVertices();  // 정점들의 리스트 가져오기

    shortestPath(vertices, vertices[start_node]);  // 최단 경로 (또는 최대 확률) 계산

    double result = vertices[end_node]->distance;  // 결과값 저장
    if (result == -std::numeric_limits<double>::infinity()) return 0.0;  // 초기값 그대로면 0 반환

    return result;  // 최대 확률 반환
}

int main() {
    Graph graph;  // 그래프 객체 생성
    vector<Vertex*> vertices;  // 정점들의 리스트
    int start, end;

    for (int i = 0; i < 3; i++) {
        vertices.push_back(graph.GenVertex(to_string(i)));  // 정점 생성 및 리스트에 추가
    }

    // 간선들 생성
    graph.GenEdge(vertices[0], vertices[1], 0.5);
    graph.GenEdge(vertices[1], vertices[2], 0.5);
    graph.GenEdge(vertices[0], vertices[2], 0.2);
    start = 0;
    end = 2;
    cout << maxProb(graph, start, end) << endl;  // 최대 확률 출력

    // 두 번째 테스트 케이스를 위한 초기화
    Graph graph2;
    vertices.clear();

    for (int i = 0; i < 3; i++) {
        vertices.push_back(graph2.GenVertex(to_string(i))); // string으로 바꿈
    }

    graph2.GenEdge(vertices[0], vertices[1], 0.5);
    start = 0;
    end = 2;
    cout << maxProb(graph2, start, end) << endl;  // 최대 확률 출력

    return 0;
}
