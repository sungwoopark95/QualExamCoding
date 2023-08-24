class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def linkiedListToList(head):
    result = []
    current = head
    while current:
        result.append(current.val)
        current = current.next
    return result