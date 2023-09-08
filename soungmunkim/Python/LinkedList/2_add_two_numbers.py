"""
[두 Linked list의 숫자를 합쳐서 한 linked list로 내보내기]

You are given two non-empty linked lists representing two non-negative integers. 
The digits are stored in reverse order, and each of their nodes contains a single digit. 
Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, 
    except the number 0 itself.

l1 = [2,4,3]
l2 = [5,6,4]
addNums(l1, l2)
>>> [7,0,8]
Explanation: 342 + 465 = 807.

Example 2:
Input: l1 = [0], l2 = [0]
Output: [0]

Example 3:
Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
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

# 주어진 두 연결 리스트를 이용하여 두 수의 합을 연결 리스트로 반환하는 함수
def addTwoNums(l1: ListNode, l2: ListNode) -> ListNode:
    dummy = ListNode()  # 더미 노드 생성
    current = dummy     # 결과 연결 리스트의 현재 위치를 나타내는 포인터
    carry = 0           # 올림값
    
    # l1과 l2 중 하나라도 남아 있거나 올림값이 있을 때까지 반복
    while l1 is not None or l2 is not None or carry:
        # 두 연결 리스트의 현재 노드 값과 올림값을 더함
        sum_val = carry
        
        if l1 is not None:
            sum_val += l1.val
            l1 = l1.next
            
        if l2 is not None:
            sum_val += l2.val
            l2 = l2.next
            
        # 더한 값이 10 이상인 경우 올림 처리
        carry = sum_val // 10
        
        # 현재 노드에 더한 값을 저장하고, current를 다음 노드로 이동
        current.next = ListNode(sum_val % 10)
        current = current.next
        
    return dummy.next  # 더미 노드의 다음 노드부터가 결과 연결 리스트이므로 dummy.next를 반환

def addNums(l1: list, l2: list):
    l1_nodes= create_linked_list(l1)
    l2_nodes= create_linked_list(l2)
    
    output = addTwoNums(l1_nodes, l2_nodes)
    
    return print_linked_list(output, [])