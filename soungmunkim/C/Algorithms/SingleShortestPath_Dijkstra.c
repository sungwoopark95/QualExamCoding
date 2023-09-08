/*
[Dijkstra algorithm 구현하기]

negative weight cycle 없다는 가정
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Vertex라는 이름의 구조체 타입 정의
// 각 정점은 아이디, 시작 정점으로부터의 거리, 부모 정점 정보를 가지고 있다.
typedef struct Vertex {
    int id;               // 각 정점의 고유한 번호 (아이디)
    double d;             // 시작 정점에서 현재 정점까지의 최단 거리
    struct Vertex* pi;   // 최단 경로 트리에서 현재 정점의 부모 정점
} Vertex;

// Graph라는 이름의 구조체 타입 정의
typedef struct Graph {
    Vertex** V;               // 그래프의 모든 정점을 저장하는 포인터 배열
    int numVertices;         // 그래프의 정점 개수
    Vertex*** Adj;           // 그래프의 각 정점에 연결된 인접 정점 리스트
    int* numAdjVertices;     // 각 정점의 인접 정점 개수를 저장하는 배열
} Graph;

// 시작 정점을 받아서 모든 정점의 거리를 무한대로 초기화하고 시작 정점만 0으로 설정
void INITIALIZE_SINGLE_SOURCE(Graph* G, Vertex* s) {
    for (int i = 0; i < G->numVertices; i++) {
        G->V[i]->d = INT_MAX;   // 최대 값으로 거리 초기화
        G->V[i]->pi = NULL;    // 부모 정점 초기화
    }
    s->d = 0;   // 시작 정점의 거리는 0
}

// 두 정점과 가중치 정보를 받아서 필요한 경우 경로를 갱신 (Relaxation)
void RELAX(Vertex* u, Vertex* v, int weights[][2]) {
    int weight = weights[u->id][v->id];
    if (v->d > u->d + weight) {
        v->d = u->d + weight;  // 거리 갱신
        v->pi = u;             // 부모 정점 갱신
    }
}

// 정점들을 거리를 기준으로 정렬하는 함수
int compare(const void* a, const void* b) {
    Vertex* vertexA = *(Vertex**)a;
    Vertex* vertexB = *(Vertex**)b;
    if (vertexA->d < vertexB->d) return -1;
    if (vertexA->d > vertexB->d) return 1;
    return 0;
}

// 경로를 출력하는 함수
void printPath(Vertex* s, Vertex* v) {
    if (v == s) {
        printf("v%d ", s->id + 1);
    } else if (v->pi == NULL) {
        printf("no path from v%d to v%d exists", s->id + 1, v->id + 1);
    } else {
        printPath(s, v->pi);
        printf("-> v%d ", v->id + 1);
    }
}

// Dijkstra 알고리즘 구현 함수
void DIJKSTRA(Graph* G, int weights[][2], Vertex* s) {
    // 모든 정점의 거리와 부모를 초기화
    INITIALIZE_SINGLE_SOURCE(G, s);
    Vertex** S = NULL;   // 방문한 정점을 저장할 배열
    int numS = 0;        // 방문한 정점의 개수
    Vertex** Q = (Vertex**)malloc(G->numVertices * sizeof(Vertex*));  // 아직 방문하지 않은 정점들의 배열
    for (int i = 0; i < G->numVertices; i++) {
        Q[i] = G->V[i];  // 초기에는 모든 정점이 방문되지 않았으므로 Q에 추가
    }
    int numQ = G->numVertices;

    while (numQ > 0) {  // 모든 정점을 방문할 때까지 반복
        qsort(Q, numQ, sizeof(Vertex*), compare);  // Q 배열을 거리를 기준으로 정렬
        Vertex* u = Q[0];  // 현재 가장 거리가 짧은 정점 선택
        S = (Vertex**)realloc(S, (numS + 1) * sizeof(Vertex*));  // S 배열에 추가
        S[numS++] = u;
        for (int i = 0; i < G->numAdjVertices[u->id]; i++) {  // 선택한 정점과 연결된 모든 정점에 대해
            Vertex* v = G->Adj[u->id][i];
            RELAX(u, v, weights);  // Relaxation 실행
        }
        for (int i = 0; i < numQ - 1; i++) {
            Q[i] = Q[i + 1];  // 현재 정점을 Q에서 제거
        }
        numQ--;  // Q의 크기 감소
    }
    free(Q);
    free(S);
}


int main() {
    // 그래프 초기화 부분
    Vertex v1 = {0, INT_MAX, NULL};
    Vertex v2 = {1, INT_MAX, NULL};
    Vertex v3 = {2, INT_MAX, NULL};
    Vertex v4 = {3, INT_MAX, NULL};

    Vertex* adj_v1[] = {&v2, &v3};
    Vertex* adj_v2[] = {&v4};
    Vertex* adj_v3[] = {&v4};

    Graph G = {
        .V = (Vertex*[]){&v1, &v2, &v3, &v4},
        .numVertices = 4,
        .Adj = (Vertex**[]){adj_v1, adj_v2, adj_v3, NULL},
        .numAdjVertices = (int[]){2, 1, 1, 0}
    };

    int weights[4][2] = {  // 각 간선의 가중치 정보
        {0, 5},
        {0, 3},
        {1, 2},
        {2, 1}
    };

    // Dijkstra 알고리즘을 실행하여 최단 경로 계산
    DIJKSTRA(&G, weights, &v1);

    // 결과 출력
    for (int i = 0; i < G.numVertices; i++) {
        printf("Distance from v1 to v%d: %f\n", G.V[i]->id + 1, G.V[i]->d);
        printf("Path: ");
        printPath(&v1, G.V[i]);
        printf("\n");
    }
}
