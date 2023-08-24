"""
[그냥 반환 type이 set인 것]
정수(int)로만 구성된 리스트를 변수(argument)로 받고, 
그중 두 번 이상 반복되는 정수의 집합(set)을 리턴하는 함수를 작성하시오.

TestCase1)
>>> P1([1, 2, 3, 1]) 
{1}
TestCase2)
>>> P1([1, 1, 2, 3, 3, 3]) 
{1, 3}
"""
def P1(lst):
    dic = {}
    ans = []
    # val count별로 dictionary에 넣기
    for val in lst:
        if val not in dic:
            dic[val] = 1
        else:
            dic[val] += 1
    # count가 2번 이상인 애들 뽑아서 list에 넣고 set으로 return하기
    for k,v in dic.items():
        if v > 1:
            ans.append(k)
    return set(ans)