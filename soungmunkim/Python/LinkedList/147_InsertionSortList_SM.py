
"""
Given the head of a singly linked list, implement the function insertion_sort_list such
that sorts the list using insertion sort, and returns the sorted list's head.

l1 = [4,2,1,3]
head1 = create_linked_list(l1)
output1 = insertion_sort_list(head1)
print_linked_list(output1, []) # [1, 2, 3, 4]


l1 = [4,2,1,3]
head1 = create_linked_list(l1)
output1 = insertion_sort_list(head1)
print_linked_list(output1, []) # [1, 2, 3, 4]

l2 = [-1,5,3,4,0]
head2 = create_linked_list(l2)
output2 = insertion_sort_list(head2)
print_linked_list(output2, []) # [-1, 0, 3, 4, 5]
"""

# Definition for Node of singly linked list
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
        
# Create a linked list from a list, then return head node
def create_linked_list(l: list):
    if len(l) == 0:
        return None
    
    start = ListNode(l[0])
    node = start
    
    for i in range(1, len(l)):
        node_new = ListNode(l[i])
        node.next = node_new
        node = node_new
        
    return start

# Print all values in the linked list
def print_linked_list(n: ListNode, l:list):
    if n is not None:
        l.append(n.val)
        print_linked_list(n.next, l)
    else:
        print(l)

# Helper: linked list to list
def linkedListToList(head):
    result = []
    current = head
    while current:
        result.append(current.val)
        current = current.next
    return result

# Helper: list to Linked list
def listToLinkedList(lst: list):
    if not lst:
        return None

    head = ListNode(lst[0], None)
    current = head

    for value in lst[1:]:
        current.next = ListNode(value, None)
        current = current.next

    return head

def insertion_sort_list(head: ListNode):
    arr = linkedListToList(head)
    for i in range(1, len(arr)):
        for j in range(i, 0, -1): # 뒤로 하나씩 이동
            if arr[j-1] > arr[j]:
                arr[j-1], arr[j] = arr[j], arr[j-1]
            else:
                break
            
    return listToLinkedList(arr)