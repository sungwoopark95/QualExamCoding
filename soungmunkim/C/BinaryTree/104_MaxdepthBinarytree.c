#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 이진 트리 노드 구조체 정의
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 주어진 코드의 maxDepth 함수

int maxDepth(struct TreeNode* root) {
    if (!root) return 0;
    int mL = maxDepth(root->left);
    int mR = maxDepth(root->right);
    return fmax(mL, mR) + 1;
}

// 테스트 케이스 및 메인 함수

int main() {
    // 이진 트리 생성
    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    root->val = 1;
    
    struct TreeNode* node2 = malloc(sizeof(struct TreeNode));
    node2->val = 2;
    root->left = node2;
    
    struct TreeNode* node3 = malloc(sizeof(struct TreeNode));
    node3->val = 3;
    root->right = node3;
    
    struct TreeNode* node4 = malloc(sizeof(struct TreeNode));
    node4->val = 4;
    node2->left = node4;
    
    struct TreeNode* node5 = malloc(sizeof(struct TreeNode));
    node5->val = 5;
    node2->right = node5;
    
    // maxDepth 함수를 호출하여 최대 깊이를 구합니다.
    int depth = maxDepth(root);
    
    // 결과 출력
    printf("Maximum Depth of Binary Tree: %d\n", depth);
    
    // 메모리 해제
    free(root);
    free(node2);
    free(node3);
    free(node4);
    free(node5);
    
    return 0;
}
