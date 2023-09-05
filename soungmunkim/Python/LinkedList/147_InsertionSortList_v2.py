"""
Given the head of a singly linked list, implement the function insertion_sort_list such
that sorts the list using insertion sort, and returns the sorted list's head.

l1 = [4,2,1,3]
head1 = create_linked_list(l1)
output1 = insertion_sort_list(head1)
print_linked_list(output1, []) # [1, 2, 3, 4]

l2 = [-1,5,3,4,0]
head2 = create_linked_list(l2)
output2 = insert_sort_list(head2)
print_linked_list(output2, []) # [-1, 0, 3, 4, 5]
"""


"""
Linked list를 유지해서 푼 버전
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

def insert_sort_list(head:ListNode):
    dummy = ListNode()
    dummy.next = head # dummy node를 head에 연결
    prev = dummy # dummy node에 Prev 포인트
    
    curr = head # head node에 curr 포인트
    # next = curr.next
    
    # curr node만 움직이면서 보기 
    while curr: 
        # 만약 비교할 Curr.next 값이 있고 현재 값이 다음 값보다 큰 경우 (swap)
        # 4 > 2
        if curr.next and curr.val > curr.next.val:
            # insert할 위치 찾기 (prev 이동시키면서)
            # prev.next.val = 4 > curr.next = 2 (while 스킵)
            while prev.next.val < curr.next.val:
                prev = prev.next
            
            # temp = curr.next = 2
            temp = curr.next # curr.next를 temp로 지정해서 풀기
            curr.next = temp.next # 4 다음 노드 -> temp.next = 1
            temp.next = prev.next # 2 다음 노드 -> prev 다음 = 4
            prev.next = temp        # prev 다음 노드 -> temp = 2
          
            prev = dummy # dummy로 prev 보내기 (바꾸고 역할 끝)
        else:
            curr = curr.next # curr을 다음으로 넘기기
        # next = curr.next
        
    return prev.next # dummy.next