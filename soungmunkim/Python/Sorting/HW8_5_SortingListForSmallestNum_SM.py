"""
[두 list 합이 최소값이 되게 list 정렬]
길이가 L이고, 음이 아닌 정수로 이루어진 두 listA,B가 있을 때,A를 재배열해서 다음 값을 최소로 만들려고 한다.
최소가 되는 S를 return하는 함수 P5(A,B)를 구현하시오. (list A, B를 입력으로 받음)
S = A[0] * B[0] + A[1] * B[1] + ... + A[L-1]*B[L-1]

TestCase1)
>>> P5([1,1,1,6,0], [2,7,8,3,1]) 
18
TestCase2)
>>> P5([1,4,2,6,1,0], [3,5,1,2,4,1]) 
21
"""

def P5(A, B):
    # A를 오름차순으로 재배열하기
    inc_lst = sorted(A)
    
    lst_size = len(B)
    i = 0
    s = 0
    # B는 내림차순으로 하면서 같은 index끼리 곱해서 더하기
    while i < lst_size: # list size 정해놓고 하기때문에 list 값 지워도 영향 안 받음
        v = max(B)
        B.remove(v)
        s += inc_lst[i] * v 
        i+=1
        
    return s