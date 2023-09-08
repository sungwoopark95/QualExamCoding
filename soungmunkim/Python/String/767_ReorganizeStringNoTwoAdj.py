"""
[인접 문자가 같지 않게 string 다시 배치하기]
Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.

Return any possible rearrangement of s or return "" if not possible.

Example 1:
Input: s = "aab"
Output: "aba"

Example 2:
Input: s = "aaab"
Output: ""
"""

import heapq
from collections import Counter

def reorganizeString(s: str) -> str:
    # 문자의 빈도수 계산
    counter = Counter(s)
    # 빈도수를 기반으로 최대 힙 생성
    max_heap = [(-freq, char) for char, freq in counter.items()]
    heapq.heapify(max_heap)
    
    # s의 길이가 n이라 할 때, n // 2 보다 큰 빈도수를 가진 문자가 있다면 재배열 불가능
    if -max_heap[0][0] > (len(s) + 1) // 2:
        return ""
    
    result = []
    while len(max_heap) > 1:
        # 가장 빈도수가 많은 두 문자 추출
        freq1, char1 = heapq.heappop(max_heap)
        freq2, char2 = heapq.heappop(max_heap)
        
        # 결과에 두 문자 추가
        result.extend([char1, char2])
        
        # 빈도수 감소 후 다시 힙에 추가
        if freq1 + 1:
            heapq.heappush(max_heap, (freq1 + 1, char1))
        if freq2 + 1:
            heapq.heappush(max_heap, (freq2 + 1, char2))
            
    # 마지막으로 남은 문자 추가
    if max_heap:
        result.append(max_heap[0][1])
    
    return ''.join(result)
