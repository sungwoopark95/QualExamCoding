"""
[Remove linked list elements]
Given the head of a linked list and an integer val, 
    remove all the nodes of the linked list that has Node.val == val, 
    and return the new head.
    
head = [1,2,6,3,4,5,6]
val = 6
head1 = create_linked_list(head)
output1 = removeElements(head1, val)
print_linked_list(output1, [])
"""


# 연결 리스트의 노드 클래스 정의
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val        # 노드의 값
        self.next = next      # 다음 노드를 가리키는 포인터
        
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

def removeElements(head: ListNode, val: int):
    # 더미 노드를 생성하고, 이 더미의 next를 head로 설정
    # (이렇게 함으로써 head 자체가 삭제 대상이 될 경우에도 처리 가능)
    dummy = ListNode(0)
    dummy.next = head
    
    # 현재 노드를 더미 노드로 설정
    current = dummy
    
    # 현재 노드의 next 노드가 None이 아닐 동안 반복
    while current.next:
        # 현재 노드의 다음 노드의 값이 삭제 대상 값과 동일한 경우
        if current.next.val == val:
            # 현재 노드의 next를 그 다음 노드로 갱신
            current.next = current.next.next
        else:
            # 그렇지 않으면 현재 노드를 다음 노드로 이동
            current = current.next
    
    # 더미 노드의 next를 반환 (새로운 head)
    return dummy.next