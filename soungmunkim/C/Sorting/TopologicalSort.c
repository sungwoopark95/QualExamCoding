#include <stdio.h>
#include <stdlib.h>

#define max 100

typedef struct {
    int top;
    int stack[max];
} stack_type;
typedef stack_type* stack_type_ptr;

void init(stack_type_ptr s) {
    // 스택 초기화 함수
    s->top = -1;
}

int is_full(stack_type s) {
    // 스택이 꽉 찼는지 확인하는 함수
    if (s.top == max - 1)
        return 1; // 꽉 찼으면 1 반환
    else
        return 0; // 꽉 차지 않았으면 0 반환
}

int is_empty(stack_type s) {
    // 스택이 비어 있는지 확인하는 함수
    if (s.top == -1)
        return 1; // 비어 있으면 1 반환
    else
        return 0; // 비어 있지 않으면 0 반환
}

int pop(stack_type_ptr s) {
    // 스택에서 원소를 꺼내는 함수
    if (!is_empty(*s)) {
        int tmp = s->stack[s->top--];
        return tmp; // 스택에서 꺼낸 원소 반환
    }
    else
        printf("스택이 비어 있음");
}

void push(stack_type_ptr s, int item) {
    // 스택에 원소를 추가하는 함수
    if (!is_full(*s)) {
        s->top++;
        s->stack[s->top] = item;
    }
    else
        printf("스택이 꽉 참");
}

int peek(stack_type s) {
    // 스택의 가장 위에 있는 원소를 확인하는 함수
    if (!is_empty(s)) {
        int tmp = s.stack[s.top];
        return tmp; // 스택의 가장 위에 있는 원소 반환
    }
    else
        printf("스택이 비어 있음");
}

typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

#define MAX_VERTICES 50

typedef struct GraphType {
    int n; // 정점의 개수
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

// 그래프 초기화
void graph_init(GraphType* g) {
    int v;
    g->n = 0;
    for (v = 0; v < MAX_VERTICES; v++)
        g->adj_list[v] = NULL;
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
    // 그래프에 정점을 추가하는 함수
    if ((g->n) + 1 > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    g->n++;
}

// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void insert_edge(GraphType* g, int u, int v) {
    // 그래프에 간선을 추가하는 함수
    GraphNode* node;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    if (g->adj_list[u] == NULL) { // insert_first
        node = (GraphNode*)malloc(sizeof(GraphNode));
        node->vertex = v;
        node->link = g->adj_list[u];
        g->adj_list[u] = node;
    }
    else { // insert_last
        node = g->adj_list[u];
        while (node->link != NULL)
            node = node->link;
        node->link = (GraphNode*)malloc(sizeof(GraphNode));
        node->link->vertex = v;
        node->link->link = NULL;
    }
}

// 위상정렬
int topo_sort(GraphType* g) {
    int i;
    stack_type s;
    GraphNode* node;

    // 모든 정점의 진입차수를 계산
    int* in_degree = (int*)malloc(g->n * sizeof(int));
    for (i = 0; i < g->n; i++)
        in_degree[i] = 0;
    for (i = 0; i < g->n; i++) {
        node = g->adj_list[i]; // 정점 i
        while (node != NULL) {
            in_degree[node->vertex]++; // 진입차수[정점 i와 인접한 정점]+1
            node = node->link;
        }
    }

    // 진입차수가 0인 정점을 스택에 삽입
    init(&s);
    for (i = 0; i < g->n; i++) {
        if (in_degree[i] == 0) {
            push(&s, i);
        }
    }

    // 위상 순서 생성으로 처리된 정점의 개수
    int num = 0;

    // 위상 순서를 생성
    while (!is_empty(s)) {
        int w;
        w = pop(&s);
        printf("정점 %d ->", w); // 정점 출력
        // 인접한 정점(들)의 진입 차수를 변경
        node = g->adj_list[w];
        while (node != NULL) {
            in_degree[node->vertex]--; // 진입차수[정점 i와 인접한 정점]-1
            // 변경하고 진입차수가 0이 되면 스택에 삽입
            if (in_degree[node->vertex] == 0)
                push(&s, node->vertex);
            node = node->link;
        }
        num++;
    }
    free(in_degree);

    // 모든 정점을 처리했으면 마지막 'end'를 출력
    if (num == g->n)
        printf("end\n");

    // 사이클이 아니면 True 반환 (num이 g->n이면 모든 정점 처리 -> 사이클 x)
    return (num == g->n);
}

int main(void) {
    GraphType g;

    graph_init(&g);
    insert_vertex(&g, 0);
    insert_vertex(&g, 1);
    insert_vertex(&g, 2);
    insert_vertex(&g, 3);
    insert_vertex(&g, 4);
    insert_vertex(&g, 5);

    // 정점 0의 인접 리스트 생성
    insert_edge(&g, 0, 2);
    insert_edge(&g, 0, 3);
    // 정점 1의 인접 리스트 생성
    insert_edge(&g, 1, 3);
    insert_edge(&g, 1, 4);
    // 정점 2의 인접 리스트 생성
    insert_edge(&g, 2, 3);
    insert_edge(&g, 2, 5);
    // 정점 3의 인접 리스트 생성
    insert_edge(&g, 3, 5);
    // 정점 4의 인접 리스트 생성
    insert_edge(&g, 4, 5);

    // 위상정렬
    topo_sort(&g);

    return 0;
}
