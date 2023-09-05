"""
[sorted list에서 Duplicated num 제거하기]
Given the head of a sorted linked list, 
delete all duplicates such that each element appears only once. 
Return the linked list sorted as well.

head = [1,1,2]
head1 = create_linked_list(head)
output1 = deleteDuplicates(head1)
print_linked_list(output1, [])      # [1, 2]

head = [1,1,2,3,3]
head2 = create_linked_list(head)
output2 = deleteDuplicates(head2)
print_linked_list(output2, [])      # [1,2,3]
"""


# 단일 연결 리스트의 노드를 위한 정의
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

def deleteDuplicates(head: ListNode):
    # dummy = ListNode()
    # dummy.next = head
    # prev = dummy
    if head is None:
        return
    
    curr = head
    
    while curr:
        # 비교할 다음 노드가 있고 현재노드와 다음노드 값이 같다면
        if curr.next and curr.val == curr.next.val:
            # 현재노드의 다음노드를 겹친 노드 그 다음으로 설정해줌 (겹치는 노드 빼기)
            curr.next = curr.next.next
        
        # 현재 노드 위치 이동
        curr = curr.next

    return head