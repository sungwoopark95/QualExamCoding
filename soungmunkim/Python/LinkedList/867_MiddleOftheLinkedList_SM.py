"""
[Linked list 중간 노드부터 프린트 하기]
Given the head of a singly linked list, return the middle node of the linked list.

If there are two middle nodes, return the second middle node.

Input: head = [1,2,3,4,5]
Output: [3,4,5]
Explanation: The middle node of the list is node 3.

Input: head = [1,2,3,4,5,6]
Output: [4,5,6]
Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.

head = [1,2,3,4,5]
head1 = create_linked_list(head)
output1 = middleNode(head1)
print_linked_list(output1, []) # [3,4,5]

head = [1,2,3,4,5,6]
head2 = create_linked_list(head)
output2 = middleNode(head2)
print_linked_list(output2, [])  # [4,5,6]
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

def middleNode(head: ListNode):
    curr = head
    lst = []
    # find middle node index (list에 넣어서 중간 인덱스 찾기)
    while curr:
        lst.append(curr.val)
        curr = curr.next
    
    middle_point = round(len(lst)/2)
    
    # 중간 인덱스 나올떄까지 돌고 찾으면 그 이후 노드들 리턴
    curr = head
    i = 0
    while i < middle_point:
        next = curr.next
        curr = next
        i+=1
    
    return curr