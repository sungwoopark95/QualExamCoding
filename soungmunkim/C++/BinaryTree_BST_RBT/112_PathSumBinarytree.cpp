/*
[root부터 마지막까지 한 path 합이 targetsum과 같은지]

Given the root of a binary tree and an integer targetSum, 
    return true if the tree has a root-to-leaf path 
    such that adding up all the values along the path equals targetSum.
    
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test
Enter node values in [a,b,c,...] format: [5,4,8,11,None,13,4,7,2,None,None,None,1]
Enter the Target Sum: 22
True

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test
Enter node values in [a,b,c,...] format: [1,2,3]
Enter the Target Sum: 5
False
*/

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <stdbool.h>

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

// 주어진 이진 트리에서 경로의 합이 주어진 목표 합과 일치하는지 확인하는 함수
bool hasPathSum(TreeNode* root, int target_sum) {
    if (!root) {
        return false;  // 빈 노드인 경우 합을 만족하는 경로가 없으므로 false 반환
    }

    // 현재 노드가 리프 노드이고 남은 합이 현재 노드의 값과 같다면
    if (!root->left && !root->right && root->val == target_sum) {
        return true;  // 합을 만족하는 경로를 찾았으므로 true 반환
    }

    // 현재 노드의 값을 현재 남은 합에서 뺍니다.
    target_sum -= root->val;

    // 왼쪽 서브트리나 오른쪽 서브트리 중 하나라도 합을 만족하는 경로가 있다면 true를 반환합니다.
    return hasPathSum(root->left, target_sum) || hasPathSum(root->right, target_sum);
}

// main function
int main() {
    vector<int> input; // 입력을 저장할 벡터
    string line; // 한 줄의 입력을 저장할 문자열
    int targetSum;

    cout << "Enter node values in [a,b,c,...] format: ";
    getline(cin, line); // 입력 받기

    // 괄호와 쉼표를 제거하고 파싱
    // 첫 번째와 마지막 문자를 제외한 나머지 부분의 문자열
    stringstream ss(line.substr(1, line.size() - 2)); 
    string item;


    while (getline(ss, item, ',')) {
        // 문자열이 "None"이 아니면 리스트에 추가
        if (item != "None" && item != "null") {
            input.push_back(stoi(item));
        }
    }


    cout << "Enter the Target Sum: ";
    cin >> targetSum; // 삭제할 키 값을 입력 받기

    TreeNode* root = vectorToTree(input); // 이진 탐색 트리 생성
    int result = hasPathSum(root, targetSum); 

    if (result)
        cout << "True" << endl;
    else
        cout << "False" << endl;

    return 0; // 프로그램 종료
}

// int main() {
//     // 이진 트리 생성 (예: [5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1])
//     TreeNode* root = new TreeNode(5);
//     root->left = new TreeNode(4);
//     root->right = new TreeNode(8);
//     root->left->left = new TreeNode(11);
//     root->left->left->left = new TreeNode(7);
//     root->left->left->right = new TreeNode(2);
//     root->right->left = new TreeNode(13);
//     root->right->right = new TreeNode(4);
//     root->right->right->right = new TreeNode(1);

//     int target_sum = 22;  // 목표 합

//     // 이진 트리에서 경로의 합이 목표 합과 일치하는지 확인하고 결과를 출력
//     bool result = hasPathSum(root, target_sum);
//     if (result) {
//         cout << "경로의 합이 목표 합과 일치합니다." << endl;
//     } else {
//         cout << "경로의 합이 목표 합과 일치하지 않습니다." << endl;
//     }

//     // 메모리 해제 (트리 삭제)
//     delete root->right->right->right;
//     delete root->right->right;
//     delete root->right;
//     delete root->right->left;
//     delete root->left->left->right;
//     delete root->left->left->left;
//     delete root->left->left;
//     delete root->left;
//     delete root;

//     return 0;
// }