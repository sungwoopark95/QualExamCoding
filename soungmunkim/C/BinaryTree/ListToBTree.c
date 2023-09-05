/*
숫자 리스트가 주어지면 그걸 그냥 binary tree로 변환하는 코드
*/

/*------------------ 완벽한 list 형태 (꽉 찬 형태)아니어도 binary tree로 구현 가능 -----------------*/
#include <stdio.h>  // 표준 입출력 라이브러리를 포함합니다.
#include <stdlib.h> // 메모리 동적 할당 및 기타 표준 라이브러리 함수를 사용하기 위해 포함합니다.

// 노드 구조체를 정의합니다.
typedef struct TreeNode {
    int val;                        // 노드의 값을 저장하는 변수입니다.
    struct TreeNode *left;          // 왼쪽 자식 노드를 가리키는 포인터입니다.
    struct TreeNode *right;         // 오른쪽 자식 노드를 가리키는 포인터입니다.
} TreeNode;
/*------------------------- TreeNode 담을 queue 구현 -----------------------*/
// 큐 구조체를 정의합니다.
typedef struct Queue {
    TreeNode** items;   // 노드 포인터들을 저장하는 포인터 배열입니다.
    int front;          // 큐의 맨 앞 인덱스를 나타냅니다.
    int rear;           // 큐의 맨 뒤 인덱스를 나타냅니다.
    int capacity;       // 큐의 최대 용량을 나타냅니다.
} Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));   // 큐 구조체에 메모리를 동적 할당합니다.
    queue->items = (TreeNode**)malloc(sizeof(TreeNode*) * capacity); // 노드 포인터 배열에 메모리를 할당합니다.
    queue->front = 0;     // front를 0으로 초기화합니다.
    queue->rear = -1;     // rear를 -1로 초기화합니다.
    queue->capacity = capacity; // 큐의 최대 용량을 설정합니다.
    return queue;         // 생성된 큐를 반환합니다.
}

int isQueueEmpty(Queue* queue) {
    return queue->rear < queue->front; // rear가 front보다 작으면 큐가 비어있다고 판단합니다.
}

void enqueue(Queue* queue, TreeNode* item) {
    if (queue->rear == queue->capacity - 1) return; // 큐가 꽉 찼다면 아무 작업도 하지 않고 반환합니다.
    queue->items[++queue->rear] = item;  // rear를 증가시킨 후 해당 위치에 노드 포인터를 저장합니다.
}

TreeNode* dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) return NULL; // 큐가 비었다면 NULL을 반환합니다.
    return queue->items[queue->front++];  // front 위치의 노드 포인터를 반환하고 front를 증가시킵니다.
}

/*------------------------- List to binary tree 구현 -----------------------*/
TreeNode* list_to_btree(int* nums, int size) {
    if (size == 0) return NULL; // 리스트가 비어있다면 NULL을 반환합니다.

    Queue* queue = createQueue(size); // 크기가 size인 큐를 생성합니다.

    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode)); // 루트 노드에 메모리를 할당합니다.
    root->val = nums[0]; // 첫 번째 원소로 루트 노드의 값을 설정합니다.
    root->left = NULL;   // 초기 상태에서 왼쪽 자식은 없으므로 NULL로 설정합니다.
    root->right = NULL;  // 초기 상태에서 오른쪽 자식은 없으므로 NULL로 설정합니다.
    enqueue(queue, root); // 루트 노드를 큐에 추가합니다.

    int i = 1;  // nums 배열의 다음 인덱스부터 검사를 시작합니다.
    while (!isQueueEmpty(queue) && i < size) { // 큐가 비어있지 않고, 아직 모든 원소를 검사하지 않았다면
        TreeNode* current = dequeue(queue); // 큐에서 노드를 하나 꺼냅니다.

        if (nums[i] != -1) {  // nums[i]의 값이 -1 (Python의 None에 해당)이 아니라면
            TreeNode* left_child = (TreeNode*)malloc(sizeof(TreeNode)); // 왼쪽 자식 노드에 메모리를 할당합니다.
            left_child->val = nums[i];   // nums[i]의 값을 왼쪽 자식 노드의 값으로 설정합니다.
            left_child->left = NULL;     // 초기 상태에서 왼쪽 자식의 왼쪽 자식은 없으므로 NULL로 설정합니다.
            left_child->right = NULL;    // 초기 상태에서 왼쪽 자식의 오른쪽 자식은 없으므로 NULL로 설정합니다.
            current->left = left_child;  // 현재 노드의 왼쪽 자식으로 설정합니다.
            enqueue(queue, left_child);  // 왼쪽 자식 노드를 큐에 추가합니다.
        }
        i++;  // nums 배열의 다음 인덱스로 이동합니다.

        if (i < size && nums[i] != -1) {  // 다음 인덱스가 유효하고, 그 값이 -1이 아니라면
            TreeNode* right_child = (TreeNode*)malloc(sizeof(TreeNode)); // 오른쪽 자식 노드에 메모리를 할당합니다.
            right_child->val = nums[i];   // nums[i]의 값을 오른쪽 자식 노드의 값으로 설정합니다.
            right_child->left = NULL;     // 초기 상태에서 오른쪽 자식의 왼쪽 자식은 없으므로 NULL로 설정합니다.
            right_child->right = NULL;    // 초기 상태에서 오른쪽 자식의 오른쪽 자식은 없으므로 NULL로 설정합니다.
            current->right = right_child; // 현재 노드의 오른쪽 자식으로 설정합니다.
            enqueue(queue, right_child);  // 오른쪽 자식 노드를 큐에 추가합니다.
        }
        i++;  // nums 배열의 다음 인덱스로 이동합니다.
    }

    free(queue->items); // 큐에서 사용한 메모리를 해제합니다.
    free(queue);        // 큐 구조체에 할당된 메모리를 해제합니다.

    return root; // 생성된 이진 트리의 루트 노드를 반환합니다.
}

// 주: 메모리 해제 함수들과 큐 관련 다른 함수들은 생략되었습니다. 필요하다면 추가해야 합니다.




/*------------------ 완벽한 list 형태 (꽉 찬 형태)여야 binary tree로 구현 가능 -----------------*/
// #include <stdio.h>
// #include <stdlib.h>

// // TreeNode 구조체를 정의합니다.
// typedef struct TreeNode {
//     int val;                         // 노드의 값을 저장하는 변수
//     struct TreeNode* left;           // 왼쪽 자식 노드를 가리키는 포인터
//     struct TreeNode* right;          // 오른쪽 자식 노드를 가리키는 포인터
// } TreeNode;

// // 숫자 배열을 이진 트리로 변환하는 함수
// TreeNode* list_to_btree(int* nums, int numsSize) {
//     // 배열의 크기가 0 이하라면 NULL을 반환합니다.
//     if (numsSize <= 0) return NULL;

//     // TreeNode 포인터의 배열을 동적 할당합니다.
//     TreeNode** nodes = malloc(numsSize * sizeof(TreeNode*));

//     // 각 숫자를 노드로 변환하여 동적 할당된 배열에 저장합니다.
//     for (int i = 0; i < numsSize; i++) {
//         nodes[i] = malloc(sizeof(TreeNode)); // 노드를 위한 메모리를 동적 할당합니다.
//         nodes[i]->val = nums[i];             // 노드의 값 설정
//         nodes[i]->left = NULL;               // 왼쪽 자식 노드를 NULL로 초기화
//         nodes[i]->right = NULL;              // 오른쪽 자식 노드를 NULL로 초기화
//     }

//     // nodes 배열을 사용하여 이진 트리를 구성합니다.
//     for (int i = 1; i < numsSize; i++) {
//         // i가 홀수면 왼쪽 자식으로 설정합니다.
//         if (i % 2 == 1) nodes[(i-1)/2]->left = nodes[i];
//         // i가 짝수면 오른쪽 자식으로 설정합니다.
//         else nodes[(i-2)/2]->right = nodes[i];
//     }

//     // 루트 노드를 반환합니다.
//     return nodes[0];
// }
