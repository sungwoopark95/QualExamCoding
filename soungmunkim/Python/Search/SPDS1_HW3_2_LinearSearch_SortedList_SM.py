"""
Elements가 sorted된 상태에서 진행하는 Linear search

>>> list1 = [3, 7, 9, 33, 126, 162]
>>> linear_search_sorted(list1, 33)
True
"""
def linear_search_sorted(lst, val):
    found = False
    for i in lst:
        if (i == val):
            found = True
            break
        if (i > val):
            found = False
    return found