"""
[0 사이의 숫자 합들을 리스트로 반환하기]

You are given the head of a linked list, 
    which contains a series of integers separated by 0's. 
    
The beginning and end of the linked list will have Node.val == 0.

For every two consecutive 0's, 
    merge all the nodes lying in between them into a single node 
    whose value is the sum of all the merged nodes. 

The modified list should not contain any 0's.

head = [0,3,1,0,4,5,2,0]
node = create_linked_list(head)
mergeNodes(node)
>>> [4, 11]

head = [0,1,0,3,0,2,2,0]
node1 = create_linked_list(head)
mergeNodes(node1)
>>> [1, 3, 4]
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

def mergeNodes(head: ListNode):
    ans = []  # 결과를 저장할 리스트
    sum = 0   # 연속된 노드의 값을 합산할 변수
    
    next = None  # 현재 노드의 다음 노드를 가리킬 변수
    cur = head   # 현재 노드를 가리키는 변수로, 처음에는 헤드 노드를 가리킵니다.
    
    if head is None:  # 헤드 노드가 None인 경우 (즉, 리스트가 비어있는 경우)
        return  # 아무것도 반환하지 않고 함수 종료
    
    while cur.next:  # 현재 노드의 다음 노드가 존재하는 동안 반복
        next = cur.next  # 다음 노드를 next 변수에 저장
        cur = next  # 현재 노드를 다음 노드로 업데이트
        
        if cur.val != 0:  # 현재 노드의 값이 0이 아닌 경우
            sum += cur.val  # sum 변수에 현재 노드의 값을 더함
        else:  # 현재 노드의 값이 0인 경우
            ans.append(sum)  # 지금까지 합산한 값을 ans 리스트에 추가
            sum = 0  # sum 변수를 0으로 초기화
    
    return ans  # ans 리스트를 반환