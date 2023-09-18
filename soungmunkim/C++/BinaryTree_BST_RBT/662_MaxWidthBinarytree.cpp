/*
[rightmost와 leftmost (non null)포함 사이 node 개수가 최대인 것 찾기]

Given the root of a binary tree, 
    return the maximum width of the given tree.

The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes 
    (the leftmost and rightmost non-null nodes), 
    where the null nodes between the end-nodes that 
    would be present in a complete binary tree extending down to that 
    level are also counted into the length calculation.
    
            1 (ID:0)
         /           \
(ID:0)  2              3 (ID: 1)
       / \              \
(ID:0)4   5(ID:1) (ID:2) 7 (ID:3)
현재 노드의 ID * 2 와 현재 노드의 ID * 2 + 1은 
전형적인 이진 트리(Binary Tree)에서 배열을 사용하여 트리를 구현할 때 사용되는 인덱싱 방식

root = [1,3,2,5,3,None,9]
tree = list_to_btree(root)
widthOfBinaryTree(tree)
4

root = [1,3,2,5,None,None,9,6,None,7]
tree = list_to_btree(root)
widthOfBinaryTree(tree)
7

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % g++ -std=c++17 662_MaxWidthBinarytree.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test                                           
Enter node values in [a,b,c,...] format: [1,3,2,5,3,None,9]
4
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test                                           
Enter node values in [a,b,c,...] format: [1,3,2,5,None,None,9,6,None,7]
7
*/
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <tuple>

using namespace std;

// 이진 트리 노드의 정의
struct TreeNode {
    int val;               // 노드의 값
    TreeNode* left;        // 왼쪽 자식 노드 포인터
    TreeNode* right;       // 오른쪽 자식 노드 포인터
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}  // 생성자
};

// 숫자 리스트를 이진 트리로 변환하는 함수
TreeNode* list_to_btree(vector<int>& nums) {
    if (nums.empty()) return nullptr;  // 빈 리스트면 nullptr 반환

    queue<TreeNode*> nodes;             // 노드들을 저장할 큐
    TreeNode* root = new TreeNode(nums[0]);  // 루트 노드 생성
    nodes.push(root);

    int i = 1;  // 리스트 순회를 위한 인덱스
    while (!nodes.empty() && i < nums.size()) {
        TreeNode* current = nodes.front();
        nodes.pop();

        if (nums[i] != -1) {
            TreeNode* left_child = new TreeNode(nums[i]);
            current->left = left_child;
            nodes.push(left_child);
        }
        i++;

        if (i < nums.size() && nums[i] != -1) {
            TreeNode* right_child = new TreeNode(nums[i]);
            current->right = right_child;
            nodes.push(right_child);
        }
        i++;
    }

    return root;  // 만들어진 트리의 루트 노드 반환
}

void maxWidthBT(TreeNode* root){
    if (not root)
        return;

    int max_width = 0;
    // tuple 형태로 TreeNode 포인터와 int를 가지는 큐를 선언
    queue<tuple<TreeNode*, int>> queue;

     // root node와 id를 tuple로 queue에 넣고 시작
    queue.push(make_tuple(root, 0));

    TreeNode* cur;
    int cur_id;
    int first_id;
    // 현재 레벨의 모든 노드를 처리합니다.
    while (!queue.empty()) {
        int level_length = queue.size();
        tie(ignore, first_id) = queue.front();

        for(int i=0 ; i < level_length; i++){
            
            tie(cur, cur_id) = queue.front(); // 큐의 맨 앞에 있는 노드를 가져옴
            queue.pop(); // 여기서 큐에서 원소를 제거해야 합니다.

            if (cur->left) 
                queue.push(make_tuple(cur->left, cur_id*2));

            if (cur->right)
                queue.push(make_tuple(cur->right, cur_id*2 + 1));
        }
        max_width = max(max_width, cur_id - first_id + 1);
           
    }
    cout << max_width << endl;
}

// main function
int main() {
    vector<int> input; // 입력을 저장할 벡터
    string line; // 한 줄의 입력을 저장할 문자열


    cout << "Enter node values in [a,b,c,...] format: ";
    getline(cin, line); // 입력 받기

    // 괄호와 쉼표를 제거하고 파싱
    // 첫 번째와 마지막 문자를 제외한 나머지 부분의 문자열
    stringstream ss(line.substr(1, line.size() - 2)); 
    string item;


    while (getline(ss, item, ',')) {
        // 문자열이 "None"이 아니면 리스트에 추가
        if (item != "None") {
            input.push_back(stoi(item));
        } else {
            input.push_back(-1);  // "None"은 -1로 처리
        }
    }


    TreeNode* root = list_to_btree(input); // 이진 탐색 트리 생성
    maxWidthBT(root);
    

    return 0; // 프로그램 종료
}

