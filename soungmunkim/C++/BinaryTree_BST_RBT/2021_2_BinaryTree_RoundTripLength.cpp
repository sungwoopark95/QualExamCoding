/*
[Tree가 주어졌을 때 가장 긴 Round trip length 구하기]
single path: 한 노드에서 시작해서 right or left 경로로 한 방향 따라가는거
round path: 특정 노드에 시작해서 subtree 타고 내려간 뒤 해당 노드로 돌아와 반대 subtree로 감
    = 두 개의 single path 결합한 것
    
** 원형 경로의 길이를 최대화하려면 각 서브트리에서의 단일 경로의 최대 길이를 사용해야 합니다.
    -> 각 노드에서 재귀적으로 단일 경로의 최대 길이를 계산하고, 이를 사용하여 원형 경로의 길이를 계산

** 해당 노드를 두번 들려야함 (출발 노드)

     1
    / \
   2   3    답은 4
   
      1
    /  \
   2    4
  /      \
3         5 답은 8


    1
     \
      2
     / \
    3   4
   /     \
  5       6   답은 8. 5에서 출발했다가 2까지 갔다가 6으로 갔다가 똑같이 돌아오면 됨. 꼭 Root를 거칠 필요 없음
*/

#include <iostream>
#include <algorithm>

using namespace std;

// 이진 트리의 노드를 표현하는 구조체
struct BTNode {
    int val;        // 노드의 값
    BTNode* left;   // 왼쪽 자식 노드 포인터
    BTNode* right;  // 오른쪽 자식 노드 포인터

    // 생성자: 값을 초기화하고 왼쪽, 오른쪽 자식 노드를 NULL로 설정
    BTNode(int x) : val(x), left(NULL), right(NULL) {}
};

int roundTripLongestRouteOfBT(BTNode* root) {
    // 도움 함수: 각 노드에서의 단일 경로와 원형 경로의 최대 길이를 계산
    function<pair<int, int>(BTNode*)> helper = [&](BTNode* node) -> pair<int, int> {
        // 노드가 NULL인 경우
        if (!node) return {0, 0};

        // 현재 노드가 리프 노드인 경우
        if (!node->left && !node->right) 
            return {0, 0};

        // 왼쪽 자식 노드만 없는 경우
        if (!node->left) {
            auto [roundLen, singleLen] = helper(node->right);
            return make_pair(max(roundLen, singleLen + 1), singleLen + 1);
        }

        // 오른쪽 자식 노드만 없는 경우
        if (!node->right) {
            auto [roundLen, singleLen] = helper(node->left);
            return make_pair(max(roundLen, singleLen + 1), singleLen + 1);
        }

        // 양쪽 자식 노드가 모두 있는 경우
        auto [l_roundLen, l_singleLen] = helper(node->left);
        auto [r_roundLen, r_singleLen] = helper(node->right);
        int roundLen = max(l_roundLen, r_roundLen);

        // 원형 경로와 단일 경로의 길이를 반환
        return make_pair(max(roundLen, l_singleLen + r_singleLen + 2), max(l_singleLen, r_singleLen) + 1);
    };

    // 함수의 결과를 반환
    return 2 * helper(root).first;
}

int main() {
    // 첫 번째 테스트 케이스
    // 트리 구성
    BTNode* tree4 = new BTNode(4);
    tree4->left = new BTNode(2);
    tree4->right = new BTNode(6);
    tree4->left->right = new BTNode(3);
    tree4->right->right = new BTNode(7);
    tree4->right->left = new BTNode(8);
    tree4->right->left->left = new BTNode(9);
    tree4->right->left->left->right = new BTNode(10);

    // 결과 출력
    cout << roundTripLongestRouteOfBT(tree4) << endl;  // 12

    // 두 번째 테스트 케이스
    // 트리 구성
    BTNode* tree9 = new BTNode(9);
    tree9->right = new BTNode(6);
    tree9->right->left = new BTNode(3);
    tree9->right->right = new BTNode(7);
    tree9->right->left->left = new BTNode(2);
    tree9->right->right->left = new BTNode(10);

    // 결과 출력
    cout << roundTripLongestRouteOfBT(tree9) << endl;  // 8

    // 메모리 누수 방지를 위해 동적 할당한 메모리를 해제해야 하지만, 여기서는 생략되었습니다.

    return 0;
}
