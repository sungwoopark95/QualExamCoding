/*
[BST에서 인접한 두 노드간의 abs 차이가 mim인 것 반환하기]

Given the root of a Binary Search Tree (BST), 
    return the minimum absolute difference between the values of any two different nodes in the tree.

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % gcc 530_MinAbsDiffBinarytree.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test
Enter node values in [a,b,c,...] format: [4,2,6,1,3]
1

Input: root = [1,0,48,null,null,12,49]
Output: 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// TreeNode 구조체를 정의합니다.
typedef struct TreeNode {
    int val;                      // 노드의 값을 저장하는 변수
    struct TreeNode* left;       // 왼쪽 자식 노드를 가리키는 포인터
    struct TreeNode* right;      // 오른쪽 자식 노드를 가리키는 포인터
} TreeNode;

// 리스트를 정렬하는 함수 (버블 정렬)
void bubbleSort(int* nums, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                // 두 요소를 교환합니다.
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }
}

// 정렬된 배열을 균형 잡힌 이진 검색 트리로 변환하는 함수
TreeNode* sorted_list_to_bst(int* nums, int start, int end) {
    int size = end - start + 1;
    bubbleSort(nums, size);

    // 시작 지점이 끝나는 지점보다 크면 NULL 반환 (재귀의 종료 조건)
    if (start > end) return NULL;

    // 중간 지점을 찾습니다.
    int mid = start + (end - start) / 2;

    // 새로운 노드를 위한 메모리를 할당하고 중간 값으로 초기화합니다.
    TreeNode* root = (TreeNode*) malloc(sizeof(TreeNode));
    root->val = nums[mid];

    // 왼쪽 하위 배열을 사용하여 왼쪽 서브트리를 구성합니다.
    root->left = sorted_list_to_bst(nums, start, mid - 1);
    
    // 오른쪽 하위 배열을 사용하여 오른쪽 서브트리를 구성합니다.
    root->right = sorted_list_to_bst(nums, mid + 1, end);

    // 현재 루트 노드를 반환합니다.
    return root;
}

// 이진 검색 트리에서 최소 절대 차이 계산 함수
int getMinimumDifference(struct TreeNode* root) {
    // 중위 순회를 위한 스택 구현
    struct TreeNode* stack[1000];
    int top = -1;  // 스택의 맨 위를 나타내는 인덱스

    struct TreeNode* current = root;
    struct TreeNode* prev = NULL;  // 이전 노드의 값을 저장

    int min_diff = INFINITY;  // 최소 절대 차이를 저장

    while (current != NULL || top != -1) {
        // 현재 노드의 왼쪽 자식들을 스택에 push
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        // 스택에서 노드를 pop하여 값을 처리
        current = stack[top--];

        // 이전 노드(prev)와 현재 노드(current)의 차이 계산
        if (prev != NULL) {
            int diff = abs(current->val - prev->val);
            if (diff < min_diff) {
                min_diff = diff;
            }
        }

        // 현재 노드를 prev에 저장하고 오른쪽 자식으로 이동
        prev = current;
        current = current->right;
    }

    return min_diff;
}


#define MAX_INPUT_SIZE 1000

int main() {
    int input[MAX_INPUT_SIZE]; // 입력 배열
    int input_size = 0;       // 입력 배열의 크기
    char line[MAX_INPUT_SIZE]; // 한 줄의 입력을 저장할 문자열
    char *token;

    printf("Enter node values in [a,b,c,...] format: ");
    fgets(line, sizeof(line), stdin); // 입력 받기
    line[strcspn(line, "\n")] = 0; // 개행 문자 제거

    // 괄호와 쉼표로 토큰 분리하여 파싱
    token = strtok(line, "[,]"); // 첫 토큰
    while(token != NULL) {
        // 문자열이 "None"이 아니면 배열에 추가
        if (strcmp(token, "None") != 0 && strcmp(token, "null") != 0) {
            input[input_size++] = atoi(token);
        }
        token = strtok(NULL, "[,]"); // 다음 토큰
    }

    // printf("%d\n", len(input));
    TreeNode* root = sorted_list_to_bst(input, 0, input_size - 1); // 이진 탐색 트리 생성
    int result = getMinimumDifference(root); 

    printf("%d\n", result);

    return 0; 
}
