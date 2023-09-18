############################### String permutation ###############################
def str_perm(s):
    def backtrack(start):
        if start == len(s):
            permutation_lst.append(''.join(s))
            return
    
        # 시작 인덱스부터 문자열의 끝까지 루프를 실행
        for i in range(start, len(s)):
            # 현재 시작 인덱스와 루프의 인덱스 위치의 문자를 교환 (스왑)
            s[start], s[i] = s[i], s[start]
            
            # 현재 시작 인덱스를 제외한 나머지 문자열에 대해 순열을 생성하기 위해 재귀적으로 호출
            backtrack(start + 1)
            
            # 이전 상태로 문자열을 복원하기 위해 다시 문자 위치를 교환 (백트래킹)
            s[start], s[i] = s[i], s[start]

    permutation_lst = []
    s = list(s)
    backtrack(0)
    return permutation_lst
##################################################################################

############################ integer list permutation ############################
def int_perm(nums):
    def backtrack(start):
        if start == len(nums):
            permutation_lst.append(nums[:])  # deep copy를 추가해주어야 합니다.
            return
    
        for i in range(start, len(nums)):
            # 현재 시작 인덱스와 루프의 인덱스 위치의 정수를 교환 (스왑)
            nums[start], nums[i] = nums[i], nums[start]
            
            # 현재 시작 인덱스를 제외한 나머지 리스트에 대해 순열을 생성하기 위해 재귀적으로 호출
            backtrack(start + 1)
            
            # 이전 상태로 리스트를 복원하기 위해 다시 정수 위치를 교환 (백트래킹)
            nums[start], nums[i] = nums[i], nums[start]

    permutation_lst = []
    backtrack(0)
    return permutation_lst
##################################################################################

# 예제
if __name__ == "__main__":
    nums = [3,2,1]
    print(int_perm(nums))
