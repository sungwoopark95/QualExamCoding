/*
connected undirected graph G
level_partition(G, s) 구현하기
    that partitions the nodes in the breadth-first tree of G rooted at s,
    list로 각 층마다 nodes들 반환하기 (층 inc order)
    
# TestCase
r, s, t, u, v = GNode('r'), GNode('s'), GNode('t'), GNode('u'), GNode('v')
w, x, y = GNode('w'), GNode('x'), GNode('y')
G = dict()
G[r], G[s], G[t], G[u], G[v] = [s, v], [w, r], [w, x, u], [t, x, y], [r]
G[w], G[x], G[y] = [s, t, x], [w, t, u, y], [x, u]


bfs(G, s) that performs a BFS algorithm (node s를 root로하여 Undirected graph G 만드는 함수)
level_partition(G, s) that uses bfs(G, s) (이전 함수 이용해서 level마다 node 담은 list 반환)

(base) soungmunkim@gimseongmun-ui-MacBookPro Graph % gcc 2022_1_2_LevelPartition_SM.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro Graph % ./test                                  
[[s], [r, w], [t, v, x], [u, y]]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 그래프의 노드를 나타내는 구조체 선언
typedef struct GNode {
    char* id;               // 노드의 고유 ID
    char color;             // 노드의 색상 (W: 흰색, G: 회색, B: 검은색)
    int distance;           // 시작 노드로부터의 거리
    struct GNode* parent;   // 부모 노드
} GNode;

// 인접 리스트를 위한 노드 구조체 선언
typedef struct Node {
    GNode* gNode;           // 인접 노드를 가리킴
    struct Node* next;      // 다음 인접 노드를 가리킴
} Node;

GNode** graph;               // 그래프의 모든 노드를 저장할 포인터 배열
Node** adjList;              // 인접 리스트를 저장할 포인터 배열
int totalNodes;              // 그래프의 노드 수

// 그래프 초기화 함수. 주어진 노드 수에 따라 메모리를 할당합니다.
void initGraph(int numNodes) {
    totalNodes = numNodes;
    graph = (GNode**)malloc(sizeof(GNode*) * totalNodes);
    adjList = (Node**)malloc(sizeof(Node*) * totalNodes);
    for (int i = 0; i < totalNodes; i++) {
        adjList[i] = NULL;
    }
}

// 주어진 소스 노드와 목적지 노드 사이에 간선을 추가하는 함수
void addEdge(int srcIndex, int destIndex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->gNode = graph[destIndex];
    newNode->next = adjList[srcIndex];
    adjList[srcIndex] = newNode;
}

// 주어진 ID로 노드를 생성하는 함수
GNode* createNode(char* id) {
    GNode* newNode = (GNode*)malloc(sizeof(GNode));
    newNode->id = strdup(id);      // ID를 복사하여 저장
    newNode->color = 'W';
    newNode->distance = -1;
    newNode->parent = NULL;
    return newNode;
}

// 그래프 메모리 해제 함수. 할당된 메모리를 모두 반환합니다.
void freeGraph() {
    for (int i = 0; i < totalNodes; i++) {
        free(graph[i]->id);
        free(graph[i]);
    }
    for (int i = 0; i < totalNodes; i++) {
        Node* current = adjList[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph);
    free(adjList);
}

// 인덱스를 찾아 해당 인덱스의 인접 노드를 가져오는 함수
int getIndex(GNode* node) {
    for (int i = 0; i < totalNodes; i++) {
        if (graph[i] == node) return i;
    }
    return -1; // 이 경우는 발생하지 않아야 합니다.
}


// 너비 우선 탐색(BFS) 알고리즘 함수
void bfs(GNode* s) {
    for (int i = 0; i < totalNodes; i++) {
        graph[i]->color = 'W';      // 모든 노드를 흰색으로 초기화
        graph[i]->distance = -1;
        graph[i]->parent = NULL;
    }
    s->color = 'G';                // 시작 노드는 회색으로
    s->distance = 0;

    GNode* queue[totalNodes];       // BFS 탐색을 위한 큐
    int front = 0, rear = 0;
    queue[rear++] = s;

    while (front < rear) {
        GNode* u = queue[front++];
        Node* temp = adjList[getIndex(u)];
        while (temp) {
            GNode* v = temp->gNode;
            if (v->color == 'W') {     // 아직 방문하지 않은 노드면
                v->color = 'G';        // 회색으로 바꾸고 큐에 추가
                v->distance = u->distance + 1;
                v->parent = u;
                queue[rear++] = v;
            }
            temp = temp->next;
        }
        u->color = 'B';                // 노드의 인접 노드들을 모두 방문했으면 검은색으로
    }
}

// BFS를 통해 계산된 노드 거리를 기반으로 그래프 레벨을 분할하고 출력하는 함수
void level_partition(GNode* s) {
    bfs(s);
    int maxDistance = -1;
    for (int i = 0; i < totalNodes; i++) {
        if (graph[i]->distance > maxDistance) {
            maxDistance = graph[i]->distance;
        }
    }
    printf("[");
    for (int i = 0; i <= maxDistance; i++) {
        printf("[");
        for (int j = 0; j < totalNodes; j++) {
            if (graph[j]->distance == i) {
                printf("%s", graph[j]->id);
                int nextIndex = j + 1;
                while (nextIndex < totalNodes && graph[nextIndex]->distance != i) {
                    nextIndex++;
                }
                if (nextIndex < totalNodes) {
                    printf(", ");
                }
            }
        }
        printf("]");
        if (i < maxDistance) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    initGraph(8);                     // 8개의 노드로 그래프 초기화

    // 노드 생성 및 추가
    graph[0] = createNode("r");
    graph[1] = createNode("s");
    graph[2] = createNode("t");
    graph[3] = createNode("u");
    graph[4] = createNode("v");
    graph[5] = createNode("w");
    graph[6] = createNode("x");
    graph[7] = createNode("y");

    // 간선 추가 (양방향 간선)
    addEdge(0, 1);
    addEdge(0, 4);
    addEdge(1, 0);
    addEdge(1, 5);
    addEdge(2, 5);
    addEdge(2, 6);
    addEdge(2, 3);
    addEdge(3, 2);
    addEdge(3, 6);
    addEdge(3, 7);
    addEdge(4, 0);
    addEdge(5, 1);
    addEdge(5, 2);
    addEdge(5, 6);
    addEdge(6, 5);
    addEdge(6, 2);
    addEdge(6, 3);
    addEdge(6, 7);
    addEdge(7, 6);
    addEdge(7, 3);

    level_partition(graph[1]);       // 's'를 시작점으로 하여 레벨 분할 출력

    freeGraph();                      // 할당된 메모리 반환
    return 0;
}
