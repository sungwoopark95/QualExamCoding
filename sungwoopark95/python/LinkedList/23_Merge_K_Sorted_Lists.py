from typing import List

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

# Create a linked list from a list, then return head node
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

def checkNones(lists) -> List[int]:
    not_nones = []
    for i, node in enumerate(lists):
        if not node:
            continue
        not_nones.append(i)
    return not_nones

def concatLists(lists: List[ListNode], indices: List[int]) -> ListNode:
    # dummy는 연결 리스트를 편리하게 다루기 위한 더미 노드입니다.
    dummy = ListNode()
    
    # curr는 현재 연결 리스트의 마지막 노드를 가리키는 포인터입니다.
    curr = None
    
    # 주어진 인덱스의 순서에 따라 각 연결 리스트를 연결합니다.
    for i in range(len(indices)):
        # 현재 연결할 리스트의 인덱스를 가져옵니다.
        idx = indices[i]
        
        # 해당 인덱스의 연결 리스트의 헤드를 가져옵니다.
        head = lists[idx]
        
        # 첫 번째 연결 리스트인 경우 dummy의 next를 첫 번째 연결 리스트의 헤드로 설정합니다.
        if i == 0:
            dummy.next = head
            curr = dummy.next
        else:
            # 그렇지 않은 경우, 현재 연결 리스트의 끝에 새로운 연결 리스트를 연결합니다.
            curr.next = head
            curr = head
        
        # curr를 현재 연결 리스트의 마지막 노드로 이동시킵니다.
        while curr.next:
            next = curr.next
            curr = next
            
    # 더미 노드 다음 노드(실제 연결 리스트의 첫 번째 노드)를 반환합니다.
    return dummy.next

def insert_sort_list(head:ListNode):
    dummy = ListNode()
    dummy.next = head # dummy node를 head에 연결
    prev = dummy # dummy node에 Prev 포인트
    
    curr = head # head node에 curr 포인트
    # next = curr.next
    
    # curr node만 움직이면서 보기 
    while curr: 
        # 만약 비교할 Curr.next 값이 있고 현재 값이 다음 값보다 큰 경우 (swap)
        # 4 > 2
        if curr.next and curr.val > curr.next.val:
            # insert할 위치 찾기 (prev 이동시키면서)
            # prev.next.val = 4 > curr.next = 2 (while 스킵)
            while prev.next.val < curr.next.val:
                prev = prev.next
            
            # temp = curr.next = 2
            temp = curr.next # curr.next를 temp로 지정해서 풀기
            curr.next = temp.next # 4 다음 노드 -> temp.next = 1
            temp.next = prev.next # 2 다음 노드 -> prev 다음 = 4
            prev.next = temp        # prev 다음 노드 -> temp = 2
        
            prev = dummy # dummy로 prev 보내기 (바꾸고 역할 끝)
        else:
            curr = curr.next # curr을 다음으로 넘기기
        # next = curr.next
    return prev.next # dummy.next

def mergeKLists(lists: List[ListNode]) -> ListNode:
    valid_index = checkNones(lists) # None이 아닌 node들의 index로 이루어진 list
    # 모든 node가 None으로만 이루어져 있다면 None return
    if not valid_index:
        return None
    head = concatLists(lists, valid_index)
    return insert_sort_list(head)

if __name__ == "__main__":
    lists = [[1,4,5],[1,3,4],[2,6]]
    links = []
    for item in lists:
        links.append(create_linked_list(item))
    merged = mergeKLists(links)
    print(linked_to_list(merged))