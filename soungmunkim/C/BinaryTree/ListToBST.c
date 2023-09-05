/*
숫자 리스트를 Binary search tree로 변환하는 코드
*/

#include <stdio.h>
#include <stdlib.h>

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

int main() {
    int nums[] = {4, 2, 8, 1, 3, 7, 9};
    int size = sizeof(nums) / sizeof(nums[0]);

    // 리스트를 정렬합니다.
    bubbleSort(nums, size);

    // 정렬된 리스트를 이진 검색 트리로 변환합니다.
    TreeNode* root = sorted_list_to_bst(nums, 0, size - 1);

    // 여기에서는 출력을 하지 않았지만 필요하면 트리를 출력하는 코드를 추가할 수 있습니다.

    return 0;
}

