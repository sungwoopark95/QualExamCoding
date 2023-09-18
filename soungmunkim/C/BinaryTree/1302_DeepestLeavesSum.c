/*
[제일 깊은 leaves의 합 구하기]

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test                             
Enter node values in [a,b,c,...] format: [1,2,3,4,5,None,6,7,None,None,None,None,8]
15

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test                             
Enter node values in [a,b,c,...] format: [6,7,8,2,7,1,3,9,None,1,4,None,None,None,5]
19
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*---------------------------------- Tree Node class + list to Binary Tree ---------------------------------*/
// 이진 트리 노드 구조체
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 새로운 노드 생성 함수
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


/*--------------------------------- Dynamic array class -----------------------------------*/
// 동적 배열을 위한 구조체 정의
typedef struct {
    int* array;       // 정수 배열 포인터
    int size;         // 현재 배열의 크기
    int capacity;     // 할당된 메모리의 크기
} Vector;

// 2차원 동적 배열을 위한 구조체 정의
typedef struct {
    Vector* array;    // Vector 구조체 배열 포인터
    int size;         // 현재 2차원 배열의 크기
    int capacity;     // 할당된 메모리의 크기
} Vector2D;

// Vector 구조체를 위한 함수들

// 새로운 Vector 인스턴스 생성
Vector createVector() {
    Vector v;
    v.size = 0;                         // 초기 크기는 0
    v.capacity = 10;                    // 초기 용량은 10
    v.array = (int*)malloc(sizeof(int) * v.capacity);  // 메모리 할당
    return v;
}

// Vector의 마지막에 원소 추가
void push_back(Vector* v, int val) {
    if (v->size == v->capacity) {       // 현재 배열이 가득 찼다면
        v->capacity *= 2;               // 용량을 2배로 확장
        v->array = (int*)realloc(v->array, sizeof(int) * v->capacity);  // 메모리 재할당
    }
    v->array[v->size++] = val;          // 원소 추가 후 size 증가
}

// Vector의 마지막 원소 반환
int back(Vector* v) {
    return v->array[v->size - 1];
}

// Vector의 마지막 원소 제거
void pop_back(Vector* v) {
    v->size--;
}

// Vector 메모리 해제
void freeVector(Vector* v) {
    free(v->array);   // 동적 할당된 배열 메모리 해제
    v->size = 0;      // 크기 초기화
    v->capacity = 0;  // 용량 초기화
}


/*--------------------------------- Dynamic nested array class (2D array) -----------------------------------*/
// Vector2D 구조체를 위한 함수들

// 새로운 Vector2D 인스턴스 생성
Vector2D createVector2D() {
    Vector2D v;
    v.size = 0;                         // 초기 크기는 0
    v.capacity = 10;                    // 초기 용량은 10
    v.array = (Vector*)malloc(sizeof(Vector) * v.capacity);  // 메모리 할당
    return v;
}

// Vector2D의 메모리를 해제하는 함수
void freeVector2D(Vector2D* v) {
    for (int i = 0; i < v->size; i++) {
        freeVector(&v->array[i]);
        v->array[i].array = NULL; // 각 Vector의 메모리를 해제한 후, 포인터를 NULL로 설정
    }
    free(v->array);
    v->array = NULL; // Vector2D의 배열 포인터를 NULL로 설정
    v->size = 0;
    v->capacity = 0;
}

// Vector2D의 마지막에 Vector 원소를 추가하는 함수
void push_back_2D(Vector2D* v, Vector vec) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->array = (Vector*)realloc(v->array, sizeof(Vector) * v->capacity);
    }
    // 새로운 메모리를 할당하고 vec의 내용을 복사
    v->array[v->size].size = vec.size;
    v->array[v->size].capacity = vec.capacity;
    v->array[v->size].array = (int*)malloc(sizeof(int) * vec.capacity);
    memcpy(v->array[v->size].array, vec.array, sizeof(int) * vec.size);
    v->size++;
}

/*-------------------------------root to leaf 경로 찾는 함수 -----------------------------------*/
// 모든 root-to-leaf 경로를 찾는 함수
void findPaths(TreeNode* root, Vector* current_path, Vector2D* paths) {
    if (!root) return;  // 노드가 없다면 반환

    push_back(current_path, root->val);  // 현재 경로에 노드의 값을 추가

    // 리프 노드인 경우
    if (!root->left && !root->right) {
        push_back_2D(paths, *current_path);  // 현재 경로를 2차원 동적 배열에 추가
    } else {  // 리프 노드가 아닌 경우
        findPaths(root->left, current_path, paths);  // 왼쪽 자식 노드로 이동
        findPaths(root->right, current_path, paths);  // 오른쪽 자식 노드로 이동
    }

    pop_back(current_path);  // 백트래킹: 현재 경로에서 마지막 노드 제거
}

// 가장 깊은 잎 노드들의 합을 계산하는 함수
int deepestLeavesSum(TreeNode* root) {
    Vector2D all_paths = createVector2D();  // 모든 경로를 저장할 2차원 동적 배열 생성
    Vector current_path = createVector();  // 현재 경로를 저장할 동적 배열 생성

    findPaths(root, &current_path, &all_paths);  // 모든 경로 찾기

    int max_len = -1;  // 가장 깊은 경로의 길이를 저장할 변수 초기화
    // 가장 긴 경로의 길이 찾기
    for (int i = 0; i < all_paths.size; i++) {
        int cur_len = all_paths.array[i].size;
        if (cur_len > max_len) {
            max_len = cur_len;
        }
    }

    int sum = 0;  // 잎 노드들의 합을 저장할 변수
    // 가장 깊은 잎 노드들의 값을 합산
    for (int i = 0; i < all_paths.size; i++) {
        if (all_paths.array[i].size == max_len) {
            sum += back(&all_paths.array[i]);  // 경로의 마지막 원소 (잎 노드의 값) 합산
        }
    }

    freeVector(&current_path);  // 현재 경로 동적 배열 메모리 해제
    freeVector2D(&all_paths);  // 모든 경로를 저장하는 2차원 동적 배열 메모리 해제

    return sum;  // 합산된 값을 반환
}

int main() {
    int nums[1000];  // 최대 1000개의 노드를 가정
    char line[10000];
    int len = 0;

    printf("Enter node values in [a,b,c,...] format: ");
    fgets(line, sizeof(line), stdin);
    char* token = strtok(line, "[], \n");

    while (token != NULL) {
        if (strcmp(token, "None") != 0 && strcmp(token, "null") != 0) {
            nums[len++] = atoi(token);  // 숫자로 변환하여 배열에 저장
        } else {
            nums[len++] = -1;  // None 값 처리
        }
        token = strtok(NULL, "[], \n");
    }

    TreeNode* tree = list_to_btree(nums, len);

    int result = deepestLeavesSum(tree);  // 목표 합을 갖는 경로 찾기

    printf("%d\n", result);

    return 0;
}

