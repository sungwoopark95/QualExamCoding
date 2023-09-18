#include <iostream>
#include <vector>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) {
        this->val = x;
        this->left = nullptr;
        this->right = nullptr;
    }
};

// Insert function implementation
TreeNode* insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);

    if (val < root->val) {
        if (root->left == nullptr) {
            root->left = new TreeNode(val);
        } else {
            insert(root->left, val);
        }
    } else {
        if (root->right == nullptr) {
            root->right = new TreeNode(val);
        } else {
            insert(root->right, val);
        }
    }
    return root;
}

// Create BST from List (using Insert function)
TreeNode* create_BST(const vector<int>& input_list) {
    TreeNode* root = nullptr;
    for (int item : input_list) {
        root = insert(root, item);
    }
    return root;
}

// Lowest common ancestor function for a given list
TreeNode* lowestCommonAncestorList(const vector<int>& root_list, int p_val, int q_val) {
    TreeNode* root = create_BST(root_list);
    TreeNode* p = new TreeNode(p_val);
    TreeNode* q = new TreeNode(q_val);

    TreeNode* min_node = p->val < q->val ? p : q;
    TreeNode* max_node = p->val < q->val ? q : p;

    vector<TreeNode*> min_parents, max_parents;

    TreeNode* curr = root;
    while (curr && curr->val != min_node->val) {
        min_parents.push_back(curr);
        curr = min_node->val < curr->val ? curr->left : curr->right;
    }
    if (curr) min_parents.push_back(curr);

    curr = root;
    while (curr && curr->val != max_node->val) {
        max_parents.push_back(curr);
        curr = max_node->val < curr->val ? curr->left : curr->right;
    }
    if (curr) max_parents.push_back(curr);

    size_t common_len = min(min_parents.size(), max_parents.size());
    vector<TreeNode*> common;
    for (size_t i = 0; i < common_len; ++i) {
        if (min_parents[i] == max_parents[i]) {
            common.push_back(min_parents[i]);
        }
    }

    if (common.empty()) {
        return nullptr;
    } else{
        return common.back();
    }
}

int main() {
    vector<int> root = {6,2,8,0,4,7,9,INT_MAX,INT_MAX,3,5}; // using INT_MAX for None
    int p = 3;
    int q = 5;

    TreeNode* result = lowestCommonAncestorList(root, p, q);
    if (result) {
        cout << result->val << endl;
    }
    return 0;
}
