#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Vertex {
    int id;
    double d;
    struct Vertex* pi;
} Vertex;

typedef struct Graph {
    Vertex** V;
    int numVertices;
    Vertex*** Adj;
    int* numAdjVertices;
} Graph;

void INITIALIZE_SINGLE_SOURCE(Graph* G, Vertex* s) {
    for (int i = 0; i < G->numVertices; i++) {
        G->V[i]->d = INT_MAX;
        G->V[i]->pi = NULL;
    }
    s->d = 0;
}

void RELAX(Vertex* u, Vertex* v, int weights[][2]) {
    int weight = weights[u->id][v->id];
    if (v->d > u->d + weight) {
        v->d = u->d + weight;
        v->pi = u;
    }
}

int compare(const void* a, const void* b) {
    Vertex* vertexA = *(Vertex**)a;
    Vertex* vertexB = *(Vertex**)b;
    if (vertexA->d < vertexB->d) return -1;
    if (vertexA->d > vertexB->d) return 1;
    return 0;
}

void DIJKSTRA(Graph* G, int weights[][2], Vertex* s) {
    INITIALIZE_SINGLE_SOURCE(G, s);
    Vertex** S = NULL;
    int numS = 0;
    Vertex** Q = (Vertex**)malloc(G->numVertices * sizeof(Vertex*));
    for (int i = 0; i < G->numVertices; i++) {
        Q[i] = G->V[i];
    }
    int numQ = G->numVertices;

    while (numQ > 0) {
        qsort(Q, numQ, sizeof(Vertex*), compare);
        Vertex* u = Q[0];
        S = (Vertex**)realloc(S, (numS + 1) * sizeof(Vertex*));
        S[numS++] = u;
        for (int i = 0; i < G->numAdjVertices[u->id]; i++) {
            Vertex* v = G->Adj[u->id][i];
            RELAX(u, v, weights);
        }
        for (int i = 0; i < numQ - 1; i++) {
            Q[i] = Q[i + 1];
        }
        numQ--;
    }
    free(Q);
    free(S);
}

int main() {
    Vertex v1 = {0, INT_MAX, NULL};
    Vertex v2 = {1, INT_MAX, NULL};
    Vertex v3 = {2, INT_MAX, NULL};
    Vertex v4 = {3, INT_MAX, NULL};

    Vertex* adj_v1[] = {&v2, &v3};
    Vertex* adj_v2[] = {&v4};
    Vertex* adj_v3[] = {&v4};

    Graph G = {
        .V = (Vertex*[]){&v1, &v2, &v3, &v4},
        .numVertices = 4,
        .Adj = (Vertex**[]){adj_v1, adj_v2, adj_v3, NULL},
        .numAdjVertices = (int[]){2, 1, 1, 0}
    };

    int weights[4][2] = {
        {0, 5},
        {0, 3},
        {1, 2},
        {2, 1}
    };

    DIJKSTRA(&G, weights, &v1);

    for (int i = 0; i < G.numVertices; i++) {
        printf("Distance from v1 to v%d: %f\n", G.V[i]->id + 1, G.V[i]->d);
    }

    return 0;
}
