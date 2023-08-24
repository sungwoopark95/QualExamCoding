"""
[Radix sort 구현; Queue 이용함]
Radix Sort는 낮은 자리수부터(일의자리, 십의자리, 등) 비교하여 정렬해 간다는 것을 기본 개념으로 정렬하는 알고리즘이다.
비교 연산을 하지 않으며 정렬 속도가 빠르지만 데이터 전체 크기에 기수 테이블의 크기만한 메모리가 더 필요하다. (공간 복잡도가 높아진다.)
"""

from collections import deque

def radix_sort(nums):
    # 0부터 9까지의 숫자를 위한 10개의 버킷을 초기화합니다.
    # 각 버킷은 deque 자료구조로 구성됩니다.
    buckets = [deque() for _ in range(10)]

    # 입력된 숫자 중에서 가장 큰 값을 찾습니다.
    max_val = max(nums)
    # 주어진 숫자들을 deque Q에 저장합니다.
    Q = deque(nums)
    # 현재 처리할 자릿수를 나타냅니다. 초기에는 1의 자리를 나타냅니다.
    cur_ten = 1

    # 가장 큰 값의 자릿수만큼 반복합니다.
    while max_val >= cur_ten:
        # Q에 있는 모든 숫자를 꺼내서 해당하는 버킷에 넣습니다.
        while Q:
            num = Q.popleft()
            # 현재 자릿수의 숫자를 찾아 해당하는 버킷에 추가합니다.
            buckets[(num // cur_ten) % 10].append(num)

        # 모든 버킷에 대해서
        for bucket in buckets:
            # 버킷에 있는 숫자를 다시 Q에 넣습니다.
            while bucket:
                Q.append(bucket.popleft())

        # 다음 자릿수를 위해 cur_ten 값을 10배로 늘립니다.
        cur_ten *= 10

    # 최종적으로 정렬된 숫자들이 저장된 Q를 리스트 형태로 반환합니다.
    return list(Q)


""" [다른 구현 방법]
def radix_sort(arr):
    # 입력 배열의 최대값을 찾습니다.
    max_val = max(arr)
    
    # 최대값의 자릿수를 구합니다. 이 값은 정렬을 수행할 최대 반복 횟수를 결정합니다.
    num_digits = len(str(max_val))
    
    # 1의 자릿수부터 최대 자릿수까지 반복합니다.
    for i in range(num_digits):
        # 10개의 빈 버킷을 준비합니다.
        buckets = [[] for _ in range(10)]
        
        # 현재 자릿수(i)를 기준으로 배열의 숫자를 버킷에 분류합니다.
        for number in arr:
            # 현재 자릿수의 숫자를 찾습니다.
            digit = (number // (10 ** i)) % 10
            # 해당 숫자를 버킷에 추가합니다.
            buckets[digit].append(number)
        
        # 버킷의 순서대로 숫자를 다시 배열에 추가합니다.
        idx = 0
        for bucket in buckets:
            for number in bucket:
                arr[idx] = number
                idx += 1
    
    return arr

# 테스트
arr = [170, 45, 75, 90, 802, 24, 2, 66]
radix_sort(arr)

"""