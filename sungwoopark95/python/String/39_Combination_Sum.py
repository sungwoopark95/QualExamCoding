from typing import List

##################### 더해서 n이 되는 모든 k개의 정수 조합을 찾는 함수 #####################
def sum_comb(n, k, current=[], start=1):
    # n이 0이고, k도 0인 경우 현재 조합(current)이 원하는 조합이므로 반환합니다.
    if k == 0 and n == 0:
        return [list(current)]
    # k가 0이거나 n이 0보다 작은 경우 유효하지 않은 조합이므로 빈 리스트를 반환합니다.
    if k == 0 or n < 0:
        return []

    result = []
    # start에서 n까지 순회하면서 가능한 조합을 탐색합니다.
    for i in range(start, n+1):
        result += sum_comb(n - i, k - 1, current + [i], start)

    return result

################################# My Code ###################################
def combinationSum(candidates: List[int], target: int) -> List[List[int]]:
    ans = []
    # 1부터 target까지의 정수에 대해 각각의 정수를 포함하는 조합을 탐색합니다.
    for i in range(1, target+1):
        # target을 만드는 i개의 조합을 탐색합니다.
        combinations = sum_comb(target, i)
        # 찾은 각 조합에 대해 처리합니다.
        for comb in combinations:
            flag = True
            # 조합의 각 요소가 candidates에 포함되어 있는지 확인합니다.
            for element in comb:
                if element not in candidates:
                    flag = False
            # 모든 요소가 candidates에 포함되어 있고, 해당 조합이 ans에 없으면 ans에 추가합니다.
            if flag and sorted(comb) not in ans:
                ans.append(comb)
    return ans
###############################################################################

################################# ChatGPT 코드 #################################
def combinationSum(candidates: List[int], target: int) -> List[List[int]]:
    def backtrack(remaining, combo, start):
        if remaining == 0:
            # 잔여 합계가 0이면 현재 조합을 결과에 추가합니다.
            result.append(list(combo))
            return
        elif remaining < 0:
            # 잔여 합계가 0보다 작으면 더 이상의 조합을 탐색할 필요가 없습니다.
            return

        for i in range(start, len(candidates)):
            # 현재 숫자를 조합에 추가하고, 백트래킹을 통해 가능한 조합을 탐색합니다.
            combo.append(candidates[i])
            backtrack(remaining - candidates[i], combo, i)
            # 백트래킹을 위해 마지막에 추가된 숫자를 제거합니다.
            combo.pop()

    result = []
    backtrack(target, [], 0)
    return result
###############################################################################
    
if __name__ == "__main__":
    candidates = [2]
    target = 1
    combinationSum(candidates, target)
    