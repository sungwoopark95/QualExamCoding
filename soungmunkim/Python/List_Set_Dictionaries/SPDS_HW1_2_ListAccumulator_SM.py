"""
[list 합치기]
list1 = [1, 2, 3]
list2 = [1, [2, 3], [[4]]]
list3 = [[[1], 3], [[4, 2], 5], 6, [[7]]]
위와 같은 정수 nested list를 입력으로 받아 저장된 모든 정수를 합쳐서 반환하는 함수

>>> list_accumulator(list1)
6
>>> list_accumulator(list2)
10
"""

def sumList(lst:list):
    sum = 0
    while lst:
        # print(lst)
        size = len(lst)
        for i in range(size):
            nums = lst.pop(0)
            # print(f"nums: {nums}")
            # print(isinstance(nums, int))
            
            # nums가 int type이면 더하고 아니면 for loop 돌면서 list에 넣기
            if isinstance(nums, int):
                sum += nums
            else:
                for i in range(len(nums)):
                    lst.append(nums[i])
                
    return sum