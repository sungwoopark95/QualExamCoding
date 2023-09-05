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


#include <stdio.h>
#include <stdlib.h>

// 이진 트리의 노드를 정의하는 구조체
typedef struct BTNode {
    int val;                 // 해당 노드가 가지는 값
    struct BTNode* left;    // 왼쪽 자식 노드에 대한 포인터
    struct BTNode* right;   // 오른쪽 자식 노드에 대한 포인터
} BTNode;

// 두 개의 정수 값을 저장하기 위한 Pair 구조체
typedef struct {
    int first;
    int second;
} Pair;

// 새로운 BTNode를 생성하고 초기화한 후 그 포인터를 반환하는 함수
BTNode* createNode(int x) {
    BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));   // 새 노드에 대한 메모리를 할당
    newNode->val = x;                                    // 값 설정
    newNode->left = NULL;                                // 초기에는 자식 노드가 없으므로 NULL로 설정
    newNode->right = NULL;                               
    return newNode;                                      // 새로 생성된 노드의 포인터 반환
}

// 주어진 노드에서 원형 경로의 최대 길이와 단일 경로의 최대 길이를 계산하는 재귀 함수
Pair helper(BTNode* node, int* diameter) {
    if (!node) return (Pair){0, 0};                      // 현재 노드가 NULL이면 (0, 0) 반환

    if (!node->left && !node->right)                     // 리프 노드인 경우
        return (Pair){0, 0};

    if (!node->left) {                                   // 왼쪽 자식만 없는 경우
        Pair rightResult = helper(node->right, diameter);    
        return (Pair){rightResult.second + 1, rightResult.second + 1};
    }

    if (!node->right) {                                  // 오른쪽 자식만 없는 경우
        Pair leftResult = helper(node->left, diameter);
        return (Pair){leftResult.second + 1, leftResult.second + 1};
    }

    Pair leftResult = helper(node->left, diameter);      // 왼쪽 서브트리에서의 결과
    Pair rightResult = helper(node->right, diameter);    // 오른쪽 서브트리에서의 결과

    int roundLen = leftResult.second + rightResult.second + 2; // 현재 노드를 기준으로 한 원형 경로의 길이

    if (*diameter < roundLen)                            // 지금까지 찾은 원형 경로의 최대 길이보다 크면 업데이트
        *diameter = roundLen;

    return (Pair){roundLen, (leftResult.second > rightResult.second ? leftResult.second : rightResult.second) + 1};
}

// 주어진 트리의 원형 경로의 최대 길이를 반환하는 함수
int roundTripLongestRouteOfBT(BTNode* root) {
    int diameter = 0;                                    // 원형 경로의 최대 길이를 저장할 변수
    helper(root, &diameter);                             // 도우미 함수 호출
    return 2 * diameter;                                 // 결과 반환
}

int main() {
    // 첫 번째 테스트 케이스 생성
    BTNode* tree4 = createNode(4);
    tree4->left = createNode(2);
    tree4->right = createNode(6);
    tree4->left->right = createNode(3);
    tree4->right->right = createNode(7);
    tree4->right->left = createNode(8);
    tree4->right->left->left = createNode(9);
    tree4->right->left->left->right = createNode(10);

    printf("%d\n", roundTripLongestRouteOfBT(tree4));  // 예상 출력: 12

    // 두 번째 테스트 케이스 생성
    BTNode* tree9 = createNode(9);
    tree9->right = createNode(6);
    tree9->right->left = createNode(3);
    tree9->right->right = createNode(7);
    tree9->right->left->left = createNode(2);
    tree9->right->right->left = createNode(10);

    printf("%d\n", roundTripLongestRouteOfBT(tree9));  // 예상 출력: 8

    return 0;
}
