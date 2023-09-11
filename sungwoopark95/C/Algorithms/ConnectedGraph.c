#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

int** initialize_adj_matrix(int N, int edges[][2], int num_edges) {
    int** adj = (int**)malloc(N*sizeof(int*));

    for (int i=0;i<N;i++) {
        adj[i] = (int*)malloc(N*sizeof(int));
        for (int j=0;j<N;j++) {
            adj[i][j] = 0;
        }
    }

    for (int i=0;i<num_edges;i++) {
        int from = edges[i][0];
        int to = edges[i][1];
        adj[from][to] = 1;
        // undirected일 경우
        adj[to][from] = 1;
    }

    return adj;
}

void dfs(int** graph, int node, int* visited, int num_nodes) {
    // printf("num nodes: %d\n", num_nodes);
    visited[node] = 1;

    for (int i=0;i<num_nodes;i++) {
        if (graph[node][i] == 1 && visited[i] == 0) {
            // printf("%d\n", i);
            dfs(graph, i, visited, num_nodes);
        }
    }
}

int isConnected(int** graph, int N) {
    // N: number of nodes
    for (int i=0;i<N;i++) {
        int* visited = (int*)malloc(N*sizeof(int));
        // initialization
        for (int j=0;j<N;j++) {
            visited[j] = 0;
        }

        dfs(graph, i, visited, N);

        for (int j=0;j<N;j++) {
            // printf("%d ", visited[j]);
            if (!visited[j]) {
                return 0;
            }
        }
    }
    return 1;
}


int main() {
    int num_nodes = 3;
    int num_edges = 3;
    int edges[MAXSIZE][2];

    edges[0][0] = 0;
    edges[0][1] = 1;
    edges[1][0] = 0;
    edges[1][1] = 2;
    edges[2][0] = 1;
    edges[2][1] = 2;
    // edges[3][0] = 3;
    // edges[3][1] = 4;

    int** graph = initialize_adj_matrix(num_nodes, edges, num_edges);

    for (int i=0;i<num_nodes;i++) {
        for (int j=0;j<num_nodes;j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    printf("This graph is connected? : ");
    if (isConnected(graph, num_nodes)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}