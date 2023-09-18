"""
두 개의 정렬된 연결 리스트를 병합하는 함수
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Input: list1 = [], list2 = []
Output: []

Input: list1 = [], list2 = [0]
Output: [0]
"""
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def create_linked_list(l: list) -> ListNode:
    if len(l) == 0:
        return None
    
    start = ListNode(l[0])
    node = start
    
    for i in range(1, len(l)):
        node_new = ListNode(l[i])
        node.next = node_new
        node = node_new
    
    return start

def linked_to_list(head:ListNode) -> list:
    ans = []
    curr = head
    while curr:
        ans.append(curr.val)
        curr = curr.next
    return ans

# 두 개의 정렬된 연결 리스트를 병합하는 함수
def mergeTwoLists(list1:ListNode, list2:ListNode) -> ListNode:
    # 두 연결 리스트 모두 비어 있으면 None 반환
    if not list1 and not list2:
        return None
    # list1이 비어 있으면 list2 반환
    if not list1:
        return list2
    # list2가 비어 있으면 list1 반환
    if not list2:
        return list1
    
    # list1과 list2의 첫 번째 노드 값을 비교하여 작은 값의 노드를 기준(base)으로 설정
    # base는 결과 연결 리스트의 첫 노드를 가리킬 것입니다.
    if list1.val < list2.val:
        base, other = list1, list2
    else:
        base, other = list2, list1
    
    # curr1과 curr2는 각 연결 리스트의 현재 위치를 추적하는 포인터입니다.
    curr1, curr2 = base, other
    
    # 두 연결 리스트 중 하나가 끝날 때까지 반복
    while curr1 and curr2:
        # curr1의 다음 노드 값이 curr2의 현재 노드 값보다 작으면
        # curr1을 다음 노드로 이동
        while curr1.next and curr1.next.val < curr2.val:
            curr1 = curr1.next
        
        # 이 시점에서 curr2의 값을 curr1의 연결 리스트에 삽입해야 할 위치를 찾았습니다.
        temp1 = curr1.next
        
        # curr2의 값들을 curr1의 연결 리스트에 삽입
        while temp1 and curr2 and curr2.val < temp1.val:
            temp2 = curr2
            curr1.next = temp2
            curr1 = curr1.next
            curr2 = curr2.next
        curr1.next = temp1
        curr1 = curr1.next
    
    # list2에 남아 있는 노드가 있으면 base 리스트의 끝에 추가
    if curr2:
        newcurr = base
        while newcurr.next:
            newcurr = newcurr.next
        newcurr.next = curr2
    
    return base  # 병합된 연결 리스트의 첫 번째 노드 반환

if __name__ == "__main__":
    list1 = [1,2,4]
    list2 = [1,3,4]
    l1, l2 = create_linked_list(list1), create_linked_list(list2)
    merged = mergeTwoLists(l1, l2)
    print(linked_to_list(merged))