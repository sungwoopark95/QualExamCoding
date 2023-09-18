/*
주어진 이진 탐색 트리(BST)에서 두 주어진 노드의 최소 공통 조상(LCA) 노드를 찾아라.

"최소 공통 조상은 두 노드 p와 q에 대하여 p와 q 모두를 후손으로 갖는 T의 가장 낮은 노드로 정의된다. 
(이때, 노드가 자신의 후손이 될 수 있음을 허용한다.)"

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test
LCA of 2 and 8 is: 6
LCA of 2 and 4 is: 2
*/


#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <algorithm>


using namespace std;

// TreeNode 클래스 정의
class TreeNode {
public:
    int val;                // 노드의 값을 저장하는 변수입니다.
    TreeNode* left;         // 왼쪽 자식 노드를 가리키는 포인터입니다.
    TreeNode* right;        // 오른쪽 자식 노드를 가리키는 포인터입니다.
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}  // 생성자 함수. 초기값 x를 받아서 노드의 값을 설정하고, 자식 노드들은 NULL로 초기화합니다.
};

// 주어진 벡터를 이진 트리로 변환하는 함수
TreeNode* vectorToTree(vector<int>& nums) {
    if (nums.empty()) return nullptr;  // 빈 벡터이면 루트 노드는 NULL입니다.

    queue<TreeNode*> nodes;  // TreeNode 포인터 큐를 생성합니다.
    TreeNode* root = new TreeNode(nums[0]);  // 루트 노드를 생성합니다.
    nodes.push(root);  // 루트 노드를 큐에 추가합니다.

    int index = 1;  // 벡터 인덱스를 초기화합니다.
    while (!nodes.empty() && index < nums.size()) {
        TreeNode* current = nodes.front();  // 현재 노드를 큐에서 꺼냅니다.
        nodes.pop();  // 현재 노드를 큐에서 제거합니다.

        // 왼쪽 자식 노드 생성 및 연결
        if (nums[index] != -1) {
            current->left = new TreeNode(nums[index]);
            nodes.push(current->left);
        }
        index++;

        // 오른쪽 자식 노드 생성 및 연결
        if (index < nums.size() && nums[index] != -1) {
            current->right = new TreeNode(nums[index]);
            nodes.push(current->right);
        }
        index++;
    }

    return root;  // 생성된 이진 트리의 루트 노드를 반환합니다.
}

TreeNode* lowestCommonAncestor(TreeNode* root, int p, int q) {
    int smallest = min(p, q);  // p, q 중 작은 값을 smallest에 저장합니다.
    int largest = max(p, q);   // p, q 중 큰 값을 largest에 저장합니다.

    while (root) {
        // 가장 작은 값이 현재 노드 값보다 크면 right subtree로 이동합니다.
        if (smallest > root->val) {
            root = root->right;
        }
        // 가장 큰 값이 현재 노드 값보다 작으면 left subtree로 이동합니다.
        else if (largest < root->val) {
            root = root->left;
        }
        // 그렇지 않다면 (즉, smallest는 현재 노드의 값보다 작거나 같고, 
        // largest는 현재 노드의 값보다 크거나 같은 경우) 현재 노드는 LCA입니다.
        else {
            return root;  // 해당 노드를 반환합니다.
        }
    }

    return nullptr;  // 만약 LCA를 찾지 못했다면 nullptr을 반환합니다. (실제로는 이런 경우는 발생하지 않아야 합니다.)
}

int main() {
    vector<int> root1 = {6,2,8,0,4,7,9,-1,-1,3,5}; // -1은 None에 대응
    int p1 = 2, q1 = 8;
    TreeNode* tree1 = vectorToTree(root1);
    cout << "LCA of " << p1 << " and " << q1 << " is: " << lowestCommonAncestor(tree1, p1, q1)->val << endl; // 6이 출력되어야 함

    vector<int> root2 = {6,2,8,0,4,7,9,-1,-1,3,5};
    int p2 = 2, q2 = 4;
    TreeNode* tree2 = vectorToTree(root2);
    cout << "LCA of " << p2 << " and " << q2 << " is: " << lowestCommonAncestor(tree2, p2, q2)->val << endl; // 2가 출력되어야 함

    // 메모리 해제 필요...

    return 0;
}