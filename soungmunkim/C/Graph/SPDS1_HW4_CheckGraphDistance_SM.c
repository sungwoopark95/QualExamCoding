/*
[Node간 거리 확인 true or false]
class Graph(filename)
filename 파일에 적힌 edge 정보를 읽어와 undirected graph를 구성한다. 
Graph의 각 node를 표현하기 위해 0 이상의 정수가 한 개 씩 ID로 배정 되며, 
    filename 파일에는 graph의 모든 edge 정보가 적혀 있다.
    
check_distance(x, y, max_distance)
x를 ID로 가지는 node와 y를 ID로 가지는 node 사이의 거리가 max distance 보다 작거나 같은지의 여부를 확인하여 반환한다. 
x에서 y로 가는 path가 없 으면 max distance값과 상관 없이 False를 반환
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NODES 100

// 그래프의 각 노드를 표현하는 구조체
typedef struct {
    int id;                                 // 노드의 고유 ID
    int neighbors[MAX_NODES];               // 인접 노드 목록
    int neighbor_count;                     // 인접 노드 수
} Node;

// 그래프를 표현하는 구조체
typedef struct {
    Node nodes[MAX_NODES];                  // 그래프의 모든 노드들
    int node_count;                         // 그래프 내의 노드 수
} Graph;

// 그래프 초기화 함수
void init_graph(Graph* g) {
    g->node_count = 0;
}

// 그래프에 노드 추가 함수
void add_node(Graph* g, int id) {
    g->nodes[g->node_count].id = id;
    g->nodes[g->node_count].neighbor_count = 0;
    g->node_count++;
}

// 그래프에 엣지 추가 함수
void add_edge(Graph* g, int id1, int id2) {
    int index1 = -1, index2 = -1;

    // ID에 해당하는 노드의 인덱스 찾기
    for (int i = 0; i < g->node_count; i++) {
        if (g->nodes[i].id == id1) {
            index1 = i;
        }
        if (g->nodes[i].id == id2) {
            index2 = i;
        }
    }

    // 두 노드 간의 엣지 정보 저장
    if (index1 != -1 && index2 != -1) {
        g->nodes[index1].neighbors[g->nodes[index1].neighbor_count++] = index2;
        g->nodes[index2].neighbors[g->nodes[index2].neighbor_count++] = index1;
    }
}

// BFS를 이용해 시작 노드에서 특정 노드까지의 최단 거리를 계산하는 함수
int bfs(Graph* g, int start_id, int end_id) {
    bool visited[MAX_NODES] = {false};
    int distances[MAX_NODES];
    for (int i = 0; i < g->node_count; i++) {
        distances[i] = -1;
    }

    int queue[MAX_NODES];
    int front = 0, rear = 0;

    int start_index = -1, end_index = -1;
    for (int i = 0; i < g->node_count; i++) {
        if (g->nodes[i].id == start_id) {
            start_index = i;
        }
        if (g->nodes[i].id == end_id) {
            end_index = i;
        }
    }

    queue[rear++] = start_index;
    visited[start_index] = true;
    distances[start_index] = 0;

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

bool check_distance(Graph* g, int x, int y, int max_distance) {
    int distance = bfs(g, x, y);
    return distance <= max_distance && distance != -1;
}

int main() {
    Graph g;
    init_graph(&g);

    // 파일에서 그래프 정보 읽기
    FILE* file = fopen("small.txt", "r");
    if (!file) {
        printf("Failed to open the file.\n");
        return -1;
    }
    int id1, id2;
    while (fscanf(file, "%d,%d", &id1, &id2) != EOF) {
        add_edge(&g, id1, id2);
    }
    fclose(file);

    // 테스트: 두 노드 사이의 거리가 주어진 거리 이하인지 체크
    printf("%d\n", check_distance(&g, 0, 1, 1));  // 1
    printf("%d\n", check_distance(&g, 0, 4, 2));  // 1
    printf("%d\n", check_distance(&g, 0, 5, 3));  // 1
    printf("%d\n", check_distance(&g, 0, 5, 2));  // 0

    return 0;
}



/*-------------------- GNode() 이런식으로 객체로 노드를 받고 그래프 그릴 때 코드 -----------------*/

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>

// #define MAX_NODES 100        // 그래프에서 사용할 최대 노드 개수
// #define MAX_NEIGHBORS 100   // 각 노드의 최대 이웃(인접 노드) 개수
// #define INF 10000           // 무한대를 의미하는 값

// // GNode 구조체: 그래프의 각 노드를 표현
// typedef struct {
//     char id[10];                    // 노드의 ID. 문자열 형태로 저장
//     char neighbors[MAX_NEIGHBORS][10]; // 해당 노드와 직접 연결된 이웃 노드들의 ID
//     int neighbor_count;             // 현재 노드에 연결된 이웃 노드의 수
// } GNode;

// // Graph 구조체: 전체 그래프를 표현
// typedef struct {
//     GNode nodes[MAX_NODES];         // 그래프의 모든 노드를 저장하는 배열
//     int node_count;                // 그래프 내의 현재 노드 수
// } Graph;

// // 그래프 초기화 함수: 그래프의 노드 수를 0으로 설정
// void init_graph(Graph* g) {
//     g->node_count = 0;
// }

// // 그래프에 새로운 노드 추가 함수
// void addNode(Graph* g, GNode node) {
//     g->nodes[g->node_count] = node;  // 새로운 노드를 그래프에 추가
//     g->node_count++;                // 그래프의 노드 개수 증가
// }

// // 그래프에 새로운 에지(연결) 추가 함수: 노드 id1과 id2를 연결
// void addEdge(Graph* g, char* id1, char* id2) {
//     // 두 노드를 서로의 이웃 목록에 추가
//     for (int i = 0; i < g->node_count; i++) {
//         // id1 노드를 찾아 id2를 이웃으로 추가
//         if (strcmp(g->nodes[i].id, id1) == 0) {
//             strcpy(g->nodes[i].neighbors[g->nodes[i].neighbor_count++], id2);
//         }
//         // id2 노드를 찾아 id1을 이웃으로 추가
//         else if (strcmp(g->nodes[i].id, id2) == 0) {
//             strcpy(g->nodes[i].neighbors[g->nodes[i].neighbor_count++], id1);
//         }
//     }
// }

// // BFS 탐색을 사용하여 시작 노드에서 다른 노드까지의 거리 계산
// int bfs(Graph* g, char* start, char* end) {
//     char queue[MAX_NODES][10];   // BFS 탐색에 사용할 큐
//     int front = 0, rear = 0;    // 큐의 앞과 뒤를 가리키는 인덱스
//     char visited[MAX_NODES][10];  // 방문한 노드의 ID 저장 배열
//     int visited_count = 0;      // 방문한 노드의 개수
//     int distances[MAX_NODES];   // 시작 노드로부터의 거리 저장 배열

//     // 초기 거리를 모두 무한대로 설정
//     for (int i = 0; i < g->node_count; i++) {
//         distances[i] = INF;
//     }

//     // 시작 노드를 큐에 추가하고 방문 목록에 기록
//     strcpy(queue[rear++], start);
//     strcpy(visited[visited_count++], start);
//     for (int i = 0; i < g->node_count; i++) {
//         if (strcmp(g->nodes[i].id, start) == 0) {
//             distances[i] = 0;  // 시작 노드의 거리는 0
//             break;
//         }
//     }

//     // BFS 탐색 시작
//     while (front < rear) {
//         char current[10];  // 현재 탐색 중인 노드의 ID
//         strcpy(current, queue[front++]);
//         int currentIndex;  // 현재 탐색 중인 노드의 인덱스
//         for (currentIndex = 0; currentIndex < g->node_count; currentIndex++) {
//             if (strcmp(g->nodes[currentIndex].id, current) == 0) {
//                 break;
//             }
//         }

//         // 현재 노드에 연결된 이웃 노드들을 방문
//         for (int i = 0; i < g->nodes[currentIndex].neighbor_count; i++) {
//             char* neighbor = g->nodes[currentIndex].neighbors[i];
//             bool isVisited = false;
//             for (int j = 0; j < visited_count; j++) {
//                 if (strcmp(visited[j], neighbor) == 0) {
//                     isVisited = true;
//                     break;
//                 }
//             }
//             // 아직 방문하지 않은 노드라면 큐에 추가
//             if (!isVisited) {
//                 strcpy(queue[rear++], neighbor);
//                 strcpy(visited[visited_count++], neighbor);
//                 distances[currentIndex] = distances[currentIndex] + 1;
//             }
//         }
//     }
//     // 시작 노드에서 목표 노드까지의 거리 반환
//     for (int i = 0; i < g->node_count; i++) {
//         if (strcmp(g->nodes[i].id, end) == 0) {
//             return distances[i];
//         }
//     }
//     return INF;  // 두 노드 사이에 경로가 없을 경우 INF 반환
// }

// // 두 노드 사이의 거리가 주어진 최대 거리 이하인지 판별하는 함수
// bool check_distance(Graph* g, char* x, char* y, int max_distance) {
//     int distance = bfs(g, x, y);  // x에서 y까지의 거리 계산
//     return distance <= max_distance;  // 거리가 max_distance 이하인지 검사
// }

// int main() {
//     Graph g;  // 그래프 객체 생성
//     init_graph(&g);  // 그래프 초기화

//     // 그래프에 노드와 에지 정보 추가
//     GNode nodes[] = {
//         {"0", {}, 0},
//         {"1", {}, 0},
//         {"2", {}, 0},
//         {"3", {}, 0},
//         {"4", {}, 0},
//         {"5", {}, 0},
//         {"6", {}, 0},
//         {"7", {}, 0}
//     };
//     for (int i = 0; i < 8; i++) {
//         addNode(&g, nodes[i]);
//     }
//     addEdge(&g, "0", "1");
//     addEdge(&g, "1", "4");
//     addEdge(&g, "4", "5");
//     addEdge(&g, "1", "6");
//     addEdge(&g, "2", "7");
//     addEdge(&g, "3", "7");

//     // 두 노드 사이의 거리가 주어진 거리 이하인지 출력
//     printf("%d\n", check_distance(&g, "0", "1", 1));  // 1 출력 (true)
//     printf("%d\n", check_distance(&g, "0", "4", 2));  // 1 출력 (true)
//     printf("%d\n", check_distance(&g, "0", "5", 3));  // 1 출력 (true)
//     printf("%d\n", check_distance(&g, "0", "5", 2));  // 0 출력 (false)

//     return 0;
// }
