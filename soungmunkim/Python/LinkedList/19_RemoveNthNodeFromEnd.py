"""
[[뒤에서 n번째 노드 지우기]]
Given the head of a linked list, 
remove the nth node from the end of the list and return its head.

Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]

Example 2:
Input: head = [1], n = 1
Output: []

Example 3:
Input: head = [1,2], n = 1
Output: [1]
"""

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
        
# 리스트로부터 연결 리스트를 생성한 후 헤드 노드를 반환
def create_linked_list(l: list):
    if len(l) == 0:         # 리스트의 길이가 0인 경우
        return None
    
    start = ListNode(l[0])  # 시작 노드 생성
    node = start            # 현재 노드를 시작 노드로 설정
    
    for i in range(1, len(l)): # 리스트의 나머지 원소들을 순회
        node_new = ListNode(l[i])  # 새 노드 생성
        node.next = node_new      # 현재 노드의 다음을 새 노드로 연결
        node = node_new           # 현재 노드를 새 노드로 갱신
        
    return start    # 연결 리스트의 시작 노드 반환

# 연결 리스트의 모든 값을 출력
def print_linked_list(n: ListNode, l:list):
    if n is not None:    # 노드가 None이 아닌 경우
        l.append(n.val)  # 노드의 값을 리스트에 추가
        print_linked_list(n.next, l) # 다음 노드로 재귀 호출
    else:
        print(l)         # 노드가 None인 경우 리스트 출력
        

def removeNthFromEnd(head: ListNode, n: int) -> ListNode:
    dummy = ListNode(0)
    dummy.next = head

    front = back = dummy

    for i in range(n): #우선 뒷 포인터를 n개 먼저 움직인다. 
        back = back.next

    while back.next: #n개 떨어진 앞, 뒤 포인터가 끝까지 순차적으로 간다
        front = front.next
        back = back.next

    front.next = front.next.next #맨 마지막에 다다르면 앞포인터를 뒷포인터와 연결한다. 

    return dummy.next

def RemoveNodeFromEnd(head: list, n: int) -> ListNode:
    node = create_linked_list(head)
    output = removeNthFromEnd(node, n)
    return print_linked_list(output, [])


if __name__ == "__main__":
    # head = [1,2,3,4,5]
    # n = 2
    # RemoveNodeFromEnd(head, n)

    head = [1]
    n = 1
    RemoveNodeFromEnd(head, n)