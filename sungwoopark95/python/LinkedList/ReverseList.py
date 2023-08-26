from LinkedListFunctions import ListNode, create_linked_list, print_linked_list

def P3(head:ListNode):
    # edge case
    if head is None:
        return None
    
    # reverse the linked list
    prev = head
    curr = head.next
    head.next = None
    while curr:
        next = curr.next
        curr.next = prev
        prev = curr
        curr = next
    return prev # required!

if __name__ == "__main__":
    l1 = create_linked_list([4,2,1,3])
    print("Before Operation:", end='\t')
    print_linked_list(l1,[])
    print("After Operation:", end='\t')
    print_linked_list(P3(l1),[])
    
    l2 = create_linked_list([-1,5,0,2,3])
    print("Before Operation:", end='\t')
    print_linked_list(l2,[])
    print("After Operation:", end='\t')
    print_linked_list(P3(l2),[])
