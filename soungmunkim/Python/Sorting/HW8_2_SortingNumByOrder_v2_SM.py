"""
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
def P2_ans(Order: str, S: str):
    ### Write code here ###
    # Order대로 S에 바로 반영하는 방식
    for i in Order[::-1]: #뒤에서부터 앞으로
        if i in S:
            S = i * S.count(i) + S.replace(i,'') 
    return S
    ### End of your code ###
    108_