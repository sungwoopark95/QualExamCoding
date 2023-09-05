/*
[현재 binary tree가 BST인지 확인하는 코드 ]
Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

The left  subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % g++ -std=c++17 98_ValidateBST_SM.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test                                      
Enter the list of integers separated by spaces: [2,1,3]
True

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test
Enter the list of integers separated by spaces: [5,1,4,null,null,3,6]
False
Explanation: The root node's value is 5 but its right child's value is 4.
*/

#include <iostream>  // 기본 입출력 라이브러리를 포함합니다.
#include <vector>    // vector 자료구조를 사용하기 위한 라이브러리를 포함합니다.
#include <queue>     // 큐 자료구조를 사용하기 위한 라이브러리를 포함합니다.
#include <stdbool.h>
#include <climits>   // inf 설정위해
#include <sstream>

using namespace std;

// 노드 구조체를 정의합니다.
struct TreeNode {
    int val;                // 노드의 값을 저장하는 변수입니다.
    TreeNode* left;         // 왼쪽 자식 노드를 가리키는 포인터입니다.
    TreeNode* right;        // 오른쪽 자식 노드를 가리키는 포인터입니다.
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}  // 생성자 함수. 초기값 x를 받아서 노드의 값을 설정하고, 자식 노드들은 NULL로 초기화합니다.
};

TreeNode* list_to_btree(vector<int>& nums) {
    if (nums.empty()) return nullptr;  // nums 벡터가 비어있다면 nullptr(=NULL)을 반환합니다.

    queue<TreeNode*> queue;  // TreeNode 포인터 타입의 큐를 선언합니다.

    TreeNode* root = new TreeNode(nums[0]);  // 벡터의 첫 번째 값을 가지는 루트 노드를 생성합니다.
    queue.push(root);  // 생성한 루트 노드를 큐에 추가합니다.

    int i = 1;  // 인덱스 변수 i를 선언하고 1로 초기화합니다. 0번 인덱스는 루트 노드에 사용되었으므로 1부터 시작합니다.
    while (!queue.empty() && i < nums.size()) {  // 큐가 비어있지 않고, i가 nums 벡터의 크기보다 작은 동안 반복합니다.
        TreeNode* current = queue.front();  // 현재 처리할 노드(부모 노드)를 큐에서 가져옵니다.
        queue.pop();  // 처리한 노드는 큐에서 제거합니다.

        if (nums[i] != -1) {  // 현재 인덱스의 값이 -1 (Python의 None에 해당)이 아니라면
            TreeNode* left_child = new TreeNode(nums[i]);  // 왼쪽 자식 노드를 생성합니다.
            current->left = left_child;  // 현재 처리 중인 부모 노드의 왼쪽 자식으로 연결합니다.
            queue.push(left_child);  // 왼쪽 자식 노드를 큐에 추가합니다.
        }
        i++;  // 인덱스를 1 증가시킵니다.

        if (i < nums.size() && nums[i] != -1) {  // i가 nums 벡터의 크기보다 작고, 현재 인덱스의 값이 -1이 아니라면
            TreeNode* right_child = new TreeNode(nums[i]);  // 오른쪽 자식 노드를 생성합니다.
            current->right = right_child;  // 현재 처리 중인 부모 노드의 오른쪽 자식으로 연결합니다.
            queue.push(right_child);  // 오른쪽 자식 노드를 큐에 추가합니다.
        }
        i++;  // 인덱스를 1 증가시킵니다.
    }

    return root;  // 최종적으로 생성된 루트 노드를 반환합니다.
}

// dfs로 돌면서 binary search tree인지 체크하기
int lower = INT_MIN;
int upper = INT_MAX;

bool dfs_BT(TreeNode* node, int lower, int upper){
    // tree가 없으니 BST라고 가정함 (base case)
    if(!node)
        return true;

    // 현재 node값이 현재 최소값보다 작으면 (범위 밖에 있으면)
    if(node->val <= lower)
        return false;
    
    // 현재 node값이 현재 최대값보다 크면 (범위 밖에 있으면)
    else if (node->val >= upper)
        return false;
    // and 연결하면 return 2개 동시에 가능 (boolean이어서 둘다 참이면 true)
    // right에서 upper는 얼마나 크든 상관 없지만 right node가 현재 노드보다 작으면 안되서 설정함
    return(dfs_BT(node->right, node->val, upper) && dfs_BT(node->left, lower, node->val));
}

bool isValidBST(vector<int>& root){
    // list를 Binary tree로 변환 (TreeNode)
    TreeNode* tree = list_to_btree(root);

    return dfs_BT(tree, lower, upper);
}


int main() {
    // 사용자에게 숫자 리스트를 입력하라는 메시지를 출력
    cout << "Enter the list of integers separated by spaces: ";
    string line;
    getline(cin, line); // 전체 라인을 읽음

    // 불필요한 문자들 제거
    for (auto& c : line) {
        if (c == '[' || c == ']' || c == ',') {
            c = ' '; // 대괄호와 쉼표를 공백으로 교체
        }
    }

    istringstream iss(line);
    int num;
    vector<int> v;
    // stringstream을 사용하여 공백을 기준으로 숫자를 파싱
    while (iss >> num) {
        v.push_back(num); // 파싱한 숫자를 벡터에 추가
    }

    if(isValidBST(v))
        cout << "True" << endl;
    else
        cout << "False" << endl;

    return 0;
}