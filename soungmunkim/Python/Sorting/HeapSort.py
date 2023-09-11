def heapify(arr, n, i):
    largest = i  # 현재 노드
    l = 2 * i + 1  # 왼쪽 자식 노드
    r = 2 * i + 2  # 오른쪽 자식 노드

    # 왼쪽 자식 노드가 존재하며, 현재 노드보다 크다면
    if l < n and arr[i] < arr[l]:
        largest = l

    # 오른쪽 자식 노드가 존재하며, largest보다 크다면
    if r < n and arr[largest] < arr[r]:
        largest = r

    # largest가 현재 노드가 아니라면
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]  # 노드 교환

        heapify(arr, n, largest)  # 재귀적으로 힙 구성

def heapSort(arr):
    n = len(arr)

    # max heap을 구성
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    # 원소 하나씩 추출하면서 힙 정렬
    for i in range(n-1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]  # 현재 루트와 마지막 원소 교환
        heapify(arr, i, 0)  # 루트를 제외하고 다시 힙 구성

    return arr

arr = [9, 6, 7, 5, 3, 1, 4, 2]
print("Original array:", arr)
sorted_arr = heapSort(arr)
print("Sorted array:", sorted_arr)
