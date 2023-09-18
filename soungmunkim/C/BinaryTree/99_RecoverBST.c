/*
[binary tree를 bst로 만들기]

이진 검색 트리의 잘못된 노드를 발견하고 복구하는 데 중점

Input: root = [1,3,null,null,2]
Output: [3,1,null,null,2]
Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.

Input: root = [3,1,4,null,null,2]
Output: [2,1,4,null,null,3]
Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % gcc 99_RecoverBST.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test    
[3, 1, Null, Null, 2]
[2, 1, 4, Null, Null, 3]
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct QueueNode {
    TreeNode* data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} Queue;

// 큐 관련 함수들
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

bool isEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, TreeNode* data) {
    QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

TreeNode* dequeue(Queue* q) {
    if (isEmpty(q)) return NULL;

    QueueNode *temp = q->front;
    TreeNode *data = temp->data;

    q->front = q->front->next;
    if (!q->front) q->rear = NULL;

    free(temp);
    return data;
}

/*--------------------------- list to binary tree ------------------------*/
// BST 구축 함수
TreeNode* vectorToTree(int nums[], int size) {
    if (size == 0) return NULL;

    Queue q;
    initQueue(&q);

    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = nums[0];
    root->left = root->right = NULL;
    enqueue(&q, root);

    int index = 1;
    while (!isEmpty(&q) && index < size) {
        TreeNode *current = dequeue(&q);

        if (nums[index] != -1) {
            current->left = (TreeNode*)malloc(sizeof(TreeNode));
            current->left->val = nums[index];
            current->left->left = current->left->right = NULL;
            enqueue(&q, current->left);
        } else {
            current->left = NULL;
        }
        index++;

        if (index < size && nums[index] != -1) {
            current->right = (TreeNode*)malloc(sizeof(TreeNode));
            current->right->val = nums[index];
            current->right->left = current->right->right = NULL;
            enqueue(&q, current->right);
        } else {
            current->right = NULL;
        }
        index++;
    }

    return root;
}

/*--------------------------- inorder로 배열에 바로 저장 ------------------------*/
// 중위 순회를 이용하여 이진 트리의 노드와 값을 배열에 저장하는 함수
void inorderTraversal(TreeNode *root, TreeNode ***nodes, int **values, int *count) {
    if (!root) return;  // 현재 노드가 null이면 반환

    // 왼쪽 서브트리를 중위 순회
    inorderTraversal(root->left, nodes, values, count);
    
    // 현재 노드와 그 값을 배열에 저장
    (*nodes)[*count] = root;
    (*values)[*count] = root->val;
    (*count)++;  // 카운트 증가

    // 오른쪽 서브트리를 중위 순회
    inorderTraversal(root->right, nodes, values, count);
}

// 이진 검색 트리에서 잘못된 위치에 있는 두 노드의 값을 바로 잡는 함수
void recoverTree(TreeNode *root) {
    // 최대 1000개의 노드를 가진 이진 트리를 가정하고 동적 메모리 할당
    TreeNode **nodes = (TreeNode**)malloc(1000 * sizeof(TreeNode*));
    int *values = (int*)malloc(1000 * sizeof(int));

    int count = 0;
    // 중위 순회를 통해 이진 트리의 노드와 그 값을 배열에 저장
    inorderTraversal(root, &nodes, &values, &count);
    
    // 저장된 값들을 오름차순으로 정렬
    qsort(values, count, sizeof(int), (int (*)(const void *, const void *)) strcmp);

    // 정렬된 값을 이진 트리의 노드에 다시 저장
    for (int i = 0; i < count; i++) {
        nodes[i]->val = values[i];
    }

    // 동적으로 할당된 메모리 해제
    free(nodes);
    free(values);
}


/*--------------------------- BFS 프린트 하는 함수 (without Null) ---------------*/
void print_BST_withoutNull(TreeNode* root) {
    if (!root) {
        printf("[Tree is empty.]\n");
        return;
    }

    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    printf("[");  // 시작 괄호 출력

    bool first = true;  // 첫 번째 원소를 확인하는 플래그

    while (!isEmpty(&q)) {
        TreeNode* current = dequeue(&q);

        if (current) {
            if (!first) { // 첫 번째 원소가 아니면 앞에 콤마와 공백 출력
                printf(", ");
            }

            printf("%d", current->val);
            
            if (current->left) { // 왼쪽 자식 노드가 있다면 큐에 추가
                enqueue(&q, current->left);
            }

            if (current->right) { // 오른쪽 자식 노드가 있다면 큐에 추가
                enqueue(&q, current->right);
            }

            first = false;  // 첫 번째 원소를 출력했으므로 플래그를 false로 설정
        }
    }
    printf("]\n");  // 종료 괄호 출력
}

/*--------------------------- BFS 프린트 하는 함수 (with Null) ---------------*/
#define MAX_SIZE 1000
void print_BST_withNull(TreeNode* root) {
    if(!root) {
        printf("Tree is empty.\n");
        return;
    }

    char* output[MAX_SIZE];
    int index = 0;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while(!isEmpty(&q)) {
        TreeNode* current = dequeue(&q);

        if(current) {
            char buffer[12]; // to accommodate int size and the null terminator
            snprintf(buffer, sizeof(buffer), "%d", current->val);
            output[index] = strdup(buffer);
            enqueue(&q, current->left);
            enqueue(&q, current->right);
        } else {
            output[index] = strdup("Null");
        }

        index++;
    }

    while(index > 0 && strcmp(output[index-1], "Null") == 0) {
        free(output[index-1]);
        index--;
    }

    printf("[");
    for (int i = 0; i < index; ++i) {
        printf("%s", output[i]);
        if (i != index - 1)
            printf(", ");
        free(output[i]);  // free the allocated memory for each string
    }
    printf("]\n");
}




int main() {
    int nums1[] = {1, 3, -1, -1, 2};
    TreeNode* tree1 = vectorToTree(nums1, 5);
    recoverTree(tree1);
    print_BST_withNull(tree1);
    
    int nums2[] = {3, 1, 4, -1, -1, 2};

    TreeNode* tree2 = vectorToTree(nums2, 6);
    recoverTree(tree2);
    print_BST_withNull(tree2);

    return 0;
}
