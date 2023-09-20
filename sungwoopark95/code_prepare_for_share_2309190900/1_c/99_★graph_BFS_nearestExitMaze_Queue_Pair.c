/*
c/99_two_pointer_K-sum pair.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Pair for Queue
typedef struct {
    int fir;
    int sec;
} Pair;

// Node(Single Linked) for Queue
typedef struct Node {
    Pair data;
    struct Node* next;
} Node;

void init_node(Node* node){
    node->next=NULL;
}

// Queue
typedef struct Queue {
    Node* front;
    Node* rear;
    int size;
} Queue;

void initializeQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size=0;
}

void enqueue(Queue* queue, int* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) { fprintf(stderr, "메모리 할당 오류\n"); exit(EXIT_FAILURE);}
    init_node(newNode);
    newNode->data.fir = data[0];
    newNode->data.sec = data[1];
    newNode->next = NULL;

    if (queue->size==0) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

Pair* dequeue(Queue* queue) {
    if (queue->size==0) { fprintf(stderr, "큐가 비어있습니다.\n"); exit(EXIT_FAILURE);}

    Pair* pair=(Pair*)malloc(sizeof(Pair));
    pair->fir=queue->front->data.fir;
    pair->sec=queue->front->data.sec;

    Node* tmp=queue->front;
    queue->front = queue->front->next;
    free(tmp);

    // 만약 큐가 비어있다면 rear도 NULL로 설정
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    queue->size--;
    return pair;
}

// 큐의 맨 앞 요소 반환 (peek)
Pair front(Queue* queue) {
    if (queue->size==0) { fprintf(stderr, "큐가 비어있습니다.\n"); exit(EXIT_FAILURE);}
    return queue->front->data;
}

int nearestExit(char** maze, int mazeSize, int* mazeColSize, int* entrance, int entranceSize){
    
    int dir[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

    Queue q;
    initializeQueue(&q);
    int step=0;
    int pair_int[]={entrance[0], entrance[1]};
    enqueue(&q, pair_int);
    maze[entrance[0]][entrance[1]]='+';

    while (q.size>0){
        int end = q.size;
        for(int i=0; i<end;i++){
            Pair* pair=dequeue(&q);
            if ((pair->fir==0)||(pair->fir==mazeSize-1)||(pair->sec==0)||(pair->sec==mazeColSize[0]-1)){
                if ((pair->fir!=entrance[0])||(pair->sec!=entrance[1])){return step;}
            }
            for(int i = 0; i < 4; i++) {
                int x = pair->fir + dir[i][0];
                int y = pair->sec + dir[i][1];
                if ((x>=0)&&(x<mazeSize)&&(y>=0)&&(y<mazeColSize[0])&&(maze[x][y]=='.')){
                    pair_int[0]=x;
                    pair_int[1]=y;
                    enqueue(&q, pair_int);
                    maze[x][y]='+';
                }
            }
            free(pair);
            
        }
        step++;
    }
    return -1;
    }
