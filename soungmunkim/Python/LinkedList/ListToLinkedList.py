class ListNode:
    def __init__(self, val, next):
        self.val = val
        self.next = next


def listToLinkedList(lst: list):
    if not lst:
        return None

    head = ListNode(lst[0], None)
    current = head

    for value in lst[1:]:
        current.next = ListNode(value, None)
        current = current.next

    return head