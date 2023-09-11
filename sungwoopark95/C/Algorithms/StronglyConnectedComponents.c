#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define UNVISITED -1 // 방문하지 않은 상태를 나타내는 상수
#define MAX_V 1000   // 최대 정점의 수

typedef struct Graph {
    int v;                     // 정점의 수
    int g[MAX_V][MAX_V];       // 인접 행렬로 그래프 표현
    int id;                    // 각 노드에 고유한 ID를 부여하기 위한 변수
} Graph;

void initGraph(Graph* graph, int vertices) {
    graph->v = vertices;
    graph->id = 0;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->g[i][j] = 0;  // 모든 간선을 0으로 초기화
        }
    }
}

void addEdge(Graph* graph, int u, int v) {
    graph->g[u][v] = 1;  // 간선 추가
}

// 깊이 우선 탐색(DFS) 함수
void dfs(Graph* graph, int at, int* low, int* ids, bool* onStack, int* stack, int* stackIndex) {
    // 현재 정점 'at'에 대한 id 할당. 이 id는 DFS의 방문 순서를 나타냅니다.
    ids[at] = graph->id;
    // 최초에는 low-link 값을 자기 자신의 id로 초기화합니다.
    low[at] = graph->id;
    graph->id++; // 다음 정점에 할당될 id 값 증가.

    onStack[at] = true;  // 현재 정점을 처리 중임을 표시
    stack[*stackIndex] = at; // 스택에 현재 정점을 푸시
    (*stackIndex)++;

    // 인접한 모든 정점들에 대해 조사
    for (int to = 0; to < graph->v; to++) {
        if (graph->g[at][to]) { // (at, to) 간선이 존재하면
            if (ids[to] == UNVISITED) { // 아직 방문하지 않은 정점이라면
                dfs(graph, to, low, ids, onStack, stack, stackIndex); // DFS로 해당 정점 방문
                // 부모 정점 'at'의 low-link 값을 업데이트
                low[at] = (low[at] < low[to]) ? low[at] : low[to]; 
            } else if (onStack[to]) {  // 이미 방문했던 정점이며 아직 처리 중인 경우 (스택에 존재)
                // low-link 값을 업데이트 (백 엣지를 발견한 경우)
                low[at] = (low[at] < ids[to]) ? low[at] : ids[to];
            }
        }
    }

    // SCC의 루트를 찾았을 때 (low와 id 값이 같을 때)
    if (low[at] == ids[at]) {
        printf("Strongly Connected Components: ");
        int w;
        // 스택에서 SCC에 속하는 모든 정점들을 pop하면서 출력
        do {
            (*stackIndex)--;
            w = stack[*stackIndex];
            printf("Node %d ", w);
            onStack[w] = false;  // 해당 정점이 더 이상 처리 중이 아니라는 것을 표시
        } while (w != at);
        printf("\n");
    }
}

// 모든 정점에 대해 SCC를 찾는 함수
void findSCCs(Graph* graph) {
    int ids[MAX_V], low[MAX_V], stack[MAX_V];
    bool onStack[MAX_V];
    int stackIndex = 0;

    // 초기화
    for (int i = 0; i < graph->v; i++) {
        ids[i] = UNVISITED;
        low[i] = UNVISITED;
        onStack[i] = false;
    }

    // 모든 노드에 대해 DFS 수행
    for (int i = 0; i < graph->v; i++) {
        if (ids[i] == UNVISITED) {
            dfs(graph, i, low, ids, onStack, stack, &stackIndex);
        }
    }
}

int main() {
    Graph g;
    initGraph(&g, 5);

    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 0);

    findSCCs(&g);

    return 0;
}
