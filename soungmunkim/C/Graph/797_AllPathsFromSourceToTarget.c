/*
[All paths From Source to Target]
DAG사용해서 풀기 (Directed Acyclic graph)

there is a directed edge from node i to node graph[i][j]

Input: graph = [[1,2],[3],[3],[]]
Output: [[0,1,3],[0,2,3]]
Explanation: There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.

Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]

(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % g++ -std=c++17 797_AllPathsFromSourceToTarget.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test
가능한 모든 경로:
0 -> 1 -> 4 -> END
0 -> 1 -> 2 -> 3 -> 4 -> END
0 -> 1 -> 3 -> 4 -> END
0 -> 3 -> 4 -> END
0 -> 4 -> END
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 최대 노드 수 설정
#define MAX_NODES 100

// 스택의 아이템을 위한 구조체 정의
typedef struct {
    int node;                   // 현재 노드
    int path[MAX_NODES];        // 현재 노드까지의 경로
    int pathSize;               // 경로의 크기
} StackItem;

// 스택을 위한 구조체 정의
typedef struct {
    StackItem items[MAX_NODES]; // 스택 아이템들
    int top;                    // 스택의 맨 위 위치
} Stack;

// 스택 초기화 함수
void initializeStack(Stack* stack) {
    stack->top = -1;            // 스택이 비어있음을 표시
}

// 스택이 비어있는지 확인하는 함수
bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

// 스택에 아이템을 추가하는 함수
void push(Stack* stack, int node, int* path, int pathSize) {
    if (stack->top == MAX_NODES - 1) {
        printf("Stack overflow.\n");
        return;
    }
    stack->top++;
    stack->items[stack->top].node = node;
    stack->items[stack->top].pathSize = pathSize;
    for (int i = 0; i < pathSize; i++) {
        stack->items[stack->top].path[i] = path[i];
    }
}

// 스택에서 아이템을 가져오는 함수
StackItem pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow.\n");
        exit(1);
    }
    return stack->items[stack->top--];
}

// 배열에 특정 값이 포함되어 있는지 확인하는 함수
bool contains(int* arr, int size, int val) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == val) return true;
    }
    return false;
}

// 모든 경로를 찾는 주요 함수
void allPathsSourceTarget(int graph[][MAX_NODES], int* graphSizes, int numNodes, int allpaths[][MAX_NODES], int* allPathsSize, int* allPathsCounts) {
    Stack stack;
    initializeStack(&stack);    // 스택 초기화

    int startPath[] = {0};      // 시작 경로
    push(&stack, 0, startPath, 1);  // 시작 노드와 경로를 스택에 추가

    *allPathsCounts = 0;        // 가능한 경로의 수를 0으로 초기화

    // 스택이 비어있지 않은 동안 반복
    while (!isEmpty(&stack)) {
        StackItem item = pop(&stack);  // 스택에서 아이템 가져오기

        // 현재 노드에서 갈 수 있는 경로가 없으면
        if (graphSizes[item.node] == 0) {
            for (int i = 0; i < item.pathSize; i++) {
                allpaths[*allPathsCounts][i] = item.path[i];
            }
            allPathsSize[*allPathsCounts] = item.pathSize;
            (*allPathsCounts)++;
            continue;
        }

        // 인접한 노드들을 반복하며 스택에 추가
        for (int i = 0; i < graphSizes[item.node]; i++) {
            int adj = graph[item.node][i];
            if (!contains(item.path, item.pathSize, adj)) {
                int newPath[MAX_NODES];
                for (int j = 0; j < item.pathSize; j++) {
                    newPath[j] = item.path[j];
                }
                newPath[item.pathSize] = adj;
                push(&stack, adj, newPath, item.pathSize + 1);
            }
        }
    }
}

int main() {
    // 예제 그래프
    int graph[MAX_NODES][MAX_NODES] = {{4,3,1},{3,2,4},{3},{4}};
    int graphSizes[] = {3, 3, 1, 1, 0};   // 각 노드별 인접한 노드의 수
    int numNodes = 5;  // 전체 노드의 수

    // 결과 저장을 위한 배열들
    int allpaths[MAX_NODES][MAX_NODES];
    int allPathsSize[MAX_NODES];
    int allPathsCounts;

    allPathsSourceTarget(graph, graphSizes, numNodes, allpaths, allPathsSize, &allPathsCounts);

    // 가능한 모든 경로 출력
    printf("가능한 모든 경로:\n");
    for (int i = 0; i < allPathsCounts; i++) {
        for (int j = 0; j < allPathsSize[i]; j++) {
            printf("%d -> ", allpaths[i][j]);
        }
        printf("END\n");
    }

    return 0;
}
