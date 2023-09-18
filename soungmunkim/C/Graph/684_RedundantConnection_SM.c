/*
[Undirected graph에서 cycle 만드는 edge 찾는 것]
undirected graph (no cycle) 만들 수 있게 중복 edge 찾아서 없애기

중복된 edge return 하기 (여러개일 경우 맨 마지막 거 return)
해당 edge가 없어져도 모든 nodes이 다 연결되는 것

Cycle path: 1 -> 2 -> 3 -> 4 -> 1
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % g++ -std=c++17 684_RedundantConnection_SM.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test
[1, 4]
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 그래프의 노드를 표현하는 구조체
typedef struct Node {
    int data;  // 노드 데이터
    struct Node* next;  // 다음 노드를 가리키는 포인터
} Node;

// 간선의 정보를 저장하는 구조체
typedef struct Edge {
    int src, dest;  // 출발 노드, 도착 노드
} Edge;

// 순환 경로를 찾는 함수
bool hasCycle(int node, int parent, Node** graph, bool* visited, int* path, int* pathIndex);

// 순환 경로를 저장하는 함수
int* findCycle(Edge* edges, int n, int* cycleSize);

// 불필요한 간선을 찾는 함수
Edge findRedundantConnection(Edge* edges, int n);

int main() {
    // 간선 배열 초기화
    Edge edges[] = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
    int n = sizeof(edges) / sizeof(edges[0]);  // 간선의 개수 계산

    Edge result = findRedundantConnection(edges, n);
    printf("[%d, %d]\n", result.src, result.dest);  // 결과 출력: [1, 4]

    return 0;
}

// 주어진 노드에서 시작하여 그래프에 순환이 있는지 확인하는 함수
bool hasCycle(int node, int parent, Node** graph, bool* visited, int* path, int* pathIndex) {
    visited[node] = true;
    path[(*pathIndex)++] = node;

    Node* temp = graph[node];
    while (temp != NULL) {
        int neighbor = temp->data;
        if (neighbor != parent) {
            if (visited[neighbor]) {
                while (path[0] != neighbor) {
                    for (int i = 0; i < (*pathIndex) - 1; i++) {
                        path[i] = path[i + 1];
                    }
                    (*pathIndex)--;
                }
                return true;
            } else if (hasCycle(neighbor, node, graph, visited, path, pathIndex)) {
                return true;
            }
        }
        temp = temp->next;  // 다음 노드로 이동
    }

    (*pathIndex)--;
    return false;
}

// 그래프의 순환 경로를 찾아 반환하는 함수
int* findCycle(Edge* edges, int n, int* cycleSize) {
    // 그래프 초기화
    Node* graph[n + 1];
    for (int i = 0; i <= n; i++) {
        graph[i] = NULL;
    }

    // 간선 정보로 그래프 구성
    for (int i = 0; i < n; i++) {
        Node* newNode1 = (Node*)malloc(sizeof(Node));
        newNode1->data = edges[i].dest;
        newNode1->next = graph[edges[i].src];
        graph[edges[i].src] = newNode1;

        Node* newNode2 = (Node*)malloc(sizeof(Node));
        newNode2->data = edges[i].src;
        newNode2->next = graph[edges[i].dest];
        graph[edges[i].dest] = newNode2;
    }

    bool visited[n + 1];
    for (int i = 0; i <= n; i++) {
        visited[i] = false;
    }

    int* path = (int*)malloc((n + 1) * sizeof(int));
    int pathIndex = 0;

    for (int i = 1; i <= n; i++) {
        if (!visited[i] && hasCycle(i, -1, graph, visited, path, &pathIndex)) {
            *cycleSize = pathIndex;
            return path;
        }
    }

    free(path);
    return NULL;
}

// 그래프의 불필요한 간선(순환 경로를 만드는 간선)을 찾아 반환하는 함수
Edge findRedundantConnection(Edge* edges, int n) {
    int cycleSize;
    int* cycle = findCycle(edges, n, &cycleSize);

    if (!cycle) {
        return (Edge){-1, -1};
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < cycleSize - 1; j++) {
            if ((edges[i].src == cycle[j] && edges[i].dest == cycle[j + 1]) ||
                (edges[i].src == cycle[j + 1] && edges[i].dest == cycle[j])) {
                free(cycle);
                return edges[i];
            }
        }
    }

    free(cycle);
    return (Edge){-1, -1};
}
