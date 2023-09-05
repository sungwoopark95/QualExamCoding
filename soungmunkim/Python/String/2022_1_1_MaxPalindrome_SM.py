"""
[Max palindrome 찾기]
"palindrome"은 앞에서 뒤로 읽었을 때와 뒤에서 앞으로 읽었을 때 동일한 문자열이나 숫자, 또는 다른 시퀀스를 의미
    즉, palindrome은 그 내용이 앞뒤가 똑같은 단어나 문장을 지칭
    
The list contains palindromes that are not a substring of another palindrome.
A substring is a contiguous sequence of characters within a string.
The characters used in a string are only lower-case alphabets and a space character.

# TestCase
>>> s = "kabccbadzdefgfeda"
>>> max_palindromes(s)
>>> ["k", "abccda", "dzd", "defgfed"]

>>> s = "kabccba dzbccbaza"
>>> max_palindromes(s)
>>> ["k", " ", "d", "zabccbaz", "aza"]
"""

"""
1. 문자열 s의 모든 substring을 찾습니다.
2. 각 substring이 palindrome인지 확인합니다.
3. palindrome이라면, 이 palindrome이 다른 palindrome의 substring인지 확인합니다.
4. substring이 아닌 palindrome 중에서 가장 긴 palindrome을 선택합니다. (palindrome 중에 서로 substring 아닌지 체크)
"""

def palindrome(s: str):
    if s == s[::-1]:
        return True
    else:
        return False

# t가 s의 substring인지 check  
def substring(s, t):
    n = len(s)
    m = len(t)
    
    # 만약 길이 자체가 t가 더 크면 -> t는 s의 substring 아님
    if m > n:
        return False
    # s와 t 길이 차이만큼 돌건데 s를 t 길이만큼 돌면서 체크할 것
    for i in range(n-m+1):
        if s[i:i+m] == t:
            return True

    return False
    
# 주어진 문자열 s 내에서 가장 긴 palindrome들을 찾아 리스트로 반환하는 함수
def max_palindromes(s):
    max_pals = []
    
    # 모든 가능한 substring 뽑기
    for i in range(len(s)):
        for j in range(i, len(s)):
            sub = s[i:j+1]
            
            if palindrome(sub): # 현재 substring이 palindrome 일때 
                is_maximal = True # 현재 palindrome이 max라고 추정하고 시작
                
                for pal in max_pals:
                    # 만약 현재 palindrome이 기존 palindrome의 substring이라면
                    if substring(pal, sub) and pal != sub:
                        is_maximal = False
                        break
                
                # 만약 현재 palindrome이 기존 palindrome의 substring이 아니라면 후보에 넣기
                if is_maximal:
                    max_pals.append(sub)
    
    # palindrome 후보들 중 substring인 후보는 빼기 (filltering 작업)
    """
    max_pals = [pal for pal in max_pals if not any(substring(other, pal) for other in max_pals if other != pal)]
    """
    filtered_max_pals = []

    for i in range(len(max_pals)):
        is_substring = False
        for j in range(len(max_pals)):
            if i != j: # 자기 자신 제외
                # max_pals[i] 가 다른 palindrome의 substring인지 체크
                if substring(max_pals[j], max_pals[i]):
                    is_substring = True
                    break
                
        if is_substring == False:
            filtered_max_pals.append(max_pals[i])
    
    return filtered_max_pals