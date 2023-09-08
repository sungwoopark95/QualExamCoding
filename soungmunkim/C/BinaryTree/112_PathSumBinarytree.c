/*
[root부터 마지막까지 한 path 합이 targetsum과 같은지]

Given the root of a binary tree and an integer targetSum, 
    return true if the tree has a root-to-leaf path 
    such that adding up all the values along the path equals targetSum.
    
root = [5,4,8,11,None,13,4,7,2,None,None,None,1]
targetSum = 22
head = list_to_btree(root)
hasPathSum(head, targetSum) # True

Explanation: The root-to-leaf path with the target sum is shown.

root = [1,2,3]
targetSum = 5
head1 = list_to_btree(root)
hasPathSum(head1, targetSum) # False

There is no root-to-leaf path with sum = 5.

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test
Enter node values in [a,b,c,...] format: [5,4,8,11,None,13,4,7,2,None,None,None,1]
Enter the target sum: 22
True
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test
Enter node values in [a,b,c,...] format: [1,2,3]
Enter the target sum: 5
False
*/

/*------------------ 완벽한 list 형태 (꽉 찬 형태)아니어도 binary tree로 구현 가능 -----------------*/
#include <stdio.h>  // 표준 입출력 라이브러리를 포함합니다.
#include <stdlib.h> // 메모리 동적 할당 및 기타 표준 라이브러리 함수를 사용하기 위해 포함합니다.
#include <math.h>
#include <string.h>
#include <stdbool.h>

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

// 주어진 TreeNode와 합을 검사하는 함수
bool hasPathSum(struct TreeNode* root, int targetSum) {
    // 루트 노드가 NULL이면 합을 만족하는 경로는 없습니다.
    if (root == NULL) {
        return false;
    }

    // 현재 노드가 leaf 노드이고 남은 합이 현재 노드의 값과 같다면 true를 반환합니다.
    if (root->left == NULL && root->right == NULL && root->val == targetSum) {
        return true;
    }

    // 현재 노드의 값을 현재 남은 합에서 뺍니다.
    targetSum -= root->val;

    // 왼쪽 서브트리나 오른쪽 서브트리 중 하나라도 합을 만족하는 경로가 있다면 true를 반환합니다.
    return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
}

#define MAX_INPUT_SIZE 1000

int main() {
    int input[MAX_INPUT_SIZE]; // 입력 배열
    int input_size = 0;       // 입력 배열의 크기
    char line[MAX_INPUT_SIZE]; // 한 줄의 입력을 저장할 문자열
    char *token;
    int targetSum;

    printf("Enter node values in [a,b,c,...] format: ");
    fgets(line, sizeof(line), stdin); // 입력 받기
    line[strcspn(line, "\n")] = 0; // 개행 문자 제거

    // 괄호와 쉼표로 토큰 분리하여 파싱
    token = strtok(line, "[,]"); // 첫 토큰
    while(token != NULL) {
        // 문자열이 "None"이 아니면 배열에 추가
        if (strcmp(token, "None") != 0) {
            input[input_size++] = atoi(token);
        }
        token = strtok(NULL, "[,]"); // 다음 토큰
    }

    printf("Enter the target sum: ");
    scanf("%d", &targetSum); // 삭제할 키 값을 입력 받기

    TreeNode* root = list_to_btree(input, input_size); // 이진 탐색 트리 생성
    int result;
    result = hasPathSum(root, targetSum); 

    if (result)
        printf("True\n");
    else
        printf("False\n");

    return 0; 
}

// int main() {
//     // TreeNode 구조체를 사용하여 이진 트리를 생성하고 검사합니다.
//     struct TreeNode node1, node2, node3, node4, node5;

//     node1.val = 5;
//     node2.val = 4;
//     node3.val = 8;
//     node4.val = 11;
//     node5.val = 13;

//     node1.left = &node2;
//     node1.right = &node3;
//     node2.left = &node4;
//     node2.right = NULL;
//     node3.left = &node5;
//     node3.right = NULL;
//     node4.left = NULL;
//     node4.right = NULL;
//     node5.left = NULL;
//     node5.right = NULL;

//     int targetSum = 22;

//     bool result = hasPathSum(&node1, targetSum);

//     if (result) {
//         printf("True\n");  // 합을 만족하는 경로가 있을 경우
//     } else {
//         printf("False\n"); // 합을 만족하는 경로가 없을 경우
//     }

//     return 0;
// }