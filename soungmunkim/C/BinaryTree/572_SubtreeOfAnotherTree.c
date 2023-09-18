/*
[subroot의 tree가 해당 root tree의 subtree인지 체크하는 함수]

root = [3,4,5,1,2]
subroot = [4,1,2]
tree= list_to_btree(root)
subtree = list_to_btree(subroot)
isSubtree(tree, subtree)
>>> True

root = [3,4,5,1,2,None, None, None,None,0]
subroot = [4,1,2]
tree = list_to_btree(root)
subtree = list_to_btree(subroot)
isSame(tree, subtree)
>>> False

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test    
True
False
*/

#include <stdio.h>      // 기본 입출력 함수를 위한 헤더 파일
#include <stdbool.h>    // bool 타입을 사용하기 위한 헤더 파일
#include <stdlib.h>     // malloc, free 함수를 위한 헤더 파일
#include <string.h>     // 문자열 함수를 위한 헤더 파일

// 이진 트리의 노드를 정의하는 구조체
typedef struct TreeNode {
    int val;              // 노드의 값을 저장하는 변수
    struct TreeNode* left;   // 왼쪽 자식 노드를 가리키는 포인터
    struct TreeNode* right;  // 오른쪽 자식 노드를 가리키는 포인터
} TreeNode;

// 새로운 노드를 생성하여 반환하는 함수
TreeNode* newNode(int x) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode)); // 새 노드를 위한 메모리를 할당
    node->val = x;   // 노드의 값을 설정
    node->left = NULL;  // 초기에는 자식 노드가 없음
    node->right = NULL; // 초기에는 자식 노드가 없음
    return node;    // 생성된 노드의 포인터를 반환
}

// 숫자 배열을 이진 트리로 변환하는 함수
TreeNode* list_to_btree(int* nums, int len) {
    if (len == 0 || nums[0] == -1) return NULL;  // 배열이 비어 있거나 첫 원소가 -1인 경우 NULL 반환

    TreeNode* root = newNode(nums[0]);  // 첫 번째 원소로 루트 노드 생성
    TreeNode* queue[len];  // 노드들을 저장할 큐
    int front = 0, rear = 0;  // 큐를 위한 front, rear 인덱스 초기화

    queue[rear++] = root;  // 루트 노드를 큐에 삽입

    // 배열의 모든 원소를 순회하며 트리 생성
    for (int i = 1; i < len && front < rear; i++) {
        TreeNode* current = queue[front++];  // 큐의 맨 앞에 있는 노드를 가져옴

        // 왼쪽 자식 노드 생성
        if (nums[i] != -1) {
            current->left = newNode(nums[i]);  // 새 노드 생성
            queue[rear++] = current->left;     // 큐에 삽입
        }
        i++;  // 다음 원소로 이동

        // 오른쪽 자식 노드 생성
        if (i < len && nums[i] != -1) {
            current->right = newNode(nums[i]);
            queue[rear++] = current->right;
        }
    }

    return root;  // 생성된 트리의 루트 노드를 반환
}

// 두 이진 트리가 동일한지 확인하는 함수
bool isSame(TreeNode* root1, TreeNode* root2) {
    if (!root1 && !root2) return true;  // 둘 다 NULL이면 동일
    if (!root1 || !root2) return false; // 한쪽만 NULL이면 동일하지 않음

    if (root1->val != root2->val) return false;  // 값이 다르면 동일하지 않음

    // 왼쪽과 오른쪽 서브트리를 재귀적으로 확인
    return isSame(root1->left, root2->left) && isSame(root1->right, root2->right);
}

// 하나의 트리 안에 다른 트리가 포함되어 있는지 확인하는 함수
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (!root) return false;  // root가 NULL이면 false 반환
    if (isSame(root, subRoot)) return true;  // root와 subRoot가 동일한 트리면 true 반환

    // 왼쪽 또는 오른쪽 서브트리에서 subRoot와 동일한 트리를 찾는다
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

// 트리의 모든 노드를 삭제하는 함수
void deleteTree(TreeNode* node) {
    if (!node) return;  // 노드가 NULL이면 반환

    deleteTree(node->left);  // 왼쪽 서브트리 삭제
    deleteTree(node->right); // 오른쪽 서브트리 삭제
    free(node);  // 현재 노드 메모리 해제
}

int main() {
    // 첫 번째 예제 데이터
    int root1[] = {3, 4, 5, 1, 2};
    int subroot1[] = {4, 1, 2};

    // 예제 데이터를 이진 트리로 변환
    TreeNode* tree1 = list_to_btree(root1, sizeof(root1) / sizeof(root1[0]));
    TreeNode* subtree1 = list_to_btree(subroot1, sizeof(subroot1) / sizeof(subroot1[0]));

    // 서브트리 여부 확인 후 결과 출력
    if (isSubtree(tree1, subtree1)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    // 사용된 트리 메모리 해제
    deleteTree(tree1);
    deleteTree(subtree1);

    // 두 번째 예제 데이터
    int root2[] = {3, 4, 5, 1, 2, -1, -1, -1, -1, 0};
    int subroot2[] = {4, 1, 2};

    // 예제 데이터를 이진 트리로 변환
    TreeNode* tree2 = list_to_btree(root2, sizeof(root2) / sizeof(root2[0]));
    TreeNode* subtree2 = list_to_btree(subroot2, sizeof(subroot2) / sizeof(subroot2[0]));

    // 서브트리 여부 확인 후 결과 출력
    if (isSubtree(tree2, subtree2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    // 사용된 트리 메모리 해제
    deleteTree(tree2);
    deleteTree(subtree2);

    return 0;  // 프로그램 종료
}
