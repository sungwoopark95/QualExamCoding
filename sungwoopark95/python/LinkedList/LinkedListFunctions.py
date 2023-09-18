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

# Print all values in the linked list
def print_linked_list(n: ListNode, l: list) -> None:
    if n is not None:
        l.append(n.val)
        print_linked_list(n.next, l)
    else:
        print(l)

## Linked List Functions
def append(head, val):
    new_node = ListNode(val)
    if head is None:
        head = new_node
    else:
        curr = head
        # 끝나는 지점 찾기 - 연결을 해야 하므로 맨 끝의 직전 노드를 찾아야 함
        while curr.next:
            curr = curr.next
        curr.next = new_node


def insert(head, index, data):
    new_node = ListNode(data)
    curr = head
    i = 0
    while i < index-1:
        curr = curr.next
        i += 1
    # 현재의 next node 복사
    next_node = curr.next
    
    # 새로운 node를 현재 노드의 next로 추가
    curr.next = new_node
    
    # 새로운 node의 next를 복사해둔 노드로 설정
    new_node.next = next_node


def remove(head, val):
    # 가상의 노드를 생성하여 연결 리스트의 시작 앞에 위치시킵니다.
    # 이렇게 하면 head 노드도 val과 일치할 경우 제거할 수 있습니다.
    dummy = ListNode(0)
    dummy.next = head
    current = dummy
    
    # 연결 리스트를 순회하면서 val과 일치하는 노드를 제거합니다.
    while current.next:
        if current.next.val == val:
            current.next = current.next.next
        else:
            current = current.next
    
    # 가상의 노드 다음 노드를 반환합니다.
    return dummy.next


def pop(head, idx):
    # 가상의 노드를 생성하여 연결 리스트의 시작 앞에 위치시킵니다.
    # 이렇게 하면 idx가 0일 경우에도 head 노드를 제거할 수 있습니다.
    dummy = ListNode(0)
    dummy.next = head
    current = dummy
    count = 0
    
    # idx 위치에 도달할 때까지 연결 리스트를 순회합니다.
    while current.next and count < idx:
        current = current.next
        count += 1
    
    # idx 위치에 노드가 있다면 그 노드를 제거하고 값을 반환합니다.
    if count == idx and current.next:
        removed_val = current.next.val
        current.next = current.next.next
        return removed_val
    else:
        # idx가 연결 리스트의 길이보다 크거나 같은 경우 None을 반환합니다.
        return None

def linked_to_list(head:ListNode) -> list:
    ans = []
    curr = head
    while curr:
        ans.append(curr.val)
        curr = curr.next
    return ans

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

if __name__ == "__main__":
    l1 = create_linked_list([1,1,1])
    append(l1, 3)
    append(l1, 4)
    append(l1, 5)
    listed = linked_to_list(l1)
    print(listed)
    print_linked_list(l1, [])
    
    insert(l1, 1, 4)
    print_linked_list(l1, [])
    
    # remove
    l1 = remove(l1, 3)
    print_linked_list(l1, [])
    
    # pop
    popped = pop(l1, 2)
    print(f"popped Value: {popped}")
    print_linked_list(l1, [])
