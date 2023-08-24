"""
[Merge Sort 구현]
하나의 리스트를 두 개의 균등한 크기로 분할하고 분할된 부분 리스트를 정렬한 다음, 
    두 개의 정렬된 부분 리스트를 합하여 전체가 정렬된 리스트가 되게 하는 방법

1. 분할(Divide): 주어진 배열을 두 개의 동일한 크기의 하위 배열로 분할합니다. 
    만약 배열의 크기가 홀수라면, 한 배열은 추가 요소를 포함할 수 있습니다.
2. 정복(Conquer): 두 개의 하위 배열을 재귀적으로 병합 정렬로 정렬합니다.
3. 병합(Merge): 두 개의 정렬된 하위 배열을 병합하여 하나의 정렬된 배열을 만듭니다.
"""

from typing import List

def merge(array:List, start:int, mid:int, last:int):
    # 시작 인덱스를 나타내기 위한 변수 k 선언
    k = start

    # 배열을 두 개의 하위 배열로 나눔
    sub1, sub2 = array[start:mid+1], array[mid+1:last+1]
    
    # 두 sublists 중 하나가 빌 때까지 반복
    i = j = 0
    while i < len(sub1) and j < len(sub2):
        if sub1[i] > sub2[j]:
            # sub2의 값이 더 작으면 원래 배열에 복사
            array[k] = sub2[j]
            j += 1
        else:
            # sub1의 값이 더 작거나 같으면 원래 배열에 복사
            array[k] = sub1[i]
            i += 1
        k += 1 # 어떤 경우든 k는 증가
    
    # 위 반복문이 종료되면 sub1 또는 sub2 중 하나는 비어있음
    if i == len(sub1): # sub1이 비어있는 경우
        array[k:last+1] = sub2[j:]
    else: # sub2가 비어있는 경우
        array[k:last+1] = sub1[i:]

def merge_help(array:List, start:int, last:int):
    # 배열의 길이가 1인지 확인
    if start == last:
        return # 아무 작업도 수행하지 않음
    else:
        mid = (start + last) // 2
        # left sub array에 대한 merge sort 재귀 호출
        merge_help(array, start, mid)
        # right sub array에 대한 merge sort 재귀 호출
        merge_help(array, mid+1, last)
        # 두 sub arrays를 병합
        merge(array, start, mid, last)

def merge_sort(array:List) -> None:
    merge_help(array, 0, len(array)-1)

# A = [34, 22, 20, 23, 19, 32, 50, 38, 43, 4]
# merge_sort(A)
# print(A)
