"""
알파벳으로만 구성된 리스트를 입력으로 받고, 대문자가 처음으로 등장하는 index를 리턴하는 함수 P5

<조건>
1. 입력 리스트는 알파벳 대문자 혹은 소문자로만 구성됨 
2. 대문자가 존재하지 않는 경우는 -1을 리턴

TestCase1)
>>> P5(['a', 'B', 'c', 'D']) 
1
"""

def P5(lst):
    idx = 0
    while idx != len(lst):
        if 65 <= ord(lst[idx]) and ord(lst[idx]) <= 90:
            return idx
        else:
            idx += 1
    return -1