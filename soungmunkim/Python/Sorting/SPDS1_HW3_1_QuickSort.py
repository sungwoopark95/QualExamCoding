"""
[Quick Sort 구현]

1. 기준이 되는 데이터인 pivot을 하나 선택한다.
    일반적으로 가장 많이 사용되는 것은 주어진 array의 첫 번째 요소이다. (array[0])
2. pivot을 기준으로 pivot 보다 작은 데이터와 pivot보다 큰 데이터로 구분한다.
3. pivot을 pivot보다 작은 데이터와 pivot보다 큰 데이터 사이에 위치시키면 pivot의 위치가 결정된다.
    [pivot 이하] [pivot] [pivot 초과]
4. pivot보다 작은 데이터와 pivot보다 큰 데이터 각각에서 동일하게 퀵 정렬을 수행한다. (재귀적으로)
"""

def quick_sort(array, start, end):
    # 만약 start와 end가 교차하거나 같다면 정렬할 원소가 없거나 하나뿐이므로 종료
    if start >= end: return 
        # 원소가 1개인 경우 종료
    
    pivot = start # 피벗(기준) 값을 첫 번째 원소로 설정
    left, right = start + 1, end # left는 시작 원소의 다음 원소부터, right는 마지막 원소부터 시작
    
    # left와 right가 교차할 때까지 반복
    while left <= right:
        # left가 가리키는 원소가 피벗보다 크거나 같을 때까지 오른쪽으로 이동
        while left <= end and array[left] <= array[pivot]:
            left += 1
        # right가 가리키는 원소가 피벗보다 작거나 같을 때까지 왼쪽으로 이동
        while right > start and array[right] >= array[pivot]:
            right -= 1
        # 만약 left와 right가 교차했다면, right와 피벗 위치의 원소를 교환
        if left > right:
            array[right], array[pivot] = array[pivot], array[right]
        # 그렇지 않다면, left와 right 위치의 원소를 교환
        else:
            array[right], array[left] = array[left], array[right]
    
    # 피벗을 기준으로 왼쪽과 오른쪽 부분 리스트로 나눠서 각각 재귀적으로 퀵 정렬 수행
    quick_sort(array, start, right - 1) # 왼쪽 부분 리스트 정렬
    quick_sort(array, right + 1, end)   # 오른쪽 부분 리스트 정렬



""" quick sort를 나눠서 구현하고 싶을때

def partition(array, start, end):
    피벗을 기준으로 배열을 분할하고, 피벗의 위치를 반환합니다.

    pivot = start
    left, right = start + 1, end
    
    while left <= right:
        # 피벗보다 큰 원소를 찾을 때까지 left를 증가
        while left <= end and array[left] <= array[pivot]:
            left += 1
        # 피벗보다 작은 원소를 찾을 때까지 right를 감소
        while right > start and array[right] >= array[pivot]:
            right -= 1
        # left와 right가 교차했다면, right와 피벗 위치의 원소를 교환
        if left > right:
            array[right], array[pivot] = array[pivot], array[right]
        # 그렇지 않다면, left와 right 위치의 원소를 교환
        else:
            array[right], array[left] = array[left], array[right]
    
    return right

def quick_sort(array, start, end):
    주어진 배열을 퀵 정렬합니다.
    
    if start >= end:
        return
    
    pivot = partition(array, start, end)  # 피벗 위치를 얻음
    quick_sort(array, start, pivot - 1)  # 왼쪽 부분 리스트 정렬
    quick_sort(array, pivot + 1, end)    # 오른쪽 부분 리스트 정렬

# 테스트
arr = [7, 5, 9, 0, 3, 1, 6, 2, 4, 8]
quick_sort(arr, 0, len(arr) - 1)
arr
"""

""" array 하나만 input으로 받고 quick sort 수행하고 싶을 때
def quick_sort_main(array, start, end):
    주어진 배열의 부분 리스트를 퀵 정렬합니다.

    if start >= end:
        return
    
    pivot = partition(array, start, end)
    quick_sort_main(array, start, pivot - 1)
    quick_sort_main(array, pivot + 1, end)

def quick_sort(array):
    주어진 배열 전체를 퀵 정렬합니다.
    
    quick_sort_main(array, 0, len(array) - 1)
    return array

# 테스트
arr = [7, 5, 9, 0, 3, 1, 6, 2, 4, 8]
quick_sort(arr)
"""