/*
[Dijkstra algorithm 구현하기] shortest path 프린트하기 

negative weight cycle 없다는 가정
*/


#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <limits>

using namespace std;

// Vertex 구조체 정의: 그래프의 각 정점에 대한 정보를 나타냅니다.
struct Vertex {
    int id;  // 정점의 고유 ID
    double d = numeric_limits<double>::infinity();  // 시작 정점에서의 거리 (초기값은 무한대)
    Vertex* pi = nullptr;  // 이전 정점 (즉, 최단 경로에서 현재 정점의 직전 정점)
};

// pair_hash 구조체 정의: std::pair에 대한 해시 함수를 정의합니다.
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);  // 첫 번째 원소에 대한 해시 값을 계산
        auto h2 = std::hash<T2>{}(p.second); // 두 번째 원소에 대한 해시 값을 계산
        return h1 ^ h2;  // 두 해시 값을 XOR 연산하여 반환
    }
};

// 초기화 함수: 시작 정점을 받아 모든 정점의 거리와 이전 정점을 초기화합니다.
void INITIALIZE_SINGLE_SOURCE(vector<Vertex*>& G, Vertex* s) {
    for (Vertex* v : G) {
        v->d = numeric_limits<double>::infinity();  // 모든 정점의 거리를 무한대로 설정
        v->pi = nullptr;  // 모든 정점의 이전 정점을 nullptr로 설정
    }
    s->d = 0;  // 시작 정점의 거리는 0으로 설정
}

// Relax 함수: 두 정점과 가중치 맵을 받아서, 필요한 경우 경로를 갱신합니다.
void RELAX(Vertex* u, Vertex* v, unordered_map<pair<Vertex*, Vertex*>, double, pair_hash>& weights) {
    auto it = weights.find({u, v});  // u에서 v로 가는 간선의 가중치를 찾습니다.
    if (it != weights.end() && v->d > u->d + it->second) {
        v->d = u->d + it->second;  // 거리 갱신
        v->pi = u;  // 이전 정점 갱신
    }
}

// Dijkstra 알고리즘 구현 함수
void DIJKSTRA(vector<Vertex*>& G, unordered_map<pair<Vertex*, Vertex*>, double, pair_hash>& weights, Vertex* s, unordered_map<Vertex*, vector<Vertex*>>& Adj) {
    INITIALIZE_SINGLE_SOURCE(G, s);  // 초기화 실행
    vector<Vertex*> S;  // 이미 처리된 정점들의 집합
    auto compare = [](Vertex* left, Vertex* right) { return left->d > right->d; };  // 비교 함수: 거리를 기준으로 정렬
    priority_queue<Vertex*, vector<Vertex*>, decltype(compare)> Q(compare);  // 우선순위 큐 정의

    for (Vertex* u : G) {
        Q.push(u);  // 모든 정점을 우선순위 큐에 삽입
    }

    while (!Q.empty()) {
        Vertex* u = Q.top();  // 현재 가장 거리가 짧은 정점을 추출
        Q.pop();
        S.push_back(u);  // 처리된 정점들의 집합에 추가
        for (Vertex* v : Adj[u]) {  // 인접한 모든 정점에 대해
            double old_distance = v->d;
            RELAX(u, v, weights);  // Relax 함수 호출
            if (v->d < old_distance) {
                Q.push(v);  // 거리가 갱신된 경우 우선순위 큐에 다시 삽입
            }
        }
    }
}

int main() {
    // Sample usage
    Vertex v1, v2, v3, v4;
    v1.id = 1;
    v2.id = 2;
    v3.id = 3;
    v4.id = 4;

    vector<Vertex*> G = {&v1, &v2, &v3, &v4};  // 그래프 정점 집합
    unordered_map<pair<Vertex*, Vertex*>, double, pair_hash> weights = {  // 각 간선의 가중치 정보
        {{&v1, &v2}, 5},
        {{&v1, &v3}, 3},
        {{&v2, &v4}, 2},
        {{&v3, &v4}, 1}
    };

    unordered_map<Vertex*, vector<Vertex*>> Adj = {  // 각 정점의 인접 정점 리스트
        {&v1, {&v2, &v3}},
        {&v2, {&v4}},
        {&v3, {&v4}},
        {&v4, {}}
    };

    DIJKSTRA(G, weights, &v1, Adj);  // Dijkstra 알고리즘 실행

    // 결과 출력 (shortest path 프린트)
    for (Vertex* v : G) {
        cout << "Distance from v1 to v" << v->id << ": " << v->d << endl;  // 각 정점까지의 최단 거리 출력
    }

    return 0;
}

