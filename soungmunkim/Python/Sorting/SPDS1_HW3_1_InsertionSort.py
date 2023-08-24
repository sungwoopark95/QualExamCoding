"""'
[Insertion Sort 구현]

- 정렬되지 않은 데이터를 이미 정렬된 부분의 적절한 위치에 "삽입"하는 방식으로 동작하는 정렬 알고리즘
- 첫 번째 원소는 항상 정렬되어 있다고 가정한다.
- 두 번째 원소(`i=1`)부터 array를 한 바퀴 돌면서
    - 다시 `i`번째 element부터 첫 번째 원소까지 서로 인접한 원소들에 대해 거꾸로 array를 살펴본다.
    - 서로 인접한 원소 가운데 앞의 원소가 뒤의 원소보다 크다면 서로 교환한다.
- 이런 식으로 정렬할 위치를 직접 찾아 insert하는 알고리즘이다.
"""

def insertion_sort(arr):
    for i in range(1, len(arr)):
        for j in range(i, 0, -1): # 뒤로 하나씩 이동
            if arr[j-1] > arr[j]:
                arr[j-1], arr[j] = arr[j], arr[j-1]
            else:
                break