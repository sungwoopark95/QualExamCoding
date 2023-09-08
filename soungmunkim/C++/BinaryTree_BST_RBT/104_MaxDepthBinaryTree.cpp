/*
[Binary tree maximum depth 찾기]
Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes 
    along the longest path from the root node down to the farthest leaf node.


root = [3, 9, 20, None, None, 15, 7]
head = list_to_btree(root)
maxDepth(head) # 3

Input: root = [1,null,2]
Output: 2
*/

#include <iostream>
#include <algorithm>

// 이진 트리 노드 구조체 정의
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 주어진 코드의 maxDepth 함수

int maxDepth(TreeNode* root) {
    if (!root) return 0;
    int mL = maxDepth(root->left);
    int mR = maxDepth(root->right);
    return std::max(mL, mR) + 1;
}

// 테스트 케이스 및 메인 함수

int main() {
    // 이진 트리 생성
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    
    // maxDepth 함수를 호출하여 최대 깊이를 구합니다.
    int depth = maxDepth(root);
    
    // 결과 출력
    std::cout << "Maximum Depth of Binary Tree: " << depth << std::endl;
    
    // 메모리 해제
    delete root->left->right;
    delete root->left->left;
    delete root->right;
    delete root->left;
    delete root;
    
    return 0;
}
