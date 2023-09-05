#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;

// Definition for TreeNode
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x);
    vector<int> printTree();
};

TreeNode::TreeNode(int x) {
    this->val = x;
    this->left = NULL;
    this->right = NULL;
}

vector<int> TreeNode::printTree() {
    vector<int> result;
    vector<TreeNode*> thislevel;
    thislevel.push_back(this);

    int none_list;
    while (!thislevel.empty()) {
        vector<TreeNode*> nextlevel;
        none_list = 1;
        for (TreeNode* n : thislevel) {
            if (n != NULL) {
                none_list = 0;
                break;
            }
        }
        if (none_list == 1) {
            return result;
        }

        for (TreeNode* n : thislevel) {
            if (n != NULL) {
                result.push_back(n->val);
                nextlevel.push_back(n->left);
                nextlevel.push_back(n->right);
            } else {
                result.push_back(NULL);
                nextlevel.push_back(NULL);
                nextlevel.push_back(NULL);
            }
        }
        thislevel = nextlevel;
    }
    return result;
}

TreeNode* create_linked_bst(vector<int>& arr) {
    if (arr.size() < 1) {
        return NULL;
    }
    auto it = arr.begin();
    TreeNode* tree = new TreeNode(*it++);
    queue<TreeNode*> fringe;
    fringe.push(tree);

    while (it != arr.end()) {
        TreeNode* head = fringe.front();
        fringe.pop();

        head->left = new TreeNode(*it++);
        fringe.push(head->left);
        head->right = new TreeNode(*it++);
        fringe.push(head->right);
    }

    return tree;
}

int main() {
    vector<int> arr = {10, 5, 15, 3, 7, NULL, 18};
    TreeNode* root = create_linked_bst(arr);
    vector<int> result = root->printTree();

    cout << "[";
    for (int i=0;i<result.size()-1;i++) {
        cout << result[i] << ", ";
    }
    cout << result[result.size()-1] << "]" << endl;

    return 0;
}