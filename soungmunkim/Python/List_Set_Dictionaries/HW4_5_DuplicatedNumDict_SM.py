"""
딕셔너리를 변수(argument)로 받아 두 번 이상 나타나는 value를 리스트로 저장하여 리턴하는 함수를 작성하시오.

TestCase1)
>>> P5({'red': 1, 'green': 1, 'blue': 2}) 
[1]
"""

def P5(dic):
    cnt = {}
    ans = []
    for val in dic.values():
        if val not in cnt:
            cnt[val] = 1
        else:
            cnt[val] += 1
    for k,v in cnt.items():
        if v > 1:
            ans.append(k)
    return ans