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
>>> P1
"""

def P1_ans(parentheses: str):
    ##### Write your Code Here #####      
    stack = []
    m = {
        ')': '(',
        '}': '{',
        ']': '['
        }
    for c in parentheses:
        if c == '(' or c == '{' or c == '[':
            stack.append(c)
        else:
            if stack.pop() != m[c]:
                return False


    return len(stack) == 0
    ##### End of your code #####