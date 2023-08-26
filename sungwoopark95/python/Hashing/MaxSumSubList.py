"""
0과 1로만 이루어진 리스트 `A`, `B`를 입력으로 받는다. 
다음 조건을 만족하는 부분 리스트 길이의 최대값을 return하는 함수를 구현하시오. 
그러한 부분 리스트가 없으면 0을 return하면 된다. (`A`와 `B`는 길이가 1 이상이고, 길이가 서로 같다.)
* 조건: `sum(A[i:j]) == sum(B[i:j]) 0<=i<=j<=len(A)`
"""
from typing import List

## O(n^2)으로 푸는 방법
def P3(A:List, B:List):
    length = len(A)
    sum_dict_A = dict()
    max_sum_A = 0
    for i in range(length):
        for j in range(i, length+1):
            sublist = A[i:j]
            if sum(sublist) in sum_dict_A:
                sum_dict_A[sum(sublist)].append((i, j))
            else:
                sum_dict_A[sum(sublist)] = [(i, j)]
            max_sum_A = max(max_sum_A, sum(sublist))
    
    sum_dict_B = dict()
    max_sum_B = 0
    for i in range(length):
        for j in range(i, length+1):
            sublist = B[i:j]
            if sum(sublist) in sum_dict_B:
                sum_dict_B[sum(sublist)].append((i, j))
            else:
                sum_dict_B[sum(sublist)] = [(i, j)]
            max_sum_B = max(max_sum_B, sum(sublist))
    
    if max_sum_A > max_sum_B:
        to_iterate = sum_dict_B
        opposite = sum_dict_A
    else:
        to_iterate = sum_dict_A
        opposite = sum_dict_B
        
    max_len = 0
    max_pair = None
    for key in to_iterate:
        if key in opposite:
            for pair in to_iterate[key]:
                if pair in opposite[key]:
#                     if max_len < pair[1] - pair[0]:
#                         max_len = pair[1] - pair[0]
#                         max_pair = pair
                    max_len = max(max_len, pair[1] - pair[0])
    print(max_pair)
    return max_len

# O(n)으로 푸는 방법 - P2와 같은 아이디어
def P3_On(A, B):
    """
    1. A와 B의 누적 합을 각각 계산합니다.
    2. 두 리스트의 누적 합의 차이를 계산합니다.
    3. 누적 합의 차이가 같은 두 지점 사이에는 sum(A[i:j]) == sum(B[i:j])라는 조건이 만족됩니다.
    4. 따라서 누적 합의 차이가 0인 지점까지의 길이나 누적 합의 차이가 같은 두 지점 사이의 길이를 찾아 최대 길이를 계산합니다.
    """
    # 누적 합의 차이와 해당 지점의 인덱스를 저장할 딕셔너리
    diff_to_index = {0: -1}
    max_len = 0
    cum_diff = 0
    
    for i in range(len(A)):
        cum_diff += A[i] - B[i]
        
        # 누적 합의 차이가 이전에 나왔던 적이 있다면, 그 지점과 현재 지점 사이의 길이를 계산
        if cum_diff in diff_to_index:
            max_len = max(max_len, i - diff_to_index[cum_diff])
        else:
            diff_to_index[cum_diff] = i
    
    return max_len
