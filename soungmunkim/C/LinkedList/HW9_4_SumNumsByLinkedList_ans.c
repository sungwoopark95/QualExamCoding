/*
[두 linked list 받아서 더한 후 linked list로 return]
0 이상의 십진수 정수를 나타내는 Linked list 두 개가 주어질 때, 두 숫자의 합을 나타내는 Linked list를 만 드는 함수를 작성하여라. 
Input으로는 각 Linked list의 첫번째 Node가 주어지며, Return값 역시 Linked list 의 첫번째 Node이다.

예를 들어, 15와 30을 나타내는 Linked list, 즉 (1)->(5), (3)->(0)이 주어진다면, 
두 숫자의 합인 45를 나타 내는 Linked list (4)->(5)를 만들어 해당 Linked list의 첫번째 Node (head)를 반환하여야 한다.

※ Linked list 형태를 유지하며 계산할 것 (주어진 Linked list를 list로 변환하여 각 원소를 더하고, 이를 다 시 Linked list로 만드는 등의 풀이는 허용하지 않음)
※ Linked list의 각 Node는 linked_list_helper.py 파일에 정의되어 있는 ListNode를 활용하면 된다.
※ linked_list_helper.py 파일의 create_linked_list 함수와 print_linked_list 함수를 활용하여 아래와 같이 함 수의 동작을 확인할 수 있다.

TestCase1)
>>> l1 = create_linked_list([1,1,1]) 
>>> l2 = create_linked_list([1,1,1]) 
>>> print_linked_list(P4(l1, l2),[]) 
[2,2,2]
TestCase2)
>>> l1 = create_linked_list([0]) 
>>> l2 = create_linked_list([0]) 
>>> print_linked_list(P4(l1, l2),[]) 
[0]
*/


#include <stdio.h>
#include <stdlib.h>

// singly linked list의 노드 정의
typedef struct ListNode {
    int val;                // 노드의 값
    struct ListNode* next;  // 다음 노드를 가리키는 포인터
} ListNode;

// 새로운 노드를 만들고 값을 할당한 뒤 해당 노드의 주소를 반환
ListNode* newListNode(int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

// linked list를 뒤집는 함수
ListNode* reverseLinkedList(ListNode* node) {
    ListNode* prev = NULL;  // 이전 노드
    ListNode* cur = node;   // 현재 노드
    ListNode* next = NULL;  // 다음 노드

    // 현재 노드가 null이 될 때까지 반복
    while (cur != NULL) {
        next = cur->next;   // 다음 노드 저장
        cur->next = prev;   // 현재 노드의 다음을 이전 노드로 설정
        prev = cur;         // 이전 노드를 현재 노드로 업데이트
        cur = next;         // 현재 노드를 다음 노드로 이동
    }
    
    return prev;            // 뒤집힌 linked list의 head 반환
}

ListNode* P2_ans(ListNode* lst1, ListNode* lst2) {
    // 더할 때 1의자리부터 더하기 위해 linked list를 먼저 뒤집는다
    ListNode* num1 = reverseLinkedList(lst1);
    ListNode* num2 = reverseLinkedList(lst2);

    int carry = 0;              // 올림 수
    ListNode* dummy = newListNode(0); // 결과 linked list의 시작 노드 (더미 노드)
    ListNode* cur = dummy;      // 현재 노드 위치 추적

    // 둘 중 하나의 linked list가 남아있거나 또는 carry 값이 있는 동안 반복
    while (carry || num1 || num2) {
        if (num1) {
            carry += num1->val;
            num1 = num1->next;  // 다음 숫자로 업데이트
        }
        if (num2) {
            carry += num2->val;
            num2 = num2->next;
        }
        // carry 값을 10으로 나눈 몫과 나머지 계산
        int x = carry % 10;
        carry /= 10;

        cur->next = newListNode(x);  // 더한 값을 리스트에 추가
        cur = cur->next;             // 현재 노드를 다음 노드로 이동
    }

    return dummy->next;             // 더한 결과 리스트의 head 반환
}

// 메모리 정리를 위한 함수
void freeLinkedList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        free(temp);
    }
}
