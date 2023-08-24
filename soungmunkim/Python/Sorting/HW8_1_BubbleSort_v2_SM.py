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

def P1_ans(num_list: list): 
### Write code here ###
    ans = 0
    for i in range(len(num_list)):
        for j in range(len(num_list)-i-1): 
            if num_list[j] > num_list[j+1]:
                num_list[j], num_list[j+1] = num_list[j+1], num_list[j]
                ans += 1
    return ans
### End of your code ###