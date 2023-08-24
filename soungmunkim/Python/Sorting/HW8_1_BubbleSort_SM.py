"""
[Bubble sort에서 swap되는 횟수]
Bubble Sort: 인접한 두 원소의 순서가 바뀌어 있을 때 (앞의 원소가 뒤의 원소보다 클 때) 서로 swap하면서 정렬하는 알고리즘
정수로 이루어진 리스트(list)를 변수(argument)로 받아 버블 정렬할 때, swap이 일어나는 횟수를 리턴하는 함수를 작성하시오.

TestCase1)
>>> P1([5, 1, 4, 2, 8]) 
4
TestCase2)
>>> P1([-1, -1, -1, -1, -1]) 
0
TestCase3)
>>> P1([6, 5, 4, 3, 2, 1]) 
15
"""

def P1(lst: int):
    swap = 0
    tot_idx = 0
    j = 1 # cursur
    # 큰 Loop로 돌기 (주변만 swap하는 거기 때문에 계속 반복해야함)
    while tot_idx < len(lst):
        # 주변 swap하기
        for i in range(0, len(lst)-1):
            if lst[i] > lst[j]:
                lst[i], lst[j] = lst[j], lst[i]
                swap += 1
            j += 1
        # 한 loop 돌았을 때 j reset해주기 & 큰 loop 횟수 +1
        j = 1
        tot_idx += 1
    return swap