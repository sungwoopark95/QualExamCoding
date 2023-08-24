"""
[binary search 구현]

>>> list1 = [3, 7, 9, 33, 126, 16
>>> binary_search_iter(list1, 126)
4
"""

def binary_search_iter(lst, val):
    low = 0
    high = len(lst) - 1
    while (low < high):
        i = int((high + low) / 2)
        if (lst[i] == val):
            return i
        elif (lst[i] < val):
            low = i + 1
        else:
            high = i - 1
    return -1
