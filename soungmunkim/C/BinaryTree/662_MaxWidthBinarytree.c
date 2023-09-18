/*
[rightmost와 leftmost (non null)포함 사이 node 개수가 최대인 것 찾기]

Given the root of a binary tree, 
    return the maximum width of the given tree.

The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes 
    (the leftmost and rightmost non-null nodes), 
    where the null nodes between the end-nodes that 
    would be present in a complete binary tree extending down to that 
    level are also counted into the length calculation.
    
            1 (ID:0)
         /           \
(ID:0)  2              3 (ID: 1)
       / \              \
(ID:0)4   5(ID:1) (ID:2) 7 (ID:3)
현재 노드의 ID * 2 와 현재 노드의 ID * 2 + 1은 
전형적인 이진 트리(Binary Tree)에서 배열을 사용하여 트리를 구현할 때 사용되는 인덱싱 방식

root = [1,3,2,5,3,None,9]
tree = list_to_btree(root)
widthOfBinaryTree(tree)
4

root = [1,3,2,5,None,None,9,6,None,7]
tree = list_to_btree(root)
widthOfBinaryTree(tree)
7

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % g++ -std=c++17 662_MaxWidthBinarytree.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test                                           
Enter node values in [a,b,c,...] format: [1,3,2,5,3,None,9]
4
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test                                           
Enter node values in [a,b,c,...] format: [1,3,2,5,None,None,9,6,None,7]
7
*/


/*------------------ 완벽한 list 형태 (꽉 찬 형태)아니어도 binary tree로 구현 가능 -----------------*/
// Node ID 도 추가한 queue 형태임
#include <stdio.h>      // 표준 입력과 출력 함수를 사용하기 위한 헤더 파일
#include <stdlib.h>     // 메모리 동적 할당 함수를 사용하기 위한 헤더 파일
#include <math.h>       // 수학 관련 함수를 사용하기 위한 헤더 파일
#include <string.h>     // 문자열 함수를 사용하기 위한 헤더 파일

// 트리의 노드를 정의하는 구조체
typedef struct TreeNode {
    int val;                        // 노드에 저장될 값
    struct TreeNode *left;          // 왼쪽 자식 노드를 가리키는 포인터
    struct TreeNode *right;         // 오른쪽 자식 노드를 가리키는 포인터
} TreeNode;

// 노드와 그 노드의 ID를 함께 저장하기 위한 구조체
typedef struct NodeID {
    TreeNode* node;                 // 트리 노드 포인터
    int id;                         // 노드의 ID (이진 트리에서의 위치를 표현하는 값)
} NodeID;

// 큐를 구현하기 위한 구조체
typedef struct Queue {
    NodeID* items;                  // NodeID 타입의 아이템들을 저장하는 배열
    int front;                      // 큐의 앞쪽 위치
    int rear;                       // 큐의 뒷쪽 위치
    int capacity;                   // 큐의 최대 크기
} Queue;

// 큐를 생성하는 함수
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));   // 큐 메모리 할당
    queue->items = (NodeID*)malloc(sizeof(NodeID) * capacity); // NodeID 배열 메모리 할당
    queue->front = 0;     // front 초기화
    queue->rear = -1;     // rear 초기화
    queue->capacity = capacity; // 큐의 최대 크기 설정
    return queue;         // 초기화된 큐 반환
}

// 큐가 비어있는지 확인하는 함수
int isQueueEmpty(Queue* queue) {
    return queue->rear < queue->front;
}

// 큐에 항목을 추가하는 함수
void enqueue(Queue* queue, TreeNode* node, int id) {
    if (queue->rear == queue->capacity - 1) return; // 큐가 가득 찼다면 함수 종료
    NodeID nodeID;                   // NodeID 객체 생성
    nodeID.node = node;              // 트리 노드 설정
    nodeID.id = id;                  // 노드 ID 설정
    queue->items[++queue->rear] = nodeID; // 큐에 NodeID 아이템 추가
}

// 큐에서 항목을 제거하고 반환하는 함수
NodeID dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {       // 큐가 비어있다면
        NodeID empty;                // 빈 NodeID 객체 생성
        empty.node = NULL;           // 빈 노드 설정
        empty.id = -1;               // ID를 -1로 설정
        return empty;                // 빈 NodeID 반환
    }
    return queue->items[queue->front++]; // 아니면 front 위치의 아이템을 반환하고 front 증가
}

/*------------------------- List to binary tree (queue struct 사용 없이) 구현 -----------------------*/
TreeNode* newNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));  // 노드 메모리 할당
    node->val = val;  // 값 설정
    node->left = NULL;  // 왼쪽 자식 초기화
    node->right = NULL;  // 오른쪽 자식 초기화
    return node;  // 생성된 노드 반환
}

// 숫자 배열을 이진 트리로 변환하는 함수
TreeNode* list_to_btree(int* nums, int len) {
    if (len == 0 || nums[0] == -1) return NULL;  // 배열이 비었거나 첫 번째 값이 None일 경우

    TreeNode* root = newNode(nums[0]);  // 루트 노드 생성
    TreeNode* queue[len];
    int front = 0, rear = 0;

    queue[rear++] = root;  // 큐에 루트 노드 추가

    for (int i = 1; i < len && front < rear; i++) {
        TreeNode* current = queue[front++];  // 큐의 앞에서 노드 가져오기

        if (nums[i] != -1) {  // 왼쪽 자식에 대한 값이 None이 아닌 경우
            current->left = newNode(nums[i]);  // 왼쪽 자식 생성
            queue[rear++] = current->left;  // 큐에 추가
        }
        i++;

        if (i < len && nums[i] != -1) {  // 오른쪽 자식에 대한 값이 None이 아닌 경우
            current->right = newNode(nums[i]);  // 오른쪽 자식 생성
            queue[rear++] = current->right;  // 큐에 추가
        }
    }

    return root;  // 생성된 트리의 루트 노드 반환
}

// 이진 트리에서 가장 넓은 너비를 찾는 함수
void maxWidthBT(TreeNode* root) {
    if (!root) return;              // 루트가 없으면 함수 종료

    int max_width = 0;              // 가장 넓은 너비를 저장하기 위한 변수
    Queue* queue = createQueue(1000); // 큐 생성
    enqueue(queue, root, 0);       // 루트 노드와 ID 0을 큐에 추가

    while (!isQueueEmpty(queue)) {  // 큐가 비어있지 않는 동안
        int level_length = queue->rear - queue->front + 1; // 현재 레벨의 노드 수
        NodeID first = queue->items[queue->front]; // 큐의 첫 번째 항목을 가져옴

        for (int i = 0; i < level_length; i++) { // 해당 레벨의 모든 노드를 확인
            NodeID current = dequeue(queue); // 현재 노드 가져오기
            if (current.node->left) {
                enqueue(queue, current.node->left, current.id * 2); // 왼쪽 자식 추가
            }
            if (current.node->right) {
                enqueue(queue, current.node->right, current.id * 2 + 1); // 오른쪽 자식 추가
            }
            if (i == level_length - 1) { // 레벨의 마지막 노드라면
                // 최대 너비 갱신
                max_width = max_width > (current.id - first.id + 1) ? max_width : (current.id - first.id + 1);
            }
        }
    }

    printf("%d\n", max_width);      // 최대 너비 출력
    free(queue->items);             // 큐의 아이템 배열 메모리 해제
    free(queue);                    // 큐 메모리 해제
}


// binary tree print 하는 방법
// void printTree(TreeNode* root) {
//     if (!root) return;
//     printf("%d ", root->val);
//     printTree(root->left);
//     printTree(root->right);
// }


int main() {
    int input[1000]; // 입력 배열
    int input_size = 0;       // 입력 배열의 크기
    char line[1000]; // 한 줄의 입력을 저장할 문자열
    char *token;


    printf("Enter node values in [a,b,c,...] format: ");
    fgets(line, sizeof(line), stdin); // 입력 받기
    line[strcspn(line, "\n")] = 0; // 개행 문자 제거

    // 괄호와 쉼표로 토큰 분리하여 파싱
    token = strtok(line, "[,]"); // 첫 토큰
    while(token != NULL) {
        if (strcmp(token, "None") == 0) {
            input[input_size++] = -1;
        } else {
            input[input_size++] = atoi(token);
        }
        token = strtok(NULL, "[,]"); // 다음 토큰
    }

    TreeNode* root = list_to_btree(input, input_size);
    // printTree(root);

    maxWidthBT(root);

    return 0;
}

