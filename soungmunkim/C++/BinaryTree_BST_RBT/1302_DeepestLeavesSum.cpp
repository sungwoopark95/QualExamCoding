/*
[제일 깊은 leaves의 합 구하기]

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % g++ -std=c++17 1302_DeepestLeavesSum.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test                                          
Enter node values in [a,b,c,...] format: [1,2,3,4,5,None,6,7,None,None,None,None,8]
15

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % g++ -std=c++17 1302_DeepestLeavesSum.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test                                          
Enter node values in [a,b,c,...] format: [6,7,8,2,7,1,3,9,None,1,4,None,None,None,5]
19
*/

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

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

// 이진 트리의 모든 root-to-leaf 경로를 찾는 함수
void findPaths(TreeNode* root, vector<int>& current_path, vector<vector<int>>& paths) {
    if (!root) return;

    current_path.push_back(root->val);  // 현재 경로에 노드 값을 추가

    if (!root->left && !root->right) {
        paths.push_back(current_path);  // 리프 노드이면 경로를 paths에 추가
    } else {
        findPaths(root->left, current_path, paths);  // 왼쪽 서브트리 탐색
        findPaths(root->right, current_path, paths); // 오른쪽 서브트리 탐색
    }

    current_path.pop_back();  // 백트래킹: 현재 경로에서 노드 값을 제거
}

int deepestLeavesSum(TreeNode* nums){
    vector<vector<int>> all_paths;

    vector<int> current_path;
    findPaths(nums, current_path, all_paths);

    // max length가 무엇인지 찾기
    int max_len = -1;
    for(auto& path : all_paths){
        int cur_len = path.size();
        if(cur_len >= max_len){
            max_len = cur_len;      
            }
    }

    int sum = 0;
    for(auto& path: all_paths){
        if(path.size() == max_len){
            sum += path[path.size()-1];
        }
    }
    return sum;
}

/*------------------- BFS로 푸는 방식 ----------------------------*/
// int deepestLeavesSum(TreeNode* root) {
//     // root가 null이면, 0을 반환합니다.
//     if(!root) return 0;

//     // BFS를 위한 큐를 생성합니다.
//     std::queue<TreeNode*> q;
//     // root 노드를 큐에 넣습니다.
//     q.push(root);

//     int sum = 0;  // 각 레벨의 합을 저장하기 위한 변수

//     // 큐가 빌 때까지 반복합니다.
//     while(!q.empty()) {
//         sum = 0;  // 매 레벨마다 합을 리셋합니다.
//         int size = q.size();  // 현재 레벨의 노드 개수

//         // 현재 레벨의 모든 노드를 처리합니다.
//         for(int i = 0; i < size; i++) {
//             TreeNode* current = q.front(); q.pop();  // 큐의 맨 앞 노드를 꺼냅니다.
//             sum += current->val;  // 현재 노드의 값을 합에 추가합니다.

//             // 왼쪽 자식 노드가 있으면 큐에 추가합니다.
//             if(current->left) q.push(current->left);
//             // 오른쪽 자식 노드가 있으면 큐에 추가합니다.
//             if(current->right) q.push(current->right);
//         }
//     }

//     // 가장 깊은 레벨의 합을 반환합니다.
//     return sum;
// }


int main() {
    vector<int> input;  // 입력값들을 저장할 벡터
    string line;

    cout << "Enter node values in [a,b,c,...] format: ";
    getline(cin, line);  // 한 줄의 입력값 받기

    stringstream ss(line.substr(1, line.size() - 2));  // 입력값 파싱을 위한 stringstream 사용
    string item;

    while (getline(ss, item, ',')) {  // 쉼표로 구분된 값을 파싱
        if (item != "None" && item != "null") {
            input.push_back(stoi(item));
        } else {
            input.push_back(-1);  // "None"이나 "null"은 -1로 변환
        }
    }
    TreeNode* tree = list_to_btree(input);

    int result = deepestLeavesSum(tree);  // 타겟 합을 갖는 경로들 찾기

    cout << result << endl;

    return 0;
}