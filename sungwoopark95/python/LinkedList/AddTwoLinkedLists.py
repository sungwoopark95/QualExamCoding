"""
0 이상의 십진수 정수를 나타내는 Linked list 두 개가 주어질 때, 두 숫자의 합을 나타내는 Linked list를 만드는 함수를 작성하여라. Input으로는 각 Linked list의 첫번째 Node가 주어지며, Return값 역시 Linked list의 첫번째 Node이다.
예를 들어, 15와 30을 나타내는 Linked list, 즉 (1)->(5), (3)->(0)이 주어진다면, 두 숫자의 합인 45를 나타내는 Linked list (4)->(5)를 만들어 해당 Linked list의 첫번째 Node (head)를 반환하여야 한다.  

* Linked list 형태를 유지하며 계산할 것 (주어진 Linked list를 list로 변환하여 각 원소를 더하고, 이를 다시 Linked list로 만드는 등의 풀이는 허용하지 않음) 
* Linked list의 각 Node는 `linked_list_helper.py` 파일에 정의되어 있는 `ListNode`를 활용하면 된다.  
* `linked_list_helper.py` 파일의 `create_linked_list` 함수와 `print_linked_list` 함수를 활용하여 아래와 같이 함수의 동작을 확인할 수 있다.  
"""
from LinkedListFunctions import ListNode, print_linked_list, create_linked_list

def P4(num1: ListNode, num2: ListNode):
    # Linked List를 뒤집는 도우미 함수
    def reverse_linked_list(head: ListNode):
        # Linked List가 비어있는 경우, None을 반환
        if head is None:
            return None

        # Linked List를 뒤집기 위한 초기 설정
        prev = head
        curr = head.next
        head.next = None
        # Linked List를 순회하며 노드의 연결을 뒤집음
        while curr:
            next = curr.next  # 다음 노드 저장
            curr.next = prev  # 현재 노드의 연결을 뒤집음
            prev = curr       # prev를 현재 노드로 이동
            curr = next       # curr를 다음 노드로 이동
        return prev  # 뒤집힌 Linked List의 헤드 반환
    
    # 합계를 저장할 변수 초기화
    ans = 0
    # 두 Linked List를 뒤집음
    reverse_num1 = reverse_linked_list(num1)
    reverse_num2 = reverse_linked_list(num2)
    
    # 10의 거듭제곱 값을 나타내는 변수 초기화
    digit_power = 0
    curr1, curr2 = reverse_num1, reverse_num2
    # 두 Linked List를 순회하며 합계 계산
    while curr1 or curr2:
        # 한 Linked List가 더 짧으면 그 값은 0으로 간주
        if not curr2:
            curr2 = ListNode(0)
        elif not curr1:
            curr1 = ListNode(0)
        # 현재 노드의 값과 10의 거듭제곱을 곱하여 합계에 더함
        ans += (curr1.val + curr2.val) * (10 ** digit_power)
        curr1 = curr1.next
        curr2 = curr2.next
        digit_power += 1  # 10의 거듭제곱 값을 증가
    
    # 합계를 Linked List로 변환
    head = ListNode()
    curr = head
    while ans:
        curr.val = ans % 10  # 가장 낮은 자릿수 추출
        # 더 남은 자릿수가 있으면 새 노드 생성
        if ans >= 10:
            curr.next = ListNode()
        else:
            curr.next = None
        curr = curr.next
        ans = ans // 10  # 가장 낮은 자릿수 제거
    
    # 올바른 순서로 된 Linked List로 반환
    return reverse_linked_list(head)

if __name__ == "__main__":
    l1 = create_linked_list([1,1,1])
    l2 = create_linked_list([1,1,1])
    print_linked_list(P4(l1, l2),[])
    
    l1 = create_linked_list([5,5,5]) 
    l2 = create_linked_list([5,5]) 
    print_linked_list(P4(l1, l2),[])
