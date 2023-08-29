#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 1000

typedef struct {
    int** adj;
    int size;
} Graph;

Graph* construct_graph(const char* fname) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->adj = (int**)malloc(MAX_NODES * sizeof(int*));
    for (int i = 0; i < MAX_NODES; i++) {
        graph->adj[i] = (int*)calloc(MAX_NODES, sizeof(int));
    }

    FILE* file = fopen(fname, "r");
    int x, y;
    while (fscanf(file, "%d,%d", &x, &y) != EOF) {
        graph->adj[x][y] = 1;
        graph->adj[y][x] = 1;
    }
    fclose(file);

    return graph;
}

int* bfs(Graph* graph, int start) {
    int* distance = (int*)malloc(MAX_NODES * sizeof(int));
    for (int i = 0; i < MAX_NODES; i++) {
        distance[i] = -1;
    }

    int queue[MAX_NODES];
    int front = 0, rear = 0;

    queue[rear++] = start;
    distance[start] = 0;

    while (front != rear) {
        int curr = queue[front++];
        int dist = distance[curr];

        for (int i = 0; i < MAX_NODES; i++) {
            if (graph->adj[curr][i] && distance[i] == -1) {
                queue[rear++] = i;
                distance[i] = dist + 1;
            }
        }
    }

    return distance;
}

bool check_distance(Graph* graph, int x, int y, int max_distance) {
    int* distance_dict = bfs(graph, x);
    bool result = (distance_dict[y] != -1 && distance_dict[y] <= max_distance);
    free(distance_dict);
    return result;
}

int main() {
    // 예제 사용
    Graph* g = construct_graph("/Users/sungwoo/Desktop/computer/gsds/QualExamCoding/sungwoopark95/python/BFSDFS/small.txt");
    printf("%d\n", check_distance(g, 1, 5, 2));
    return 0;
}
