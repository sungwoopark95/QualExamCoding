/*
숫자 리스트를 binary search tree로 변환하는 코드
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

int main() {
    BinarySearchTree bst;
    std::vector<int> nums = {4, 2, 8, 1, 3, 7, 9};

    // 리스트 정렬
    bst.sortList(nums);

    // 정렬된 리스트를 이진 검색 트리로 변환
    TreeNode* root = bst.sortedListToBST(nums);

    // 트리 출력
    std::cout << "Binary Search Tree (Pre-order traversal): ";
    bst.printTree(root);
    std::cout << std::endl;

    return 0;
}
