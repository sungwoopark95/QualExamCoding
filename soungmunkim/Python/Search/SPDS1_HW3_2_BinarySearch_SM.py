"""
[binary search 구현]

>>> list1 = [3, 7, 9, 33, 126, 16
>>> binary_search(list1, 126)
4
"""

def binary_search(lst, val):
    # bs: 내부 재귀 함수로 실제 바이너리 탐색을 수행합니다.
    def bs(lst, low, high, val):
        # low가 high보다 큰 경우, 탐색할 대상이 없으므로 -1을 반환합니다.
        if (low > high):
            return -1
        
        # 현재 탐색할 리스트의 중간 인덱스를 계산합니다.
        i = int((low + high) / 2)
        
        # 중간 인덱스에 있는 값이 찾고자 하는 값과 같다면, 해당 인덱스를 반환합니다.
        if (lst[i] == val):
            return i
        
        # 중간 인덱스에 있는 값이 찾고자 하는 값보다 작다면, 
        # 중간 인덱스 이후의 부분 리스트에서 다시 탐색합니다.
        elif (lst[i] < val):
            return bs(lst, i+1, high, val)
        # 중간 인덱스에 있는 값이 찾고자 하는 값보다 크다면, 
        # 중간 인덱스 이전의 부분 리스트에서 다시 탐색합니다.
        else:
            return bs(lst, low, i-1, val)

    # 전체 리스트에서 시작하여 바이너리 탐색을 수행합니다.
    return bs(lst, 0, len(lst)-1, val)
