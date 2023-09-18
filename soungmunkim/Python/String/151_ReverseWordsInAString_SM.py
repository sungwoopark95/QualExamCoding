"""
[string 거꾸로 뒤집기]
공백이 얼마나 있던 간에 뒤집었을 때는 공백 1개로 프린트되게 하게

s = "the sky is blue"
reverseWords(s)
>>> 'blue is sky the'

['the', 'sky', 'is', 'blue']
j:  3 word:  blue
j:  2 word:  is
j:  1 word:  sky
j:  0 word:  the

s = "  hello world  "
reverseWords(s)
>>> 'example good a'

s = "a good   example"
reverseWords(s)
>>> 'example good a'
"""

def reverseWords(s:str) -> str:
  
    sentence = []
    word = ""
    for i in range(len(s)):
        # 만약 빈칸이라면
        if ord(s[i]) == 32:
            # 그 전도 빈칸이었다면 건너 뛰고
            if ord(s[i-1]) == 32:
                continue
            # 아니라면 그 단어를 list에 넣기
            sentence.append(word)
            word = "" # reset word
        # 빈칸이 아니라면 word에 추가
        else:
            word += s[i]
    
    # print("last word: ", word)
    
    # 마지막 단어가 빈단어가 아닐 경우 넣기
    if word != '': 
        sentence.append(word)  
    # print(sentence)
    

    ans = ""
    # 거꾸로 돌면서 reverse 넣기
    for j in range(len(sentence)-1, -1, -1):
        # print("j: ", j, "word: ", sentence[j])
        
        # 만약 빈칸이 있으면 넘길 수 있게 (혹시 모를 상황)
        if sentence[j] == '':
            continue
        
        # 첫 시작 제외하고는 단어 앞에 space 하나 넣기
        # reverse이므로 맨 마지막이 첫 시작임
        if j != len(sentence)-1:
            ans += " "
        # 단어 계속 붙이기
        ans += sentence[j]
    
    return ans