"""_summary_
주어진 후보 숫자 집합(candidates)과 목표 숫자(target)가 있을 때, 후보 숫자의 합이 목표 숫자가 되는 모든 유일한 조합을 찾아야 합니다.
각 후보 숫자는 조합에서 한 번만 사용될 수 있습니다.
참고: 결과 집합에는 중복된 조합이 포함되어서는 안 됩니다.

예시 1:
입력: candidates = [10,1,2,7,6,1,5], target = 8
출력:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

예시 2:
입력: candidates = [2,5,2,1,2], target = 5
출력:
[
[1,2,2],
[5]
]
"""

from typing import List

############################# My Code - Time Limit Exceeded ##########################
def combinationSum2(candidates: List[int], target: int) -> List[List[int]]:
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
            # backtracking을 할 때, i부터 시작하면 자기 자신의 index부터 다시 시작하기 때문에 자기 자신도 포함될 수 있음
            # 여기서는 중복을 방지하기 위해 i+1로 자기 자신을 지난 다음부터 backtracking하도록 조작
            backtrack(remaining - candidates[i], combo, i+1)
            # 백트래킹을 위해 마지막에 추가된 숫자를 제거합니다.
            combo.pop()

    result = []
    backtrack(target, [], 0)

    # 중복제거
    unique_result = []
    for item in result:
        if sorted(item) not in unique_result:
            unique_result.append(sorted(item))
    return unique_result
##########################################################################################

####################################### ChatGPT ##########################################
def combinationSum2(candidates: List[int], target: int) -> List[List[int]]:
    def backtrack(start, target, path):
        # 타겟이 0이 되면 결과 리스트에 경로를 추가한다.
        if target == 0:
            res.append(path)
            return
        for i in range(start, len(candidates)):
            # 중복된 숫자를 건너뛴다.
            if i > start and candidates[i] == candidates[i-1]:
                continue
            # 만약 현재 숫자가 타겟보다 크다면 더 이상 탐색하지 않는다.
            if candidates[i] > target:
                break
            # 다음 숫자로 백트래킹
            backtrack(i+1, target-candidates[i], path+[candidates[i]])

    candidates.sort()  # 후보 숫자 정렬
    res = []
    backtrack(0, target, [])
    return res
###########################################################################################


if __name__ == "__main__":
    candidates = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
    target = 30
    print(combinationSum2(candidates, target))