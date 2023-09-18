/*
Binary Tree의 모든 node에 대해서, 해당 노드의 left subtree의 depth와 right subtree의 depth가 1보다 많이 차이나면 False, 1 이하로 차이나면 True
=> 모든 node에 대해 검사해야 하므로 recursion 필요!

vector<int*> root_list = {new int(3), new int(9), new int(20), nullptr, nullptr, new int(15), new int(7)};
TreeNode* root = list_to_btree(root_list);
cout << isBalanced(root) << endl; -> 1
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 노드들을 연결하기 위해 리스트를 순회하는 함수
TreeNode* list_to_btree(const vector<int*>& nums) {
    if (nums.empty()) {
        return nullptr;
    }
    queue<TreeNode*> queue;
    TreeNode* root = new TreeNode(*nums[0]);
    queue.push(root);

    int i = 1;
    while (!queue.empty() && i < nums.size()) {
        TreeNode* current = queue.front();
        queue.pop();
        if (nums[i]) {
            current->left = new TreeNode(*nums[i]);
            queue.push(current->left);
        }
        i++;
        if (i < nums.size() && nums[i]) {
            current->right = new TreeNode(*nums[i]);
            queue.push(current->right);
        }
        i++;
    }
    return root;
}

// 함수 bfs는 주어진 노드로부터 가장 깊은 깊이(레벨)를 반환합니다.
int bfs(TreeNode* root) {
    if (!root){
        return 0;
    }
    queue<pair<TreeNode*, int>> queue;
    queue.push({root, 0});
    int curr_level;
    while (!queue.empty()) {
        TreeNode* curr_node = queue.front().first;
        curr_level = queue.front().second;
        queue.pop();
        if (curr_node->left) queue.push({curr_node->left, curr_level + 1});
        if (curr_node->right) queue.push({curr_node->right, curr_level + 1});
    }
    return curr_level + 1;
}

// 트리의 루트 노드에서 시작하여 전체 트리가 균형 잡혔는지 판단하는 함수
bool isBalanced(TreeNode* root) {
    if (!root){
        return true;
    }
    int left_depth = bfs(root->left);
    int right_depth = bfs(root->right);
    if (abs(left_depth - right_depth) > 1){
        return false;
    }
    return isBalanced(root->left) && isBalanced(root->right);
}

int main() {
    vector<int*> root_list = {new int(3), new int(9), new int(20), nullptr, nullptr, new int(15), new int(7)};
    TreeNode* root = list_to_btree(root_list);
    cout << isBalanced(root) << endl;

    // Free allocated memory
    for (int* num : root_list) {
        delete num;
    }
}
