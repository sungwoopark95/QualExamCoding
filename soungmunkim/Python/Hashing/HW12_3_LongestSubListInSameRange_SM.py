"""
[두 부분 List의 합이 같은 최대 길이 반환]

0 과 1 로만 이루어진 리스트 A, B 를 입력으로 받는다. 
다음 조건을 만족하는 부분 리스트 길이의 최대값을 return 하는 함수를 구현하시오. 
그러한 부분 리스트가 없으면 0 을 return 하면 된다.
(A와 B는 길이가 1이상이고, 길이가 서로 같다.)
조건: 
𝑠𝑢𝑚(𝐴[𝑖: 𝑗]) == 𝑠𝑢𝑚(𝐵[𝑖: 𝑗]), 0 ≤ 𝑖 ≤ 𝑗 ≤ 𝑙𝑒𝑛(𝐴)

TestCase1)
>>> A = [0,1,1,(0,1,0,1,1),1]
>>> B = [0,0,0,(1,0,1,0,1),0]
>>>>P3(A,B)
5 

"""

def P3_withfunc(A, B):
    
    # 누적 합 구하는 함수
    def get_cumulative_sum(nums):
        cum_sum = [0]
        total = 0
        for num in nums:
            total += num
            cum_sum.append(total)
        return cum_sum
    # 누적합을 각 리스트 마다 만들기
    cum_sum_A = get_cumulative_sum(A)
    cum_sum_B = get_cumulative_sum(B)

    max_len = 0
    sum_diff = {}

    # 각 위치에서의 누적 합의 차이를 저장하며 동일한 차이를 가진 위치를 찾는다.
    for i in range(len(A) + 1):
        diff = cum_sum_A[i] - cum_sum_B[i]
        
        # 만약 동일한 차이가 이전에 나타났다면
        if diff in sum_diff:
            # 현재 위치와 이전 위치의 차이를 길이로 계산
            length = i - sum_diff[diff]
            max_len = max(max_len, length)
        else:
            sum_diff[diff] = i

    return max_len
