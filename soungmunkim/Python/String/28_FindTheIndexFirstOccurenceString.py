"""
[첫번째로 needle이 나온 index 반환하기]

Example 1:
Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.

Example 2:
Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.
"""

def strStr(haystack: str, needle: str) -> int:

    # 얼마큼 잘라서 볼 건지 size 정하기
    window_size = len(needle)
    
    # 하나씩 이동하면서 해당 size만큼 잘라서 비교하기
    for i in range(0, len(haystack)):
        window = haystack[i:i+window_size]
        print(window)
        if window == needle:
            return i
    return -1