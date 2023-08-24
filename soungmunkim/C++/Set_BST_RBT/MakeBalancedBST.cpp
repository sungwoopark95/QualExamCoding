/*
balanced bst 만들기
*/

#include <iostream>
#include <vector>

// TreeNode 클래스: 이진 트리의 노드를 표현하기 위한 클래스
struct TreeNode {
    int val;  // 노드의 값
    TreeNode* left;  // 왼쪽 자식 노드를 가리키는 포인터
    TreeNode* right;  // 오른쪽 자식 노드를 가리키는 포인터
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 중위 순회 함수: 주어진 노드를 시작으로 중위 순회를 하며 결과를 벡터에 저장
void inorder_traversal(TreeNode* node, std::vector<int>& result) {
    if (!node) return;
    inorder_traversal(node->left, result);  // 왼쪽 서브트리 순회
    result.push_back(node->val);  // 현재 노드의 값을 벡터에 추가
    inorder_traversal(node->right, result);  // 오른쪽 서브트리 순회
}

// 정렬된 벡터로부터 높이 균형 BST 생성 함수
TreeNode* sorted_list_to_BST(std::vector<int>& nums, int start, int end) {
    if (start > end) return nullptr;

    int mid = (start + end) / 2;  // 벡터의 중앙 인덱스 계산

    // 중앙 인덱스 값을 가진 노드를 루트 노드로 생성
    TreeNode* root = new TreeNode(nums[mid]);
    // 중앙 인덱스 왼쪽의 벡터를 사용하여 왼쪽 서브트리 생성
    root->left = sorted_list_to_BST(nums, start, mid - 1);
    // 중앙 인덱스 오른쪽의 벡터를 사용하여 오른쪽 서브트리 생성
    root->right = sorted_list_to_BST(nums, mid + 1, end);

    return root;  // 생성된 서브트리의 루트 노드 반환
}

// 주어진 이진 트리를 높이 균형 BST로 변환하는 함수
TreeNode* convert_to_BST(TreeNode* root) {
    // 중위 순회를 통해 트리의 모든 값을 벡터에 저장
    std::vector<int> values;
    inorder_traversal(root, values);

    // 정렬된 벡터를 이용해 높이 균형 BST 구성 후 반환
    return sorted_list_to_BST(values, 0, values.size() - 1);
}

// 변환된 BST 확인을 위한 중위 순회 출력 함수
void print_inorder(TreeNode* node) {
    if (!node) return;
    print_inorder(node->left);  // 왼쪽 서브트리 순회
    std::cout << node->val << " ";  // 현재 노드의 값 출력
    print_inorder(node->right);  // 오른쪽 서브트리 순회
}

int main() {
    // 예제 이진 트리 생성
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(7);
    root->right->right = new TreeNode(18);

    // 높이 균형 BST로 변환
    TreeNode* new_root = convert_to_BST(root);

    std::cout << "Converted Height Balanced BST (Inorder): ";
    print_inorder(new_root);
    std::cout << std::endl;

    return 0;
}
