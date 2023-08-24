"""
[Linear Search]

    리스트에서 주어진 키를 선형 탐색하여 그 인덱스를 반환합니다.
    키가 리스트에 없으면 -1을 반환합니다.

    :param lst: 탐색할 리스트
    :param val: 찾을 값
    :return: 키의 인덱스 또는 -1
    
>>> list1 = [3, 7, 9, 33, 5, 7, 12, 16]
>>> linear_search(list1, 5)
4
"""

def linear_search(lst, val):
    n = len(lst)
    idx = -1
    for i in range(n):
        if (lst[i] == val):
            idx = i
    return idx


# def linear_search(lst, val):
#     for i, value in enumerate(lst):
#         if value == val:
#             return i  # 키가 리스트에 있으면 해당 인덱스를 반환
#     return -1  # 키가 리스트에 없으면 -1 반환