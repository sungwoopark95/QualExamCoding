"""
[각 쌍의 합이 모두 k로 나눠지는 짝 만들기]
0 이상 정수로 이루어진 리스트 nums 와 0 이상 정수 k 를 입력으로 받는다. 
리스트의 원소를 둘씩 짝지으려고 하는데, 각각의 쌍의 합이 모두 k로 나누어지도록 짝을 지으려 한다. 
가능하면 True, 불가능하면 False 를 return 하는 함수를 구현하시오.
(리스트의 길이는 2 이상 짝수이다)

TestCase1)
>>> P1([123, 36, 54, 28, 39, 28], 3)
True
"""

def P1(nums:list, k:int):
    remainder_dct = {}
    # 각 숫자를 k로 나눈 뒤 나머지 값을 저장하는 dict
    for num in nums:
        remainder = num % k
        if remainder not in remainder_dct:
            remainder_dct[remainder] = 1
        else:
            remainder_dct[remainder] += 1
            
    # 나머지 값이 0인 숫자가 홀수면 False 
    if remainder_dct.get(0) % 2 != 0:
        return False
    
    # 나머지 값이 0인 숫자들은 서로 짝지으면 되서 dictionary에서 삭제
    if 0 in remainder_dct:
        del remainder_dct[0]
    
    # 나머지 개수들 확인해서 가능한 짝 찾기
    for remainder, count in remainder_dct.items():
        # 현재 나머지와 짝지어질 수 있는 다른 나머지가 없으면 
        if k - remainder not in remainder_dct:
            return False
        # 현재 나머지 개수와 짝 지어질 수 있는 다른 나머지 개수가 다르면 (모두 짝 지을 수 없어서)
        if remainder_dct[k - remainder] != count:
            return False 
    
    return True
    