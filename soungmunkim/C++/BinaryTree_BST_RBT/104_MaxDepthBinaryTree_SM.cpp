/*
[Binary tree maximum depth 찾기]
Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes 
    along the longest path from the root node down to the farthest leaf node.


(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test
숫자 리스트를 입력하세요: [3, 9, 20, None, None, 15, 7]
이진 트리의 최대 깊이: 3

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % g++ -std=c++17 104_MaxDepthBinaryTree_SM.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test
숫자 리스트를 입력하세요: [1,null,2]
이진 트리의 최대 깊이: 2
*/

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <sstream>

// using namespace std;

// // TreeNode 클래스 정의
// class TreeNode {
// public:
//     int val;                // 노드의 값을 저장하는 변수입니다.
//     TreeNode* left;         // 왼쪽 자식 노드를 가리키는 포인터입니다.
//     TreeNode* right;        // 오른쪽 자식 노드를 가리키는 포인터입니다.
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}  // 생성자 함수. 초기값 x를 받아서 노드의 값을 설정하고, 자식 노드들은 NULL로 초기화합니다.
// };

// // 주어진 벡터를 이진 트리로 변환하는 함수
// TreeNode* vectorToTree(vector<int>& nums) {
//     if (nums.empty()) return nullptr;  // 빈 벡터이면 루트 노드는 NULL입니다.

//     queue<TreeNode*> nodes;  // TreeNode 포인터 큐를 생성합니다.
//     TreeNode* root = new TreeNode(nums[0]);  // 루트 노드를 생성합니다.
//     nodes.push(root);  // 루트 노드를 큐에 추가합니다.

//     int index = 1;  // 벡터 인덱스를 초기화합니다.
//     while (!nodes.empty() && index < nums.size()) {
//         TreeNode* current = nodes.front();  // 현재 노드를 큐에서 꺼냅니다.
//         nodes.pop();  // 현재 노드를 큐에서 제거합니다.

//         // 왼쪽 자식 노드 생성 및 연결
//         if (nums[index] != -1) {
//             current->left = new TreeNode(nums[index]);
//             nodes.push(current->left);
//         }
//         index++;

//         // 오른쪽 자식 노드 생성 및 연결
//         if (index < nums.size() && nums[index] != -1) {
//             current->right = new TreeNode(nums[index]);
//             nodes.push(current->right);
//         }
//         index++;
//     }

//     return root;  // 생성된 이진 트리의 루트 노드를 반환합니다.
// }

// // 주어진 트리의 깊이를 계산하는 함수
// int maxDepth(TreeNode* root) {
//     if (!root) return 0;
//     int leftDepth = maxDepth(root->left);
//     int rightDepth = maxDepth(root->right);
//     return max(leftDepth, rightDepth) + 1;
// }

// int main() {
//     // 입력 벡터 생성
//     vector<int> inputVector = {3, 9, 20, -1, -1, 15, 7};

//     // 벡터를 이진 트리로 변환
//     TreeNode* root = vectorToTree(inputVector);

//     // 트리의 깊이를 계산하고 출력
//     int depth = maxDepth(root);
//     cout << "이진 트리의 최대 깊이: " << depth << endl;

//     return 0;
// }


/*------------- 사용자로부터 리스트 입력받고 사용할때 (None으로 입력 포함) ------------------*/
#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>

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

// 주어진 트리의 깊이를 계산하는 함수
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);
    return max(leftDepth, rightDepth) + 1;
}

int main() {
    // 사용자로부터 "[3, 9, 20, None, None, 15, 7]" 형태의 입력을 받습니다.
    cout << "숫자 리스트를 입력하세요: ";
    string input;
    getline(cin, input);

    // 입력 문자열을 파싱하여 숫자 리스트로 변환
    vector<int> inputVector;
    istringstream iss(input);
    string token;
    while (getline(iss, token, ',')) {
        // 문자열에서 공백 및 괄호 제거
        token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
        token.erase(remove(token.begin(), token.end(), '['), token.end());
        token.erase(remove(token.begin(), token.end(), ']'), token.end());

        if (token == "None" || token == "null")  {
            inputVector.push_back(-1);  // "None"을 -1로 변환합니다.
        } else {
            inputVector.push_back(stoi(token));
        }
    }

    // 벡터를 이진 트리로 변환
    TreeNode* root = vectorToTree(inputVector);

    // 트리의 깊이를 계산하고 출력
    int depth = maxDepth(root);
    cout << "이진 트리의 최대 깊이: " << depth << endl;

    return 0;
}
