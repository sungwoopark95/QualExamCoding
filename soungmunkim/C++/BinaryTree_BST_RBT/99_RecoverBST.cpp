/*
[binary tree를 bst로 만들기]

Input: root = [1,3,null,null,2]
Output: [3,1,null,null,2]
Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.

Input: root = [3,1,4,null,null,2]
Output: [2,1,4,null,null,3]
Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % g++ -std=c++17 99_RecoverBST.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test                                  
[3, 1, Null, Null, 2]
[2, 1, 4, Null, Null, 3]
*/

/*------------------ 완벽한 list 형태 (꽉 찬 형태)가 아니어도 binary tree로 구현 가능 -----------------*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// TreeNode 클래스 정의
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 벡터를 이진 트리로 변환하는 함수
TreeNode* vectorToTree(vector<int>& nums) {
    if (nums.empty()) return nullptr;

    queue<TreeNode*> nodes;
    TreeNode* root = new TreeNode(nums[0]);
    nodes.push(root);

    int index = 1;
    while (!nodes.empty() && index < nums.size()) {
        TreeNode* current = nodes.front();
        nodes.pop();

        if (nums[index] != -1) {
            current->left = new TreeNode(nums[index]);
            nodes.push(current->left);
        }
        index++;

        if (index < nums.size() && nums[index] != -1) {
            current->right = new TreeNode(nums[index]);
            nodes.push(current->right);
        }
        index++;
    }

    return root;
}

// 중위 순회를 통해 트리 노드들과 해당 노드의 값을 벡터에 저장하는 함수
void inorder_traversal(TreeNode* root, vector<TreeNode*>& nodes, vector<int>& values) {
    if (!root) return;  // 현재 노드가 null이면 함수를 종료

    inorder_traversal(root->left, nodes, values);  // 왼쪽 서브트리를 중위 순회
    
    nodes.push_back(root);  // 현재 노드를 nodes 벡터에 추가
    values.push_back(root->val);  // 현재 노드의 값을 values 벡터에 추가

    inorder_traversal(root->right, nodes, values);  // 오른쪽 서브트리를 중위 순회
}

// 잘못된 BST를 수정하는 함수
void recoverTree(TreeNode* root) {
    vector<TreeNode*> nodes;  // 노드들을 저장할 벡터
    vector<int> values;  // 노드의 값을 저장할 벡터
    
    inorder_traversal(root, nodes, values);  // 중위 순회를 통해 nodes와 values 벡터를 채움
    sort(values.begin(), values.end());  // values 벡터를 오름차순으로 정렬
    
    // 모든 노드의 값을 정렬된 값으로 업데이트
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i]->val = values[i];
    }
}

// BST를 프린트하는 함수
vector<string> print_BST_wihtNull(TreeNode* node) {
    if (!node) {
        return {};  // 노드가 null이면 빈 벡터 반환
    }

    vector<string> output;  // 출력 결과를 저장할 벡터
    queue<TreeNode*> queue;  // BFS를 위한 큐
    queue.push(node);  // 초기 노드를 큐에 삽입

    // 큐가 비어있지 않은 동안 반복
    while (!queue.empty()) {
        TreeNode* current = queue.front();  // 큐의 첫 번째 노드를 가져옴
        queue.pop();  // 큐에서 해당 노드 제거

        if (current) {
            output.push_back(to_string(current->val));  // 현재 노드의 값을 결과 벡터에 추가
            queue.push(current->left);  // 현재 노드의 왼쪽 자식을 큐에 추가
            queue.push(current->right);  // 현재 노드의 오른쪽 자식을 큐에 추가
        } else {
            output.push_back("Null");  // 현재 노드가 null이면 "Null"을 결과 벡터에 추가
        }
    }

    // 결과의 끝에 있는 "Null"들을 제거
    while (!output.empty() && output.back() == "Null") {
        output.pop_back();
    }

    return output;  // 결과 벡터 반환
}

// BST를 프린트하는 함수 (without null)
vector<string> print_BST(TreeNode* node) {
    if (!node) {
        return {};  // 노드가 null이면 빈 벡터 반환
    }

    vector<string> output;  // 출력 결과를 저장할 벡터
    queue<TreeNode*> queue;  // BFS를 위한 큐
    queue.push(node);  // 초기 노드를 큐에 삽입

    // 큐가 비어있지 않은 동안 반복
    while (!queue.empty()) {
        TreeNode* current = queue.front();  // 큐의 첫 번째 노드를 가져옴
        queue.pop();  // 큐에서 해당 노드 제거

        if (current) {
            output.push_back(to_string(current->val));  // 현재 노드의 값을 결과 벡터에 추가
            // 노드가 null이 아닐 때만 자식 노드들을 큐에 추가
            if(current->left) queue.push(current->left);  // 현재 노드의 왼쪽 자식을 큐에 추가
            if(current->right) queue.push(current->right);  // 현재 노드의 오른쪽 자식을 큐에 추가
        }
    }

    return output;  // 결과 벡터 반환
}


int main() {
    vector<int> nums1 = {1, 3, -1, -1, 2};
    TreeNode* tree1 = vectorToTree(nums1);
    recoverTree(tree1);
    vector<string> output1 = print_BST_wihtNull(tree1);
    cout << "[";
    for (size_t i = 0; i < output1.size(); ++i) {
        cout << output1[i];
        if (i != output1.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;
    vector<int> nums2 = {3, 1, 4, -1, -1, 2, -1, -1, -1};
    TreeNode* tree2 = vectorToTree(nums2);
    recoverTree(tree2);
    vector<string> output2 = print_BST_wihtNull(tree2);
    cout << "[";
    for (size_t i = 0; i < output2.size(); ++i) {
        cout << output2[i];
        if (i != output2.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;


    return 0;
}
