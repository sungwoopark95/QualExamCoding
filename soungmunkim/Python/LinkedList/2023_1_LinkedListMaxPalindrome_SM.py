"""
[Linked list로 max palindrome 찾기]
|!!! Linked list를 list로 변환해서 푼 것 !!!

Suppose we represent a sequence of integers from 0 to 9 with a list, and it is implemented with a linked list. 
For example, an integer list [3, 7, 6, 8] is implemented with a linked list:

A list of integers is a palindrome if it is identical to its reversion. 
Given a list s of integers, you will finally implement a function max_palindromes(s) 
    that prints a list of sub-lists of s that are maximal palindromes. 
    
That is, t is a list that contains palindrome sub-lists of s that are not a sub-list of another palindrome sub-list of s. 

For example, when s is [8,1,2,3,3,2,1,4,9,5,4,5,6,7,6,5,4,1], 
    **max-palindromes(s)** prints:
    [[8], [1,2,3,3,2,1], [4,9,4], [4,5,6,7,6,5,4]].

When s is [8,1,2,3,3,2,1,0,4,9,1,2,3,3,2,1,9,1], 
    max_palindromes(s) prints:
    [[8], [0], [4], [9,1,2,3,3,2,1,9], [1,9,1]].

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

# (a) prints the sequence (i.e., the linked list) s in the list format. 
output = []
def print_list(s:Node):
    if s is not None:
        output.append(s.data)
        print_list(s.next)
    else:
        print(output)

# (b) Write a function palindrome(s)
def palindrome(s: str):
    if s == s[::-1]:
        return 1
    else:
        return 0

# (c) Write a function sub_list(s, t)
def substring(s:str, t:str):
    n = len(s)
    m = len(t)
    
    # 만약 길이 자체가 t가 더 크면 -> t는 s의 substring 아님
    if m > n:
        return False
    # s와 t 길이 차이만큼 돌건데 s를 t 길이만큼 돌면서 체크할 것
    for i in range(n-m+1):
        if s[i:i+m] == t:
            return 1

    return 0

# helper (Linked list to List)
def linkiedListToList(head):
    result = []
    current = head
    while current:
        result.append(current.data)
        current = current.next
    return result

# helper (List to Linked list)
def listToLinkedList(lst: list):
    if not lst:
        return None

    head = Node(lst[0], None)
    current = head

    for value in lst[1:]:
        current.next = Node(value, None)
        current = current.next

    return head
 
# (d) Write the function max_palindromes(s)
def max_palindromes(s:Node):
    listToLinkedList(s)
    max_pals = []
    
    # 모든 가능한 substring 뽑기
    for i in range(len(s)):
        for j in range(i, len(s)):
            sub = s[i:j+1]
            
            if palindrome(sub): # 현재 substring이 palindrome 일때 
                is_maximal = True # 현재 palindrome이 max라고 추정하고 시작
                for pal in max_pals:
                    # 만약 현재 palindrome이 기존 palindrome의 substring이라면
                    if substring(pal, sub) and pal != sub:
                        is_maximal = False
                        break
            
                # 만약 현재 palindrome이 기존 palindrome의 substring이 아니라면 후보에 넣기
                if is_maximal:
                    max_pals.append(sub)
                    
    # palindrome 후보들 중 substring인 후보는 빼기 (filltering 작업)
    """
    max_pals = [pal for pal in max_pals if not any(substring(other, pal) for other in max_pals if other != pal)]
    """
    filtered_max_pals = []

    for i in range(len(max_pals)):
        is_substring = False
        for j in range(len(max_pals)):
            if i != j: # 자기 자신 제외
                # max_pals[i] 가 다른 palindrome의 substring인지 체크
                if substring(max_pals[j], max_pals[i]):
                    is_substring = True
                    break
                
        if is_substring == False:
            filtered_max_pals.append(max_pals[i])  
    
    s_node =  listToLinkedList(filtered_max_pals)
    print_list(s_node)