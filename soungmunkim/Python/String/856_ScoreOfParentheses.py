"""
[유효한 parentheses 점수 계산하기]

valid한 stack인지 체크하는 함수
    -> valid 하지 않으면 -1 return
    
valid parethese일 경우 score = 1
A + B 형태일 경우 score + score
(A) 같은 형태일 경우 score * 2

stack에 각 점수를 넣고 열림도 0으로 stack에 표시하며 문제 품

Example 1:
Input: s = "()"
Output: 1

Example 2:
Input: s = "(())"
Output: 2

Example 3:
Input: s = "()()"
Output: 2
"""

# 유효한 괄호 문자열인지 확인하는 함수
def is_valid(s: str) -> bool:
    stack = []  # 스택을 이용해 괄호 쌍을 확인
    mapping = {')': '(', '}': '{', ']': '['}  # 닫는 괄호와 열린 괄호의 쌍
    
    for char in s:
        if char in mapping:  # 닫는 괄호인 경우
            # 스택의 최상위 요소 추출
            if stack:
                top_element = stack.pop()
            else:  # top이 없는 경우 예외처리
                '#'
    
            if mapping[char] != top_element:  # 매칭되는 괄호가 아니면 False 반환
                return False
            
        else:  # 여는 괄호인 경우
            stack.append(char)
    
    return not stack  # 스택이 비어 있으면 유효한 괄호 문자열 (True)

"""
2. 초기 설정
스택을 초기화하고 주어진 문자열을 순회하기 시작합니다.

3. 여는 괄호를 만났을 때
stack.append(0)을 사용하여 여는 괄호를 스택에 추가합니다.
    예시 "(()[])((()))"의 첫 번째 문자는 여는 괄호이므로 스택에는 [0]이 됩니다.

4. 닫는 괄호를 만났을 때
직전에 넣은 항목이 0(여는 괄호)이면, 
    그 괄호는 닫는 괄호와 직접적으로 쌍을 이룹니다. 
    따라서 stack.pop()으로 여는 괄호를 제거하고, 점수 1을 스택에 추가합니다.

그렇지 않다면, 이미 스택에 저장된 점수들과 결합하여 새로운 점수를 계산합니다. 
    여는 괄호를 만날 때까지 스택에서 숫자를 추출하여 curr에 더하고, 
    최종적으로 curr * 2를 스택에 추가합니다.

예시 문자열에서 두 번째 문자는 닫는 괄호입니다. 스택의 마지막 요소는 0이므로 stack.pop()으로 여는 괄호를 제거하고 점수 1을 스택에 추가합니다. 스택은 [1]이 됩니다.
"""

# 괄호 문자열의 점수를 계산하는 함수 
def score(s: str) -> int:
    if not is_valid(s):  # 문자열이 유효하지 않으면 -1 반환
        return -1

    stack = []  # 점수를 계산하기 위한 스택 초기화
    
    for char in s:
        if char in '([{':  # 여는 괄호인 경우 스택에 추가
            stack.append(0)  # 0을 스택에 추가하여 여는 괄호를 표시합니다.
        else:
            # 괄호의 쌍이 바로 연속된 경우 (예: '()')
            if stack[-1] == 0:
                stack.pop()  # 여는 괄호를 표시하는 0 제거
                stack.append(1)  # 점수 1 추가
            else:  
                curr = 0  # 현재 계산 중인 점수 초기화
                # 스택의 최상위 요소가 숫자인 동안(여는 괄호가 나올 때까지) 숫자를 추출해 curr에 더함
                while stack[-1] != 0:
                    curr += stack.pop()
                stack.pop()  # 여는 괄호를 표시하는 0 제거
                stack.append(curr * 2)  # 괄호 안의 점수 * 2를 스택에 추가


    return sum(stack)  # 스택에 있는 모든 점수 합산 후 반환


if __name__ == "__main__":
    test_strs = [
        "()",
        "(())",
        "[]",
        "{}",
        "([])",
        "(())[]{}",
        "((())[]{}[]())"
    ]

    for test_str in test_strs:
        print(f"String: {test_str}, Score: {score(test_str)}")