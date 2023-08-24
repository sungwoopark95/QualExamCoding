"""
rat_1, rat_2는 두 마리의 rat의 무게를 열흘 간 매일 측정하여 기록해놓은 리스트이다. 
두 리스트와 1과 10사이의 숫자가 하나가 주어졌을때,해당 숫자에 해당하는 날에 1번 rat의 무게가 더 높았으면 True,
아니라면 False를 리턴하는 함수 P10을 작성하세요.

<조건> 
1.두 rat의 무게가 완전히 같아지는 날은 없음

<입력 리스트 예시> 
rat_1=[5,6,7,6,7,8,10,9,8,10] 
rat_2=[7,8,6,7,8,10,9,8,10,11]

TestCase1)
>>> P10(rat_1, rat_2, 1) 
False
"""
def P10(lst1, lst2, day):
    idx = day-1
    ans = True
    if lst1[idx] < lst2[idx]:
        ans = False
    return ans