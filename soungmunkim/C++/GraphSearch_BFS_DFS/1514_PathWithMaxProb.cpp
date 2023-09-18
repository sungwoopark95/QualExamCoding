/*
[undirected graph sorce -> target 까지의 max prob을 반환하기]
DFS + Relaxation 방법으로 품

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
#include <unordered_map>
#include <algorithm>

using namespace std;

    // 최대 확률을 찾기 위한 함수
    unordered_map<int, double> shortestpath(const unordered_map<int, vector<pair<int, double>>>& G, int s) {
        unordered_map<int, double> distances;

        // distances를 -inf로 초기화
        for (const auto& key : G) {
            distances[key.first] = -numeric_limits<double>::infinity();
        }

        // 시작 노드는 확률 1로 초기화
        distances[s] = 1;
        vector<int> stack = {s};

        while (!stack.empty()) {
            int cur = stack.back();
            stack.pop_back();

            // 연결된 노드들의 확률을 업데이트
            for (const auto& [node, weight] : G.at(cur)) {
                if (distances[node] < distances[cur] * weight) {
                    distances[node] = distances[cur] * weight;
                    stack.push_back(node);
                }
            }
        }

        return distances;
    }

// 최대 확률을 찾는 함수
double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
    // 그래프를 표현할 unordered_map 생성 (키는 시작 노드, 값은 (도착 노드, 확률)의 pair)
    unordered_map<int, vector<pair<int, double>>> G;
    
    // 주어진 간선 정보로 그래프 구성 (양방향)
    for (int i = 0; i < edges.size(); i++) {
        int from_ = edges[i][0];
        int to = edges[i][1];
        
        // 주어진 확률과 함께 그래프에 정보 저장
        G[from_].push_back({to, succProb[i]});
        G[to].push_back({from_, succProb[i]});
    }

    unordered_map<int, double> dist = shortestpath(G, start_node);
    
    // 종료 노드의 확률이 업데이트 되지 않았으면 0 반환
    if (dist[end_node] == -numeric_limits<double>::infinity()) {
        return 0;
    } else {
        return dist[end_node];
    }
}

int main() {
    // 첫번째 테스트 케이스
    int n1 = 3;
    vector<vector<int>> edges1 = {{0,1},{1,2},{0,2}};
    vector<double> succProb1 = {0.5, 0.5, 0.2};
    int start1 = 0, end1 = 2;
    double result1 = maxProbability(n1, edges1, succProb1, start1, end1);
    cout << "Result for the first test case: " << result1 << endl;

    // 두번째 테스트 케이스
    int n2 = 3;
    vector<vector<int>> edges2 = {{0,1}};
    vector<double> succProb2 = {0.5};
    int start2 = 0, end2 = 2;
    double result2 = maxProbability(n2, edges2, succProb2, start2, end2);
    cout << "Result for the second test case: " << result2 << endl;

    return 0;
}