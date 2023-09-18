"""
[s를 k개의 palindrome으로 나눌 수 있다면 True 반환]
1. palindrome이 될 수 있는지 체크하는 함수
2. palindrome이 될 수 있는 단어를 palindrome으로 만드는 함수 
3. 한 단어의 조합들이 Palindrome이 될 수 있는 단어들을 모은 partition 함수 
    -> backtracking 사용

Example 1:
Input: s = "annabelle", k = 2
Output: true
Explanation: You can construct two palindromes using all characters in s.
Some possible constructions "anna" + "elble", "anbna" + "elle", "anellena" + "b"

s = "annabelle" 
k = 2
canConstruct(s,k)
[['anna', 'elble'], ['anbna', 'elle']]
True

Example 2:
Input: s = "leetcode", k = 3
Output: false
Explanation: It is impossible to construct 3 palindromes using all the characters of s.

Example 3:
Input: s = "true", k = 4
Output: true
Explanation: The only possible solution is to put each character in a separate string.
"""

from collections import Counter

## -------------- palindrome이 될 수 있는지 체크하는 함수 -------------- ##
def canPalindrome(word: str):
    # word의 char 빈도 dict 만들기 
    cnt = Counter(word)
    # print(cnt)
    even, odd = 0, 0
    # 빈도수 짝, 홀수 체크하기
    for val in cnt.values():
        if val % 2 == 0:
            even += 1
        else:
            odd += 1
            
    # 만약 모두 다 짝수거나 하나만 홀수이면 palindrome 만들 수 있음
    if even == len(cnt):
        return True
    if even == len(cnt) - 1 and odd == 1:
        return True
    return False

## -------------- palindrome 만드는 함수 (palindrome 만들 수 있을 때) -------------- ##
def constructPalindrome(w: str):
    # 만일 w를 palindrome으로 만들 수 없다면 "Not a palindrome"을 return하고 종료합니다.
    if not canPalindrome(w):
        return "Not a palindrome"
    
    # palindrome으로 만들 수 있다면, 먼저 w에 등장한 문자들의 빈도를 count합니다.
    cnt = Counter(w)
    # 정답 string을 담아놓을 list를 하나 생성합니다.
    # 정답 string은 w와 같은 길이를 가질 것이므로, w의 길이만큼의 list를 생성한 후, 0으로 초기화
    ans = [0 for _ in range(len(w))]
    
    # 길이가 홀수라면, 홀수번 등장하는 문자가 적어도 하나 있으므로,
    # 해당 문자 가운데 하나를 middle index에 끼워넣고, 그 문자의 빈도를 하나 줄입니다.
    if len(w) % 2 != 0:
        mid_idx = len(w)//2
        for ch, val in cnt.items():
            if val % 2 != 0:
                ans[mid_idx] = ch
                cnt[ch] -= 1
    
    # 이제 나머지 문자는 모두 짝수 번 등장하므로, 각 문자를 ans에 끼워넣습니다.
    # 이때 index를 0으로 초기화하고, 문자들을 양 끝에서 안쪽으로 하나씩 옮겨가며 채워넣습니다.
    idx = 0
    for ch, val in cnt.items():
        # 빈도수가 0보다 클 때까지
        while val > 0:
            # 왼쪽 끝에 하나 채우고, 빈도수를 하나 줄입니다.
            ans[idx] = ch
            val -= 1
            # 오른쪽 끝에 하나 채우고, 역시 빈도수를 하나 줄입니다.
            ans[len(w)-idx-1] = ch
            val -= 1
            # 안 쪽으로 한 칸 이동시킵니다.
            idx += 1
        # 만일 왼쪽 끝과 오른쪽 끝이 같아지거나(midpoint)
        # 왼쪽 끝이 오른쪽 끝보다 커진다면, 더 이상 채울 문자가 없다는 의미이므로 반복을 종료합니다.
        if idx >= len(w) - idx - 1:
            break
    # ans에 담아놓은 문자들을 string으로 만듭니다. 
    return ''.join(ans)
    
## ------------------------------------------------------------ #

def canConstruct(s:str, k:int):
    # 문자열의 모든 회문 파티션을 찾는 함수
    result = []
    path = []
    
    def backtrack(start):
        # 현재 위치가 문자열의 끝이라면, path를 결과에 추가
        if start == len(s):
            result.append(list(path))
            return
        
        # 현재 위치에서 시작하는 모든 부분 문자열에 대해
        for end in range(start, len(s)):
            
            # 현재 부분 문자열이 palindrome이 될 수 있다면
            if canPalindrome(s[start:end+1]):
                
                # 이 부분 문자열을 path에 추가하고
                path.append(s[start:end+1])
                
                # 다음 부분 문자열을 위해 재귀 호출
                backtrack(end+1)
                
                path.pop()
    
    backtrack(0)
    
    ans = []
    # 결과들을 돌면서 palindrome 이룬 단어가 k개라면
    for i in range(len(result)):
        partitions = []
        if len(result[i]) == k:
            # 해당 k개인 단어를 palindrome으로 만들고 ans에 넣기
            for j in range(len(result[i])):
                partitions.append(constructPalindrome(result[i][j]))
            ans.append(partitions)
            
    # print(ans)
    if len(ans) > 0:
        return True
    return False