"""
[소인수분해: Prime Factorizer]
자연수 한 개를 입력으로 받아 이를 소인수분해한 결과를 반환하는 함수 prime factorizer를 작성하라. 
소인 수분해한 결과는 (소수, 지수)의 tuple을 담은 list로 반환하며, 
리스트 내 tuple의 순서는 소수 크기의 오름차 순으로 정렬하여야 한다.

TestCase1)
>>> prime_factorizer(1)
[]
TestCase2)
>>> prime_factorizer(24)
[(2.3), (3,1)]
TestCase3)
>>> prime_factorizer(30)
[(2,1), (3,1), (5,1)]
"""

def prime_factorizer(num: int):
    ans = []
    i = 2
    quotient = num
    while quotient > 1:
        cnt = 0 # cnt 초기화 하기 (i가 달라질 때마다)
        while quotient % i == 0:
            quotient = quotient // i # 정수 나눗셈을 사용화여 결과를 정수로 유지
            cnt += 1
        if cnt > 0: # 소수의 count(지수)가 0보다 큰 경우에서 ans에 넣기
            ans.append((i, cnt))
        i += 1
                
    return ans   