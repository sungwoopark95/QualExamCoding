/*
[BST에서 인접한 두 노드간의 abs 차이가 mim인 것 반환하기]

Given the root of a Binary Search Tree (BST), 
    return the minimum absolute difference between the values of any two different nodes in the tree.

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % g++ -std=c++17 530_MinAbsDiffBinarytree.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test                                             
Enter node values in [a,b,c,...] format: [4,2,6,1,3]
1

Input: root = [1,0,48,null,null,12,49]
Output: 1
*/

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class TreeNode {
public:
    int val;                 // 노드의 값을 저장할 멤버 변수
    TreeNode* left;          // 왼쪽 자식 노드를 가리키는 포인터
    TreeNode* right;         // 오른쪽 자식 노드를 가리키는 포인터
    
    // TreeNode 클래스의 생성자
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    // 정렬된 리스트를 이진 검색 트리로 변환하는 함수
    TreeNode* sortedListToBST(vector<int>& nums) {
        sortList(nums);
        return sortedListToBSTHelper(nums, 0, nums.size() - 1);
    }
    /*---------------Sorted list 만들기 (bubble sort 사용) --------------------*/
    // 리스트를 정렬하는 함수 (선택 정렬 사용)
    void sortList(vector<int>& nums) {
        for (size_t i = 0; i < nums.size() - 1; i++) {
            size_t min_idx = i;
            // 현재 위치부터 가장 작은 원소를 찾는 과정
            for (size_t j = i + 1; j < nums.size(); j++) {
                if (nums[j] < nums[min_idx]) {
                    min_idx = j;
                }
            }
            // 가장 작은 원소와 현재 원소를 교환
            if (min_idx != i) {
                swap(nums[i], nums[min_idx]);
            }
        }
    }

    // 이진 트리를 전위 순회하며 출력하는 함수
    void printTree(TreeNode* root) {
        if (root == nullptr) return;
        cout << root->val << " ";   // 현재 노드 출력
        printTree(root->left);           // 왼쪽 서브트리 출력
        printTree(root->right);          // 오른쪽 서브트리 출력
    }

private:
    // sortedListToBST 함수를 위한 재귀적 도우미 함수
    TreeNode* sortedListToBSTHelper(const vector<int>& nums, int start, int end) {
        // 시작 위치가 끝 위치보다 큰 경우 null 반환
        if (start > end) return nullptr;

        // 중간 위치 계산
        int mid = start + (end - start) / 2;
        // 중간 위치의 값으로 새로운 노드 생성
        TreeNode* root = new TreeNode(nums[mid]);

        // 왼쪽과 오른쪽 서브트리 생성
        root->left = sortedListToBSTHelper(nums, start, mid - 1);
        root->right = sortedListToBSTHelper(nums, mid + 1, end);

        return root;
    }
};

int getMinimumDifference(TreeNode* root) {
    int min_diff = INT_MAX;  // 최소 절대 차이를 저장하는 변수를 최대로 초기화합니다.
    TreeNode* prev = NULL;   // 이전 노드를 저장하는 포인터를 초기화합니다.

    // 중위 순회 함수를 정의합니다.
    function<void(TreeNode*)> inorderTraversal = [&](TreeNode* node) {
        if (node == NULL) {  // 노드가 NULL인 경우, 즉 더 이상 노드가 없을 때 함수를 종료합니다.
            return;
        }

        inorderTraversal(node->left);  // 왼쪽 서브트리를 중위 순회합니다.

        if (prev != NULL) {  // 이전 노드가 NULL이 아닌 경우
            int diff = abs(node->val - prev->val);  // 현재 노드와 이전 노드 사이의 차이를 계산합니다.
            min_diff = min(min_diff, diff);  // 최소 절대 차이를 갱신합니다.
        }

        prev = node;  // 현재 노드를 이전 노드로 설정합니다.

        inorderTraversal(node->right);  // 오른쪽 서브트리를 중위 순회합니다.
    };

    inorderTraversal(root);  // 중위 순회를 시작합니다.

    return min_diff;  // 최소 절대 차이를 반환합니다.
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
        if (item != "None" && item != "null") {
            input.push_back(stoi(item));
        }
    }
    // 연결 리스트 생성 및 출력
    BinarySearchTree* bst = new BinarySearchTree();
    TreeNode* head = bst->sortedListToBST(input);

    int result = getMinimumDifference(head);

    // 최종 결과 프린트하기
    cout << result << endl;

    return 0;
}







// #include <iostream>
// #include <vector>
// #include <climits>

// struct TreeNode {
//     int val;
//     TreeNode* left;
//     TreeNode* right;

//     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
// };

// int getMinimumDifference(TreeNode* root) {
//     int min_diff = INT_MAX;
//     TreeNode* prev = NULL;

//     function<void(TreeNode*)> inorderTraversal = [&](TreeNode* node) {
//         if (node == NULL) {
//             return;
//         }

//         inorderTraversal(node->left);

//         if (prev != NULL) {
//             int diff = abs(node->val - prev->val);
//             min_diff = min(min_diff, diff);
//         }

//         prev = node;

//         inorderTraversal(node->right);
//     };

//     inorderTraversal(root);

//     return min_diff;
// }

// TreeNode* createBinaryTree() {
//     TreeNode* root = new TreeNode(4);
//     root->left = new TreeNode(2);
//     root->left->left = new TreeNode(1);
//     root->left->right = new TreeNode(3);
//     root->right = new TreeNode(6);
//     root->right->right = new TreeNode(7);
//     return root;
// }

// int main() {
//     TreeNode* root = createBinaryTree();
//     int min_diff = getMinimumDifference(root);
//     cout << "최소 절대 차이: " << min_diff << endl;
//     return 0;
// }
