/*
balanced BST 만들기
*/

#include <stdio.h>
#include <stdlib.h>

// 이진 트리의 노드를 표현하는 구조체
typedef struct TreeNode {
    int val;  // 노드의 값
    struct TreeNode* left;  // 왼쪽 자식 노드를 가리키는 포인터
    struct TreeNode* right;  // 오른쪽 자식 노드를 가리키는 포인터
} TreeNode;

// 주어진 값으로 새로운 노드를 생성하는 함수
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));  // 새 노드를 위한 메모리 할당
    newNode->val = value;  // 노드의 값 설정
    newNode->left = NULL;  // 왼쪽 자식 노드 초기화
    newNode->right = NULL;  // 오른쪽 자식 노드 초기화
    return newNode;  // 새로 생성된 노드 반환
}

// 중위 순회를 통해 트리의 노드 값을 배열에 저장하는 함수
void inorder_traversal(TreeNode* node, int* result, int* index) {
    if (!node) return;  // 현재 노드가 NULL이면 반환

    inorder_traversal(node->left, result, index);  // 왼쪽 서브트리 순회
    result[*index] = node->val;  // 배열에 현재 노드의 값을 저장
    (*index)++;  // 배열의 인덱스 증가
    inorder_traversal(node->right, result, index);  // 오른쪽 서브트리 순회
}

// 트리를 중위 순회하여 출력하는 함수
void print_inorder(TreeNode* node) {
    if (!node) return;  // 현재 노드가 NULL이면 반환

    print_inorder(node->left);  // 왼쪽 서브트리 순회
    printf("%d ", node->val);  // 현재 노드의 값 출력
    print_inorder(node->right);  // 오른쪽 서브트리 순회
}

// 정렬된 배열을 사용하여 높이 균형 BST를 생성하는 함수
TreeNode* sorted_list_to_BST(int* nums, int start, int end) {
    if (start > end) return NULL;  // 시작 인덱스가 종료 인덱스보다 크면 NULL 반환

    int mid = (start + end) / 2;  // 중간 인덱스 계산
    TreeNode* root = createNode(nums[mid]);  // 중간 인덱스의 값을 가진 노드 생성

    // 왼쪽 서브트리와 오른쪽 서브트리를 재귀적으로 생성
    root->left = sorted_list_to_BST(nums, start, mid - 1);  
    root->right = sorted_list_to_BST(nums, mid + 1, end);

    return root;  // 생성된 서브트리의 루트 노드 반환
}

// 주어진 이진 트리를 높이 균형 BST로 변환하는 함수
TreeNode* convert_to_BST(TreeNode* root, int size) {
    int* values = (int*)malloc(size * sizeof(int));  // 트리의 값을 저장할 배열 할당
    int index = 0;  // 배열의 인덱스 초기화

    inorder_traversal(root, values, &index);  // 중위 순회를 통해 배열에 트리의 값을 저장

    return sorted_list_to_BST(values, 0, size - 1);  // 배열을 사용하여 높이 균형 BST 생성 후 반환
}

int main() {
    // 예제 이진 트리 생성
    TreeNode* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->right = createNode(18);

    // 주어진 이진 트리를 높이 균형 BST로 변환
    TreeNode* newRoot = convert_to_BST(root, 6);  // 여기서 6은 트리의 노드 수

    // 변환된 트리를 중위 순회하여 출력
    printf("Converted Height Balanced BST (Inorder): ");
    print_inorder(newRoot);
    printf("\n");

    return 0;  // 프로그램 종료
}
