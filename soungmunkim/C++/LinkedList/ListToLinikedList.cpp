#include <iostream>  // 입출력 관련 헤더 파일 포함
#include <vector>    // vector 컨테이너 사용을 위한 헤더 파일 포함

// ListNode 클래스 정의
class ListNode {
public:              // public 섹션 시작
    int val;        // 노드에 저장될 값
    ListNode* next; // 다음 노드를 가리키는 포인터

    // 생성자 정의. 노드 값을 초기화하고 next 포인터는 NULL로 설정
    ListNode(int x) : val(x), next(NULL) {}
};

// 벡터를 연결 리스트로 변환하는 함수 정의
ListNode* listToLinkedList(std::vector<int>& lst) {
    // 벡터가 비어 있는지 확인
    if (lst.empty()) {
        return nullptr;  // 비어 있으면 nullptr 반환
    }

    // 머리 노드를 동적 할당으로 생성하고 lst의 첫 번째 요소로 초기화
    ListNode* head = new ListNode(lst[0]);
    ListNode* current = head;  // 현재 노드를 머리 노드로 설정

    // 벡터의 나머지 요소들을 순회하며 연결 리스트의 노드 생성
    for (int i = 1; i < lst.size(); i++) {
        current->next = new ListNode(lst[i]); // 새 노드 생성 및 초기화
        current = current->next;  // 현재 노드를 새로 생성된 노드로 업데이트
    }

    return head;  // 연결 리스트의 머리 노드 반환
}
