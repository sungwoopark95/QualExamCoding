"""
[0과 1의 개수가 같은 부분 list의 길이 반환]

0과 1로만 이루어진 리스트 nums를 입력으로 받는다. 0과 1의 개수가 같은 부분 리스트의 길이의 최대값을 return 하는 함수를 구현하시오. 
부분 리스트란, 𝑛𝑢𝑚𝑠[𝑖: 𝑗], 0 ≤ 𝑖 ≤ 𝑗 ≤ 𝑙𝑒𝑛(𝑛𝑢𝑚𝑠)와 같이 리스트의 연속된 일부분을 뜻한다. 
그러한 부분 리스트가 없으면 0 을 return 하면 된다.
(리스트의 길이는 1 이상이다.)

TestCase1)
P2([1,1,0,1,0,1])
4
"""

def P2_ans(nums: list):
    # 첫번째 발견된 누적 개수를 저장하는 딕셔너리 (누적 개수: 인덱스)
    first_cnt = dict()
    
    # 현재까지 1과 0의 차이를 누적한 개수 (1은 +1, 0은 -1로 카운트)
    curr_cnt = 0
    
    # 0과 1의 개수가 같은 최대 부분 리스트의 길이
    max_len = 0
    
    # 리스트의 모든 요소를 순회하면서
    for i in range(len(nums)):
        # 현재 값이 0이면 curr_cnt를 1 감소
        if nums[i] == 0:
            curr_cnt += -1
        # 현재 값이 1이면 curr_cnt를 1 증가
        else:
            curr_cnt += 1
        
        # 만약 curr_cnt가 0이면, 이전부터 현재까지 0과 1의 개수가 같다는 의미
        if curr_cnt == 0:
            print(i)
            max_len = i+1
        else:
            # curr_cnt 값이 이전에 발견되었으면, 그 위치부터 현재 위치까지 0과 1의 개수가 같다는 의미
            if curr_cnt in first_cnt:
                max_len = max(max_len, i - first_cnt[curr_cnt])
            # 처음 발견된 curr_cnt 값이면 위치 정보 저장
            else:
                first_cnt[curr_cnt] = i
    
    return max_len