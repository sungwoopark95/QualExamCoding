/*
[BFS로 graph 구현하기 = 거리 계산 with colors]
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
    int distance;           // 시작 노드로부터의 거리
    struct GNode* parent;   // 부모 노드의 포인터
} GNode;

// 그래프를 표현하기 위한 구조체
typedef struct {
    GNode* nodes[MAX_NODES];        // 그래프의 모든 노드를 저장하는 배열
    GNode* adjList[MAX_NODES][MAX_NODES];  // 인접 리스트
    int nodeCount;                  // 그래프의 노드 수
} Graph;

// 그래프 초기화 함수
void initGraph(Graph* g) {
    g->nodeCount = 0;
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            g->adjList[i][j] = NULL;
        }
    }
}

// 그래프에 노드를 추가하는 함수
void addNode(Graph* g, GNode* node) {
    g->nodes[g->nodeCount++] = node;
}

// 그래프에 간선을 추가하는 함수 (양방향 간선)
void addEdge(Graph* g, GNode* src, GNode* dest) {
    int i;
    for (i = 0; g->adjList[src->id[0] - 'a'][i] != NULL; i++);
    g->adjList[src->id[0] - 'a'][i] = dest;

    for (i = 0; g->adjList[dest->id[0] - 'a'][i] != NULL; i++);
    g->adjList[dest->id[0] - 'a'][i] = src;
}

// 노드의 정보를 출력하는 함수
void printNode(GNode* node) {
    if (node->parent) {
        printf("(%s, %c, %d, %s) ", node->id, node->color, node->distance, node->parent->id);
    } else {
        printf("(%s, %c, %d, None) ", node->id, node->color, node->distance);
    }
}

// 그래프의 정보를 출력하는 함수
void printGraph(Graph* g) {
    for (int i = 0; i < g->nodeCount; i++) {
        printNode(g->nodes[i]);
        printf(": ");
        for (int j = 0; g->adjList[i][j] != NULL; j++) {
            printNode(g->adjList[i][j]);
        }
        printf("\n");
    }
    printf("=========================================\n");
}

// BFS 알고리즘을 수행하는 함수
void bfs(Graph* g, GNode* s) {
    for (int i = 0; i < g->nodeCount; i++) {
        g->nodes[i]->color = 'W';
        g->nodes[i]->distance = -1;
        g->nodes[i]->parent = NULL;
    }
    s->color = 'G';
    s->distance = 0;

    GNode* Q[MAX_NODES];  // BFS를 위한 큐
    int front = 0, rear = 0;
    Q[rear++] = s;

    printGraph(g);

    while (front < rear) {
        GNode* u = Q[front++];
        for (int i = 0; g->adjList[u->id[0] - 'a'][i] != NULL; i++) {
            GNode* v = g->adjList[u->id[0] - 'a'][i];
            if (v->color == 'W') {
                v->color = 'G';
                v->distance = u->distance + 1;
                v->parent = u;
                Q[rear++] = v;
            }
        }
        u->color = 'B';
        printGraph(g);
    }
}

int main() {
    Graph g;
    initGraph(&g);

    GNode r = {"r"};
    GNode s = {"s"};
    GNode t = {"t"};
    GNode u = {"u"};
    GNode v = {"v"};
    GNode w = {"w"};
    GNode x = {"x"};
    GNode y = {"y"};

    addNode(&g, &r);
    addNode(&g, &s);
    addNode(&g, &t);
    addNode(&g, &u);
    addNode(&g, &v);
    addNode(&g, &w);
    addNode(&g, &x);
    addNode(&g, &y);

    addEdge(&g, &r, &s);
    addEdge(&g, &r, &v);
    addEdge(&g, &s, &w);
    addEdge(&g, &t, &w);
    addEdge(&g, &t, &x);
    addEdge(&g, &t, &u);
    addEdge(&g, &u, &x);
    addEdge(&g, &u, &y);
    addEdge(&g, &w, &x);
    addEdge(&g, &x, &y);

    printGraph(&g);  // 초기 그래프 상태 출력
    bfs(&g, &s);     // s 노드부터 BFS 수행

    return 0;
}

