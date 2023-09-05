"""
[Linked list로 max palindrome 찾기]
|!!! Linked list로 푼 것 ( 안 풀림...)!!!

Assume that the length of s is at most 32.


(a) Write a function **print_list(s)** that prints the sequence (i.e., the linked list) s in the list format. 
    For example, linked list in Figure 3 should be printed as [3,7,6,8].

(b) Write a function **palindrome(s)** that returns 1 if the list s is a palindrome. O
    therwise, it returns 0.

(c) Write a function **sub_list(s, t)** that returns 1 if the list t is a sub-list of the list s. 
    Otherwise, it returns 0. 

(d) Write the function **max_palindromes(s)** that uses palindrome(s), sub_list(s, t), and print_list(s).

In **print_list** and **max_palindromes**, the printed string should only contain square brackets ([ and ]), commas, digits (0 9), 
    and spaces between them. We accept any formats and orders that describe the answer. 
    For example, “[ [1, 2, 1], [3]]” and “[[3], [1,2,1]]” are both OK if the answer is [[1,2,1],[3]].
"""

#node definition
class Node:
	def __init__(self, data, next):
		self.data = data
		self.next = next
  
# (a) print_list(s) 구현
def print_list(s: Node):
    current = s  # 현재 노드를 s로 초기화
    result = []  # 결과를 저장할 리스트 초기화
    while current:  # 연결 리스트의 끝까지 반복
        result.append(current.data)  # 현재 노드의 데이터를 결과 리스트에 추가
        current = current.next  # 다음 노드로 이동
    print(result)  # 결과 리스트 출력


"""
1. palindrome 함수
연결 리스트의 중앙을 찾아 앞쪽 절반의 노드들의 값을 스택에 넣습니다. 
그 다음에 스택의 값을 뒤쪽 절반의 노드들의 값과 비교합니다.

slow, fast 포인터 사용: fast 포인터가 두 번의 속도로 움직이기 때문에 slow는 중간에 있을 때 fast는 끝에 도착합니다.

예: 리스트 = 1 -> 2 -> 3 -> 2 -> 1
초기: slow = 1, fast = 1
1회 반복 후: slow = 2, fast = 3
2회 반복 후: slow = 3, fast = 1 (끝)
여기서 slow는 중앙에 위치합니다.
중간에 도착한 후에는 slow 포인터를 사용하여 뒤쪽 절반을 스택의 top과 비교하면서 회문인지 확인합니다.

2. sub_list 함수
이 함수는 연결 리스트 t가 s의 부분 리스트인지 확인합니다.

current_s 포인터를 사용하여 s 리스트를 처음부터 끝까지 검사합니다.
각 위치에서 temp_s 포인터를 사용하여 s의 현재 부분과 t의 모든 노드를 비교합니다 (temp_t 포인터 사용).
만약 t의 모든 노드가 s의 연속된 부분 노드와 일치하면, t는 s의 부분 리스트입니다.
예제로 설명하자면:

s = 1 -> 2 -> 3 -> 4 -> 5
t = 3 -> 4

current_s는 1을 가리킵니다. 이 위치에서 temp_s와 temp_t를 사용하여 비교를 시작합니다. 
    1은 3과 다르므로 다음 위치로 이동합니다.
current_s는 2를 가리킵니다. 2와 3은 다릅니다. 
    다음 위치로 이동합니다.
current_s는 3을 가리킵니다. temp_s와 temp_t를 사용하여 비교를 시작하면, 3 -> 4와 3 -> 4가 일치하므로 t는 s의 부분 리스트임을 알 수 있습니다.
이렇게 palindrome 함수는 중앙을 찾아 회문을 판별하며, sub_list 함수는 부분 리스트를 확인하기 위해 포인터를 사용하여 두 연결 리스트를 비교합니다.
"""    
# (b) palindrome(s) 구현
def palindrome(s: Node):
    slow, fast = s, s  # 두 포인터 초기화: slow는 한 칸씩, fast는 두 칸씩 이동
    stack = []  # 스택 초기화
    
    while fast and fast.next:  # fast 포인터가 리스트의 끝에 도달할 때까지
        stack.append(slow.data)  # slow 포인터의 데이터를 스택에 추가
        slow = slow.next  # slow 포인터를 한 칸 이동
        fast = fast.next.next  # fast 포인터를 두 칸 이동
        
    if fast:                # 연결 리스트의 길이가 홀수인 경우
        slow = slow.next    # 중간 요소는 건너뛰고 slow를 한 칸 더 이동
    
    while slow:             # slow 포인터가 리스트의 끝에 도달할 때까지
        if slow.data != stack.pop():  # 스택의 맨 위 요소와 slow 포인터의 데이터를 비교
            return 0  # 회문이 아님
        
        slow = slow.next  # slow 포인터를 한 칸 이동
    return 1  # 회문임

# (c) sub_list(s, t) 함수
# t가 s의 부분 리스트인지 확인하는 함수입니다.
def sub_list(s: Node, t: Node):
    current_s = s  # s의 현재 위치를 가리키는 포인터
    
    while current_s:  # s의 끝까지 반복
        temp_s, temp_t = current_s, t  # 두 포인터를 각 리스트의 현재 위치로 초기화
        
        while temp_t and temp_s and temp_s.data == temp_t.data:  # 두 리스트의 요소가 같은 동안 반복
            temp_s = temp_s.next  # s의 포인터를 한 칸 이동
            temp_t = temp_t.next  # t의 포인터를 한 칸 이동
        
        if not temp_t:  # t가 끝까지 도달한 경우 (부분 리스트임을 의미)
            return 1
        current_s = current_s.next  # s의 포인터를 한 칸 이동
    
    return 0  # t는 s의 부분 리스트가 아님

# (d) max_palindromes(s) 함수
# 이 함수는 연결 리스트에서 모든 최대 회문을 찾아 출력합니다.
def max_palindromes(s: Node):
    n = 0  # 연결 리스트의 길이를 저장할 변수 초기화
    temp = s  # 임시 포인터 초기화
    while temp:  # 연결 리스트의 길이 계산
        n += 1
        temp = temp.next

    results = []  # 결과를 저장할 리스트 초기화
    for length in range(n, 0, -1):  # 연결 리스트의 길이부터 1까지 반복
        current = s  # 현재 위치를 s로 초기화
        for _ in range(n - length + 1):
            end = current
            for _ in range(length - 1):  # 부분 리스트의 끝을 찾음
                end = end.next

            temp_next = end.next  # 부분 리스트의 다음 노드 저장
            end.next = None  # 부분 리스트 임시 분리

            if palindrome(current):  # 분리된 부분 리스트가 회문인지 확인
                is_sublist = False
                for result in results:  # 이미 찾은 회문 리스트와 비교
                    if sub_list(result, current):  # 부분 리스트인지 확인
                        is_sublist = True
                        break
                    
                if not is_sublist:  # 다른 회문의 부분 리스트가 아니면 복제하여 추가
                    head = Node(current.data, None)
                    node, temp = head, current.next
                    
                    while temp:
                        node.next = Node(temp.data, None)
                        node, temp = node.next, temp.next
                    results.append(head)

            end.next = temp_next  # 연결 리스트 복원
            current = current.next  # s의 포인터를 한 칸 이동

    for result in results:  # 찾은 회문 부분 리스트 출력
        print_list(result)
