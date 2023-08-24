"""
[selection sort 구현하기]
가장 작은 element를 선택(select)하여 정렬하는 알고리즘
"""

def selection_sort(arr):
    for i in range(len(arr)):
        smallest = i # initialize smallest
        for j in range(i, len(arr)):
            if arr[j] < arr[smallest]:
                smallest = j # update smallest
        if arr[smallest] < arr[i]:
            arr[i], arr[smallest] = arr[smallest], arr[i] # swap