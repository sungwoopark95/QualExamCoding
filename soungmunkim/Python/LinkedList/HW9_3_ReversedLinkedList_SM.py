"""
주어진 Singly linked list를 뒤집는 함수를 작성하여라. 
함수의 Input은 Singly linked list의 첫번째 Node이 며, Return값은 순서가 뒤집힌 Singly linked list의 첫번째 Node이다.

※ Linked list의 각 Node는 linked_list_helper.py 파일에 정의되어 있는 ListNode를 활용하면 된다.
※ linked_list_helper.py 파일의 create_linked_list 함수와 print_linked_list 함수를 활용하여 아래와 같이 함 수의 동작을 확인할 수 있다.
※ Space complexity는 O(1)이어야 합니다.

TestCase1)
>>> l1 = create_linked_list([4,2,1,3]) 
>>> print_linked_list(P3(l1),[]) 
[3,1,2,4]
TestCase2)
>>> l2 = create_linked_list([-1,5,0,2,3]) 
>>> print_linked_list(P3(l2),[]) 
[3,2,0,5,-1]
"""

# [dummy node 넣어서]

# Definition for Node of singly linked list.
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
def print_linked_list(n: ListNode, l: list):
    if n is not None:
        l.append(n.val)
        print_linked_list(n.next, l)
    else:
        print(l)

# Dummy node 넣어서 reverse 하는 방법
def P3(head):
    dummy = ListNode()
    
    while head:
        cur = head
        head = head.next
        
        cur.next = dummy.next
        dummy.next = cur
        
    return dummy.next