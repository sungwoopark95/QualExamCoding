/*
[node key의 빈도가 most frequently인 node key를 list로 반환하는 문제]
해당 bst는 left subtree는 해당 root와 key 값이 작거나 같고
right subtree도 해당 root와 key 값이 크거나 같다.

이럴때, node key의 빈도가 most frequently인 node key를 list로 반환하는 문제

Given the root of a binary search tree (BST) with duplicates, 
return all the mode(s) (i.e., the most frequently occurred element) in it.

If the tree has more than one mode, return them in any order.

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test
Enter node values in [a,b,c,...] format: [1,None,2,2]
[2]
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test
Enter node values in [a,b,c,...] format: [0] 
[0]
*/

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <algorithm>
#include <map>


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


vector<int> findMode(TreeNode* root) {
    if (!root) return {}; // 루트가 없으면 빈 벡터를 반환합니다.

    queue<TreeNode*> q;         // TreeNode 포인터를 저장하기 위한 큐입니다.
    map<int, int> cnt;         // 노드 값의 빈도수를 저장하기 위한 맵입니다.

    q.push(root);  // 루트 노드를 큐에 추가합니다.
    
    while (!q.empty()) {
        TreeNode* cur = q.front();  // 현재 노드를 큐의 앞에서 꺼냅니다.
        q.pop(); // 현재 노드를 큐에서 제거합니다.

        // 현재 노드의 값을 맵에서 증가시킵니다.
        cnt[cur->val]++;

        // 오른쪽 자식 노드가 있으면 큐에 추가합니다.
        if (cur->right) q.push(cur->right);

        // 왼쪽 자식 노드가 있으면 큐에 추가합니다.
        if (cur->left) q.push(cur->left);
    }

    int mode = -1;
    vector<int> ans;

    // 맵에서 가장 빈도수가 높은 값을 찾습니다.
    for (auto& [key, val] : cnt) {
        if (val > mode) mode = val;
    }

    // 해당 빈도수를 가진 키를 벡터에 추가합니다.
    for (auto& [key, val] : cnt) {
        if (val == mode) ans.push_back(key);
    }

    return ans;  // 결과 벡터를 반환합니다.
}

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

    TreeNode* root = vectorToTree(input); // 이진 탐색 트리 생성
    vector<int> result = findMode(root); 

    // 최종 결과 프린트하기
    cout << "[";
    for (int i = 0; i < result.size(); i++){
        cout  << result[i];
        if(i != result.size() - 1){
            cout << ", ";
        }
    }
    cout << "]" << endl;

}

/* ------------------------- 챗지피티 답 버전 -------------------------------*/

// #include <iostream>
// #include <vector>
// #include <map>
// #include <algorithm>
// #include <functional>

// using namespace std;

// class TreeNode {
// public:
//     int val;
//     TreeNode* left;
//     TreeNode* right;
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
// };

// vector<int> findMode(TreeNode* root) {
//     // 빈도수를 저장할 map과 결과 vector 초기화
//     map<int, int> count;
//     vector<int> result;

//     // 중위 순회 함수
//     function<void(TreeNode*)> inorder = [&](TreeNode* node) {
//         if (!node) return;

//         inorder(node->left);

//         // 현재 노드의 값의 빈도수를 1 증가
//         if (count.find(node->val) != count.end()) {
//             count[node->val]++;
//         } else {
//             count[node->val] = 1;
//         }

//         inorder(node->right);
//     };

//     // 트리를 중위 순회하며 각 값의 빈도수를 계산
//     inorder(root);

//     // 가장 높은 빈도수 찾기
//     int max_count = INT_MIN;
//     for (auto& [key, val] : count) {
//         max_count = max(max_count, val);
//     }

//     // 가장 높은 빈도수를 가진 값을 결과 벡터에 추가
//     for (auto& [key, val] : count) {
//         if (val == max_count) {
//             result.push_back(key);
//         }
//     }

//     return result;
// }
