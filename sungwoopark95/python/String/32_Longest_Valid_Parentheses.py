"""
주어진 괄호 문자열에서 valid한 최대 길이의 parentheses를 찾는 함수

Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".

Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".

Input: s = ""
Output: 0
"""
################################### MY CODE - TIME LIMIT ###################################
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

def longestValidParentheses(s: str) -> int:
    if len(s) < 2:
        return 0
    valid_substring = []
    for i in range(len(s)):
        for j in range(i+1, len(s)+1):
            substring = s[i:j]
            if isValid(substring):
                valid_substring.append(substring)
    if len(valid_substring) == 0:
        return 0
    max_len = -1
    for item in valid_substring:
        if max_len < len(item):
            max_len = len(item)
    return max_len
    
    # sorted_valid = sorted(valid_substring, key=lambda x:len(x), reverse=True)
    
    # if not sorted_valid:
    #     return 0
    # return len(sorted_valid[0])
################################### MY CODE - TIME LIMIT ###################################

######################################### ChatGPT #########################################
def longestValidParentheses(s: str) -> int:
    # `left`와 `right` 변수는 각각 여는 괄호와 닫는 괄호의 개수를 추적합니다.
    left, right, maxlength = 0, 0, 0
    
    # 첫 번째 순회: 왼쪽에서 오른쪽으로 문자열을 순회합니다.
    for i in range(len(s)):
        # 만약 현재 문자가 여는 괄호라면 `left` 카운터를 1 증가시킵니다.
        if s[i] == '(':
            left += 1
        # 만약 현재 문자가 닫는 괄호라면 `right` 카운터를 1 증가시킵니다.
        else:
            right += 1

        # 만약 `left`와 `right` 카운터가 동일하다면, 유효한 부분 문자열의 길이를 업데이트합니다.
        if left == right:
            maxlength = max(maxlength, 2*right)
        # 만약 `right` 카운터가 `left` 카운터보다 크다면, 두 카운터를 다시 0으로 초기화합니다.
        elif right >= left:
            left, right = 0, 0

    # 두 카운터를 다시 0으로 초기화합니다.
    left, right = 0, 0
    
    # 두 번째 순회: 오른쪽에서 왼쪽으로 문자열을 순회합니다.
    for i in range(len(s)-1, -1, -1):
        # 만약 현재 문자가 여는 괄호라면 `left` 카운터를 1 증가시킵니다.
        if s[i] == '(':
            left += 1
        # 만약 현재 문자가 닫는 괄호라면 `right` 카운터를 1 증가시킵니다.
        else:
            right += 1

        # 만약 `left`와 `right` 카운터가 동일하다면, 유효한 부분 문자열의 길이를 업데이트합니다.
        if left == right:
            maxlength = max(maxlength, 2*left)
        # 만약 `left` 카운터가 `right` 카운터보다 크다면, 두 카운터를 다시 0으로 초기화합니다.
        elif left >= right:
            left, right = 0, 0

    # 가장 긴 유효한 부분 문자열의 길이를 반환합니다.
    return maxlength
######################################### ChatGPT #########################################

if __name__ == "__main__":
    s = """))))))()((()(((()((()((())()((()))()()(()()))))()())()))())())))(((()()()()(()()))()((()))))()(()()(((()())(((())(((())((()))))()(()(())(()(()(((((())(())))(()))())(((((())))))))()(())((((((()())()))))(()))(((()()(()(())()((())))()(())))())()())((((()))))()()((((((())()((((()(())((((()()())(())()())))()(()((())))))))()())((((()))())())))()))((())))()((()(())((()((())))((())((()())()))))())))())(((((((()))(((())(((()((()))(((()(())))((((()()())))))))())()))(()))())))()(()))((())()))((())))((())(()())(((()((()()))))()()(())))))()))))()((()((()(((()())(((())))(()(())())))((((((()()()))))((()))))(()(())()(()((())((()))()()()()(()((()())((((())()((()()))()))))()(((()())())))(()(((()()))()())))()()))))((()((((()(()))()(()()(((()()()()())((())()(((())(())))))()))))()())()()())(())))((())(()))(((())()))))))())()())((()((()()(())))())((()(((()(((((()(())(())()()))()))(()((((((((()(()()))()(()(()))(())(())())))))(())))))))()))))()())()()(((())()))((()))))))(())((()))(()((()()())())((()))))((()()())(()(((()))))(())(((()(()()()()((())())(())()))()())))())))()(((()))(()))()))()((((()()()(()(()))(((())()()(((())()((()(())((())())(((()()))((()())))())(()(())(()()))(((()(())(())))(()())(()()()()(()((()()()))(())(()(((()())))()((((())()())((()(()(())))(()()(()(()))))))(()())((()))()))()(()))((()()))))()()()))(())(())(())))()(()))(()()(((()((((())())))(()(())(()()))))))((()((()()))())))((((((())()))())(())())(()()(()(()()))()))((()((())(()((()(())))()((()))()(((()()()())()((())))(()()()()(()((()()((()((()()()(()(((())))))(())(()()(()())((((()()()()((()(())()(((()))(()(())(((()())())((()()))("""
    print(longestValidParentheses(s))