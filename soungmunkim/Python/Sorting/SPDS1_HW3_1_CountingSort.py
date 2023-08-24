"""
[Counting sort 구현]
1. 가장 작은 데이터부터 가장 큰 데이터까지의 범위가 모두 담길 수 있는 리스트를 생성
2. 데이터를 하나씩 확인하며 데이터의 값과 동일한 인덱스의 데이터를 1씩 증가
3. 증가된 리스트에서 0인 값을 제외하고, 인덱스를 인덱스 값만큼 출력

"""

def counting_sort(arr):
    # 주어진 배열에서 가장 큰 값과 가장 작은 값을 찾습니다.
    max_val = max(arr)
    min_val = min(arr)
    
    # 카운팅 배열의 크기를 결정합니다. (최대값 - 최소값 + 1)
    # 이후 카운팅 배열을 0으로 초기화합니다.
    count_size = max_val - min_val + 1
    count_array = [0] * count_size
    
    # 주어진 배열의 각 숫자를 순회하며, 해당 숫자의 발생 횟수를 카운팅 배열에 저장합니다.
    for num in arr:
        count_array[num - min_val] += 1
    
    # 카운팅 배열의 정보를 사용하여 입력 배열을 정렬합니다.
    idx = 0
    for i in range(count_size):
        while count_array[i] > 0:
            # 카운팅 배열의 인덱스와 최소값을 더하여 실제 숫자를 구합니다.
            arr[idx] = i + min_val
            idx += 1
            count_array[i] -= 1
            
    return arr

"""[다른 방법으로 구현한 것 ]
def counting_sort(arr):
    max_arr = max(arr)
    count = [0] * (max_arr + 1)
    sorted_arr = list()
    
    for i in arr:	# 카운팅
        count[i] += 1

    for i in range(max_arr + 1):
        for _ in range(count[i]):
            sorted_arr.append(i)
    return sorted_arr
"""