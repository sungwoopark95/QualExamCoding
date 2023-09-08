/*
[dfs로 graph 구현하기 with colors]
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 100  // 그래프의 최대 노드 수

// 그래프 노드를 표현하기 위한 구조체
typedef struct GNode {
    char id[10];            // 노드의 고유 ID (문자열 형태)
    char color;             // 노드의 색상 ('W': 흰색, 'G': 회색, 'B': 검은색)
    int start, finish;      // DFS 탐색에서의 시작 시간과 종료 시간
    struct GNode* parent;   // 부모 노드의 포인터
} GNode;

// 그래프를 표현하기 위한 구조체
typedef struct {
    GNode* nodes[MAX_NODES];               // 그래프의 모든 노드를 저장하는 배열
    GNode* adjList[MAX_NODES][MAX_NODES];  // 인접 리스트
    int nodeCount;                         // 그래프의 노드 수
} Graph;

Graph graph;  // 전역 그래프 변수
int time_count = 0;  // DFS 탐색에서의 전체 시간을 계산하는 변수

// 그래프의 노드 정보를 출력하는 함수
void printNode(GNode* node) {
    printf("(%s, %c, (%d, %d), ", node->id, node->color, node->start, node->finish);
    if (node->parent) {
        printf("%s) ", node->parent->id);
    } else {
        printf("None) ");
    }
}

// 그래프의 정보를 출력하는 함수
void printGraph() {
    for (int i = 0; i < graph.nodeCount; i++) {
        printNode(graph.nodes[i]);
        printf(": ");
        for (int j = 0; graph.adjList[i][j] != NULL; j++) {
            printNode(graph.adjList[i][j]);
        }
        printf("\n");
    }
}

// DFS 탐색의 핵심 함수
void dfs_visit(GNode* u) {
    time_count++;
    u->start = time_count;
    u->color = 'G';

    printGraph();

    for (int i = 0; graph.adjList[u->id[0] - 'u'][i] != NULL; i++) {
        GNode* v = graph.adjList[u->id[0] - 'u'][i];
        if (v->color == 'W') {
            v->parent = u;
            dfs_visit(v);
        }
    }

    u->color = 'B';
    time_count++;
    u->finish = time_count;

    printGraph();
}

// 모든 노드에 대해 깊이 우선 탐색을 시작하는 함수
void dfs() {
    for (int i = 0; i < graph.nodeCount; i++) {
        graph.nodes[i]->color = 'W';
        graph.nodes[i]->start = -1;
        graph.nodes[i]->finish = -1;
        graph.nodes[i]->parent = NULL;
    }

    printGraph();

    for (int i = 0; i < graph.nodeCount; i++) {
        GNode* u = graph.nodes[i];
        if (u->color == 'W') {
            dfs_visit(u);
        }
    }
}

int main() {
    GNode u = {"u"};
    GNode v = {"v"};
    GNode w = {"w"};
    GNode x = {"x"};
    GNode y = {"y"};
    GNode z = {"z"};

    graph.nodes[0] = &u;
    graph.nodes[1] = &v;
    graph.nodes[2] = &w;
    graph.nodes[3] = &x;
    graph.nodes[4] = &y;
    graph.nodes[5] = &z;
    graph.nodeCount = 6;

    graph.adjList[0][0] = &v;
    graph.adjList[0][1] = &x;

    graph.adjList[1][0] = &y;

    graph.adjList[2][0] = &y;
    graph.adjList[2][1] = &z;

    graph.adjList[3][0] = &v;

    graph.adjList[4][0] = &x;

    graph.adjList[5][0] = &z;

    printGraph();
    dfs();

    return 0;
}
