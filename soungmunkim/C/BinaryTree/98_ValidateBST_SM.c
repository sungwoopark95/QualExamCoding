/*
[현재 binary tree가 BST인지 확인하는 코드 ]
Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

The left  subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % gcc 98_ValidateBST_SM.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test    
Enter the list of integers in the format [x,y,z,...]: [2,1,3]
True

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test
Enter the list of integers in the format [x,y,z,...]: [5,1,4,null,null,3,6]
False
Explanation: The root node's value is 5 but its right child's value is 4.
*/


#include <stdio.h>  // 표준 입출력 라이브러리를 포함합니다.
#include <stdlib.h> // 메모리 동적 할당 및 기타 표준 라이브러리 함수를 사용하기 위해 포함합니다.
#include <limits.h> // infinity 사용 위해 (INT_MIN or INT_MAX)
#include <stdbool.h>
#include <string.h> // strok 사용에 필요함

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

int lower = INT_MIN;
int upper = INT_MAX;

bool dfs_BT(TreeNode* node, int lower, int upper){
    // tree가 없으니 BST라고 가정함 (base case)
    if (!node)
        return true;

    // 현재 node값이 현재 최소값보다 작으면 (범위 밖에 있으면)
    if(node->val <= lower)
        return false;

    // 현재 node값이 현재 최대값보다 크면 (범위 밖에 있으면)
    else if (node->val >= upper)
        return false;
    
    // and 연결하면 return 2개 동시에 가능 (boolean이어서 둘다 참이면 true)
    // right에서 upper는 얼마나 크든 상관 없지만 right node가 현재 노드보다 작으면 안되서 설정함
    return(dfs_BT(node->right, node->val, upper) && dfs_BT(node->left, lower, node->val));    
}

bool isValidBST(int* root, int size){
    // list를 binary tree로 변환 (TreeNode)
    TreeNode* tree = list_to_btree(root, size);

    return dfs_BT(tree, lower, upper);
}

int main(){
    // 사용자에게 숫자 리스트를 입력하라는 메시지를 출력
    printf("Enter the list of integers in the format [x,y,z,...]: ");
    char line[1000]; // 입력 라인의 최대 길이로 가정
    fgets(line, sizeof(line), stdin); // 전체 라인을 읽음

    // \n character을 지우기 
    char *newline = strchr(line, '\n');
    if (newline) {
        *newline = '\0';
    }

    int arr[1000]; // 최대 1000개의 숫자를 가정
    int n = 0;
    char *token = strtok(line, "[], "); // 대괄호, 쉼표, 공백을 기준으로 첫 번째 토큰(숫자)를 얻음
    while (token) {
        arr[n++] = atoi(token); // 토큰을 정수로 변환하여 배열에 추가
        token = strtok(NULL, "[], "); // 다음 토큰을 얻음
    }

    if(isValidBST(arr, n))
        printf("True\n");
    else 
        printf("False\n");
}