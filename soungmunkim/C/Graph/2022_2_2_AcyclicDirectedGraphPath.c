/*
[Acyclic Directed Graph paths 구하기]
paths(G, s, t)를 구현해라
acyclic directed graph G에서 주어진 nodes간의 가능한 paths들을 다 [] 형태로 반환하기

!! DFS 방법으로 풀기 !!!
< 그냥 vector들을 프린트할 때 이런식으로 프린트 시키는 것>
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % g++ -std=c++17 2022_2_2_AcyclicDirectedGraphPaths.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test                                                       
["a", "c"], ["a", "b", "d", "c"]
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 그래프 노드를 표현하기 위한 구조체 정의
typedef struct GNode {
    char* id;       // 노드의 ID를 저장하는 포인터. 여기서는 알파벳 문자열로 표현
} GNode;

// 그래프의 인접 리스트의 각 항목을 표현하기 위한 구조체 정의
typedef struct Vertex {
    GNode* node;    // 인접한 노드의 포인터
    struct Vertex* next; // 다음 인접 항목에 대한 포인터
} Vertex;

// DFS 탐색 시 사용될 스택의 각 항목을 표현하기 위한 구조체 정의
typedef struct StackElem {
    GNode* node;        // 스택에 들어있는 노드의 포인터
    char** path;        // 현재까지의 경로를 저장하는 이중 포인터
    int pathSize;       // 현재 경로의 길이
    struct StackElem* next; // 스택의 다음 항목에 대한 포인터
} StackElem;

// GNode 생성자 함수: 새로운 그래프 노드를 생성하고 초기화
GNode* createGNode(const char* id) {
    GNode* newNode = (GNode*)malloc(sizeof(GNode));
    newNode->id = strdup(id);
    return newNode; 
}

// Vertex 생성자 함수: 새로운 정점(인접 리스트 항목)을 생성하고 초기화
Vertex* createVertex(GNode* node) {
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
    newVertex->node = node;
    newVertex->next = NULL;
    return newVertex; 
}

// StackElem 생성자 함수: 새로운 스택 항목을 생성하고 초기화
StackElem* createStackElem(GNode* node, char** path, int pathSize) {
    StackElem* newStackElem = (StackElem*)malloc(sizeof(StackElem));
    newStackElem->node = node;
    newStackElem->path = path;
    newStackElem->pathSize = pathSize;
    newStackElem->next = NULL;
    return newStackElem; 
}

// 스택에 새로운 항목을 추가하는 함수
void push(StackElem** stack, GNode* node, char** path, int pathSize) {
    StackElem* newStackElem = createStackElem(node, path, pathSize);
    newStackElem->next = *stack;
    *stack = newStackElem; 
}

// 스택의 맨 위 항목을 제거하고 반환하는 함수
StackElem* pop(StackElem** stack) {
    if (!*stack) return NULL;
    StackElem* temp = *stack;
    *stack = (*stack)->next;
    return temp; 
}

// 스택이 비어 있는지 확인하는 함수
bool isStackEmpty(StackElem* stack) {
    return !stack; 
}

// 경로를 복사하여 새로운 경로를 생성하는 함수
char** copyPath(char** original, int originalSize, char* newNode) {
    char** newPath = (char**)malloc((originalSize + 1) * sizeof(char*));
    for (int i = 0; i < originalSize; i++) {
        newPath[i] = strdup(original[i]);
    }
    newPath[originalSize] = strdup(newNode);
    return newPath; 
}

// 주어진 그래프에서 시작 노드에서 종료 노드까지의 모든 경로를 찾아 출력하는 함수
void paths(Vertex* G[], GNode* start, GNode* end) {
    StackElem* S = NULL;  // 경로 탐색에 사용할 스택을 NULL로 초기화

    // 시작 노드를 위한 경로 배열 초기화
    char** startPath = (char**)malloc(sizeof(char*));
    startPath[0] = start->id;  // 시작 노드의 ID를 경로 배열에 추가
    push(&S, start, startPath, 1);  // 스택에 시작 노드와 해당 경로 정보를 푸시

    bool firstPrint = true;  // 첫 번째 경로 출력을 확인하기 위한 플래그

    // 스택이 빌 때까지 경로 탐색을 계속한다 (DFS 사용)
    while (!isStackEmpty(S)) {
        StackElem* current = pop(&S);  // 스택의 최상단 요소를 팝
        GNode* curNode = current->node;  // 현재 탐색 중인 노드
        char** curPath = current->path;  // 현재 노드까지의 경로
        int curSize = current->pathSize;  // 현재 경로의 길이

        // 현재 경로가 종료 노드에 도달하면 해당 경로를 출력
        if (strcmp(curNode->id, end->id) == 0) {
            if (firstPrint) {  // 첫 번째 출력인 경우
                firstPrint = false;  // 플래그를 false로 변경
                printf("[");  // 경로들의 시작 괄호 출력
            } else {  // 첫 번째 출력이 아닌 경우
                printf(", ");  // 이전 경로와 구분하기 위한 쉼표와 공백 출력
            }

            // 해당 경로 출력
            printf("[");
            for (int i = 0; i < curSize; i++) {
                printf("\"%s\"", curPath[i]);
                if (i != curSize - 1) printf(", ");  // 경로 내의 노드들을 쉼표로 구분
            }
            printf("]");
        }

        // 현재 노드에 인접한 노드들을 탐색
        Vertex* adjacent = G[curNode->id[0] - 'a'];
        while (adjacent) {
            bool isContained = false;
            // 이미 경로에 포함된 노드인지 확인
            for (int i = 0; i < curSize; i++) {
                if (strcmp(curPath[i], adjacent->node->id) == 0) {
                    isContained = true;
                    break;
                }
            }
            if (!isContained) {  // 경로에 포함되지 않았다면
                // 새로운 경로 정보를 생성
                char** newPath = copyPath(curPath, curSize, adjacent->node->id);
                // 스택에 새로운 경로 정보와 인접 노드를 푸시
                push(&S, adjacent->node, newPath, curSize + 1);
            }
            adjacent = adjacent->next;  // 다음 인접 노드로 이동
        }
        free(current);  // 현재 스택 요소 메모리 해제
    }
    printf("\n");  // 모든 경로 출력 후 줄바꿈
}


// 코드 실행을 위한 메인 함수
int main() {
    // 노드들 생성
    GNode* a = createGNode("a");
    GNode* b = createGNode("b");
    GNode* c = createGNode("c");
    GNode* d = createGNode("d");

    // 그래프 (인접 리스트) 초기화
    Vertex* G[26] = {NULL}; 
    G['a' - 'a'] = createVertex(b);
    G['a' - 'a']->next = createVertex(c);
    G['b' - 'a'] = createVertex(d);
    G['d' - 'a'] = createVertex(c);

    // a에서 c까지의 모든 경로 찾아 출력
    paths(G, a, c); 

    // 이 예제에서는 메모리 해제 부분이 생략되었습니다.
    return 0;
}

