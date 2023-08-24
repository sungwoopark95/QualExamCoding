/*
[Topological order 만들기 ]
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_V 100

// 연결 리스트의 노드를 표현하는 구조체
typedef struct Node {
    int dest;           // 목적지 정점
    struct Node* next;  // 다음 노드를 가리키는 포인터
} Node;

// 그래프를 표현하는 구조체
typedef struct Graph {
    int V;                 // 그래프의 정점 수
    Node* array[MAX_V];    // 인접 리스트 배열
} Graph;

// 새로운 연결 리스트 노드를 생성하는 함수
Node* newListNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// 새로운 그래프를 생성하는 함수
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    for (int i = 0; i < V; i++)
        graph->array[i] = NULL;  // 각 인접 리스트를 NULL로 초기화
    return graph;
}

// 그래프에 새로운 간선을 추가하는 함수
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = newListNode(dest);
    newNode->next = graph->array[src];  // 노드를 인접 리스트의 맨 앞에 추가
    graph->array[src] = newNode;
}

// 위상 정렬을 위한 DFS 도우미 함수
void topologicalSortUtil(Graph* graph, int v, bool visited[], int* stack, int* top) {
    visited[v] = true;  // 현재 정점을 방문했음을 표시

    // 현재 정점에 인접한 모든 정점에 대해
    Node* temp = graph->array[v];
    while (temp) {
        if (!visited[temp->dest]) {
            topologicalSortUtil(graph, temp->dest, visited, stack, top);
        }
        temp = temp->next;
    }

    // 현재 정점의 처리가 끝나면 스택에 추가
    stack[*top] = v;
    (*top)--;
}

// 그래프의 위상 정렬을 수행하는 함수
void topologicalSort(Graph* graph) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));  // 방문 배열
    int* stack = (int*)malloc(graph->V * sizeof(int));      // 결과를 저장할 스택

    for (int i = 0; i < graph->V; i++) {
        visited[i] = false;  // 방문 배열 초기화
    }

    int top = graph->V - 1;
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {  // 방문하지 않은 정점에 대해 DFS 수행
            topologicalSortUtil(graph, i, visited, stack, &top);
        }
    }

    printf("해당 그래프의 위상 정렬 결과:\n");
    for (int i = 0; i < graph->V; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");

    free(visited);
    free(stack);
}

int main() {
    int V = 6;  // 그래프의 정점 수
    Graph* graph = createGraph(V);

    // 예시 그래프에 간선 추가
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    topologicalSort(graph);  // 위상 정렬 수행

    // 메모리 해제
    for (int i = 0; i < V; i++) {
        Node* temp = graph->array[i];
        while (temp) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph);

    return 0;
}
