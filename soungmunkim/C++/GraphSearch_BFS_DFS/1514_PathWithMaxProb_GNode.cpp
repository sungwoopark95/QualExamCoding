/*
[undirected graph sorce -> target 까지의 max prob을 반환하기]
DFS + Relaxation 방법으로 품
!! GNode or Vertex 버전 !!

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
#include <stack>
#include <limits>

using namespace std;

// 그래프 노드를 표현하는 클래스
class GNode {
public:
    int id;  // 노드의 고유 아이디
    double distance;  // 노드까지의 최대 확률 (거리)
    vector<pair<GNode*, double>> edges;  // 이 노드에서부터 연결된 다른 노드들과 그 연결의 가중치를 저장하는 벡터

    // 생성자
    GNode(int _id) : id(_id), distance(-std::numeric_limits<double>::infinity()) {}  // 초기 거리값은 -std::numeric_limits<double>::infinity()로 설정

    // 이 노드에서 다른 노드로 연결(간선) 추가하는 함수
    void addEdge(GNode* node, double weight) {
        edges.push_back({node, weight});
    }
};

// 최단 경로(최대 확률)를 찾는 함수
void shortestPath(vector<GNode*>& nodes, GNode* s) {
    s->distance = 1;  // 시작 노드의 확률을 1로 설정
    stack<GNode*> stk;  // 노드를 저장할 스택
    stk.push(s);  // 시작 노드를 스택에 추가

    while (!stk.empty()) {
        GNode* cur = stk.top();  // 현재 노드를 스택에서 가져옴
        stk.pop();

        // 현재 노드와 연결된 모든 인접 노드에 대해
        for (auto& [adj, weight] : cur->edges) {
            if (adj->distance < cur->distance * weight) {  // 확률을 업데이트할 경우
                adj->distance = cur->distance * weight;
                stk.push(adj);  // 인접 노드를 스택에 추가
            }
        }
    }
}

// 최대 확률을 찾는 메인 함수
double maxProb(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
    vector<GNode*> nodes;

    // 그래프의 노드 초기화
    for (int i = 0; i < n; i++) {
        nodes.push_back(new GNode(i));
    }

    // 그래프의 간선 정보 추가
    for (int i = 0; i < edges.size(); i++) {
        nodes[edges[i][0]]->addEdge(nodes[edges[i][1]], succProb[i]);
        nodes[edges[i][1]]->addEdge(nodes[edges[i][0]], succProb[i]);
    }

    shortestPath(nodes, nodes[start_node]);  // 최단 경로(최대 확률) 탐색

    double result = nodes[end_node]->distance;  // 결과값 저장
    if (result == -std::numeric_limits<double>::infinity()) return 0.0;  // 초기값과 같으면 0 반환

    // 메모리 해제
    for (GNode* node : nodes) {
        delete node;
    }

    return result;  // 최대 확률 반환
}

int main() {
    int n;
    vector<vector<int>> edges;
    vector<double> succProb;
    int start, end;

    // 첫 번째 테스트 케이스
    n = 3;
    edges = {{0,1},{1,2},{0,2}};
    succProb = {0.5,0.5,0.2};
    start = 0;
    end = 2;
    cout << maxProb(n, edges, succProb, start, end) << endl;

    // 두 번째 테스트 케이스
    n = 3;
    edges = {{0,1}};
    succProb = {0.5};
    start = 0;
    end = 2;
    cout << maxProb(n, edges, succProb, start, end) << endl;

    return 0;
}












/*------------------ add edge 함수 없이 그냥 GNode만 추가해서 구현한 버전 ------------------*/
// class GNode {
// public:
//     int id; // 노드의 고유 아이디
//     double distance; // 노드까지의 최대 확률 (거리)
//     GNode(int _id, double d=-std::numeric_limits<double>::infinity()) : id(_id), distance(d) {} // 생성자
// };

// void shortestPath(unordered_map<GNode*, vector<pair<GNode*, double>>>& graph, GNode* s) {
//     // 그래프의 모든 노드 초기화
//     for (auto& [key, _] : graph) {
//         key->distance = -std::numeric_limits<double>::infinity();
//     }

//     // 시작 노드 거리 설정
//     s->distance = 1;
//     vector<GNode*> stack;
//     stack.push_back(s);

//     // dfs + relaxation으로 업뎃하기
//     while (!stack.empty()) {
//         GNode* cur = stack.back();
//         stack.pop_back();

//         for (auto& [adj, weight] : graph[cur]) {
//             if (adj->distance < cur->distance * weight) {
//                 adj->distance = cur->distance * weight;
//                 stack.push_back(adj);
//             }
//         }
//     }
// }

// double maxProb(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
//     unordered_map<int, GNode*> nodes;
//     unordered_map<GNode*, vector<pair<GNode*, double>>> G;

//     // 그래프 초기화 및 GNode 인스턴스 생성
//     for (int i = 0; i < n; i++) {
//         nodes[i] = new GNode(i);
//         G[nodes[i]] = {};
//     }

//     // 그래프에 간선 정보 추가
//     for (int i = 0; i < edges.size(); i++) {
//         GNode* from_ = nodes[edges[i][0]];
//         GNode* to = nodes[edges[i][1]];
//         G[from_].push_back({to, succProb[i]});
//         G[to].push_back({from_, succProb[i]});
//     }

//     shortestPath(G, nodes[start_node]);

//     if (nodes[end_node]->distance == -std::numeric_limits<double>::infinity()) return 0;
//     else return nodes[end_node]->distance;
// }