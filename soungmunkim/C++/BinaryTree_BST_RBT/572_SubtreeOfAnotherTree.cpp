/*
[subroot의 tree가 해당 root tree의 subtree인지 체크하는 함수]

root = [3,4,5,1,2]
subroot = [4,1,2]
tree= list_to_btree(root)
subtree = list_to_btree(subroot)
isSubtree(tree, subtree)
>>> True

root = [3,4,5,1,2,None, None, None,None,0]
subroot = [4,1,2]
tree = list_to_btree(root)
subtree = list_to_btree(subroot)
isSame(tree, subtree)
>>> False

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test    
True
False
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 이진 트리의 노드를 정의하는 클래스
class TreeNode {
public:
    int val;                // 노드의 값
    TreeNode* left;         // 왼쪽 자식 노드
    TreeNode* right;        // 오른쪽 자식 노드

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}  // 생성자
};

// 숫자 리스트를 이진 트리로 변환하는 함수
TreeNode* list_to_btree(const vector<int*>& nums) {
    if (nums.empty()) return nullptr;  // 입력 리스트가 비어있다면 nullptr 반환

    queue<TreeNode*> q;                // 노드를 담을 큐
    TreeNode* root = new TreeNode(*nums[0]);  // 루트 노드 생성
    q.push(root);                     // 루트 노드를 큐에 삽입

    int i = 1;                        // 리스트의 두 번째 요소부터 시작
    while (!q.empty() && i < nums.size()) {
        TreeNode* current = q.front(); // 큐의 맨 앞 노드 추출
        q.pop();

        if (nums[i]) {  // 왼쪽 자식 노드가 nullptr이 아니라면
            current->left = new TreeNode(*nums[i]);
            q.push(current->left);
        }
        i++;

        if (i < nums.size() && nums[i]) {  // 오른쪽 자식 노드가 nullptr이 아니라면
            current->right = new TreeNode(*nums[i]);
            q.push(current->right);
        }
        i++;
    }

    return root;   // 생성된 이진 트리의 루트 노드 반환
}

// 두 이진 트리가 동일한지 확인하는 함수
bool isSame(TreeNode* root1, TreeNode* subRoot) {
    if (!root1 && !subRoot) return true;  // 둘 다 nullptr이면 true
    if (!root1 || !subRoot) return false; // 한쪽만 nullptr이면 false

    if (root1->val != subRoot->val) return false;  // 값이 다르면 false

    // 재귀적으로 왼쪽과 오른쪽 서브 트리 모두 확인
    return isSame(root1->left, subRoot->left) && isSame(root1->right, subRoot->right);
}

// 트리 root가 subRoot를 서브트리로 가지고 있는지 확인
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (!root) return false;
    if (isSame(root, subRoot)) return true;  // root와 subRoot가 같으면 true

    // 재귀적으로 왼쪽 또는 오른쪽 서브 트리에서 subRoot를 찾음
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

// 트리의 메모리를 해제하는 함수
void deleteTree(TreeNode* node) {
    if (!node) return;  // nullptr이면 반환

    deleteTree(node->left);   // 왼쪽 서브트리 메모리 해제
    deleteTree(node->right);  // 오른쪽 서브트리 메모리 해제
    delete node;              // 현재 노드 메모리 해제
}

int main() {
    // 첫 번째 예제
    vector<int*> root1 = {new int(3), new int(4), new int(5), new int(1), new int(2)};
    vector<int*> subroot1 = {new int(4), new int(1), new int(2)};
    
    TreeNode* tree1 = list_to_btree(root1);
    TreeNode* subtree1 = list_to_btree(subroot1);

    if (isSubtree(tree1, subtree1)) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }

    deleteTree(tree1);
    deleteTree(subtree1);

    for(int* p : root1) delete p; 
    for(int* p : subroot1) delete p;  

    // 두 번째 예제
    vector<int*> root2 = {new int(3), new int(4), new int(5), new int(1), new int(2), nullptr, nullptr, nullptr, nullptr, new int(0)};
    vector<int*> subroot2 = {new int(4), new int(1), new int(2)};

    TreeNode* tree2 = list_to_btree(root2);
    TreeNode* subtree2 = list_to_btree(subroot2);

    if (isSubtree(tree2, subtree2)) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }

    deleteTree(tree2);
    deleteTree(subtree2);

    for(int* p : root2) delete p; 
    for(int* p : subroot2) delete p; 

    return 0;
}