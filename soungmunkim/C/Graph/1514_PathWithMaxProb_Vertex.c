/*
[undirected graph sorce -> target 까지의 max prob을 반환하기]
DFS + Relaxation 방법으로 품
!!  Vertex 버전 !!

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
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#define INITIAL_CAPACITY 10

typedef struct Edge {
    struct Vertex* vertex;  // 대상 정점
    double weight;  // 가중치
} Edge;

typedef struct Vertex {
    int id;  // 정점의 ID
    char name[10];  // 정점의 이름
    double distance;  // 정점까지의 거리(확률 값)

    Edge* edges;  // 간선들의 배열
    int num_edges;  // 간선의 수
    int capacity_edges;  // 할당된 간선의 크기

    struct Vertex** adjacency_list;  // 인접한 정점들의 배열
    int num_adjacent;  // 인접한 정점의 수
    int capacity_adjacent;  // 할당된 인접 리스트의 크기
} Vertex;

typedef struct Graph {
    Vertex** vertices;  // 정점들의 배열
    int num_vertices;  // 정점의 수
    int capacity_vertices;  // 할당된 정점의 크기
} Graph;

// 새로운 정점을 생성하는 함수
Vertex* GenVertex(int id, const char* name) {
    Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));  // 정점에 메모리 할당
    vertex->id = id;  // ID 설정
    strncpy(vertex->name, name, sizeof(vertex->name) - 1);  // 이름 복사
    vertex->distance = -INFINITY;  // 거리 초기화
    vertex->num_edges = 0;  // 간선 수 초기화
    vertex->capacity_edges = INITIAL_CAPACITY;  // 간선 배열의 초기 용량 설정
    vertex->edges = (Edge*)malloc(vertex->capacity_edges * sizeof(Edge));  // 간선 배열에 메모리 할당
    vertex->num_adjacent = 0;  // 인접한 정점의 수 초기화
    vertex->capacity_adjacent = INITIAL_CAPACITY;  // 인접 리스트의 초기 용량 설정
    vertex->adjacency_list = (Vertex**)malloc(vertex->capacity_adjacent * sizeof(Vertex*));  // 인접 리스트에 메모리 할당
    return vertex;  // 생성된 정점 반환
}

// 새로운 간선을 생성하는 함수
void GenEdge(Vertex* start, Vertex* end, double weight) {
    // 시작 정점의 간선 배열이 꽉 찼다면 용량을 두 배로 늘린다.
    if (start->num_edges >= start->capacity_edges) {
        start->capacity_edges *= 2;
        start->edges = (Edge*)realloc(start->edges, start->capacity_edges * sizeof(Edge));
    }
    start->edges[start->num_edges].vertex = end;  // 간선의 대상 정점 설정
    start->edges[start->num_edges].weight = weight;  // 간선의 가중치 설정
    start->num_edges++;  // 간선 수 증가

    // 종료 정점의 간선 배열이 꽉 찼다면 용량을 두 배로 늘린다.
    if (end->num_edges >= end->capacity_edges) {
        end->capacity_edges *= 2;
        end->edges = (Edge*)realloc(end->edges, end->capacity_edges * sizeof(Edge));
    }
    end->edges[end->num_edges].vertex = start;  // 간선의 대상 정점 설정
    end->edges[end->num_edges].weight = weight;  // 간선의 가중치 설정
    end->num_edges++;  // 간선 수 증가

    // 시작 정점의 인접 리스트가 꽉 찼다면 용량을 두 배로 늘린다.
    if (start->num_adjacent >= start->capacity_adjacent) {
        start->capacity_adjacent *= 2;
        start->adjacency_list = (Vertex**)realloc(start->adjacency_list, start->capacity_adjacent * sizeof(Vertex*));
    }
    start->adjacency_list[start->num_adjacent++] = end;  // 인접 리스트에 종료 정점 추가
}

// 주어진 시작 정점으로부터 모든 다른 정점까지의 최단 경로 계산 함수
void shortestPath(Vertex** vertices, int num_vertices, Vertex* s) {
    s->distance = 1;  // 시작 정점의 거리는 1로 설정

    // 스택을 이용하여 방문할 정점을 관리
    Vertex** stack = (Vertex**)malloc(num_vertices * sizeof(Vertex*));
    int stack_size = 0;
    stack[stack_size++] = s;

    // 스택이 비어있지 않을 때까지
    while (stack_size > 0) {
        Vertex* cur = stack[--stack_size];  // 현재 정점을 스택에서 pop

        // 현재 정점과 연결된 모든 간선에 대해
        for (int i = 0; i < cur->num_edges; i++) {
            Vertex* adj = cur->edges[i].vertex;  // 인접한 정점
            double weight = cur->edges[i].weight;  // 간선의 가중치
            if (adj->distance < cur->distance * weight) {
                adj->distance = cur->distance * weight;
                stack[stack_size++] = adj;  // 스택에 인접한 정점을 push
            }
        }
    }

    free(stack);  // 스택 메모리 해제
}

// 시작 노드에서 종료 노드까지의 최대 확률 계산 함수
double maxProb(Graph* graph, int start_node, int end_node) {
    Vertex* s = graph->vertices[start_node];  // 시작 정점
    shortestPath(graph->vertices, graph->num_vertices, s);  // 최단 경로 계산

    double result = graph->vertices[end_node]->distance;  // 결과 값 저장
    return (result == -INFINITY) ? 0.0 : result;  // 결과가 무한대인 경우 0.0 반환
}

int main() {
    Graph graph;
    graph.num_vertices = 0;
    graph.capacity_vertices = INITIAL_CAPACITY;
    graph.vertices = (Vertex**)malloc(graph.capacity_vertices * sizeof(Vertex*));  // 정점 배열 메모리 할당

    // 3개의 정점 생성
    for (int i = 0; i < 3; i++) {
        // 정점 배열의 용량이 부족하면 두 배로 늘림
        if (graph.num_vertices >= graph.capacity_vertices) {
            graph.capacity_vertices *= 2;
            graph.vertices = (Vertex**)realloc(graph.vertices, graph.capacity_vertices * sizeof(Vertex*));
        }
        char name[10];
        snprintf(name, sizeof(name), "%d", i);  // 정점 이름 설정
        graph.vertices[graph.num_vertices++] = GenVertex(i, name);  // 정점 생성
    }

    // 간선 생성
    GenEdge(graph.vertices[0], graph.vertices[1], 0.5);
    GenEdge(graph.vertices[1], graph.vertices[2], 0.5);
    GenEdge(graph.vertices[0], graph.vertices[2], 0.2);

    int start = 0;  // 시작 노드 인덱스
    int end = 2;    // 종료 노드 인덱스
    printf("%f\n", maxProb(&graph, start, end));  // 최대 확률 출력

    // 할당된 메모리 해제
    for (int i = 0; i < graph.num_vertices; i++) {
        free(graph.vertices[i]->edges);
        free(graph.vertices[i]->adjacency_list);
        free(graph.vertices[i]);
    }
    free(graph.vertices);  // 정점 배열 메모리 해제

    return 0;
}

