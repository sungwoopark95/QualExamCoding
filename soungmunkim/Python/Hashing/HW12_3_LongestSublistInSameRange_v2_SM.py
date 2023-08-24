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

def P3(A, B):
    # 누적 합 리스트를 계산
    """
    각각의 리스트에 대한 누적 합을 저장합니다. 
    예를 들어, A = [1, 2, 3] 이면 cum_sum_A = [0, 1, 3, 6]이 됩니다.
    """
    cum_sum_A = [0]
    cum_sum_B = [0]
    
    for a, b in zip(A, B):
        cum_sum_A.append(cum_sum_A[-1] + a)
        cum_sum_B.append(cum_sum_B[-1] + b)

    max_len = 0
    
    # 가능한 모든 시작점에 대하여
    for i in range(len(A) + 1):
        # 가능한 모든 종료점에 대하여
        for j in range(i + 1, len(A) + 1):
            # A와 B의 부분 리스트 합을 계산
            """
            부분 리스트 A[i:j]의 합은 cum_sum_A[j] - cum_sum_A[i]와 같습니다.
            """
            sum_A = cum_sum_A[j] - cum_sum_A[i]
            sum_B = cum_sum_B[j] - cum_sum_B[i]
            
            # 만약 두 부분 리스트의 합이 같다면, 최대 길이 Update 해보기
            if sum_A == sum_B:
                max_len = max(max_len, j - i)

    return max_len
