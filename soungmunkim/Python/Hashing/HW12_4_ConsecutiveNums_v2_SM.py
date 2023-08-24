"""
[연속적인 수 뽑기]

정수로 이루어진 리스트 nums 를 입력으로 받는다. 
여기서 몇 개의 수를 뽑는데, 뽑은 수들이 연속적이어야 한다 (순서는 상관없음). 
뽑을 수 있는 최대 개수를 return 하는 함수를 구현하시오. (리스트의 길이는 1 이상이다.)

TestCase1)
>>>P4([3, 6, 4, 64, 10, 29, 5, 9, 11])
4
설명:3,6,4,5를 뽑으면 연속된 4개의 정수가 된다. 뽑는 방법은 여러가지일 수 있고, 최대 개수만 return 하면 된다.
"""

def P4_ans(nums: list):
    
    max_len = 0
    # 중복 숫자 제외
    s = set(nums)
    
    for i in range(len(nums)):
        # nums[i]가 연속된 숫자의 시작 숫자인지 확인
        # 만약 nums[i]-1이 set에 없으면, nums[i]는 연속된 숫자의 시작일 것임
        if nums[i] - 1 not in s:
            end = nums[i]
           
            # nums[i]부터 시작하여 연속되는 숫자가 있는 동안 반복
            # 즉, end는 연속된 숫자의 마지막 숫자의 다음 숫자를 가리키게 됨 
            while end in s:
                end += 1
            # 현재 연속된 숫자의 길이를 계산하고, 이전까지의 최대 길이와 비교하여 더 큰 값을 저장
            # 연속된 숫자니까 index 차이로 계산 안 해도 구할 수 있음
            max_len = max(max_len, end - nums[i])

    return max_len    