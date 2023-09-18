/*
[전체노드 visit되는 최소한의 시간 구하기 (Directed graph with weight)]
-> Shortest path 찾는 것처럼 푼 뒤 가장 max인 weight 뽑기 (다 들린 후 min time)

You are given a network of n nodes, labeled from 1 to n. 
You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), 
where ui is the source node, vi is the target node, 
and wi is the time it takes for a signal to travel from source to target.

We will send a signal from a given node k. 
Return the minimum time it takes for all the n nodes to receive the signal. 
If it is impossible for all the n nodes to receive the signal, return -1.

(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test                                         
Enter n: 4
Enter k: 2
Enter the times in the format [[from,to,weight],...]:
[[2,1,1],[2,3,1],[3,4,1]]
Minimum time for all nodes to receive the signal: 2

(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test
Enter n: 4
Enter k: 2
Enter the times in the format [[from,to,weight],...]:
[2,1,1],[2,3,1],[3,4,1
Minimum time for all nodes to receive the signal: 2

(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test
Enter n: 2
Enter k: 2
Enter the times in the format [[from,to,weight],...]:
[1,2,1]
Minimum time for all nodes to receive the signal: -1
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <limits>
#include <algorithm>

using namespace std;

// 그래프 노드를 표현하는 클래스
class GNode {
public:
    int id;  // 노드의 고유 번호
    double time;  // 노드까지의 시간
    vector<pair<int, double>> edges;  // 연결된 다른 노드들과 그 연결의 시간을 저장하는 벡터

    // 생성자
    GNode(int _id) : id(_id), time(std::numeric_limits<double>::infinity()) {}  // 초기 시간값은 무한대로 설정

    // 연결 추가하는 함수
    void addEdge(int to, double weight) {
        edges.push_back(make_pair(to, weight));  // 주어진 목적지 및 가중치를 edges에 추가
    }
};

// 최단 경로 계산 함수
void shortestPath(unordered_map<int, GNode*>& nodes, GNode* s) {
    s->time = 0;  // 시작 노드의 시간을 0으로 설정
    stack<GNode*> stk;  // DFS를 위한 스택
    stk.push(s);  // 시작 노드를 스택에 추가

    while (!stk.empty()) {
        GNode* cur = stk.top();  // 현재 노드 추출
        stk.pop();

        for (auto& [to, weight] : cur->edges) {  // 현재 노드의 모든 인접 노드에 대해
            if (nodes[to]->time > cur->time + weight) {  // 더 짧은 경로가 발견된 경우
                nodes[to]->time = cur->time + weight;  // 시간 업데이트
                stk.push(nodes[to]);  // 해당 노드를 스택에 추가
            }
        }
    }
}

double networkDelayTime(vector<vector<int>>& times, int n, int k) {
    unordered_map<int, GNode*> nodes;  // 노드 저장을 위한 해쉬맵

    // 모든 노드를 초기화하고 딕셔너리에 저장
    for (int i = 1; i <= n; ++i) {
        nodes[i] = new GNode(i);
    }

    // 인접 리스트 생성
    for (const auto& time : times) {
        int from_ = time[0];
        int to = time[1];
        double weight = time[2];

        nodes[from_]->addEdge(to, weight);  // 각 노드에 연결 추가
    }

    // DFS를 사용하여 시작 노드에서 다른 노드로의 최단 시간을 계산
    shortestPath(nodes, nodes[k]);

    // 모든 노드의 최대 시간을 계산
    double max_time = -1;
    for (int i = 1; i <= n; ++i) {
        max_time = max(max_time, nodes[i]->time);  // 최대 시간 계산
    }

    // 모든 노드에 도달할 수 없는 경우 -1 반환
    for (int i = 1; i <= n; ++i) {
        if (nodes[i]->time == std::numeric_limits<double>::infinity()) {
            return -1;  // 무한대인 경우는 도달할 수 없는 경우
        }
    }

    return max_time;  // 최대 지연 시간 반환
}

int main() {
    vector<vector<int>> times = {{1, 2, 1}, {2, 3, 2}, {1, 3, 4}};
    int n = 3;
    int k = 1;

    cout << networkDelayTime(times, n, k) << endl;  // 네트워크 지연 시간 출력

    return 0;
}
