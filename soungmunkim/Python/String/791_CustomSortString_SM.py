"""
[order 순서대로 s의 순서를 바꾸기]

Example 1:
Input: order = "cba", s = "abcd"
Output: "cbad"
Explanation: 
"a", "b", "c" appear in order, so the order of "a", "b", "c" should be "c", "b", and "a". 
Since "d" does not appear in order, it can be at any position in the returned string. "dcba", "cdba", "cbda" are also valid outputs.

Example 2:
Input: order = "cbafg", s = "abcd"
Output: "cbad"

order = "cba"
s = "abcd"
customSortString(order, s)
>>> 'cbad'

order = "cbafg"
s = "abcd"
customSortString(order, s)
>>> 'cbad'
"""

def customSortString(order:str, s:str) -> str:
    # s의 각 char 빈도수 저장
    cnt = dict()
    for i in range(len(s)):
        if s[i] not in cnt:
            cnt[s[i]] = 1
        else:
            cnt[s[i]] += 1
    
    
    ans = ""
    for i in range(len(order)):
        if order[i] in s:
            # 해당 char 빈도수만큼 ans에 넣기
            ans += order[i] * cnt.get(order[i]) 
            s = s.replace(order[i], "")
    
    if len(s) > 0:
        ans += s
    
    return ans

