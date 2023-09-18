"""
[끝 과 끝이 twin일 경우 Max sum twin 값 찾기]

In a linked list of size n, where n is even, 
    the ith node (0-indexed) of the linked list is 
    known as the twin of the (n-1-i)th node, if 0 <= i <= (n / 2) - 1.

For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the twin of node 2. 
These are the only nodes with twins for n = 4.
The twin sum is defined as the sum of a node and its twin.

Given the head of a linked list with even length, 
    return the maximum twin sum of the linked list.
    
Input: head = [5,4,2,1]
Output: 6
Explanation:
Nodes 0 and 1 are the twins of nodes 3 and 2, respectively. All have twin sum = 6.
There are no other nodes with twins in the linked list.
Thus, the maximum twin sum of the linked list is 6. 

Input: head = [1,100000]
Output: 100001
Explanation:
There is only one node with a twin in the linked list having twin sum of 1 + 100000 = 100001.
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


def pairSum(head: ListNode) -> int:
    # linked list를 list로 만들기
    lst = []
    current = head
    while current:
        lst.append(current.val)
        current = current.next
    
    # 끝과 끝을 같이 사용해야하니까 반만 for loop을 돌게함
    n = len(lst)
    max_sum = -1 # 끝과 끝을 더하면서 max 바꿈
    for i in range(n//2):
        print(lst[i], lst[n-1-i])
        if max_sum < lst[i] + lst[n-1-i]:
            max_sum = lst[i] + lst[n-1-i]
    
    return max_sum