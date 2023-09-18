#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
using namespace std;

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

/* ============================== 두 트리가 대칭인지 확인하는 함수 ============================== */ 
bool isSame(TreeNode* root1, TreeNode* root2) {
    // 두 노드 모두 NULL이면, 두 트리는 동일하므로 true 반환
    if (!root1 && !root2) { return true; }

    // 둘 중 하나의 노드만 NULL이면, 두 트리는 동일하지 않으므로 false 반환
    if (!root1 || !root2) { return false; }

    // 두 노드의 값이 다르면, 두 트리는 동일하지 않으므로 false 반환
    if (root1->val != root2->val) { return false; }

    // 위의 조건들을 모두 통과한 경우, 재귀적으로 왼쪽 서브트리와 오른쪽 서브트리가 동일한지 확인
    // 두 서브트리 모두 동일해야만 true 반환
    return isSame(root1->left, root2->right) && isSame(root1->right, root2->left);
};
/* ======================================================================================= */ 

/* ============================= 주어진 트리가 대칭인지 확인하는 함수 ============================= */ 
// 
bool isSymmetric(TreeNode* root) {
    // 트리의 왼쪽 서브트리와 오른쪽 서브트리가 대칭인지 확인
    return isSame(root->left, root->right);
}
/* ======================================================================================= */

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
    bool symmetric = isSymmetric(root);
    cout << "Is this tree symmetric? : " << symmetric << endl;

    return 0;
}