##################### list에서 정해진 길이만큼의 조합(combination)을 만드는 함수 #####################
def list_comb(nums, length):
    # 리스트의 길이가 요구되는 길이보다 짧을 경우 에러 메시지를 출력하고 빈 리스트 반환
    if length > len(nums):
        print("length cannot be greater than the length of nums")
        return []

    def backtrack(start, length, path):
        # 기저 조건: path의 길이가 요구되는 길이와 같을 경우
        if len(path) == length:
            output.append(path[:])  # path의 복사본을 output에 추가
            return
        for i in range(start, len(nums)):
            # 현재의 숫자를 path에 추가
            path.append(nums[i])
            # 다음 정수들을 사용하여 조합을 완성
            backtrack(i + 1, length, path)
            # 백트래킹: 마지막에 추가된 숫자 제거
            path.pop()
    
    output = []  # 최종 결과를 저장할 리스트
    backtrack(0, length, [])  # 백트래킹 시작
    return output  # 완성된 조합들의 리스트 반환
############################# 예시 #############################
# lst = [1, 2, 3]
# length = 2
# print(list_comb(lst, length)) # [[1, 2], [1, 3], [2, 3]]
###############################################################


##################### string에서 정해진 길이만큼의 조합(combination)을 만드는 함수 #####################
def str_comb(nums, length):
    # 입력된 문자열의 길이가 요구되는 길이보다 짧을 경우 에러 메시지 출력 후 빈 리스트 반환
    if length > len(nums):
        print("length cannot be greater than the length of nums")
        return []

    def backtrack(start, length, path):
        # 기저 조건: path의 길이가 원하는 길이와 동일한 경우
        if len(path) == length:
            # path의 내용을 문자열로 변환하여 output에 추가
            output.append(''.join(path[:]))
            return
        for i in range(start, len(nums)):
            # 현재 문자를 path에 추가
            path.append(nums[i])
            # 다음 문자들을 사용하여 조합을 완성
            backtrack(i + 1, length, path)
            # 백트래킹: path의 마지막 문자 제거
            path.pop()

    output = []  # 최종 결과를 저장할 리스트
    backtrack(0, length, [])  # 백트래킹 시작
    return output  # 완성된 조합들의 리스트 반환
############################# 예시 #############################
# string = "str"
# length = 2
# print(str_comb(string, length)) # ["st", "tr", "sr"]
###############################################################


##################### 더해서 n이 되는 모든 k개의 정수 조합을 찾는 함수 #####################
def sum_comb(n, k, current=[], start=1):
    if k == 0 and n == 0:
        return [list(current)]
    if k == 0 or n < 0:
        return []

    result = []
    for i in range(start, n+1):
        result += sum_comb(n - i, k - 1, current + [i], start)

    return result
############################# 예시 #############################
# n = 4
# k = 3
# print(list_comb(n, k)) # [[1, 1, 2], [1, 2, 1], [2, 1, 1]]
###############################################################