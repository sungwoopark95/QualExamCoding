/*
숫자 리스트가 주어지면 그걸 그냥 binary tree로 변환하는 코드
*/


/*------------------ 완벽한 list 형태 (꽉 찬 형태)가 아니어도 binary tree로 구현 가능 -----------------*/
#include <iostream>  // 기본 입출력 라이브러리를 포함합니다.
#include <vector>    // vector 자료구조를 사용하기 위한 라이브러리를 포함합니다.
#include <queue>     // 큐 자료구조를 사용하기 위한 라이브러리를 포함합니다.

// 노드 구조체를 정의합니다.
struct TreeNode {
    int val;                // 노드의 값을 저장하는 변수입니다.
    TreeNode* left;         // 왼쪽 자식 노드를 가리키는 포인터입니다.
    TreeNode* right;        // 오른쪽 자식 노드를 가리키는 포인터입니다.
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}  // 생성자 함수. 초기값 x를 받아서 노드의 값을 설정하고, 자식 노드들은 NULL로 초기화합니다.
};

TreeNode* list_to_btree(std::vector<int>& nums) {
    if (nums.empty()) return nullptr;  // nums 벡터가 비어있다면 nullptr(=NULL)을 반환합니다.

    std::queue<TreeNode*> queue;  // TreeNode 포인터 타입의 큐를 선언합니다.

    TreeNode* root = new TreeNode(nums[0]);  // 벡터의 첫 번째 값을 가지는 루트 노드를 생성합니다.
    queue.push(root);  // 생성한 루트 노드를 큐에 추가합니다.

    int i = 1;  // 인덱스 변수 i를 선언하고 1로 초기화합니다. 0번 인덱스는 루트 노드에 사용되었으므로 1부터 시작합니다.
    while (!queue.empty() && i < nums.size()) {  // 큐가 비어있지 않고, i가 nums 벡터의 크기보다 작은 동안 반복합니다.
        TreeNode* current = queue.front();  // 현재 처리할 노드(부모 노드)를 큐에서 가져옵니다.
        queue.pop();  // 처리한 노드는 큐에서 제거합니다.

        if (nums[i] != -1) {  // 현재 인덱스의 값이 -1 (Python의 None에 해당)이 아니라면
            TreeNode* left_child = new TreeNode(nums[i]);  // 왼쪽 자식 노드를 생성합니다.
            current->left = left_child;  // 현재 처리 중인 부모 노드의 왼쪽 자식으로 연결합니다.
            queue.push(left_child);  // 왼쪽 자식 노드를 큐에 추가합니다.
        }
        i++;  // 인덱스를 1 증가시킵니다.

        if (i < nums.size() && nums[i] != -1) {  // i가 nums 벡터의 크기보다 작고, 현재 인덱스의 값이 -1이 아니라면
            TreeNode* right_child = new TreeNode(nums[i]);  // 오른쪽 자식 노드를 생성합니다.
            current->right = right_child;  // 현재 처리 중인 부모 노드의 오른쪽 자식으로 연결합니다.
            queue.push(right_child);  // 오른쪽 자식 노드를 큐에 추가합니다.
        }
        i++;  // 인덱스를 1 증가시킵니다.
    }

    return root;  // 최종적으로 생성된 루트 노드를 반환합니다.
}

// 주: 메모리 해제 및 필요한 추가 함수는 생략되었습니다. 필요하다면 추가해야 합니다.


/*------------------ 완벽한 list 형태 (꽉 찬 형태)여야 binary tree로 구현 가능 -----------------*/
// #include <vector>

// // TreeNode 구조체를 정의합니다.
// struct TreeNode {
//     int val;                      // 노드의 값을 저장하는 변수
//     TreeNode* left;               // 왼쪽 자식 노드를 가리키는 포인터
//     TreeNode* right;              // 오른쪽 자식 노드를 가리키는 포인터
//     // 생성자: 노드 값을 초기화하고, 왼쪽/오른쪽 자식 포인터는 nullptr로 초기화합니다.
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
// };

// // 숫자 벡터를 이진 트리로 변환하는 함수
// TreeNode* list_to_btree(const std::vector<int>& nums) {
//     // 벡터가 비어있다면 nullptr을 반환합니다.
//     if (nums.empty()) return nullptr;

//     std::vector<TreeNode*> nodes;    // TreeNode 포인터들의 벡터를 선언합니다.
//     // nums의 각 숫자를 이진 트리의 노드로 변환하여 nodes 벡터에 추가합니다.
//     for (int num : nums) {
//         nodes.push_back(new TreeNode(num));
//     }

//     // nodes 벡터를 사용하여 이진 트리를 구성합니다.
//     for (int i = 1; i < nums.size(); i++) {
//         // i가 홀수면 해당 노드를 왼쪽 자식으로 설정합니다.
//         if (i % 2 == 1) nodes[(i-1)/2]->left = nodes[i];
//         // i가 짝수면 해당 노드를 오른쪽 자식으로 설정합니다.
//         else nodes[(i-2)/2]->right = nodes[i];
//     }

//     // 루트 노드를 반환합니다.
//     return nodes[0];
// }
