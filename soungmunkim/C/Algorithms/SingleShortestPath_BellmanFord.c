/*
[Single Source Shortest Paths - Bellman Ford Algorithm]
그래프의 최단 경로 (minimum weight)를 찾는 알고리즘
negative weights 포함 가능하며 negative cycle 찾을 수 있음

gcc SingleShortestPath_BellmanFord.c -o Bellman

True/False 로 반환하는 코드지만 path 또는 path & distance 반환 코드도 넣어놓음
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h> // INT_MAX를 위해 사용 (like infinity)

// 에지 구조체 정의
typedef struct Edge {
    int u, v;       // 시작 정점 u, 종료 정점 v
    int weight;     // 에지의 가중치
} Edge;

// 그래프 구조체 정의
typedef struct Graph {
    int V, E;       // V: 정점의 수, E: 에지의 수
    Edge* edges;    // 에지 정보를 담을 배열
} Graph;

// 그래프 생성 함수
Graph* createGraph(int V, int E) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->E = E;
    g->edges = (Edge*)malloc(E * sizeof(Edge));
    return g;
}

// 그래프에 에지 추가 함수
void addEdge(Graph* g, int index, int u, int v, int weight) {
    g->edges[index].u = u;
    g->edges[index].v = v;
    g->edges[index].weight = weight;
}

int* distance;      // 각 정점까지의 최단 거리를 저장하는 배열
int* predecessor;   // 최단 경로 트리에 사용되는 선행 정점 정보를 저장하는 배열

// 시작 정점으로부터의 거리와 선행 정점을 초기화하는 함수
void Initialize_Single_Source(Graph* g, int source) {
    distance = (int*)malloc(g->V * sizeof(int));
    predecessor = (int*)malloc(g->V * sizeof(int));

    for (int i = 0; i < g->V; i++) {
        distance[i] = INT_MAX;    // 모든 거리를 무한대로 초기화
        predecessor[i] = -1;      // 선행 정점을 없음으로 초기화
    }

    distance[source] = 0;         // 시작 정점의 거리는 0으로 설정
}

// 에지 (u, v)에 대한 Relax 연산을 수행하는 함수
void Relax(int u, int v, int weight) {
    // 새로운 경로가 더 짧으면 거리와 선행 정점을 업데이트
    if (distance[v] > distance[u] + weight) {
        distance[v] = distance[u] + weight;
        predecessor[v] = u;
    }
}

// Bellman-Ford 알고리즘을 수행하는 함수
bool Bellman_Ford(Graph* g, int source) {
    Initialize_Single_Source(g, source);

    // 각 에지에 대해 Relax 연산을 V-1번 반복 수행
    for (int i = 1; i <= g->V - 1; i++) {
        for (int j = 0; j < g->E; j++) {
            int u = g->edges[j].u;
            int v = g->edges[j].v;
            Relax(u, v, g->edges[j].weight);
        }
    }

    // 음수 가중치의 사이클이 있는지 확인
    for (int i = 0; i < g->E; i++) {
        int u = g->edges[i].u;
        int v = g->edges[i].v;
        if (distance[v] > distance[u] + g->edges[i].weight) {
            return false;
        }
    }

    return true;
}


/* 최단 경로 반환하고 싶을 때 추가해야할 코드 */
// void GetShortestPath(int destination) {
//     if (predecessor[destination] == -1) {
//         printf("%d", destination);
//         return;
//     }
//     GetShortestPath(predecessor[destination]);
//     printf(" -> %d", destination);
// }

/*---------------- OR -------------------*/

/* 최단 경로와 거리를 반환하고 싶을 때 추가해야 할 코드*/

// 특정 목적지에 대한 최단 경로를 추적하는 함수
// void GetShortestPath(int destination) {
//     if (predecessor[destination] == -1) {
//         printf("%d", destination);
//         return;
//     }
//     GetShortestPath(predecessor[destination]);
//     printf(" -> %d", destination);
// }

// // 특정 목적지에 대한 최단 경로와 거리를 반환하는 함수
// void GetShortestPathAndDistance(int destination) {
//     printf("0 to %d (distance: %d): ", destination, distance[destination]);
//     GetShortestPath(destination);
//     printf("\n");
// }

int main() {
    int V = 5;
    int E = 8;
    Graph* g = createGraph(V, E);

    // 그래프에 에지 추가
    addEdge(g, 0, 0, 1, -1);
    addEdge(g, 1, 0, 2, 4);
    addEdge(g, 2, 1, 2, 3);
    addEdge(g, 3, 1, 3, 2);
    addEdge(g, 4, 1, 4, 2);
    addEdge(g, 5, 3, 2, 5);
    addEdge(g, 6, 3, 1, 1);
    addEdge(g, 7, 4, 3, -3);

    // Bellman-Ford 알고리즘 수행
    if (Bellman_Ford(g, 0)) {
        printf("최단 경로가 성공적으로 계산되었습니다!\n");

        /* 최단 경로 반환하고 싶을 때 추가해야할 코드 */
        // for (int i = 0; i < V; i++) {
        //     printf("0 to %d: ", i);
        //     GetShortestPath(i);
        //     printf("\n");
        // }

    /*---------------- OR -------------------*/

        /*최단 경로와 거리를 반환하고 싶을 때 추가해야 할 코드*/
        // for (int i = 0; i < V; i++) {
        //     GetShortestPathAndDistance(i);
        // }

    } else {
        printf("그래프에 음수 가중치의 사이클이 존재합니다!\n");
    }

    // 동적으로 할당한 메모리 해제
    free(distance);
    free(predecessor);
    free(g->edges);
    free(g);

    return 0;
}