"""
'(', ')', '{', '}', '[', ']'으로 구성된 String을 `Input`으로 받고, 이 String이 아래 규칙에 의해 유효한지를 판단하여 `True`/`False`를 return하는 함수를 작성하여라.
1) 괄호가 열렸다면 같은 타입의 괄호에 의해 닫혀야 한다. 
2) 적절한 순서로 괄호가 배열되어야 한다. 안쪽에서 열린 괄호가 먼저 닫히고, 바깥쪽 괄호가 닫혀야 한다. 
"""

from ArrayBasedStack import Stack

def P1(parantheses:str):
    pair = {')': '(', '}': '{', ']': '['}
    s = Stack()
    for char in parantheses:
        if char in ['(', '{', '[']:
            s.push(char)
        else:
            if pair[char] != s.pop():
                return False
    return True

if __name__ == "__main__":
    print(P1('()'))
    print(P1('([)]'))
