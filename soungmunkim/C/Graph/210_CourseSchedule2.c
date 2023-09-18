/*
[directed graph 순서 나열하기 (topological order)]

There are a total of numCourses courses you have to take, 
    labeled from 0 to numCourses - 1. 
You are given an array prerequisites 
    where prerequisites[i] = [ai, bi] indicates that 
    you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 
you have to first take course 1. (directed graph)
Return the ordering of courses you should take to finish all courses. 
If there are many valid answers, return any of them. 
If it is impossible to finish all courses, return an empty array.


Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So the correct course order is [0,1].

numCourses = 4
prerequisites = [[1,0],[2,0],[3,1],[3,2]]
findOrder(numCourses, prerequisites)
[0, 1, 2, 3]

numCourses = 1
prerequisites = []
findOrder(numCourses, prerequisites)
[0]
*/

#include <stdio.h>
#include <stdlib.h>

// 그래프 구조체 정의
typedef struct {
    int** edges;       // 엣지 정보 저장
    int* size;         // 각 노드의 엣지 개수 저장
    int numVertices;   // 그래프의 노드(정점) 개수
} Graph;

// 큐 구조체 정의
typedef struct {
    int* data;         // 데이터 저장
    int front, back;   // 큐의 앞, 뒤 위치 정보
    int capacity;      // 큐의 최대 용량
} Queue;

// 그래프 생성 함수
Graph* createGraph(int numVertices) {
    // Graph 구조체를 위한 메모리 동적 할당
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    
    // 각 노드가 가지고 있는 엣지들의 목록을 위한 메모리 할당
    graph->edges = (int**)malloc(numVertices * sizeof(int*));

    // 각 노드의 엣지 개수를 저장하기 위한 메모리 할당 및 초기화
    graph->size = (int*)calloc(numVertices, sizeof(int));

    // 그래프의 전체 노드(정점) 개수 설정
    graph->numVertices = numVertices;

    // 각 노드 별로 엣지 리스트 메모리 동적 할당
    for (int i = 0; i < numVertices; i++) {
        graph->edges[i] = (int*)malloc(numVertices * sizeof(int));
    }

    // 생성된 그래프의 주소 반환
    return graph;
}


// 그래프에 엣지 추가 함수
void addEdge(Graph* graph, int src, int dest) {
    graph->edges[src][graph->size[src]++] = dest;
}

// 그래프 메모리 해제 함수
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->edges[i]);
    }
    free(graph->edges);
    free(graph->size);
    free(graph);
}

// 큐 생성 함수
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (int*)malloc(capacity * sizeof(int));
    queue->front = 0;
    queue->back = 0;
    queue->capacity = capacity;
    return queue;
}

// 큐에 데이터 삽입 함수
void enqueue(Queue* queue, int item) {
    queue->data[queue->back++] = item;
}

// 큐에서 데이터 추출 함수
int dequeue(Queue* queue) {
    return queue->data[queue->front++];
}

// 큐가 비어있는지 확인 함수
int isEmpty(Queue* queue) {
    return queue->front == queue->back;
}

// 큐 메모리 해제 함수
void freeQueue(Queue* queue) {
    free(queue->data);
    free(queue);
}

// 주어진 조건에 맞는 순서 찾기 함수
int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* returnSize) {
    // 그래프 생성
    Graph* graph = createGraph(numCourses); 

    // prerequisites 정보를 바탕으로 그래프에 엣지 추가
    for (int i = 0; i < prerequisitesSize; i++) {
        addEdge(graph, prerequisites[i][1], prerequisites[i][0]);
    }

    // 각 노드의 진입차수를 저장하기 위한 배열 초기화
    int* indegree = (int*)calloc(numCourses, sizeof(int));

    // 그래프를 순회하면서 각 노드의 진입차수 계산
    for (int i = 0; i < numCourses; i++) {
        for (int j = 0; j < graph->size[i]; j++) {
            indegree[graph->edges[i][j]]++;
        }
    }

    // 진입차수가 0인 노드를 저장하기 위한 큐 생성
    Queue* queue = createQueue(numCourses);
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) {
            enqueue(queue, i);
        }
    }

    // 위상 정렬 결과를 저장할 배열 할당
    int* order = (int*)malloc(numCourses * sizeof(int));
    *returnSize = 0;

    // 큐가 빌 때까지 반복
    while (!isEmpty(queue)) {
        // 큐에서 노드를 하나 꺼냄
        int cur = dequeue(queue);
        order[(*returnSize)++] = cur;  // 결과 배열에 현재 노드 추가

        // 현재 노드와 인접한 노드의 진입차수 감소
        for (int j = 0; j < graph->size[cur]; j++) {
            int adj = graph->edges[cur][j];
            indegree[adj]--;
            // 진입차수가 0이 된 노드를 큐에 추가
            if (indegree[adj] == 0) {
                enqueue(queue, adj);
            }
        }
    }

    // 모든 정점을 방문하지 않은 경우 (사이클 존재)
    if (*returnSize != numCourses) {
        free(order);   // 결과 배열 메모리 해제
        order = NULL;  // 포인터 초기화
        *returnSize = 0;  // 반환할 배열의 크기 초기화
    }

    // 동적 할당한 메모리 해제
    freeGraph(graph);
    freeQueue(queue);
    free(indegree);

    // 최종 결과 반환
    return order;
}

// 주어진 크기와 데이터를 기반으로 방향성 있는 간선들을 생성하는 함수
int** createDirectedEdges(int size, int data[][2]) {
    // 크기에 따라 int 포인터 배열을 동적 할당합니다.
    int** edges = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        // 각 원소에 대하여 int 배열 크기 2를 할당합니다.
        edges[i] = (int*)malloc(2 * sizeof(int));
        // 데이터에서 간선의 시작점을 복사합니다.
        edges[i][0] = data[i][0];
        // 데이터에서 간선의 끝점을 복사합니다.
        edges[i][1] = data[i][1];
    }
    // 생성된 간선 리스트를 반환합니다.
    return edges;
}

// 방향성 있는 간선들의 메모리를 해제하는 함수
void freeDirectedEdges(int** edges, int size) {
    for (int i = 0; i < size; i++) {
        // 각 원소에 할당된 메모리를 해제합니다.
        free(edges[i]);
    }
    // 전체 배열에 할당된 메모리를 해제합니다.
    free(edges);
}
// 출력 함수 숫자 리스트 [1,2,3,4] 형태로 
void printOrder(int* order, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", order[i]);
        if (i < size - 1) printf(",");
    }
    printf("]\n");
}


int main() {
    // 예제 1
    int prerequisitesData1[][2] = {{1, 0}};
    int** prerequisites1 = createDirectedEdges(1, prerequisitesData1);

    int returnSize1;
    int* order1 = findOrder(2, prerequisites1, 1, &returnSize1);

    // 출력 
    printOrder(order1, returnSize1);

    
    freeDirectedEdges(prerequisites1, 1);
    free(order1);

    // 예제 2
    int prerequisitesData2[][2] = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    int** prerequisites2 = createDirectedEdges(4, prerequisitesData2);

    int returnSize2;
    int* order2 = findOrder(4, prerequisites2, 4, &returnSize2);

    // 출력
    printOrder(order2, returnSize2);

    freeDirectedEdges(prerequisites2, 4);
    free(order2);

    // 예제 3
    int returnSize3;
    int* order3 = findOrder(1, NULL, 0, &returnSize3);

    // 출력
    printOrder(order3, returnSize3);

    free(order3);

    return 0;
}


