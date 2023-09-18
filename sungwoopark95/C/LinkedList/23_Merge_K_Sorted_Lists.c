#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

ListNode* create_linked_list(int* l, int size) {
    if (size == 0) {
        return NULL;
    }

    ListNode* start = (ListNode*)malloc(sizeof(ListNode));
    start->val = l[0];
    start->next = NULL;

    ListNode* node = start;
    for (int i = 1; i < size; ++i) {
        ListNode* node_new = (ListNode*)malloc(sizeof(ListNode));
        node_new->val = l[i];
        node_new->next = NULL;

        node->next = node_new;
        node = node_new;
    }
    return start;
}

int* linked_to_list(ListNode* head, int* size) {
    *size = 0;
    ListNode* curr = head;
    while (curr) {
        (*size)++;
        curr = curr->next;
    }

    int* ans = (int*)malloc((*size) * sizeof(int));
    curr = head;
    int idx = 0;
    while (curr) {
        ans[idx++] = curr->val;
        curr = curr->next;
    }
    return ans;
}

int* checkNones(ListNode** lists, int listSize, int* returnSize) {
    int* not_nones = (int*)malloc(listSize * sizeof(int));
    *returnSize = 0;
    for (int i = 0; i < listSize; ++i) {
        if (lists[i]) {
            not_nones[(*returnSize)++] = i;
        }
    }
    return not_nones;
}

ListNode* concatLists(ListNode** lists, int* indices, int indicesSize) {
    ListNode dummy;
    dummy.next = NULL;
    ListNode* curr = NULL;
    for (int i = 0; i < indicesSize; ++i) {
        int idx = indices[i];
        ListNode* head = lists[idx];
        if (i == 0) {
            dummy.next = head;
            curr = dummy.next;
        } else {
            curr->next = head;
            curr = head;
        }
        while (curr && curr->next) {
            curr = curr->next;
        }
    }
    return dummy.next;
}

ListNode* insert_sort_list(ListNode* head) {
    ListNode dummy;
    dummy.next = head;
    ListNode* prev = &dummy;
    ListNode* curr = head;

    while (curr) {
        if (curr->next && curr->val > curr->next->val) {
            while (prev->next && prev->next->val < curr->next->val) {
                prev = prev->next;
            }

            ListNode* temp = curr->next;
            curr->next = temp->next;
            temp->next = prev->next;
            prev->next = temp;
            prev = &dummy;
        } else {
            curr = curr->next;
        }
    }
    return dummy.next;
}

ListNode* mergeKLists(ListNode** lists, int listSize) {
    int returnSize;
    int* valid_index = checkNones(lists, listSize, &returnSize);
    if (returnSize == 0) {
        free(valid_index);
        return NULL;
    }
    ListNode* head = concatLists(lists, valid_index, returnSize);
    free(valid_index);
    return insert_sort_list(head);
}

int main() {
    int arr1[] = {1, 4, 5};
    int arr2[] = {1, 3, 4};
    int arr3[] = {2, 6};
    ListNode* links[3];
    links[0] = create_linked_list(arr1, sizeof(arr1) / sizeof(int));
    links[1] = create_linked_list(arr2, sizeof(arr2) / sizeof(int));
    links[2] = create_linked_list(arr3, sizeof(arr3) / sizeof(int));

    ListNode* merged = mergeKLists(links, 3);

    int size;
    int* result = linked_to_list(merged, &size);
    for (int i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    for (int i = 0; i < 3; i++) {
        ListNode* curr = links[i];
        while (curr) {
            ListNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    return 0;
}
