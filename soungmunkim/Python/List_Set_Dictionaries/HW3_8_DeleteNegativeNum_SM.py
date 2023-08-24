"""
숫자로 구성된 리스트를 입력으로 받고, 해당 리스트에서 음수만 제거하는 함수 P8를 작성하세요. 

<조건>
1. 입력으로는 숫자만 주어짐

TestCase1)
>>> P8([1, 2, 3, -3, 6, -1, -3, 1]) 
[1,2,3,6,1]
"""
def P8(lst):
    idx = 0
    copy = lst[:]
    while idx != len(copy):
        # 보존되는 copy로 negative index찾고 해당 값을 다른 list에서 지우기
        if copy[idx] < 0:
            lst.remove(copy[idx])
        idx += 1
    
    return lst 