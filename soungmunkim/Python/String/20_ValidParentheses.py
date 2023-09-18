"""
[유효한 괄호 찾기]
‘(‘, ‘)’, ‘{‘, ‘}’, ‘[‘, ‘]’으로 구성된 String을 Input으로 받고, 
이 String이 아래 규칙에 의해 유효한지를 판단하여 True/False를 return하는 함수를 작성하여라.

<조건>
(1) 괄호가 열렸다면 같은 타입의 괄호에 의해 닫혀야 한다.
(2) 적절한 순서로 괄호가 배열되어야 한다. 안쪽에서 열린 괄호가 먼저 닫히고, 바깥쪽 괄호가 닫혀야 한다.

TestCase2)
>>> P1(‘()[]{}’) True
TestCase3)
>>> P1(‘([)]’) False
"""

def P1(bracket:str):
    dct = {'(':')', '{':'}', '[':']'}
    
    # 괄호 짝수가 안 맞으면
    if len(bracket) % 2 != 0:
        return False
    
    for i in range(0, len(bracket), 2):
        # 같은 쌍의 괄호가 아닐 때
        if bracket[i] in dct:
            if bracket[i+1] != dct.get(bracket[i]):
                return False
        # 시작이 열린 괄호가 아닐 때
        else:
            return False
    return True

####################### STACK 사용 #######################
def isValid(s: str) -> bool:
    if len(s) % 2 == 1:
        return False
    valid = {"(": ")", "{": "}", "[": "]"}
    stack = []
    for c in s:
        if c in valid.keys():
            stack.append(c)
        else:
            if not stack or valid[stack[-1]] != c:
                return False
            stack.pop(-1)

    return not stack