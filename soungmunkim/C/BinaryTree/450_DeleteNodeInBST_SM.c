/*
[BST에서 특정 노드 삭제하기]
!! TreeNode class만 주어졌을 때 !!
> deleteNode(list, key:int) 형태임

< 구헌된 함수들 >
Queue
Dynamic string array
Dynamic int array 
구현되어 있음 

1. create_BST
    Insert
2. transplant
3. delete
4. seach
5. minimum
5. print_BST
    inorder
    level order(왼쪽에서 오른쪽)
    null 표시하게 프린트 or null 없이 프린트

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % g++ -std=c++17 450_DeleteNodeInBST_SM.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test                                           
Enter node values in [a,b,c,...] format: [5,3,6,2,4,None,7]
Enter the key to delete: 3
5 4 6 2 Null Null 7 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*--------------------- TreeNode class 구현 시작--------------------------------*/
typedef struct TreeNode {
    int key;
    struct TreeNode* parent;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 새로운 TreeNode 생성 함수
TreeNode* createNode(int key) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->key = key;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}


/*-------------Linked list기반 Queue class 구현 시작--------------------------------*/
typedef struct QueueNode {
    TreeNode* value;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;


// 큐 관련 함수들
void initializeQueue(Queue* q) {
    q->front = q->rear = NULL;
}

bool isEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, TreeNode* value) {
    QueueNode* newNode = malloc(sizeof(QueueNode));
    newNode->value = value;
    newNode->next = NULL;
    if (q->rear) {
        q->rear->next = newNode;
    } else {
        q->front = newNode;
    }
    q->rear = newNode;
}

TreeNode* dequeue(Queue* q) {
    if (isEmpty(q)) {
        return NULL;
    }
    QueueNode* oldFront = q->front;
    TreeNode* returnValue = oldFront->value;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(oldFront);
    return returnValue;
}

/*---------------- Dynamic String Array (동적할당 list) class 구현 시작--------------------------------*/
typedef struct {
    char** strings;
    int size;
    int capacity;
} DynamicStringArray;


void initializeDynamicStringArray(DynamicStringArray* array) {
    array->size = 0;
    array->capacity = 10;
    array->strings = malloc(array->capacity * sizeof(char*));
}

void pushBack(DynamicStringArray* array, const char* str) {
    if (array->size >= array->capacity) {
        array->capacity *= 2;
        array->strings = realloc(array->strings, array->capacity * sizeof(char*));
    }
    array->strings[array->size] = strdup(str); // 문자열 복사
    array->size++;
}

void popBack(DynamicStringArray* array) {
    if (array->size == 0) return;
    free(array->strings[array->size - 1]);
    array->size--;
}


/*--------------------- insert 함수 구현--------------------------------*/
TreeNode* insert(TreeNode* root, int key) {
    if (!root) {
        return createNode(key);
    }
    if (key < root->key) {
        if (!root->left) {
            root->left = createNode(key);
            root->left->parent = root;
        } else {
            root->left = insert(root->left, key);
        }
    } else {
        if (!root->right) {
            root->right = createNode(key);
            root->right->parent = root;
        } else {
            root->right = insert(root->right, key);
        }
    }
    return root;
}

/*--------------------List에서 BST 만들기 (Insert함수 이용)--------------------------*/
TreeNode* create_BST(int* input_list, int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert(root, input_list[i]);
    }
    return root;
}

/*------------------ (delete 위해) transplant 함수 구현-----------------------*/
TreeNode* transplant(TreeNode* root, TreeNode* u, TreeNode* v) {
    if (!u->parent) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    if (v) {
        v->parent = u->parent;
    }

    return root;
}

/*----------------------- (delete or get target 찾는) search 함수 구현 -----------------*/
TreeNode* search(TreeNode* node, int key) {
    while (node && key != node->key) {
        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}

/*-------------------------- minimum node 찾는 함수 구현------------------------*/
TreeNode* minimum(TreeNode* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

/*------------------------ delete 함수 구현 ---------------------------------*/
TreeNode* delete_node(TreeNode* root, int key) {
    TreeNode* z = search(root, key);

    if (z) {
        if (!z->left) {
            root = transplant(root, z, z->right);
            free(z); // C에서는 free 함수를 사용하여 메모리 해제
        } else if (!z->right) {
            root = transplant(root, z, z->left);
            free(z);
        } else {
            TreeNode* y = minimum(z->right);

            if (y->parent != z) {
                root = transplant(root, y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            root = transplant(root, z, y);
            y->left = z->left;
            y->left->parent = y;
            free(z);
        }
    }
    return root;
}

/*--------(Null 프린트 없이) 왼쪽에서 오른쪽 방향으로 BFS 형태로 프린트 하기 ----------------*/
DynamicStringArray print_BST(TreeNode* node) {

    DynamicStringArray result; // 동적 문자열 배열을 위한 변수 선언
    initializeDynamicStringArray(&result); // 동적 문자열 배열 초기화

    if (!node) { // 만약 노드가 NULL이면
        return result; // 초기화된 결과를 그대로 반환
    }

    Queue queue; // 큐 선언
    initializeQueue(&queue); // 큐 초기화
    enqueue(&queue, node); // 노드를 큐에 추가

    char buffer[20]; // 노드 값(key)를 문자열로 변환하기 위한 버퍼

    while (!isEmpty(&queue)) { // 큐가 비어있지 않는 동안 반복

        TreeNode* current = dequeue(&queue); // 큐에서 노드를 하나 꺼냄
        
        if (current) { // 노드가 NULL이 아니라면
            snprintf(buffer, sizeof(buffer), "%d", current->key); // 노드의 키 값을 버퍼에 문자열로 변환
            pushBack(&result, buffer); // 결과 배열에 문자열 추가
            if (current->left) enqueue(&queue, current->left);  // NULL 노드가 아니면 큐에 추가
            if (current->right) enqueue(&queue, current->right);  // NULL 노드가 아니면 큐에 추가
        }
    }

    // 큐에서 꺼낸 노드들 중 마지막의 "Null" 문자열들을 제거
    while (result.size > 0 && strcmp(result.strings[result.size - 1], "Null") == 0) {
        popBack(&result);
    }

    return result; // 결과 배열 반환
}


/*----------- (None node Null로 프린트) 왼쪽에서 오른쪽 방향으로 BFS 형태로 프린트 하기 -----------*/
// DynamicStringArray print_BST(TreeNode* node) {
//     DynamicStringArray result;
//     initializeDynamicStringArray(&result);

//     Queue queue;
//     initializeQueue(&queue);
//     enqueue(&queue, node);

//     char buffer[20];

//     while (!isEmpty(&queue)) {
//         TreeNode* current = dequeue(&queue);
        
//         if (current) {
//             snprintf(buffer, sizeof(buffer), "%d", current->key);
//             pushBack(&result, buffer);
//             enqueue(&queue, current->left);
//             enqueue(&queue, current->right);
//         } else {
//             pushBack(&result, "Null");
//         }
//     }

//     while (result.size > 0 && strcmp(result.strings[result.size - 1], "Null") == 0) {
//         popBack(&result);
//     }

//     return result;
// }


/*---------------- Dynamic int Array (int 동적할당 list) class 구현 시작--------------------------------*/
// typedef struct {
//     int* data;
//     int size;
//     int capacity;
// } IntArray;

// void initializeIntArray(IntArray* array) {
//     array->size = 0;
//     array->capacity = 10;
//     array->data = malloc(array->capacity * sizeof(int));
// }

// void pushIntArray(IntArray* array, int value) {
//     if (array->size >= array->capacity) {
//         array->capacity *= 2;
//         array->data = realloc(array->data, array->capacity * sizeof(int));
//     }
//     array->data[array->size] = value;
//     array->size++;
// }

/*------------- inorder traversal 순서대로 프린트 --------------*/
// void inorderTraversal(TreeNode* node, IntArray* result) {
//     if (node) {
//         inorderTraversal(node->left, result);
//         pushIntArray(result, node->key);
//         inorderTraversal(node->right, result);
//     }
// }

// IntArray print_BST(TreeNode* node) {
//     IntArray result;
//     initializeIntArray(&result);
//     inorderTraversal(node, &result);
//     return result;
// }

#define MAX_INPUT_SIZE 1000

int main() {
    int input[MAX_INPUT_SIZE]; // 입력 배열
    int input_size = 0;       // 입력 배열의 크기
    char line[MAX_INPUT_SIZE]; // 한 줄의 입력을 저장할 문자열
    char *token;
    int key;

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

    printf("Enter the key to delete: ");
    scanf("%d", &key); // 삭제할 키 값을 입력 받기

    TreeNode* root = create_BST(input, input_size); // 이진 탐색 트리 생성
    root = delete_node(root, key); // 노드 삭제

    // print_BST 함수에서 반환되는 DynamicStringArray에서 strings를 가져오는 부분
    DynamicStringArray resultArray = print_BST(root); 
    char** output = resultArray.strings;

    for (int i = 0; i < resultArray.size; i++) {
        printf("%s ", output[i]);
        free(output[i]);
    }
    printf("\n");

    free(output);  // 결과 문자열 배열 해제
    return 0; 
}
