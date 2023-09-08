"""
[linked list cycle 찾기]

Given head, the head of a linked list, 
    determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

Return true if there is a cycle in the linked list. Otherwise, return false.

Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, 
    where the tail connects to the 1st node (0-indexed).
"""

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val       # 노드의 값을 설정합니다.
        self.next = next     # 다음 노드를 가리키는 포인터를 설정합니다.

def hasCycle(head: ListNode) -> bool:
    visited_nodes = []    # 방문한 노드들을 저장할 리스트를 초기화합니다.
    
    while head:           # head가 None이 될 때까지 순회합니다.
        # 만약 현재 노드가 이미 방문한 노드 리스트에 있다면 사이클이 존재합니다.
        if head in visited_nodes:
            return True
        
        # 현재 노드를 방문한 노드 리스트에 추가합니다.
        visited_nodes.append(head)
        
        # 다음 노드로 이동합니다.
        head = head.next
        
    # 사이클이 없다면 False를 반환합니다.
    return False

# 주어진 리스트로 연결 리스트를 생성하고, 주어진 pos 위치에 사이클을 추가합니다.
def create_linked_list_with_cycle(nums: list, pos: int) -> ListNode:
    if not nums:
        return None

    head = ListNode(nums[0])
    node = head
    nodes = [head]

    for num in nums[1:]:
        new_node = ListNode(num)
        node.next = new_node
        node = new_node
        nodes.append(new_node)

    # 주어진 위치에 사이클을 추가합니다.
    if pos != -1:
        node.next = nodes[pos]

    return head

# 테스트 코드
if __name__ == "__main__":
    test_list = [3, 2, 0, -4]
    pos = 1
    test_linked_list = create_linked_list_with_cycle(test_list, pos)
    
    print(hasCycle(test_linked_list))  # True가 출력되어야 합니다.
