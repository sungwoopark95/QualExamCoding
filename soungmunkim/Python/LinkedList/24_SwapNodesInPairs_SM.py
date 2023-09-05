"""
[인접한 두 노드 swap하기]

Given a linked list, swap every two adjacent nodes and return its head. 
You must solve the problem without modifying the values in the list's nodes 
(i.e., only nodes themselves may be changed.)

head = []
head2 = create_linked_list(head)
output2 = swapPairs(head2)
print_linked_list(output2, []) # []

head = [1]
head3 = create_linked_list(head)
output3 = swapPairs(head3)
print_linked_list(output3, []) # [1]

head = [1,2,3,4]
head1 = create_linked_list(head)
output1 = swapPairs(head1)
print_linked_list(output1, []) # [2, 1, 4, 3]
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
        
# 연결 리스트의 연속된 두 노드를 교환
def swapPairs(head: ListNode):
    if head is None:    # 헤드 노드가 없는 경우
        return
    
    dummy = ListNode()  # 더미 노드 생성
    dummy.next = head   # 더미의 다음 노드를 헤드로 설정
    prev = dummy        # prev 포인터를 더미 노드로 설정
    
    curr = head         # curr 포인터를 헤드 노드로 설정
    
    while curr:        # curr가 None이 아닐 때까지 순회
        temp = curr.next   # temp는 curr의 다음 노드
        if temp == None:  # temp가 None인 경우
            return curr
        print('cur: ', curr.val, 'cur.next: ', curr.next.val)
        curr.next = temp.next  # curr의 다음 노드를 temp의 다음 노드로 연결
        temp.next = curr      # temp의 다음 노드를 curr로 연결
        prev.next = temp      # prev의 다음 노드를 temp로 연결
        prev = temp           # prev를 temp로 갱신
        
        curr = curr.next      # curr를 다음 노드로 이동
        prev = prev.next      # prev를 다음 노드로 이동
    
    return dummy.next         # 더미 노드의 다음 노드(첫 노드)를 반환
