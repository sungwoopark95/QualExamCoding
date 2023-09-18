######################################## MY CODE - TIME LIMIT ########################################
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

def str_perm(s):
    def backtrack(start):
        if start == len(s):
            string = ''.join(s)
            if string not in permutation_lst:
                permutation_lst.append(''.join(s))
                return
    
        # 시작 인덱스부터 문자열의 끝까지 루프를 실행
        for i in range(start, len(s)):
            # 현재 시작 인덱스와 루프의 인덱스 위치의 문자를 교환 (스왑)
            s[start], s[i] = s[i], s[start]
            
            # 현재 시작 인덱스를 제외한 나머지 문자열에 대해 순열을 생성하기 위해 재귀적으로 호출
            backtrack(start + 1)
            
            # 이전 상태로 문자열을 복원하기 위해 다시 문자 위치를 교환 (백트래킹)
            s[start], s[i] = s[i], s[start]

    permutation_lst = []
    s = list(s)
    backtrack(0)
    return permutation_lst

def generateParenthesis(n:int):
    candidate = ['(' for _ in range(n)] + [')' for _ in range(n)]
    perms = str_perm(candidate)
    ans = []
    for perm in perms:
        if isValid(perm):
            ans.append(perm)
    return ans
######################################################################################################

############################################## Chat GPT ##############################################
def generateParenthesis(n):
    # generate 함수는 재귀적으로 괄호의 조합을 생성합니다.
    # p: 현재까지 만들어진 괄호의 조합 문자열
    # left: 사용할 수 있는 남은 여는 괄호의 수
    # right: 사용할 수 있는 남은 닫는 괄호의 수
    # parens: 지금까지 만들어진 모든 괄호의 조합 리스트
    def generate(p, left, right, parens=[]):
        # 만약 남은 여는 괄호가 있다면, 현재의 조합 문자열에 여는 괄호를 추가합니다.
        # 그리고 남은 여는 괄호의 수를 하나 줄입니다.
        if left:         
            generate(p + '(', left-1, right)
        
        # 닫는 괄호의 남은 수가 여는 괄호의 남은 수보다 많다면,
        # 현재의 조합 문자열에 닫는 괄호를 추가합니다.
        # 그리고 남은 닫는 괄호의 수를 하나 줄입니다.
        if right > left: 
            generate(p + ')', left, right-1)
        
        # 더 이상 사용할 닫는 괄호가 없다면, 현재 괄호 조합을 결과 목록에 추가합니다.
        # 이는 올바른 괄호 조합이 완성된 경우입니다.
        if not right:   
            parens += p,
        
        return parens

    # generate 함수를 호출하여 올바른 괄호의 조합을 생성하고 반환합니다.
    # 처음에는 아무런 괄호도 없는 상태로 시작하며, n개의 여는 괄호와 n개의 닫는 괄호를 사용할 수 있습니다.
    return generate('', n, n)
######################################################################################################


if __name__ == "__main__":
    print(generateParenthesis(3))