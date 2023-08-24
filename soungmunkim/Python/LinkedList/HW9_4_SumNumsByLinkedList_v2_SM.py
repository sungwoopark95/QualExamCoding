"""
[두 linked list 받아서 더한 후 linked list로 return]
0 이상의 십진수 정수를 나타내는 Linked list 두 개가 주어질 때, 두 숫자의 합을 나타내는 Linked list를 만 드는 함수를 작성하여라. 
Input으로는 각 Linked list의 첫번째 Node가 주어지며, Return값 역시 Linked list 의 첫번째 Node이다.

예를 들어, 15와 30을 나타내는 Linked list, 즉 (1)->(5), (3)->(0)이 주어진다면, 
두 숫자의 합인 45를 나타 내는 Linked list (4)->(5)를 만들어 해당 Linked list의 첫번째 Node (head)를 반환하여야 한다.

※ Linked list 형태를 유지하며 계산할 것 (주어진 Linked list를 list로 변환하여 각 원소를 더하고, 이를 다 시 Linked list로 만드는 등의 풀이는 허용하지 않음)
※ Linked list의 각 Node는 linked_list_helper.py 파일에 정의되어 있는 ListNode를 활용하면 된다.
※ linked_list_helper.py 파일의 create_linked_list 함수와 print_linked_list 함수를 활용하여 아래와 같이 함 수의 동작을 확인할 수 있다.

TestCase1)
>>> l1 = create_linked_list([1,1,1]) 
>>> l2 = create_linked_list([1,1,1]) 
>>> print_linked_list(P4(l1, l2),[]) 
[2,2,2]
TestCase2)
>>> l1 = create_linked_list([0]) 
>>> l2 = create_linked_list([0]) 
>>> print_linked_list(P4(l1, l2),[]) 
[0]
"""
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
        
def P2_ans(lst1, lst2):
    # linked list reverse 하는 함수
    def reverseLinkedlist(node):
        prev = None
        cur = node
        next = None
        
        while node:
            next = cur.next
            cur.next = prev
            prev = cur
            cur = next
        return prev
    # 더할 때 1의자리 부터 더하기 때문에 linked list를 먼저 뒤집고 시작 필요
    num1, num2 = reverseLinkedlist(lst1), reverseLinkedlist(lst2)
    carry = 0 # 올림 수
    dummy = ListNode() # 결과 linked list의 시작 node
    cur = dummy # 현재 노드 위치 추적
    
    # 둘 중 하나의 linked list가 남아있거나 또는 carry 값이 있는 동안 반복 
    while carry or num1 or num2:
            if num1:
                # carry에 값 계속 더해준 후 10으로 나눠서 carry값 다시 업뎃하는 방식
                carry += num1.val
                num1 = num1.next # 다음 숫자로 update
            if num2:
                carry += num2.val
                num2 = num2.next 
            # carry를 10으로 나눴을 때 몫 = carry, 나머지 = x로 저장
            carry, x = divmod(carry, 10)
            cur.next = ListNode(x) # 더미 다음에 결과 값 붙이기
            cur = cur.next # 현재 노드 update (다음 결과 값 붙이기 위해)