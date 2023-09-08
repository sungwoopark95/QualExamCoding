/*
[두 Linked list의 숫자를 합쳐서 한 linked list로 내보내기]

You are given two non-empty linked lists representing two non-negative integers. 
The digits are stored in reverse order, and each of their nodes contains a single digit. 
Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, 
    except the number 0 itself.

Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

Example 2:
Input: l1 = [0], l2 = [0]
Output: [0]

Example 3:
Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
*/


#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>  // NULL 정의를 위한 헤더 파일

/* 단일 연결 리스트를 위한 정의 */
struct ListNode {
    int val;                // 노드의 값을 저장하는 변수
    struct ListNode *next;  // 다음 노드를 가리키는 포인터
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    // dummy 노드를 생성하여 결과 연결 리스트의 시작을 가리키게 함
    struct ListNode* dummy = malloc(sizeof(struct ListNode));
    struct ListNode* ans = dummy;  // 결과 연결 리스트를 구성하기 위한 포인터

    int carry = 0;  // 두 숫자의 합에서 발생하는 올림 값을 저장하기 위한 변수
    
    // l1, l2 또는 올림 값이 있는 동안 루프를 계속 실행
    while (l1 || l2 || carry) {
        int val1 = 0, val2 = 0;  // 두 연결 리스트의 현재 노드 값을 저장하기 위한 변수
        
        // l1이 NULL이 아닌 경우, val1에 현재 노드의 값을 저장하고 다음 노드로 이동
        if (l1) {
            val1 = l1->val;
            l1 = l1->next;
        }
        // l2가 NULL이 아닌 경우, val2에 현재 노드의 값을 저장하고 다음 노드로 이동
        if (l2) {
            val2 = l2->val;
            l2 = l2->next;
        }
        
        // 두 연결 리스트의 현재 노드 값과 올림 값을 합산
        int curr_val = val1 + val2 + carry;
        
        // 새 노드를 생성하고 합산 값의 마지막 자릿수를 저장
        struct ListNode* newNode = malloc(sizeof(struct ListNode));
        newNode->val = curr_val % 10;
        newNode->next = NULL;
        
        // 결과 연결 리스트에 새로운 노드를 추가
        ans->next = newNode;
        // 올림 값을 갱신 (합산 값에서 10으로 나눈 몫)
        carry = curr_val / 10;
        // 결과 연결 리스트의 포인터를 다음 위치로 이동
        ans = ans->next;
    }

    // 결과 연결 리스트의 시작 위치 (dummy 노드 다음)를 반환하기 전에 dummy 노드의 메모리를 해제
    struct ListNode* ret = dummy->next;
    free(dummy);
    return ret;  // 결과 연결 리스트의 시작 위치를 반환
}
