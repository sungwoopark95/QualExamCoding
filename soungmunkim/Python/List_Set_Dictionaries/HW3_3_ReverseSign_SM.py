"""
[양수 음수 변경]
정수로 구성된 리스트를 입력으로 받고 리스트 안의 값이 음수이면 양수로, 
양수이면 음수로 변경하여 리턴하는 함수 P3를 작성

<조건>
1.값이0일때는변경없음
2. 입력 받은 원본 리스트를 변경하지 말고, 새로운 리스트를 리턴하여야 함

TestCase1)
>>> P3([-1, 2]) 
[1, -2]
"""
def P3(lst):
    ans = []
    for val in lst:
        if val != 0:
            ans.append(-val)
        else:
            ans.append(val)

    return ans   