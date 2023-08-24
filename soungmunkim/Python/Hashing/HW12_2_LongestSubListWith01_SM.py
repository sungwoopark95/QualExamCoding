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

def P2(nums:list):
    # j로 끝을 확인하기 위해 -1를 뒤에 붙이기
    nums.append(-1)
    dct = {0:1, 1:0}
    
    j = 1
    idx_lst = []
    max_len = 0
    cnt = 0
        
    for i in range(len(nums)-1):
        # 1과 0이 교차되는 index 쌍 list에 저장
        if dct.get(nums[i]) == nums[j]:
            idx_lst.append((i, j))
            
        # 1과 0이 교차되지 않거나 num list가 끝나면   
        elif dct.get(nums[i]) != nums[j] or nums[j] == -1: 
            
            #만약 교차된 게 있다면 끝점 - 시작점으로 count 알기
            if len(idx_lst) > 0:
                cnt = idx_lst[-1][-1] - idx_lst[0][0]
           
            # 최대값 Update
            max_len = max(max_len, cnt)
            # count가 홀수일 경우 +1 해서 짝수로 (1,0같은 개수 = 짝수)
            if max_len % 2 != 0:
                max_len += 1
                
            idx_list = [] # 교차되는 지점 다시 reset
        
        j += 1
    
    return max_len
            