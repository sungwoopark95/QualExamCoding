/*
[undirected graph sorce -> target 까지의 max prob을 반환하기]
DFS + Relaxation 방법으로 품
!! GNode버전 !!

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

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

// 그래프의 노드를 표현하기 위한 구조체 선언
typedef struct GNode {
    int id;                     // 노드의 고유 아이디
    double distance;            // 노드까지의 최대 확률 (거리)
    struct Edge* edges;         // 이 노드와 연결된 간선들의 정보
    int edge_count;             // 연결된 간선의 수
} GNode;

// 간선 정보를 표현하기 위한 구조체 선언
typedef struct Edge {
    GNode* node;                // 이 간선과 연결된 노드의 포인터
    double weight;              // 이 간선의 가중치
} Edge;

// 간선을 추가하는 함수
void addEdge(GNode* node, GNode* target, double weight) {
    node->edges = (Edge*)realloc(node->edges, sizeof(Edge) * (node->edge_count + 1));
    node->edges[node->edge_count].node = target;
    node->edges[node->edge_count].weight = weight;
    node->edge_count++;
}

// 최단 경로를 찾는 함수
void shortestPath(GNode** nodes, int num_nodes, GNode* s) {
    s->distance = 1.0;            // 시작 노드의 확률을 1로 설정

    GNode** stack = (GNode**)malloc(sizeof(GNode*) * num_nodes);
    int top = 0;
    stack[top++] = s;            // 시작 노드를 스택에 추가

    while (top > 0) {
        GNode* cur = stack[--top];

        // 현재 노드와 연결된 모든 노드에 대한 로직
        for (int i = 0; i < cur->edge_count; i++) {
            GNode* adj = cur->edges[i].node;
            double weight = cur->edges[i].weight;

            if (adj->distance < cur->distance * weight) {
                adj->distance = cur->distance * weight;
                stack[top++] = adj;
            }
        }
    }

    free(stack);
}

// 최대 확률을 계산하는 함수
double maxProb(int n, int** edges, int edges_count, double* succProb, int start_node, int end_node) {
    GNode** nodes = (GNode**)malloc(sizeof(GNode*) * n);

    for (int i = 0; i < n; i++) {
        nodes[i] = (GNode*)malloc(sizeof(GNode));
        nodes[i]->id = i;
        nodes[i]->distance = -DBL_MAX;
        nodes[i]->edges = NULL;
        nodes[i]->edge_count = 0;
    }

    for (int i = 0; i < edges_count; i++) {
        addEdge(nodes[edges[i][0]], nodes[edges[i][1]], succProb[i]);
        addEdge(nodes[edges[i][1]], nodes[edges[i][0]], succProb[i]);
    }

    shortestPath(nodes, n, nodes[start_node]);

    double result = nodes[end_node]->distance;

    // 동적으로 할당된 메모리 해제
    for (int i = 0; i < n; i++) {
        free(nodes[i]->edges);
        free(nodes[i]);
    }
    free(nodes);

    if (result == -DBL_MAX) return 0.0;   // 확률이 초기값과 같으면 0 반환
    return result;
}

int main() {
    int n;
    int** edges;
    double* succProb;
    int start, end;

    n = 3;
    edges = (int**)malloc(sizeof(int*) * 3);
    edges[0] = (int[]){0, 1};
    edges[1] = (int[]){1, 2};
    edges[2] = (int[]){0, 2};
    succProb = (double[]){0.5, 0.5, 0.2};
    start = 0;
    end = 2;
    printf("%lf\n", maxProb(n, edges, 3, succProb, start, end));

    n = 3;
    free(edges);
    edges = (int**)malloc(sizeof(int*) * 1);
    edges[0] = (int[]){0, 1};
    succProb = (double[]){0.5};
    start = 0;
    end = 2;
    printf("%lf\n", maxProb(n, edges, 1, succProb, start, end));

    free(edges);
    return 0;
}
