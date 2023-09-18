/*
[node key의 빈도가 most frequently인 node key를 list로 반환하는 문제]
해당 bst는 left subtree는 해당 root와 key 값이 작거나 같고
right subtree도 해당 root와 key 값이 크거나 같다.

이럴때, node key의 빈도가 most frequently인 node key를 list로 반환하는 문제

Given the root of a binary search tree (BST) with duplicates, 
return all the mode(s) (i.e., the most frequently occurred element) in it.

If the tree has more than one mode, return them in any order.

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % gcc 501_FindModeInBST_SM.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test
숫자 리스트를 입력하세요: [1,None,2,2]
Output: [2]
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test
숫자 리스트를 입력하세요: [0] 
Output: [0]
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

// 빈도수와 해당 값을 저장하기 위한 구조체 정의
typedef struct {
    int val;    // 값
    int count;  // 해당 값의 빈도수
} ValueCount;

ValueCount* findMode(TreeNode* root, int* returnSize) {
    if (!root) {  // root가 NULL인 경우
        *returnSize = 0; // 반환할 사이즈를 0으로 설정
        return NULL; // NULL 반환
    }

    Queue* q = createQueue(1000);  // 큐 생성. 여기서는 큐의 크기를 1000으로 가정
    enqueue(q, root);  // 루트 노드 큐에 삽입
    ValueCount countArray[1000] = {0};  // 고유한 값을 저장할 배열. 최대 1000개의 고유한 값으로 가정
    int distinctValues = 0;  // 현재까지 발견된 고유한 값의 수

    while (!isQueueEmpty(q)) {  // 큐가 비어있지 않는 동안
        TreeNode* cur = dequeue(q);  // 큐에서 노드 하나를 가져옴

        int found = 0;  // 현재 값이 countArray에 있는지 여부 체크용 변수
        for (int i = 0; i < distinctValues; i++) {  // 기존에 저장된 고유한 값들을 순회
            if (countArray[i].val == cur->val) {  // 같은 값 발견시
                countArray[i].count++;  // 해당 값의 빈도수 증가
                found = 1;  // 발견 표시
                break;  // 더 이상 검사하지 않고 반복문 종료
            }
        }
        if (!found) {  // 값이 새롭게 발견된 경우
            countArray[distinctValues].val = cur->val;  // 새로운 고유한 값 저장
            countArray[distinctValues].count = 1;  // 빈도수 초기화
            distinctValues++;  // 고유한 값의 수 증가
        }

        if (cur->right) enqueue(q, cur->right);  // 오른쪽 자식 노드가 있다면 큐에 삽입
        if (cur->left) enqueue(q, cur->left);    // 왼쪽 자식 노드가 있다면 큐에 삽입
    }

    int mode = -1;  // 최빈값의 빈도수 초기화
    for (int i = 0; i < distinctValues; i++) {  // 모든 고유한 값들을 순회
        if (countArray[i].count >= mode) {  // 빈도수가 mode보다 크거나 같은 경우
            mode = countArray[i].count;  // mode 업데이트
        }
    }

    ValueCount* ans = (ValueCount*)malloc(sizeof(ValueCount) * distinctValues);  // 결과를 저장할 메모리 동적 할당
    int idx = 0;  // 결과 배열의 인덱스 초기화
    for (int i = 0; i < distinctValues; i++) {  // 모든 고유한 값들을 순회
        if (countArray[i].count == mode) {  // 해당 값의 빈도수가 mode와 같은 경우
            ans[idx] = countArray[i];  // 결과 배열에 추가
            idx++;  // 결과 배열 인덱스 증가
        }
    }

    *returnSize = idx;  // 결과 배열의 크기 설정
    return ans;  // 결과 배열 반환
}

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

    int returnSize;  // 결과 배열의 크기를 저장할 변수를 선언합니다.
    ValueCount* result = findMode(root, &returnSize);  

    // 결과를 출력합니다.
    printf("Output: [");
    for (int i = 0; i < returnSize; i++) {
        printf("%d", result[i].val);
        if (i < returnSize - 1) {
            printf(", ");
        }
    }
    printf("]\n");


    free(result); // 결과 배열에 할당된 메모리를 해제합니다.

    return 0;
}

/*------------------------- 챗지피티 답 버전 ------------------------------- */
/* inorder로 순회하면서 node 빈도 체크하는 방식*/
// // TreeNode 구조체 정의
// typedef struct TreeNode {
//     int val;                          // 노드의 값
//     struct TreeNode* left;            // 왼쪽 자식 노드를 가리키는 포인터
//     struct TreeNode* right;           // 오른쪽 자식 노드를 가리키는 포인터
// } TreeNode;

// // 중위 순회 함수를 위한 helper 함수
// void inorder(TreeNode* root, int* count, int* maxCount) {
//     if (!root) return;               // 현재 노드가 NULL이면 함수 종료
    
//     inorder(root->left, count, maxCount);  // 왼쪽 서브트리를 중위 순회

//     count[root->val] += 1;           // 현재 노드의 값에 대한 빈도수 증가
//     if(count[root->val] > *maxCount) {   // 만약 현재 노드의 빈도수가 최대 빈도수보다 크면
//         *maxCount = count[root->val];    // 최대 빈도수 업데이트
//     }

//     inorder(root->right, count, maxCount); // 오른쪽 서브트리를 중위 순회
// }

// int* findMode(TreeNode* root, int* returnSize) {
//     if (!root) {                     // 루트 노드가 NULL이면
//         *returnSize = 0;             // 결과 배열의 크기를 0으로 설정하고
//         return NULL;                 // NULL 반환
//     }

//     int* count = (int*)calloc(50000, sizeof(int));  // 최대 50000개의 고유한 값으로 가정하여 카운트 배열 할당 및 초기화
//     int maxCount = 0;                // 최대 빈도수 초기화
//     inorder(root, count, &maxCount); // 트리를 중위 순회하며 각 노드의 빈도수 계산

//     int* result = (int*)malloc(50000 * sizeof(int));  // 결과 배열 할당
//     *returnSize = 0;                  // 결과 배열의 크기 초기화

//     for (int i = 0; i < 50000; ++i) { // 카운트 배열을 순회
//         if (count[i] == maxCount) {  // 현재 값의 빈도수가 최대 빈도수와 같으면
//             result[*returnSize] = i;   // 결과 배열에 현재 값을 추가
//             (*returnSize)++;          // 결과 배열의 크기 증가
//         }
//     }

//     free(count);                      // 더 이상 필요하지 않은 count 배열 해제

//     return result;                    // 결과 배열 반환
// }

// int main() {
//     char input[1000];  // 충분한 크기의 입력 버퍼를 할당합니다.
//     printf("숫자 리스트를 입력하세요: ");
//     fgets(input, sizeof(input), stdin);  // 사용자로부터 입력을 받습니다.

//     // 입력에서 숫자 부분만 추출하여 배열에 저장합니다.
//     int nums[1000];  // 숫자를 저장할 배열을 선언합니다.
//     int numCount = 0;  // 숫자의 개수를 저장할 변수를 초기화합니다.

//     // 입력 문자열에서 ','와 'None' 또는 'null'을 기준으로 숫자를 추출합니다.
//     char* token = strtok(input, "[,]\n");
//     while (token != NULL) {
//         if (compareStrings(token, "None") || compareStrings(token, "null")) {
//             nums[numCount] = -1;  // 'None' 또는 'null'을 -1로 대체합니다.
//         } else {
//             nums[numCount] = atoi(token);  // 문자열을 정수로 변환하여 저장합니다.
//         }
//         numCount++;
//         token = strtok(NULL, "[,]\n");
//     }

//     // 변환된 숫자 배열과 개수를 이용하여 이진 트리를 생성합니다.
//     TreeNode* root = list_to_btree(nums, numCount);

//     int returnSize;  // 결과 배열의 크기를 저장할 변수를 선언합니다.
//     int* result = findMode(root, &returnSize);  

//     // 결과를 출력합니다.
//     printf("Output: [");
//     for (int i = 0; i < returnSize; i++) {
//         printf("%d", result[i].val);
//         if (i < returnSize - 1) {
//             printf(", ");
//         }
//     }
//     printf("]\n");


//     free(result); // 결과 배열에 할당된 메모리를 해제합니다.

//     return 0;
// }