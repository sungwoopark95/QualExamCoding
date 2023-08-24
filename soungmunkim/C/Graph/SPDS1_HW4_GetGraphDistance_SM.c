/*
[BFS를 이용해서 graph 노드간의 distance 얻기]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NODES 100

// 노드 구조체
typedef struct {
    char id[10];                            // 각 노드의 고유 ID (문자열로 표현)
    int neighbors[MAX_NODES];               // 이 노드와 연결된 이웃 노드들의 인덱스 목록
    int neighbor_count;                     // 현재 노드와 연결된 이웃 노드의 수
} GNode;

// 그래프 구조체
typedef struct {
    GNode nodes[MAX_NODES];                 // 그래프에 포함된 모든 노드들
    int node_count;                         // 그래프에 포함된 노드의 총 수
} Graph;

// 그래프 초기화 함수
void init_graph(Graph* g) {
    g->node_count = 0;                      // 노드 수를 0으로 초기화
}

// 그래프에 새로운 노드 추가 함수
void add_node(Graph* g, const char* id) {
    strcpy(g->nodes[g->node_count].id, id); // 입력 받은 ID로 노드 ID 설정
    g->nodes[g->node_count].neighbor_count = 0; // 이웃 노드 수 초기화
    g->node_count++;                        // 그래프 내의 노드 수 증가
}

// 그래프 내 두 노드 간의 엣지 추가 함수
void add_edge(Graph* g, const char* id1, const char* id2) {
    int index1 = -1, index2 = -1;

    // ID에 해당하는 노드의 인덱스 찾기
    for (int i = 0; i < g->node_count; i++) {
        if (strcmp(g->nodes[i].id, id1) == 0) {
            index1 = i;
        }
        if (strcmp(g->nodes[i].id, id2) == 0) {
            index2 = i;
        }
    }
    // 두 노드 간의 연결 정보 저장
    if (index1 != -1 && index2 != -1) {
        g->nodes[index1].neighbors[g->nodes[index1].neighbor_count++] = index2;
        g->nodes[index2].neighbors[g->nodes[index2].neighbor_count++] = index1;
    }
}

// BFS를 이용해 시작 노드에서 특정 노드까지의 최단 거리를 반환하는 함수
int get_distance(Graph* g, const char* start_id, const char* end_id) {
    bool visited[MAX_NODES] = {false};      // 방문 여부를 저장하는 배열
    int distances[MAX_NODES];               // 시작 노드로부터의 거리를 저장하는 배열
    for (int i = 0; i < g->node_count; i++) {
        distances[i] = -1;                  // 초기 거리를 -1로 설정
    }
    int start_index = -1, end_index = -1;

    // 시작 및 종료 노드의 인덱스 찾기
    for (int i = 0; i < g->node_count; i++) {
        if (strcmp(g->nodes[i].id, start_id) == 0) {
            start_index = i;
        }
        if (strcmp(g->nodes[i].id, end_id) == 0) {
            end_index = i;
        }
    }

    if (start_index == -1 || end_index == -1) {
        return -1;
    }

    int queue[MAX_NODES];
    int front = 0, rear = 0;
    queue[rear++] = start_index;
    visited[start_index] = true;
    distances[start_index] = 0;

    // BFS 탐색 시작
    while (front < rear) {
        int current = queue[front++];
        for (int i = 0; i < g->nodes[current].neighbor_count; i++) {
            int neighbor = g->nodes[current].neighbors[i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue[rear++] = neighbor;
                distances[neighbor] = distances[current] + 1;
            }
        }
    }

    return distances[end_index];
}

int main() {
    Graph g;
    init_graph(&g);

    // 예제 그래프 구성
    add_node(&g, "0");
    add_node(&g, "1");
    add_node(&g, "2");
    add_node(&g, "3");
    add_node(&g, "4");
    add_node(&g, "5");
    add_node(&g, "6");
    add_node(&g, "7");

    add_edge(&g, "0", "1");
    add_edge(&g, "1", "4");
    add_edge(&g, "4", "5");
    add_edge(&g, "1", "6");
    add_edge(&g, "2", "7");
    add_edge(&g, "3", "7");

    printf("Distance between 0 and 1: %d\n", get_distance(&g, "0", "1"));
    printf("Distance between 0 and 4: %d\n", get_distance(&g, "0", "4"));
    printf("Distance between 0 and 5: %d\n", get_distance(&g, "0", "5"));
    printf("Distance between 0 and 5: %d\n", get_distance(&g, "0", "5"));

    return 0;
}
