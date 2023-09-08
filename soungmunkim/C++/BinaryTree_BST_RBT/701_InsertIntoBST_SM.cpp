/*
[특정 key를 BST에 넣는 코드]

You are given the root node of a binary search tree (BST) and a value to insert into the tree. 
Return the root node of the BST after the insertion. 
It is guaranteed that the new value does not exist in the original BST.

Notice that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % g++ -std=c++17 701_InsertIntoBST_SM.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test
Enter node values in [a,b,c,...] format: [4,2,7,1,3]\
Enter the key to insert: 5
BST after insertion: 4 2 7 1 3 5 %  

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test
Enter node values in [a,b,c,...] format: [4,2,7,1,3,None,None,None,None,None,None]
Enter the key to insert: 5
BST after insertion: 4 2 7 1 3 5 %  
*/

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

// TreeNode 클래스 정의
class TreeNode {
public:
    int key;                // 노드에 저장될 키 값
    TreeNode *parent;       // 부모 노드
    TreeNode *left;         // 왼쪽 자식 노드
    TreeNode *right;        // 오른쪽 자식 노드
    
    // 생성자 함수
    TreeNode(int value) : key(value), parent(nullptr), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {}  // 초기화 리스트를 이용한 생성자

    // BST에 노드를 삽입하는 함수
    void insert(int key) {
        root = insertRecursive(root, key);
    }

    // BST를 BFS 방식으로 프린트하는 함수
    void print() {
        if (!root) return;  // 루트가 없으면 반환

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            cout << current->key << " ";

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

private:
    TreeNode* insertRecursive(TreeNode* node, int key) {
        if (!node) return new TreeNode(key);

        if (key < node->key) {
            node->left = insertRecursive(node->left, key);
            node->left->parent = node;
        } else {
            node->right = insertRecursive(node->right, key);
            node->right->parent = node;
        }

        return node;
    }
};

int main() {
    BinaryTree tree;

    cout << "Enter node values in [a,b,c,...] format: ";
    string line;
    getline(cin, line); // 사용자로부터 한 줄 입력 받기

    // 대괄호 제거
    if (!line.empty() && line.front() == '[') line.erase(line.begin());
    if (!line.empty() && line.back() == ']') line.pop_back();

    istringstream iss(line);
    string token;
    while (getline(iss, token, ',')) { // 콤마를 기준으로 문자열 분리
        if (token != "None") {
            tree.insert(stoi(token)); // 문자열을 int로 변환 후 삽입
        }
    }

    cout << "Enter the key to insert: ";
    int key;
    cin >> key; // 키 값 입력 받기
    tree.insert(key);

    cout << "BST after insertion: ";
    tree.print();

    return 0;
}
