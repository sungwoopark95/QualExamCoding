"""
자연수를 parameter로 받고, 해당 자연수가 2개의 소수의 곱으로 표현된다면 True, 
아니라면 False를 반환하는 함수 P1를 작성하라.

<조건>
1. 유효하지 않은 input은 없다고 가정 
2. 리턴 값은 bool 타입

TestCase1)
>>> P1(6) #2*3
True
TestCase2)
>>>P1(12) #2*2*3 
False
"""
def P1(val: int) -> bool:
    i = 2
    cnt = 0
    quotient = val
    while quotient > 1 and cnt < 2:
        # 나누기가 되는 숫자이고 count도 가능하면 
        # 몫을 나눠야 할 값으로 업뎃하고 카운트 +1
        while quotient % i == 0 and cnt < 2:
            quotient = quotient / i
            cnt += 1
        # 나누기가 안 되는 숫자면 다음 숫자로 넘기기
        i += 1
       
    if quotient == 1 and cnt == 2:
        return True
    else:
        return False