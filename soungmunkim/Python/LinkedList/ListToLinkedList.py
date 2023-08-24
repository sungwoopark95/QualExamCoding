class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


def listToLinkedList(lst: list):
    if not lst:
        return None

    head = ListNode(lst[0])
    current = head

    for value in lst[1:]:
        current.next = ListNode(value)
        current = current.next

    return head