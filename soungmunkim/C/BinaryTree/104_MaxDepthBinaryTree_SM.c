/*
[Binary tree maximum depth 찾기]
Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes 
    along the longest path from the root node down to the farthest leaf node.


(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % gcc 104_MaxDepthBinaryTree_SM.c -o test                                     
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test
숫자 리스트를 입력하세요: [3, 9, 20, None, None, 15, 7]
이진 트리의 최대 깊이: 3

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test
숫자 리스트를 입력하세요: [1,null,2]
이진 트리의 최대 깊이: 2
*/


/*------------------ 완벽한 list 형태 (꽉 찬 형태)아니어도 binary tree로 구현 가능 -----------------*/
#include <stdio.h>  // 표준 입출력 라이브러리를 포함합니다.
#include <stdlib.h> // 메모리 동적 할당 및 기타 표준 라이브러리 함수를 사용하기 위해 포함합니다.
#include <math.h>
#include <string.h>

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

/*--------------------------- binary tree maximum depth 함수 -----------------------------*/
// 주어진 코드의 maxDepth 함수
int maxDepth(struct TreeNode* root) {
    if (!root) return 0;
    int mL = maxDepth(root->left);
    int mR = maxDepth(root->right);
    return fmax(mL, mR) + 1;
}

/*--------------------------- 문자열 비교 함수 -----------------------------*/
// 문자열 비교 함수
int compareStrings(const char* str1, const char* str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return (*str1 == *str2);
}

int main() {
    char input[1000];  // 충분한 크기의 입력 버퍼를 할당합니다.
    printf("숫자 리스트를 입력하세요: ");
    fgets(input, sizeof(input), stdin);  // 사용자로부터 입력을 받습니다.

    // 입력에서 숫자 부분만 추출하여 배열에 저장합니다.
    int nums[1000];  // 숫자를 저장할 배열을 선언합니다.
    int numCount = 0;  // 숫자의 개수를 저장할 변수를 초기화합니다.

    // 입력 문자열에서 ','와 'None' 또는 'null'을 기준으로 숫자를 추출합니다.
    char* token = strtok(input, "[,]\n");
    while (token != NULL) {
        if (compareStrings(token, "None") || compareStrings(token, "null")) {
            nums[numCount] = -1;  // 'None' 또는 'null'을 -1로 대체합니다.
        } else {
            nums[numCount] = atoi(token);  // 문자열을 정수로 변환하여 저장합니다.
        }
        numCount++;
        token = strtok(NULL, "[,]\n");
    }

    // 변환된 숫자 배열과 개수를 이용하여 이진 트리를 생성합니다.
    TreeNode* root = list_to_btree(nums, numCount);

    // 생성한 이진 트리의 높이를 계산합니다.
    int depth = maxDepth(root);

    // 결과를 출력합니다.
    printf("이진 트리의 최대 깊이: %d\n", depth);

    return 0;
}
