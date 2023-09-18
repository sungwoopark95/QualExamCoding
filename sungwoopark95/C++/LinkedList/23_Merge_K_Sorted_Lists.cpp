#include <iostream>
#include <vector>

using namespace std;

class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* create_linked_list(const vector<int>& l) {
    if (l.empty()) {
        return nullptr;
    }

    ListNode* start = new ListNode(l[0]);
    ListNode* node = start;
    for (int i = 1; i < l.size(); ++i) {
        ListNode* node_new = new ListNode(l[i]);
        node->next = node_new;
        node = node_new;
    }
    return start;
}

vector<int> linked_to_list(ListNode* head) {
    vector<int> ans;
    ListNode* curr = head;
    while (curr) {
        ans.push_back(curr->val);
        curr = curr->next;
    }
    return ans;
}

vector<int> checkNones(const vector<ListNode*>& lists) {
    vector<int> not_nones;
    for (int i = 0; i < lists.size(); ++i) {
        if (lists[i]) {
            not_nones.push_back(i);
        }
    }
    return not_nones;
}

ListNode* concatLists(vector<ListNode*>& lists, const vector<int>& indices) {
    ListNode dummy(0);
    ListNode* curr = nullptr;
    for (int i = 0; i < indices.size(); ++i) {
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
    ListNode dummy(0);
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

ListNode* mergeKLists(vector<ListNode*>& lists) {
    vector<int> valid_index = checkNones(lists);
    if (valid_index.empty()) {
        return nullptr;
    }
    ListNode* head = concatLists(lists, valid_index);
    return insert_sort_list(head);
}

int main() {
    vector<vector<int>> lists = {{1, 4, 5}, {1, 3, 4}, {2, 6}};
    vector<ListNode*> links;

    for (const auto& item : lists) {
        links.push_back(create_linked_list(item));
    }

    ListNode* merged = mergeKLists(links);

    vector<int> result = linked_to_list(merged);
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    // 메모리 정리
    for (ListNode* node : links) {
        while (node) {
            ListNode* temp = node;
            node = node->next;
            delete temp;
        }
    }
}
