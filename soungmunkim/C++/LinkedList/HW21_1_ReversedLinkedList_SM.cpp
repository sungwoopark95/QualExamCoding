/*
[reversed linked list]
프로그램의 입력값(Argument)으로 Singly linked list의 각 Data값을 순서대로 입력 받은 뒤, 
순서를 뒤집은 Singly linked list로 만들고 이를 출력하는 함수를 작성하여라.
 (출력 시 node 사이에 공백이나 맨 마지막에 공백, new line 등은 불필요함) 

※ Command line argument 입력 시 각 node는 공백(space)으로 구분된다. 

TestCase1)
>>> ./P1 1 2 3 4 5
54321
*/

/* ------------------------ With Dummy Node --------------------------*/
#include <iostream>
#include <vector>

// singly linked list의 노드 정의
class ListNode {
public:
    int val;               // 노드의 값
    ListNode* next;        // 다음 노드를 가리키는 포인터

    // 생성자: 노드 값을 초기화하고 다음 노드는 nullptr로 설정
    ListNode(int x = 0, ListNode* nextNode = nullptr) : val(x), next(nextNode) {}
};

// 주어진 벡터를 기반으로 linked list 생성 후 head 노드 반환
ListNode* create_linked_list(const std::vector<int>& lst) {
    // 벡터가 비어있는 경우 nullptr 반환
    if (lst.empty()) {
        return nullptr;
    }

    // 첫 번째 노드 생성
    ListNode* start = new ListNode(lst[0]);
    ListNode* node = start;

    // 벡터의 나머지 요소들로 노드 생성
    for (int i = 1; i < lst.size(); i++) {
        node->next = new ListNode(lst[i]);
        node = node->next;
    }

    return start;
}

// linked list의 모든 값을 출력
void print_linked_list(ListNode* node) {
    while (node) {
        std::cout << node->val << " ";  // 현재 노드의 값을 출력
        node = node->next;              // 다음 노드로 이동
    }
    std::cout << std::endl;             // 한 줄 띄우기
}

// Dummy node를 사용하여 linked list 뒤집기
ListNode* P3(ListNode* head) {
    // 더미 노드 초기화
    ListNode dummy;

    // head가 nullptr이 될 때까지 노드들을 뒤집기
    while (head) {
        ListNode* cur = head;           // 현재 노드 저장
        head = head->next;              // head를 다음 노드로 이동

        cur->next = dummy.next;         // 현재 노드의 다음을 더미 노드의 다음 노드로 설정
        dummy.next = cur;               // 더미 노드의 다음을 현재 노드로 설정
    }

    return dummy.next;                  // 뒤집힌 linked list의 head 반환
}

int main() {
    // 예제 테스트
    ListNode* l1 = create_linked_list({4, 2, 1, 3});
    print_linked_list(P3(l1));         // 출력: 3 1 2 4

    ListNode* l2 = create_linked_list({-1, 5, 0, 2, 3});
    print_linked_list(P3(l2));         // 출력: 3 2 0 5 -1
}



/* ------------------------ Without Dummy Node --------------------------*/
// #include <iostream>
// #include <vector>

// // singly linked list의 노드 정의
// class ListNode {
// public:
//     int val;               // 노드의 값
//     ListNode* next;        // 다음 노드를 가리키는 포인터

//     // 생성자: 노드 값을 초기화하고 다음 노드는 nullptr로 설정
//     ListNode(int x = 0, ListNode* nextNode = nullptr) : val(x), next(nextNode) {}
// };

// // 주어진 벡터를 기반으로 linked list 생성 후 head 노드 반환
// ListNode* create_linked_list(const std::vector<int>& lst) {
//     // 벡터가 비어있는 경우 nullptr 반환
//     if (lst.empty()) {
//         return nullptr;
//     }

//     // 첫 번째 노드 생성
//     ListNode* start = new ListNode(lst[0]);
//     ListNode* node = start;

//     // 벡터의 나머지 요소들로 노드 생성
//     for (int i = 1; i < lst.size(); i++) {
//         node->next = new ListNode(lst[i]);
//         node = node->next;
//     }

//     return start;
// }

// // linked list의 모든 값을 출력
// void print_linked_list(ListNode* node) {
//     while (node) {
//         std::cout << node->val << " ";  // 현재 노드의 값을 출력
//         node = node->next;              // 다음 노드로 이동
//     }
//     std::cout << std::endl;             // 한 줄 띄우기
// }

// // Dummy node 없이 linked list 뒤집기
// ListNode* P3(ListNode* head) {
//     ListNode* prev = nullptr;           // 이전 노드 초기화
//     ListNode* cur = head;               // 현재 노드를 head로 설정
//     ListNode* next = nullptr;           // 다음 노드 초기화
    
//     // cur이 nullptr이 될 때까지 반복
//     while (cur != nullptr) {
//         next = cur->next;               // 다음 노드 저장
//         cur->next = prev;               // 현재 노드의 다음을 이전 노드로 설정
//         prev = cur;                     // 이전 노드를 현재 노드로 업데이트
//         cur = next;                     // 현재 노드를 다음 노드로 이동
//     }
    
//     return prev;                        // 뒤집힌 linked list의 head 반환
// }

// int main() {
//     // 예제 테스트
//     ListNode* l1 = create_linked_list({4, 2, 1, 3});
//     print_linked_list(P3(l1));         // 출력: 3 1 2 4

//     ListNode* l2 = create_linked_list({-1, 5, 0, 2, 3});
//     print_linked_list(P3(l2));         // 출력: 3 2 0 5 -1
// }
