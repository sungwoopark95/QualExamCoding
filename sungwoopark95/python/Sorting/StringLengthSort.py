"""
다음 조건을 만족하는 리스트(`list`)가 있다.

1. 모든 원소는 알파벳 소문자로 된 문자열(string)이다. (공백 없음)
2. 각 string의 길이는 1 이상 20 이하이다.

이 리스트를 변수(argument)로 받아 다음 조건에 따라 정렬하여 리턴하는 함수를 작성하시오.

1. 길이가 짧은 문자열이 앞에 있어야 한다.
2. 길이가 같다면 사전 순서가 빠른 문자열이 앞에 있어야 한다.
"""

from typing import List

## key 활용하지 않는 방법
def P3(arr:List):
    len_list = [len(word) for word in arr]
    
    ## length 기준으로 우선 sorting - bubble sort
    for i in range(len(len_list)):
        for j in range(len(len_list)-i-1):
            if len_list[j] > len_list[j+1]:
                len_list[j], len_list[j+1] = len_list[j+1], len_list[j]
                arr[j], arr[j+1] = arr[j+1], arr[j]
    
    ## length 같은 item들은 서로 붙어있음 - 다시 같은 length 가진 item에 대해서 sorting
    for length in set(len_list):
        indices = []
        for idx, word in enumerate(arr):
            if len(word) == length:
                indices.append(idx)
        for i in range(min(indices), max(indices)+1):
            for j in range(min(indices), max(indices)-i):
                if arr[j] > arr[j+1]:
                    arr[j], arr[j+1] = arr[j+1], arr[j]
                    
    return arr

## sorted의 key 활용하는 방법
def P3_(arr:List):
    return sorted(arr, key=lambda item: (len(item), item))

if __name__ == "__main__":
    print(P3(['solve', 'this', 'problem', 'or', 'you', 'will', 'get', 'f']))
    print(P3(['computing', 'class', 'is', 'so', 'funny', 'haha']))
    print(P3(['making', 'homework', 'is', 'very', 'hard']))
