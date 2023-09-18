/*
주어진 이진 탐색 트리(BST)에서 두 주어진 노드의 최소 공통 조상(LCA) 노드를 찾아라.

"최소 공통 조상은 두 노드 p와 q에 대하여 p와 q 모두를 후손으로 갖는 T의 가장 낮은 노드로 정의된다. 
(이때, 노드가 자신의 후손이 될 수 있음을 허용한다.)"

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % gcc 235_LowestCommonAncestorBST.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test
First Case LCA: 6
Second Case LCA: 2
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

TreeNode* lowestCommonAncestor(TreeNode* root, int p, int q) {
    int smallest, largest;
    
    // p, q 중에서 가장 큰 값을 largest, 가장 작은 값을 smallest에 저장합니다.
    if (p < q) {
        smallest = p;
        largest = q;
    } else {
        smallest = q;
        largest = p;
    }

    while (root) {
        // 가장 작은 값이 현재 노드 값보다 크면 right subtree로 이동합니다.
        if (smallest > root->val) {
            root = root->right;
        }
        // 가장 큰 값이 현재 노드 값보다 작으면 left subtree로 이동합니다.
        else if (largest < root->val) {
            root = root->left;
        }
        // 그렇지 않다면 (즉, smallest는 현재 노드의 값보다 작거나 같고
        // largest는 현재 노드의 값보다 크거나 같은 경우)
        // LCA임으로 해당 노드를 반환합니다.
        else {
            return root;
        }
    }

    return NULL; // LCA를 찾지 못한 경우 NULL을 반환합니다.
}

int main() {
    // 첫 번째 케이스에 대한 데이터
    int root1[] = {6,2,8,0,4,7,9,-1,-1,3,5};
    int size1 = sizeof(root1) / sizeof(root1[0]); // 배열의 크기를 계산합니다.
    TreeNode* tree1 = list_to_btree(root1, size1);
    TreeNode* result1 = lowestCommonAncestor(tree1, 2, 8);
    if (result1) {
        printf("First Case LCA: %d\n", result1->val);
    } else {
        printf("First Case LCA not found\n");
    }

    // 두 번째 케이스에 대한 데이터
    int root2[] = {6,2,8,0,4,7,9,-1,-1,3,5};
    int size2 = sizeof(root2) / sizeof(root2[0]); // 배열의 크기를 계산합니다.
    TreeNode* tree2 = list_to_btree(root2, size2);
    TreeNode* result2 = lowestCommonAncestor(tree2, 2, 4);
    if (result2) {
        printf("Second Case LCA: %d\n", result2->val);
    } else {
        printf("Second Case LCA not found\n");
    }

    // 메모리를 해제하는 코드는 여기에 추가해야합니다. (트리 노드와 큐 관련 메모리)

    return 0;
}
