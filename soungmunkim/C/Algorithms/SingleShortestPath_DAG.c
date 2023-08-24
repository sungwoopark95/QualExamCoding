/*
[최단 경로 찾기 DAG]
cycle이 없음 (directed graph)

(base) soungmunkim@gimseongmun-ui-MacBookPro Algorithms % gcc SingleShortestPath_DAG.c -o DAG
(base) soungmunkim@gimseongmun-ui-MacBookPro Algorithms % ./DAG 
Distance from 0 to 0 is: 0
Distance from 0 to 1 is: 5
Distance from 0 to 2 is: 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_V 100
#define INF 2147483647

// 각 노드를 표현하는 구조체
typedef struct Node {
    int to;       // 연결된 정점의 번호
    int weight;   // 이 노드를 통해 연결된 정점까지의 가중치
    struct Node* next; // 다음 노드를 가리키는 포인터
} Node;

// 그래프를 표현하는 구조체
typedef struct {
    int V, E;           // V는 그래프의 정점의 수, E는 간선의 수
    Node* adj[MAX_V];   // 인접 리스트로 그래프를 표현
} Graph;

int distance[MAX_V]; // 시작 정점으로부터 각 정점까지의 최단 거리를 저장

// 그래프 초기화 함수: 정점의 수 V를 받아서 그래프를 생성하고 초기화
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = 0;
    for (int i = 0; i < V; i++) {
        graph->adj[i] = NULL;  // 각 정점의 인접 리스트 초기화
    }
    return graph;
}

// 그래프에 간선을 추가하는 함수
void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->to = dest;
    newNode->weight = weight;
    newNode->next = graph->adj[src]; // 새 노드를 인접 리스트의 맨 앞에 추가
    graph->adj[src] = newNode;
    graph->E++; // 간선의 수 증가
}

// 위상 정렬을 위한 깊이 우선 탐색(DFS) 함수
void topologicalSortUtil(Graph* graph, int v, bool visited[], int* stack, int* stackIndex) {
    visited[v] = true; // 정점 방문 표시
    Node* node = graph->adj[v];
    while (node) {
        if (!visited[node->to]) {
            topologicalSortUtil(graph, node->to, visited, stack, stackIndex);
        }
        node = node->next;
    }
    stack[(*stackIndex)++] = v; // 정점을 스택에 푸시
}

// 시작 정점의 거리를 초기화하는 함수
void Initialize_Single_Source(Graph* graph, int source) {
    for (int i = 0; i < graph->V; i++) {
        distance[i] = INF; // 모든 거리를 무한대로 초기화
    }
    distance[source] = 0; // 시작 정점의 거리는 0
}

// relax 함수: 거리 배열을 업데이트
void relax(int u, int v, int weight) {
    if (distance[u] != INF && distance[u] + weight < distance[v]) {
        distance[v] = distance[u] + weight; // 거리 갱신
    }
}

// DAG에서의 최단 경로를 계산하는 함수
void DAG_shortest_path(Graph* graph, int source) {
    bool visited[MAX_V] = {0};
    int stack[MAX_V];
    int stackIndex = 0;

    // 모든 정점에 대해 DFS 수행하여 위상 정렬
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, stack, &stackIndex);
        }
    }

    Initialize_Single_Source(graph, source);
    // 위상 정렬된 순서대로 relax 연산 수행
    for (int i = stackIndex - 1; i >= 0; i--) {
        int u = stack[i];
        Node* node = graph->adj[u];
        while (node) {
            relax(u, node->to, node->weight);
            node = node->next;
        }
    }
}

int main() {
    int V = 3, E = 2; // 예제 데이터: 정점 3개, 간선 2개
    Graph* graph = createGraph(V);

    // 예제 그래프에 간선 추가
    addEdge(graph, 0, 1, 5);
    addEdge(graph, 0, 2, 3);

    int source = 0; // 시작 정점 설정
    Initialize_Single_Source(graph, source);

    DAG_shortest_path(graph, source);


    for (int i = 0; i < V; i++) {
        if (distance[i] != INF) {
            printf("Distance from %d to %d is: %d\n", source, i, distance[i]);
        } else {
            printf("Distance from %d to %d is: INF\n", source, i);
        }
    }

    return 0;
}

