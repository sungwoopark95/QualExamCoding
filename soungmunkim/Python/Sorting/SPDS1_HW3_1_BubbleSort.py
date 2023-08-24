"""
[Bubble sort 구현하기]
Bubble Sort: 인접한 두 원소의 순서가 바뀌어 있을 때 (앞의 원소가 뒤의 원소보다 클 때) 서로 swap하면서 정렬하는 알고리즘
정수로 이루어진 리스트(list)를 변수(argument)로 받아 버블 정렬할 때, swap이 일어나는 횟수를 리턴하는 함수를 작성하시오.

"""
## 오름차순 정렬: [3 1 4 2] -> [1 2 3 4]
def bubble_sort(arr):
    for i in range(len(arr)):
        for j in range(len(arr)-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
                
                
"""
## 내림차순 정렬: [3 1 4 2] -> [4 3 2 1]
def bubble_sort(arr:List[int]):
    for i in range(len(arr)):
        for j in range(len(arr)-i-1):
            if arr[j] < arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
"""