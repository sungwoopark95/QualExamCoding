/*
[root부터 leaf까지 합이 target sum 합과 같은 모든 paths 찾기]

Enter node values in [a,b,c,...] format: [5,4,8,11,None,13,4,7,2,None,None,5,1]
Enter target sum: 22
[5, 4, 11, 2], [5, 8, 4, 5]

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test                                
Enter node values in [a,b,c,...] format: [1,2,3]
Enter target sum: 5
[]
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

// 주어진 타겟 합을 갖는 경로들을 찾는 함수
vector<vector<int>> hasPathSum2(vector<int>& nums, int target_sum) {
    vector<vector<int>> all_paths;
    TreeNode* tree = list_to_btree(nums);

    vector<int> current_path;
    findPaths(tree, current_path, all_paths);


    vector<vector<int>> ans;
    for (auto& path : all_paths) {
        int sum = 0;
        for (int num : path) {
            sum += num;
        }
        if (sum == target_sum) {
            ans.push_back(path);  // 타겟 합을 갖는 경로를 ans에 추가
        }
    }

    // cout << "Number of paths found: " << ans.size() << endl;
    return ans;
}

int main() {
    vector<int> input;  // 입력값들을 저장할 벡터
    string line;
    int targetSum;

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

    cout << "Enter target sum: ";
    cin >> targetSum;  // 타겟 합 입력받기

    vector<vector<int>> result = hasPathSum2(input, targetSum);  // 타겟 합을 갖는 경로들 찾기

    // 결과를 출력합니다. (필요한 경우 출력 형식을 조정할 수 있습니다.)
    if (result.empty()) { // 결과가 비어있을 경우 [] 출력
        cout << "[]"; 
    } else {
        for (size_t i = 0; i < result.size(); ++i) {
            cout << "[";
            for (size_t j = 0; j < result[i].size(); ++j) {
                cout << result[i][j];
                if (j != result[i].size() - 1)
                    cout << ", ";
            }
            cout << "]";
            if (i != result.size() - 1)
                cout << ", ";
        }
    }
    cout << endl;


    return 0;
}
