/*
"""
두 개의 정렬된 연결 리스트를 병합하는 함수
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Input: list1 = [], list2 = []
Output: []

Input: list1 = [], list2 = [0]
Output: [0]
"""
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

ListNode* createNode(int x) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->val = x;
    newNode->next = NULL;
    return newNode;
}

ListNode* create_linked_list(int l[], int size) {
    if (size == 0) {
        return NULL;
    }

    ListNode* start = createNode(l[0]);
    ListNode* node = start;

    for (int i = 1; i < size; i++) {
        ListNode* node_new = createNode(l[i]);
        node->next = node_new;
        node = node_new;
    }

    return start;
}

void linked_to_list(ListNode* head, int** ans, int* ansSize) {
    *ansSize = 0;
    ListNode* curr = head;
    while (curr) {
        (*ansSize)++;
        curr = curr->next;
    }

    *ans = (int*)malloc(sizeof(int) * (*ansSize));
    curr = head;
    for (int i = 0; curr; i++) {
        (*ans)[i] = curr->val;
        curr = curr->next;
    }
}

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    // 두 연결 리스트가 모두 비어 있는 경우 NULL 반환
    if (!list1 && !list2) {
        return NULL;
    }
    // list1이 비어 있는 경우 list2를 반환
    if (!list1) {
        return list2;
    }
    // list2가 비어 있는 경우 list1을 반환
    if (!list2) {
        return list1;
    }

    ListNode* base;  // 기준이 될 리스트의 현재 노드를 가리킬 포인터
    ListNode* other; // 다른 리스트의 현재 노드를 가리킬 포인터

    // list1의 첫 번째 노드 값과 list2의 첫 번째 노드 값을 비교
    if (list1->val < list2->val) {
        base = list1; // list1의 값이 더 작으면 base를 list1으로 설정
        other = list2;
    } else {
        base = list2; // 그렇지 않으면 base를 list2로 설정
        other = list1;
    }

    // base와 other의 현재 위치를 추적하기 위한 포인터 설정
    ListNode* curr1 = base;
    ListNode* curr2 = other;

    // 두 리스트 중 하나가 끝날 때까지 반복
    while (curr1 && curr2) {
        // curr1의 다음 노드 값이 curr2의 현재 노드 값보다 작은 동안 curr1을 이동
        while (curr1->next && curr1->next->val < curr2->val) {
            curr1 = curr1->next;
        }

        // curr1의 다음 노드를 임시로 저장
        ListNode* temp1 = curr1->next;

        // curr2의 값이 temp1의 값보다 작을 때까지 curr2의 노드들을 curr1의 뒤에 삽입
        while (temp1 && curr2 && curr2->val < temp1->val) {
            ListNode* temp2 = curr2;
            curr1->next = temp2; // curr2 노드를 curr1 뒤에 연결
            curr1 = curr1->next; // curr1 포인터를 한 칸 이동
            curr2 = curr2->next; // curr2 포인터를 한 칸 이동
            temp1 = curr1->next; // temp1 포인터를 한 칸 이동
        }
    }

    // curr2에 아직 처리되지 않은 노드가 남아있다면 base 리스트의 끝에 연결
    if (curr2) {
        ListNode* newcurr = base;
        while (newcurr->next) {
            newcurr = newcurr->next; // base 리스트의 마지막 노드를 찾음
        }
        newcurr->next = curr2; // curr2의 남은 노드들을 base 리스트의 끝에 연결
    }

    return base; // 병합된 리스트의 첫 번째 노드 반환
}

int main() {
    int l1[] = {1, 3, 5};
    int l2[] = {2, 4, 6};

    ListNode* list1 = create_linked_list(l1, sizeof(l1) / sizeof(l1[0]));
    ListNode* list2 = create_linked_list(l2, sizeof(l2) / sizeof(l2[0]));

    ListNode* mergedList = mergeTwoLists(list1, list2);

    int* ans;
    int ansSize;
    linked_to_list(mergedList, &ans, &ansSize);
    for (int i = 0; i < ansSize; i++) {
        printf("%d ", ans[i]);
    }
    free(ans);

    // C에서는 동적 할당된 메모리를 해제해야 합니다. 
    // 여기서는 단순화를 위해 메모리 해제를 생략했지만 실제로는 모든 노드에 대해 free를 호출해야 합니다.
}

