/*
[binary tree의 오른쪽 side node만 프린트하기]

Given the root of a binary tree, imagine yourself standing on the right side of it, 
return the values of the nodes you can see ordered from top to bottom.

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % g++ -std=c++17 199_RightSideViewBinarytree.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test
Enter node values in [a,b,c,...] format: [1,2,3,None,5,None,4]
[1, 3, 4]

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test
Enter node values in [a,b,c,...] format: [1,None,3]
[1, 3]

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test
Enter node values in [a,b,c,...] format: []
[]
*/

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

// 이진 트리에서 오른쪽 뷰 노드 값 추출 함수
vector<int> rightSideView(TreeNode* root) {
    if (!root) return vector<int>();

    queue<TreeNode*> q;
    q.push(root);
    vector<int> ans;

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; i++) {
            TreeNode* a = q.front();
            q.pop();

            if (a->left) q.push(a->left);
            if (a->right) q.push(a->right);

            if (i == levelSize - 1) {
                ans.push_back(a->val);
            }
        }
    }

    return ans;
}

int main() {
     // 사용자에게 숫자 리스트를 입력하라는 메시지를 출력
    cout << "Enter node values in [a,b,c,...] format: ";
    vector<int> input; // 입력을 저장할 벡터
    string line;
    getline(cin, line); // 입력 받기

    // 괄호와 쉼표를 제거하고 파싱
    // 첫 번째와 마지막 문자를 제외한 나머지 부분의 문자열
    stringstream ss(line.substr(1, line.size() - 2)); 
    string item;


    while (getline(ss, item, ',')) {
        // 문자열이 "None"이 아니면 리스트에 추가
        if (item != "None") {
            input.push_back(stoi(item));
        }
    }
    // 연결 리스트 생성 및 출력
    TreeNode* head = vectorToTree(input);

    vector<int> result = rightSideView(head);

    // 최종 결과 프린트하기
    cout << "[";
    for (int i = 0; i < result.size(); i++){
        cout  << result[i];
        if(i != result.size() - 1){
            cout << ", ";
        }
    }
    cout << "]" << endl;

    return 0;
}