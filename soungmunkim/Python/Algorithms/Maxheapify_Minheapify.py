def max_heapify(arr, n, i):
    # 최대 힙을 만들기 위한 함수
    largest = i                  # 현재 노드를 최대 값으로 설정
    l = 2 * i + 1                # 왼쪽 자식 노드의 인덱스 계산
    r = 2 * i + 2                # 오른쪽 자식 노드의 인덱스 계산

    if l < n and arr[i] < arr[l]:   # 왼쪽 자식이 존재하고 현재 노드 값보다 크면
        largest = l                # 최대 값 업데이트

    if r < n and arr[largest] < arr[r]:  # 오른쪽 자식이 존재하고 지금까지의 최대 값보다 크면
        largest = r                # 최대 값 업데이트

    if largest != i:              # 최대 값이 현재 노드와 다르다면 (swap 필요)
        arr[i], arr[largest] = arr[largest], arr[i]  # 현재 노드와 최대 값 노드의 위치 교환
        max_heapify(arr, n, largest)  # 재귀적으로 최대 힙 만들기

def min_heapify(arr, n, i):
    # 최소 힙을 만들기 위한 함수
    smallest = i                 # 현재 노드를 최소 값으로 설정
    l = 2 * i + 1                # 왼쪽 자식 노드의 인덱스 계산
    r = 2 * i + 2                # 오른쪽 자식 노드의 인덱스 계산

    if l < n and arr[i] > arr[l]:   # 왼쪽 자식이 존재하고 현재 노드 값보다 작으면
        smallest = l               # 최소 값 업데이트

    if r < n and arr[smallest] > arr[r]:  # 오른쪽 자식이 존재하고 지금까지의 최소 값보다 작으면
        smallest = r               # 최소 값 업데이트

    if smallest != i:             # 최소 값이 현재 노드와 다르다면 (swap 필요)
        arr[i], arr[smallest] = arr[smallest], arr[i]  # 현재 노드와 최소 값 노드의 위치 교환
        min_heapify(arr, n, smallest)  # 재귀적으로 최소 힙 만들기
