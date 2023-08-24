"""
[특정 order에 따라 string 수정하기]
두 문자열(string) Order와 S가 있다. 
Order의 모든 문자는 중복이 없고 어떤 규칙에 의해 이미 정렬되어 있다. 
S를 다음 규칙에 따라 수정하여 Correct_S라는 새로운 문자열을 만들려고 한다.

규칙1> 만약 S에 Order에 포함된 문자가 있으면 Order에서 사용된 규칙에 의해 우선 정렬되어야 한다.
규칙2> Order에 없는 문자에 대해서는 원래 S의 순서를 따르며, 규칙 1에서 정렬된 문자열 뒤에 나타내야 한다.
규칙3> S는 Order의 일부만 포함하거나 아예 포함하지 않는 경우, 중복된 경우도 있다.

TestCase1)
>>> P2(‘cba', ‘abcd’) 
‘cbad’
TestCase2)
>>> P2('cba', 'xyhabcd') 
'cbaxyhd'
"""
from collections import Counter
def P2(Order:str,S:str):
    # 고쳐야 할 문자열의 각 char 개수 count 저장된 dictionary 만듦
    dic = Counter(S)
    ans = ""
    # Order에 있는 char이 dic에 있으면 그 개수만큼 먼저 ans에 넣기
    for ch in Order:
        if ch in dic:
            cnt = dic[ch]
            ans += ch * cnt
            S = S.replace(ch, '') #ans에 넣은 char을 S에서 지우기
            
    # 만약 S에 아직 char이 남아있다면 그 순서 그대로 ans에 넣기
    if len(S)>0:
        ans += S;
        
    return ans 