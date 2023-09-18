"""
주어진 string을 뒤집되, 새로운 list를 생성하지 않고 in-place로 작동하도록 해야 함

Input: s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]

Input: s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
"""
from typing import List

def reverseString(s: List[str]) -> None:
    """
    Do not return anything, modify s in-place instead.
    """
    s[:] = s[::-1]
    
if __name__ == "__main__":
    s = ["H","a","n","n","a","h"]
    reverseString(s)
    print(s)